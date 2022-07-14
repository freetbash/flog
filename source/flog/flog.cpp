#include <flog.h>
#include <string>
#include <float.h>
#include <thread>
#include <time.h>
#include <string.h>
#include <iostream>
std::string colorstring(std::string text, std::string color){
    std::string fuck_string = "\033["+color+text+"\033[0m";
    return fuck_string;
}

std::string gettimestring(){
    time_t rawtime;
    struct tm *info;
    char buffer[50];
    time(&rawtime);
    info=localtime(&rawtime);
    strftime(buffer,50,"|%Y-%m-%d %H:%M:%S %p\t| ",info);
    return std::string(buffer);
}

Flogger::Flogger(bool enable){
    this->file_enable=false;
    this->enable=enable;

}
Flogger::~Flogger(){
    this->file.close();
}
void Flogger::openfile(std::string file_path){
    this->file.open(file_path,std::ios::app);
    std::cout << gettimestring()+colorstring("START",GREEN)+"\t| Start Record log !" <<std::endl;
    this->file << gettimestring()+"START\t| Start Record log !" <<std::endl;
    this->file_enable=true;
}

void Flogger::log_to_file(std::string record){
    this->_.lock();
    this->file << record << std::endl;
    this->_.unlock();
}
void Flogger::log_file(std::string mode, std::string record){
    if(this->enable){
        if(this->file_enable){
           std::thread _(&Flogger::log_to_file,this,gettimestring()+mode+record);
           _.detach();
        }
    }
}


void Flogger::fuck_print(std::string mode,std::string f_string){
    if(this->enable){
        if(this->file_enable){
            std::thread _(&Flogger::log_to_file,this,gettimestring()+mode+f_string);
            _.detach();
        }
        std::string temp;
        if(mode=="LOG"){
            temp=colorstring(mode, WHITE);
        }else if(mode=="DEBUG"){
            temp=colorstring(mode,YELLOW);
        }else if(mode=="WARN"){
            temp=colorstring(mode,PUPLE);
        }else if(mode=="TRACE"){
            temp=colorstring(mode,BLUE);
        }else if(mode=="ERROR"){
            temp=colorstring(mode,RED);
        }else if(mode=="INFO"){
            temp=colorstring(mode, BLOD);
        }
        std::cout << gettimestring() + temp + f_string<<std::endl;
    }
}



void Flogger::log(std::string f_string){
    this->fuck_print("LOG",f_string);
}
void Flogger::debug(std::string f_string){
    this->fuck_print("DEBUG",f_string);
}
void Flogger::warn(std::string f_string){
    this->fuck_print("WARN",f_string);
}
void Flogger::trace(std::string f_string){
    this->fuck_print("TRACE",f_string);
}
void Flogger::error(std::string f_string){
    this->fuck_print("ERROR",f_string);
}
void Flogger::info(std::string f_string){
    this->fuck_print("INFO",f_string);
}
