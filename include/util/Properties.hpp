#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <util/Logger.hpp>

using namespace std;

class Properties {

public:
    Properties() = default;
    /**
     *
     */
    virtual ~Properties(){
        properties_map.clear();
    }
    /**
     * loading properties
     * @param fileName
     */
    inline void loadingProperties(std::string &&fileName) {
        read(fileName);
    }

    /**
     * Gets the property value from a given key.
     *
     * This method throws a PropertyNotFoundException when a given key does not
     * exist.
     */
    inline std::string get(const std::string &&key) const {
        if (properties_map.find(key) == properties_map.end()) {
            throw invalid_argument("not found key:"+key);
        }
        return properties_map.at(key);
    }

    /**
     *
     * @param key
     * @return
     */
    inline int getInt(const std::string && key){
        if (properties_map.find(key) == properties_map.end()) {
            throw invalid_argument("not found key:"+key);
        }
        return std::stoi(properties_map.at(key));
    }
    /**
     *
     * @param key
     * @return
     */
    inline long getLong(const std::string && key){
        if (properties_map.find(key) == properties_map.end()) {
            throw invalid_argument("not found key:"+key);
        }
        return std::stol(properties_map.at(key));
    }

    /**
     *
     * @param key
     * @return
     */
    inline double getDouble(const std::string && key){
        if (properties_map.find(key) == properties_map.end()) {
            throw invalid_argument("not found key:"+key);
        }
        return std::stod(properties_map.at(key));
    }

    /**
     *
     * @param key
     * @return
     */
    inline double getFloat(const std::string && key){
        if (properties_map.find(key) == properties_map.end()) {
            throw invalid_argument("not found key:"+key);
        }
        return std::stof(properties_map.at(key));
    }

    /**
     * debug info
     */
    inline void debug() {
        auto logger = Logger::createLogger("propertiesLoadingLogger");
        for (auto it:properties_map) {
            logger->info("k:{},v:{}", it.first, it.second);
        }
    }


    /**
     * Gets the property value from a given key. Use a default value if not found.
     */
    inline std::string get(const std::string &&key, const std::string &&defaultValue) const {
        if (properties_map.find(key) == properties_map.end()) {
            return defaultValue;
        }
        return properties_map.at(key);
    }

private:
    /**
     *
     * @param file
     * @return
     */
    inline void read(const std::string &file) {
        std::ifstream is; //
        is.open(file.c_str());
        if (!is.is_open()) {
            std::string msg = "Unable to read " + file;
            throw invalid_argument(msg);
        }
        //
        try {
            std::string line;
            while (std::getline(is, line)) {
                if (IsEmptyLine(line) || IsComment(line)) {
                    // ignore it
                } else if (IsProperty(line)) {
                    std::pair<std::string, std::string> prop = ParseProperty(line);
                    properties_map.insert(prop);
                } else {
                    std::string msg = "Invalid line: " + line;
                    throw invalid_argument(msg);
                }
            }
            //done
            is.close();
        } catch (...) {
            // don't forget to close the ifstream
            is.close();
            throw;
        }
    }


    //utils
    const std::string TRIM_DELIMITERS = " \f\n\r\t\v";

    inline std::string ltrim(const std::string &str) {
        std::string::size_type s = str.find_first_not_of(TRIM_DELIMITERS);
        if (s == std::string::npos) {
            return "";
        }
        return str.substr(s);
    }


    inline std::string RightTrim(const std::string &str) {
        std::string::size_type s = str.find_last_not_of(TRIM_DELIMITERS);
        if (s == std::string::npos) {
            return "";
        }
        return str.substr(0, s + 1);
    }

    /**
     *
     * @param str
     * @return
     */
    inline std::string LeftTrim(const std::string &str) {
        std::string rstr = ltrim(str);
        while (rstr != ltrim(rstr)) {
            rstr = ltrim(rstr);
        }
        return rstr;
    }

    inline std::string Trim(const std::string &str) {
        return RightTrim(LeftTrim(str));
    }

    inline bool IsProperty(const std::string &str) {
        std::string trimmedStr = LeftTrim(str);
        std::string::size_type s = trimmedStr.find_first_of('=');
        if (s == std::string::npos) {
            return false;
        }
        std::string key = Trim(trimmedStr.substr(0, s));
        // key can't be empty
        if (key.empty()) {
            return false;
        }
        return true;
    }

    /**
     *
     * @param str
     * @return
     */
    inline std::pair<std::string, std::string> ParseProperty(const std::string &str) {
        std::string trimmedStr = LeftTrim(str);
        std::string::size_type s = trimmedStr.find_first_of('=');
        std::string key = Trim(trimmedStr.substr(0, s));
        std::string value = LeftTrim(trimmedStr.substr(s + 1));
        return std::pair<std::string, std::string>(key, value);
    }


    inline bool IsComment(const std::string &str) {
        std::string trimmedStr = LeftTrim(str);
        return trimmedStr[0] == '#';
    }

    inline bool IsEmptyLine(const std::string &str) {
        std::string trimmedStr = LeftTrim(str);
        return trimmedStr.empty();
    }

private:
// to preserve the order
    std::map<std::string, std::string> properties_map;
};
