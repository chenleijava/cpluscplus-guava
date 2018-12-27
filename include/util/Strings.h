//
// Created by chenlei on 2018-12-20.
//

#ifndef CPLUSPLUSGUAVA_STRINGS_H
#define CPLUSPLUSGUAVA_STRINGS_H

#include <string>
#include <vector>
using namespace std;

class Strings{

public:
// trim from end of string (right)
    inline static std::string& rtrim(std::string& s,char *t=const_cast<char*>("\t\n\r\f\v"))
    {
        s.erase(s.find_last_not_of(t) + 1);
        return s;
    }

// trim from beginning of string (left)
    inline static std::string& ltrim(std::string& s,char *t=const_cast<char*>("\t\n\r\f\v"))
    {
        s.erase(0, s.find_first_not_of(t));
        return s;
    }

// trim from both ends of string (left & right)
    inline  static std::string& trim(std::string& s,char *t=const_cast<char*>("\t\n\r\f\v"))
    {
        return ltrim(rtrim(s, t), t);
    }

    /**
     *
     * @param s
     * @param v
     * @param c
     */
    static void split(const std::string& s, std::vector<std::string>& v, const std::string& c)
    {
        std::string::size_type pos1, pos2;
        pos2 = s.find(c);
        pos1 = 0;
        while(std::string::npos != pos2)
        {
            v.push_back(s.substr(pos1, pos2-pos1));

            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if(pos1 != s.length())
            v.push_back(s.substr(pos1));
    }
};


#endif //CPLUSPLUSGUAVA_STRINGS_H
