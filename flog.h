#ifndef F_LOG_H
#define F_LOG_H
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#define BLOD  "1m"
#define RED     "31m"
#define GREEN   "32m"
#define YELLOW  "33m"
#define BLUE    "34m"
#define PUPLE   "35m"
#define WHITE   "37m"
#define FLOG_INIT() Flogger global_flogger();
#define F_STRING(record) std::string("\t| ")+std::string(__FILE__)+std::string(":")+std::to_string(__LINE__)+std::string(":")+std::string(__FUNCTION__)+std::string("\t| ")+record

std::string colorstring(std::string text, std::string color);
std::string gettimestring();

class Flogger{
private:
    std::mutex _;
    bool enable;
    bool file_enable;
    std::ofstream file;
    void fuck_print(std::string mode,std::string f_string);
    void log_to_file(std::string record);


    
public:
    Flogger(bool enable);
    ~Flogger();
    void openfile(std::string file_path);
    void log_to_file(std::string mode,std::string record);
    void log(std::string f_string); // white
    void debug(std::string f_string) ;// yellow
    void warn(std::string f_string); // puple
    void trace(std::string f_string); // blue
    void error(std::string f_string); // red
    void info(std::string f_string); // blod

};

extern Flogger global_flogger;

#endif
