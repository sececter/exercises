#ifndef TIMESTAMP_H
#define TIMESTAMP_H

class TimeStampException {
public:
    TimeStampException();
    ~TimeStampException();
};

class TimeStamp {
public:
    TimeStamp();
    ~TimeStamp();
    long get(void) const;
    void set(long);
    void update(void);
private:
    long timestamp;
};
std::ostream& operator<<(std::ostream& s, TimeStamp& t);


#endif // TIMESTAMP_H
