#include<iostream>
#include<fstream>
#include<istream>
#include<sstream>
#include<iterator>
#include "fileparser.h"

namespace WET {
    const int maxBufSize = 1024;
    enum theParsingStatuses { outState, inTagState, inValueState };
    const char charCloseTag = '>';
    const char charQuote = '\"';
    const char charSpace = ' ';
    const char charNewLine = '\n';
    const char charEqual = '=';
};

FileParserException::FileParserException() { }
FileParserException::~FileParserException() { }

FileParser::FileParser() { }
FileParser::FileParser(std::string theFileName, std::string theParseTag) :
  fileName(theFileName), parseTag(theParseTag) { }

FileParser::~FileParser() { }

void FileParser::setFileName(std::string theFileName) {
  fileName = theFileName;
}

std::string FileParser::getFileName(void) const {
  return fileName;
}

void FileParser::setParseTag(std::string theParseTag) {
  parseTag = theParseTag;
}

std::string FileParser::getParseTag(void) const {
  return parseTag;
}

void FileParser::parse(void) throw(FileParserException) {
    using namespace std;
    using namespace WET;
    ifstream is(fileName.c_str());

    //------- ERROR HANLING --------
    if (!is) {
        cerr << "FileParser::parse() cannot open file " << fileName << endl;
        throw FileParserException();
    }
    if (parseTag.size() == 0) {
        cerr << "FileParser:parse(): parse tag not initialized" << endl;
        throw FileParserException();
    }
    //-- END OF ERROR HANDLING --

    //------ DATA INIT --------
    stringstream buffer;
    int buffersize = 0;
    char nextChar;
    string nextString;
    int parseStatus = outState;
    bool openQuote = false;
    string tmpString;
    //-- END OF DATA INIT --

    //------- PARSING ----------
    while(!is.eof()) {
        is.get(nextChar);

        if (parseStatus == outState) {
            buffer << nextChar;
            buffersize++;
            if (buffersize > parseTag.size()) {
                tmpString = buffer.str().substr(1, buffer.str().npos);
                buffer.str("");
                buffer << tmpString;
                buffersize--;
            }
            if (isTailCaseInsensitive(buffer.str(), parseTag)) {
                parseStatus = inTagState;
                buffer.str("");
            }
        }
        else if (parseStatus == inTagState) {
            if (nextChar == charEqual) {
                is.get(nextChar);
                while(nextChar == charSpace || nextChar == charNewLine) {
                    is.get(nextChar);
                }
                if (is.eof()) {
                    cerr << "FileParser::parse(): EOF reached before tag finished" << endl;
                } else {
                    parseStatus = inValueState;
                    if (nextChar == charQuote) {
                        is.putback(nextChar);
                    }
                }
            }
        }
        else if (parseStatus == inValueState) {
            if (!openQuote && nextChar == charQuote) { openQuote = true; }
            else if ((openQuote && nextChar == charQuote) ||
                    (!openQuote && (nextChar == charSpace || nextChar == charNewLine || nextChar == charCloseTag))) {
                parsedString.push_back(buffer.str());
                buffer.str("");
                buffersize = 0;
                openQuote = false;
                parseStatus = outState;
            } else {
                buffer << nextChar;
            }
        }
    }
}


int FileParser::getNumberOfParsedStrings(void) const {
    return parsedString.size();
}

std::string FileParser::getParsedString(int i) const throw (FileParserException) {
    using namespace std;
    if (i >= parsedString.size() || i < 0) {
        cerr << "FileParser::getParsedString(" << i
                << "): counter out of bounds" << endl;
        throw FileParserException();
    }
    return parsedString[i];
}

int FileParser::compareCaseInsensitive(const std::string& s1,
        const std::string& s2) const {
    using namespace std;
    string::const_iterator p1 = s1.begin();
    string::const_iterator p2 = s2.begin();
    while (p1 != s1.end() && p2 != s2.end()) {
        if (toupper(*p1) < toupper(*p2)) {
            return -1;
        } else if (toupper(*p1) > toupper(*p2)) {
            return 1;
        }
        p1++;
        p2++;
    }
    if (s1.size() < s2.size()) {
        return -1;
    } else if (s1.size() > s2.size()) {
        return 1;
    }
    return 0;
}

bool FileParser::isTailCaseInsensitive(const std::string& s1,
        const std::string& s2) const {
    using namespace std;
    int s2len = s2.size();
    if (s1.size() >= s2.size()
            && compareCaseInsensitive(s1.substr(s1.size() - s2len, s2len), s2)
                    == 0) {
        return true;
    }
    return false;
}
