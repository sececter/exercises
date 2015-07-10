#ifndef URL_H
#define URL_H

#include<string>
#include "htmlpage.h"

class URLException {
public:
    URLException();
    ~URLException();
};

class URL {
public:

    URL();
    URL(std::string theURL);
    ~URL();

    std::string getURLName(void) const;
    void setURLName(std::string theURL);
    std::string getFileName(void) const;

    // download the URL
    void download(void) throw (URLException);

    // return the HTTP links in the URL
    std::string getNextLink(void) throw (URLException);

    // return the hostname in the URL
    std::string getHostName(void);

private:
    HTMLPage* htmlPagePtr;
    std::string URLName;
    std::string fileName;
    int linkCounter;

};

#endif // URL_H
