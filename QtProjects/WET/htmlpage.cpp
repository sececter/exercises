#include <iostream>
#include <algorithm>
#include "htmlpage.h"

namespace WET {
    const char charColon = ':';
    const char charSlash = '/';
    const char charDot = '.';
    const char charHash = '#';
    const std::string httpProtocolName = "http";
};

HTMLPageException::HTMLPageException() { }
HTMLPageException::~HTMLPageException() { }

HTMLPage::HTMLPage(std::string theFileName, std::string theURL)
    throw(HTMLPageException()) :
    htmlFileName(theFileName), URL(theURL), FileParser(theFileName, "HREF"){

    using namespace std;
    using namespace WET;

    if (URL.find(charColon) == URL.npos) {
        cerr << "HTMLPage::HTMLPage(): " << URL << " is not absolute" << endl;
        throw HTMLPageException();
    }
    if (count(URL.begin(), URL.end(), charSlash) < 3) {
        URLPrefix = URL + charSlash;
    } else {
        URLPrefix = URL.substr(0, URL.rfind(charSlash + 1));
    }

    parse();
    int n = getNumberOfParsedStrings();
    string theLink;
    for(int i = 0; i < n; i++) {
        theLink = getParsedString(i);
        if(isHTTP(theLink)) {
            theLink = makeAbsoluteURL(theLink);
            link.push_back(theLink);
        }
    }
}

HTMLPage::~HTMLPage() {
#ifdef DEBUG
    std::cerr << "Destroying HTMLPage " << this << std::endl;
#endif
}

int HTMLPage::getNumberOfLinks(void) const {
    return link.size();
}

std::string HTMLPage::getLink(int i) const throw(HTMLPageException) {
    using namespace std;
    if(i < 0 || i >= link.size()) {
        cerr << "HTMLPage::getLink(" << i << "): counter out of bounds" << endl;
        throw HTMLPageException();
    }
    return link[i];
}

bool HTMLPage::isHTTP(const std::string& theLink) const {
    using namespace std;
    using namespace WET;

    if (theLink[0] == charHash) { return false; }
    int colonpos = theLink.find(charColon);
    if (colonpos == theLink.npos) { return true; }
    if (compareCaseInsensitive(theLink.substr(0, colonpos), httpProtocolName) == 0) {
        return true;
    }
    return false;
}

std::string HTMLPage::makeAbsoluteURL(const std::string& theLink) const {
    using namespace std;
    using namespace WET;

    string ret;
    string::size_type colon = theLink.find(charColon);
    if (colon < theLink.npos && theLink[colon + 1] == charSlash &&
            theLink[colon + 2] == charSlash) {
        return theLink;
    }

    if (theLink[0] == charSlash) {
        int thePos = URLPrefix.find(charSlash);
        thePos = URLPrefix.find(charSlash, thePos + 2);
        ret = URLPrefix.substr(0, thePos) + theLink;
    } else {
        ret = URLPrefix + theLink;
    }
    return ret;
}
