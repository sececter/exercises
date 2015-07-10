#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<unistd.h>
#include "url.h"

namespace WET {
const char charSlash = '/';
const char charQuote = '\"';
const std::string protocolTag = "http://";
const std::string theCommand = "wget --timeout=10 --quiet -O ";
const std::string stdFileName = ".wet.html";
}
;

URLException::URLException() {
}
URLException::~URLException() {
}

URL::URL() :
        htmlPagePtr(NULL), linkCounter(0) {
}

URL::URL(std::string theURL) :
        URLName(theURL), htmlPagePtr(NULL), linkCounter(0) {
}

URL::~URL() {
    if (htmlPagePtr) {
        delete htmlPagePtr;
#ifdef DEBUG
        std::cerr << "** destroying URL " << this
        << " and htmlPagePtr " << htmlPagePtr << std::endl;
    } else {
        std::cerr << "** destroying URL " << this << std::endl;
#endif
    }
}

std::string URL::getURLName(void) const {
    return URLName;
}

void URL::setURLName(std::string theURL) {
    URLName = theURL;
}

std::string URL::getFileName(void) const {
    return fileName;
}

void URL::download(void) throw (URLException) {
    using namespace std;
    using namespace WET;
    if (URLName == "") {
        cerr << "URL::download(): URLName not initialized" << endl;
        throw URLException();
    }
    unlink(stdFileName.c_str());
    string cmd = theCommand + stdFileName + " " + charQuote + URLName
            + charQuote;
    // spawn the command
#ifdef DEBUG
    cerr << "** URL: exec " << cmd << endl;
#endif
    int status = system(cmd.c_str());
    // create the HTML page
    htmlPagePtr = new HTMLPage(stdFileName, URLName);
    // delete the filename now
    unlink(stdFileName.c_str());
}

std::string URL::getNextLink(void) throw (URLException) {
    using namespace std;
    if (!htmlPagePtr) {
        cerr << "URL::getNextLink(): uninitialized htmlPagePtr" << endl;
        throw URLException();
    }
    string ret;
    if (linkCounter == htmlPagePtr->getNumberOfLinks()) {
        linkCounter = 0;
        return ret;
    }
    ret = htmlPagePtr->getLink(linkCounter);
    linkCounter++;
    return ret;
}

std::string URL::getHostName(void) {
    using namespace std;
    string::size_type p = URLName.find(WET::protocolTag);
    string::size_type from, to, length;
    if (p == URLName.npos) {
        // not found
        from = 0;
    } else {
        from = WET::protocolTag.size();
    }
    to = URLName.find(WET::charSlash, from);
    if (to == URLName.npos) {
        length = URLName.size();
    } else {
        length = to - from;
    }
    string ret = URLName.substr(from, length);
    return ret;
}

