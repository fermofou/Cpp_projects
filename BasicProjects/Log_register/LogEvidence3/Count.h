#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
struct Count {
public:
    string ip;
    int counter;
    bool operator<(Count count);
    bool operator<=(Count count);
    bool operator>=(Count count);
    bool operator!=(Count count);
    bool operator==(Count count);
    bool operator>(Count count);
    
    Count ();
    Count (string ip);

};

Count::Count() {
    // vacio
}

Count::Count(string ip) {
    this->ip = ip;
    this->counter = 1;
    }

bool Count::operator<(Count count) {
    return this->counter < count.counter;
}
bool Count::operator<=(Count count) {
    return this->counter <= count.counter;
}
bool Count::operator>(Count count) {
    return this->counter > count.counter;
}
bool Count::operator>=(Count count) {
    return this->counter >= count.counter;
}
bool Count::operator!=(Count count) {
    return this->counter != count.counter;
}
bool Count::operator==(Count count) {
    return this->counter == count.counter;
}
