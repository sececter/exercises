#ifndef HTMLPAGE_H
#define HTMLPAGE_H
#include <string>
#include <vector>
#include "fileparser.h"

class HTMLPageException {
public:
    HTMLPageException();
    ~HTMLPageException();
};

class HTMLPage : public FileParser {
public:
    HTMLPage(std::string theFileName, std::string theURL)
        throw(HTMLPageException());
    ~HTMLPage();

    int getNumberOfLinks(void) const;
    std::string getLink(int i) const throw(HTMLPageException);

private:
    bool isHTTP(const std::string& theLink) const;
    std::string makeAbsoluteURL(const std::string& theLink) const;

    std::string htmlFileName;
    std::string URL;
    std::string URLPrefix;
    std::vector<std::string> link;
};
#endif // HTMLPAGE_H
