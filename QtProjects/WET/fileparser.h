#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <string>
#include <vector>

class FileParserException {
public:
    FileParserException();
    ~FileParserException();
};

class FileParser {
public:
    FileParser();
    FileParser(std::string theFileName, std::string theParseTag);
    ~FileParser();

    void setFileName(std::string theFileName);
    std::string getFileName(void) const;
    void setParseTag(std::string theParseTag);
    std::string getParseTag(void) const;

    void parse(void) throw(FileParserException);

    int getNumberOfParsedStrings(void) const;

    std::string getParsedString(int i) const throw(FileParserException);

protected:
    std::string fileName;
    std::string parseTag;

    int compareCaseInsensitive(const std::string& s1, const std::string& s2) const;

    bool isTailCaseInsensitive(const std::string& s1, const std::string& s2) const;

private:
    std::vector<std::string> parsedString;
};

#endif // FILEPARSER_H
