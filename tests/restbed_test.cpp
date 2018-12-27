//
// Created by chenlei on 2018-12-17.
//


#include <gtest/gtest.h>
#include <future>
#include <util/Logger.hpp>
#include <restbed>
#include <memory>
#include <cstdlib>
#include <thread>
#include <nlohmann/json.hpp>
#include <thread>
using json=nlohmann::json ;

#include <util/SingleInstance.hpp>
#include "restbed_logger.h"
#include "restbed/restbed_service.h"

using namespace std;
using namespace restbed;

std::shared_ptr<spdlog::logger> restbedLogger=logger::createLogger("restbedLogger");
std::shared_ptr<spdlog::logger> ruleLogger=logger::createLogger("ruleLogger");
std::shared_ptr<RestBedLogger> restBedRecordLogger=SingleInstance<RestBedLogger>::getInstance();



/**
 *
 * @param session
 */
void post_method_handler( const shared_ptr< restbed::Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< restbed::Session > session,
            const restbed::Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close(restbed:: OK, "Hello, World!", { { "Content-Length", "13" } } );
    } );
}


#include "restbed/restbed_logger.h"
/**
 *
 * @param session
 */
void get_method_handler( const shared_ptr< Session > session ){

    const auto& request = session->get_request( );
    auto keep_alive= request->get_header( "Connection", String::lowercase );
    std::string name=request->get_query_parameter( "name" );
    json j={
            {"data","Hello," + name}
    };
    Response response;
    response.set_status_code(OK);
    auto data=j.dump();
    auto p=data.data();
  //  data=compressed_data(p,data.size());
    response.set_body(data);
//    response.set_headers({
//            {"Content-Encoding","gzip"},
//            {"Content-Length",std::to_string(data.size())}
//    });



    session->close(response);


    //done  record logger
    restBedRecordLogger->webInfoLogger(session,response);
   // restbedLogger->info("get_query_parameter name:{} keep_alive:{}-- done!!!!",name,keep_alive);
}




// custom logger
class CustomLogger : public restbed::Logger{
public:
    void stop( void )
    {
        return;
    }

    void start( const shared_ptr< const Settings >& )
    {
        return;
    }

    void log( const Level, const char* format, ... )
    {
        va_list arguments;
        va_start( arguments, format );
        vfprintf( stderr, format, arguments );
        fprintf( stderr, "\n" );
        va_end( arguments );
    }

    void log_if( bool expression, const Level level, const char* format, ... )
    {
        if ( expression )
        {
            va_list arguments;
            va_start( arguments, format );
            log( level, format, arguments );
            va_end( arguments );
        }
    }
};




//logger rule
class LogRule : public Rule
{
public:
    LogRule( void ) : Rule( )
    {
        return;
    }

    virtual ~LogRule( void )
    {
        return;
    }
    /**
     *
     * @param session
     * @return
     */
     bool condition( const shared_ptr< Session > session ) final override{
        return true;
    }

    void action( const shared_ptr< Session > session,
            const function< void ( const shared_ptr< Session > ) >& callback ) final override
    {

        ruleLogger->info("action rule begin>>>>>>>>>");
        const auto request = session->get_request( );
        auto host=request->get_header("HOST");
        ruleLogger->info("host:{}",host);
        const auto type = request->get_header( "Accept", String::lowercase );

        callback( session ); // call back!

        auto response= request->get_response();
        long use_count=response.use_count();
        ruleLogger->info("response use_count:{}",use_count);
        test_shared_ptr(response);
        //int statusCode=response->get_status_code();
        ruleLogger->info("action rule end,protocl:{}  version:{}  orgion:{}",request->get_protocol(),request->get_version(),session->get_origin());
    }


    /**
     *
     * @param response  ref
     */
    void test_shared_ptr(const std::shared_ptr< const Response > response){
        long use_count=response.use_count();
        EXPECT_EQ(use_count,0);
     }

};


//https://github.com/Corvusoft/restbed/blob/master/documentation/example/DIGEST_AUTHENTICATION.md
//curl -w'\n' -v --digest -XGET 'http://Corvusoft:Glasgow@localhost:1984/resource'
#include <regex>
string build_authenticate_header( void )
{
    string header = "Digest realm=\"Restbed\",";
    header += "algorithm=\"MD5\",";
    header += "stale=false,";
    header += "opaque=\"0000000000000000\",";
    header += "nonce=\"Ny8yLzIwMDIgMzoyNjoyNCBQTQ\"";

    return header;
}

void authentication_handler( const shared_ptr< Session > session,
                             const function< void ( const shared_ptr< Session > ) >& callback )
{
    const auto request = session->get_request( );

    auto authorisation = request->get_header( "Authorization" );

    bool authorised = regex_match( authorisation, regex( ".*response=\"02863beb15feb659dfe4703d610d1b73\".*" ) );

    if ( authorised )
    {
        callback( session );
    }
    else
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", build_authenticate_header( ) } } );
    }
}


void service_error_handler( const int, const exception& e, const shared_ptr< Session > session )
{
     restbedLogger->info("service_error_handler {}",e.what());
    //session->close( 5000, "Custom Service Internal Server Error", { { "Content-Length", "36" } } );
}



//https://github.com/Corvusoft/restbed/blob/master/documentation/example/SIGNAL_HANDLING.md
#include <memory>
#include <cstdlib>
#include <restbed>
#include <csignal>
#include <sys/types.h>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif
void sighup_handler( const int signal_number )
{
    fprintf( stderr, "Received SIGINT signal number '%i'.\n", signal_number );
}

void sigterm_handler( const int signal_number )
{
    fprintf( stderr, "Received SIGTERM signal number '%i'.\n", signal_number );
}

/**
 *
 */
void ready_handler( Service& )
{
#ifdef _WIN32
    fprintf( stderr, "Service PID is '%i'.\n", _getpid( ) );
#else
    fprintf( stderr, "Service PID is '%i'.\n", getpid( ) );
#endif
}


#include "restbed_syslog_logger.hpp"


/**
 *
 */
TEST(test_restBedService,restBedService){
    //set controller
    //https://github.com/Corvusoft/restbed/blob/master/documentation/example/RESOURCE_FILTERING.md
    auto resource = std::make_shared<restbed::Resource>();
    resource->set_path( "/index" );
    resource->set_method_handler( "POST",post_method_handler );

    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler);


    RestBedService restBedService("restBedServiceTestLogger");
    restBedService.start(8080,resource);
}





/**
 * https://github.com/corvusoft/restbed
 */
TEST(test_restbed,restbed){
    //set controller
    //https://github.com/Corvusoft/restbed/blob/master/documentation/example/RESOURCE_FILTERING.md
    auto resource = make_shared<restbed::Resource>();
    resource->set_path( "/index" );
    resource->set_method_handler( "POST",post_method_handler );

    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler);

    //base setting
    uint16_t port=8080;
    auto settings = make_shared<restbed::Settings>();
    settings->set_port(port);
    settings->set_default_headers( {
        {"Connection", "close"},
        {"Content-Type","application/json;charset=UTF-8"},
    } );


//    restbedLogger->info("default work_limit:{},connect_limit:{} connect_time_out:{} ms insensitive_uris:{}",
//            settings->get_worker_limit(),settings->get_connection_limit(),
//                 connect_time_out.count(),settings->get_case_insensitive_uris());


    //work limit eq cpu*2 .connection_limit INT_MAX ,time_out is 5 seconds
    settings->set_worker_limit(std::thread::hardware_concurrency()*2); //default is 0
    settings->set_connection_limit(INT_MAX); //default is 128
    settings->set_connection_timeout(std::chrono::milliseconds(5*1000)); //default is 5000ms


    auto connect_time_out=settings->get_connection_timeout();
    restbedLogger->info("after work_limit:{},connect_limit:{} connect_time_out:{} ms",
                 settings->get_worker_limit(),settings->get_connection_limit(),
                 connect_time_out.count());


    //start rest service
    restbed::Service service;
    service.publish(resource);
    //service.set_logger(std::make_shared<SyslogLogger>());
  //  service.add_rule(std::make_shared<LogRule>());
    //service.set_authentication_handler(authentication_handler);
    restbedLogger->info("restbed service started,listen to port:{}",port);
    service.set_error_handler(service_error_handler);
    //
    service.set_ready_handler( ready_handler );
    service.set_signal_handler( SIGINT, sighup_handler );
    service.set_signal_handler( SIGTERM, sigterm_handler );
    service.start( settings );
}