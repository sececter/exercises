#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include "timestamp.h"

TimeStampException::TimeStampException() { }
TimeStampException::~TimeStampException() { }

TimeStamp::TimeStamp() {
#ifdef _DEBUG
    std::cout << "TimeStamp object constructed at the address" << this << std::endl;
#endif
}

TimeStamp::~TimeStamp() {
#ifdef _DEBUG
    std::cout << "TimeStamp object at address" << this << " destroyed" << std::endl;
#endif
}

long TimeStamp::get(void) const {
    return timestamp;
}

void TimeStamp::set(long t) {
    timestamp = t;
}

void TimeStamp::update(void) {
    struct timeval tv;
    struct timezone tz;
    int retVal = gettimeofday(&tv, &tz);
    timestamp = tv.tv_sec;
}

std::ostream& operator<<(std::ostream& out, TimeStamp& ts){
    time_t secondsSince1970 = ts.get();
    char* buffer = ctime(&secondsSince1970);
    buffer[strlen(buffer) - 1] = '\0';
    std::string theDateString(buffer);
    out << theDateString << std::endl;
    return out;
}
