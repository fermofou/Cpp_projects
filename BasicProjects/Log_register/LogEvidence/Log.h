#pragma once
#include <iostream>
#include <string>
#include <algorithm>

struct Log {
    string year;
    string month;
    string day;
    string time;
    string ip;
    string message;
    long long key;
    bool operator<(Log log);
    bool operator>(Log log);
    void keyGenerator();
    Log(string year, string month, string day, string time, string ip, string message);
};

Log::Log(string year, string month, string day, string time, string ip, string message) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->time = time;
    this->ip = ip;
    this->message = message;
}
//esta funcion genera key con cada Log, creo una nueva variable timecopy para que al imprimir/agregar
// el log completo,pueda mostrar el string time con (:) y no todos los numeros juntos
void Log::keyGenerator() {
    string timecopy=time;
    timecopy.erase(std::remove(timecopy.begin(), timecopy.end(), ':'), timecopy.end());
    string keyStr = year + month + day + timecopy;
    key = std::stoll(keyStr);
}

bool Log::operator<(Log log) {
    return this->key < log.key;
}

bool Log::operator>(Log log) {
    return this->key > log.key;
}