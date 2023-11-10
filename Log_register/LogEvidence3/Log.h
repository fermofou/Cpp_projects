#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct Log {
public:
    string year;
    string month;
    string day;
    string time;
    string ip;
    string message;
    string key1;
    string key2;
    bool operator<(Log log);
    bool operator>(Log log);
    
    Log();
    Log(string year, string month, string day, string time, string ip, string message,string key1, string key2);

};

Log::Log() {
    // vacio
}

Log::Log(string year, string month, string day, string time, string ip, string message,string key1, string key2) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->time = time;
    this->ip = ip;
    this->message = message;
    this->key1 = key1;
    this->key2 = key2;
    }



bool Log::operator<(Log log) {
    return this->key1 < log.key1;
}

bool Log::operator>(Log log) {
    return this->key1 > log.key1;
}
