#include<iostream>
#include<string>
#include<cstring>
#include <fstream>
#include <cstdlib>

#include "wet.h"

namespace WET {
enum exitCodes {
    exitNormal, exitError
};
const char charDot = '.';
const char charSlash = '/';
const std::string localPrefix1 = "http://127.0.0.1";
const std::string localPrefix2 = "http://localhost";
const std::string htmlExtension1 = "html";
const std::string htmlExtension2 = "htm";
const std::string protocolTag = "http://";
const int lastFewCharsSize = 5;
}
;

void WET::help(void) {
    using namespace std;
    cerr << "wet (WWW Exploring Topologizer), Leo Liberti 2006" << endl;
    cerr << "Syntax: wet [options] URL maxDepth" << endl;
    cerr << "  Retrieves neighbourhood of radius maxDepth starting with URL"
            << endl;
    cerr << "  -h       display this help" << endl;
    cerr << "  -v       verbose progress output on stderr" << endl;
    cerr << "  -l       limits exploration to local downloads" << endl;
    cerr << "  -g       limits exploration to global downloads" << endl;
}

int WET::compareCaseInsensitive(const std::string& s1, const std::string& s2) {
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

bool WET::isHeadCaseInsensitive(const std::string& s1, const std::string& s2) {
    using namespace std;
    int s2len = s2.size();
    if (s1.size() >= s2.size()
            && WET::compareCaseInsensitive(s1.substr(0, s2len), s2) == 0) {
        return true;
    }
    return false;
}

bool WET::isLocalURL(const std::string& theURL) {
    using namespace std;
    using namespace WET;
    return isHeadCaseInsensitive(theURL, localPrefix1)
            || isHeadCaseInsensitive(theURL, localPrefix2);
}

std::string WET::getRelativeURL(const std::string& theURL) {
    using namespace std;
    string ret;
    if (!isHeadCaseInsensitive(theURL, protocolTag)) {
        ret = theURL;
        return ret;
    }
    string tmp = theURL.substr(protocolTag.size() + 1);
    int lastSlashPos = tmp.find(charSlash);
    if (lastSlashPos == tmp.npos) {
        return ret;
    }
    ret = tmp.substr(tmp.find(charSlash) + 1);
    return ret;
}

bool WET::isTextOrDirURL(const std::string& theURL) {
    using namespace std;
    // jump over three slashes
    string relativeURL = getRelativeURL(theURL);
    // get the last few characters
    string lastFewChars;
    if (relativeURL.size() > lastFewCharsSize) {
        lastFewChars = relativeURL.substr(
                relativeURL.size() - lastFewCharsSize);
    } else {
        lastFewChars = relativeURL;
    }
    // get the extension
    string extension = lastFewChars.substr(lastFewChars.rfind(charDot) + 1);
    if (extension.size() == 0) {
        return true;
    }
    if (compareCaseInsensitive(extension, htmlExtension1) == 0
            || compareCaseInsensitive(extension, htmlExtension2) == 0) {
        return true;
    }
    return false;
}

void WET::retrieveData(std::string theURL, int maxDepth, Digraph& G,
        bool localOnly, bool globalOnly, bool verbose) {
    TimeStamp ts;
    ts.update();
    G.setTimeStamp(ts);
    // notice that theURL must be an absolute URL
    WET::retrieveData(theURL, maxDepth, G, localOnly, globalOnly, verbose, 0,
            NULL);
}

void WET::retrieveData(std::string URLName, int maxDepth, Digraph& G,
        bool localOnly, bool globalOnly, bool verbose, int currentDepth,
        VertexURL* vParent) {
    using namespace std;
    using namespace WET;
    bool proceed = true;
    if (verbose) {
        cerr << "wet: " << URLName;
    }

    // checks for proceeding to store url as vertex
    if (currentDepth >= maxDepth) {
        // check that we are not exceeding recursion level
        proceed = false;
    }
    if (localOnly && !isLocalURL(URLName)) {
        // if local flag is set, check that URL is local
        proceed = false;
    }
    if (globalOnly) {
        // if global flag is set, check that URL is global: scan all vertices to
        // see if one already contains the same hostname - if yes, ignore this
        int vSize = G.getNumberOfVertices();
        for (int i = 0; i < vSize; i++) {
            Vertex& theVertex = G.getVertex(i);
            VertexURL* theVtxURL = dynamic_cast<VertexURL*>(&theVertex);
            URL& theURL = theVtxURL->getURL();
            string hostName = theURL.getHostName();
            if (URLName.find(hostName) != URLName.npos) {
                // found
                proceed = false;
                break;
            }
        }
    }
    if (!isTextOrDirURL(URLName)) {
        proceed = false;
    }
    // check that this new URLName was not already downloaded at some point
    int vSize = G.getNumberOfVertices();
    for (int i = 0; i < vSize; i++) {
        Vertex& theVertex = G.getVertex(i);
        VertexURL* theVtxURL = dynamic_cast<VertexURL*>(&theVertex);
        URL& theURL = theVtxURL->getURL();
        string secondURL = theURL.getURLName();
        if (URLName == secondURL) {
            // vertex already exists, just add an arc vParent -> theVertex
            int theID = theVertex.getID();
            if (vParent) {
                vParent->addAdjacentVertexID(theID);
            }
            Arc* arcPtr = new Arc(vParent->getID(), theID);
            G.addArc(*arcPtr);
            proceed = false;
            break;
        }
    }

    // do it
    if (proceed) {
        if (verbose) {
            cerr << ": downloading" << endl;
        }
        URL* myURLPtr = new URL(URLName);
        myURLPtr->download();
        // get next available vertex ID
        int theID = G.getNumberOfVertices();
        VertexURL* vtxPtr = new VertexURL(theID, myURLPtr);
        // vertex pointers are only stored in the graph
        // (where VertexURL objects are stored as virtual base Vertex objects)
        G.addVertex(*vtxPtr);
        if (vParent) {
            // add the vertex ID to the adjacency list of the parent vertex
            vParent->addAdjacentVertexID(theID);
            // arc pointers are only stored in the graph
            Arc* arcPtr = new Arc(vParent->getID(), theID);
            G.addArc(*arcPtr);
        }
        // get next link
        string theLink = myURLPtr->getNextLink();
        while (theLink.size() > 0) {
            // if there is a next link, recurse
            retrieveData(theLink, maxDepth, G, localOnly, globalOnly, verbose,
                    currentDepth + 1, vtxPtr);
            theLink = myURLPtr->getNextLink();
        }
    } else if (verbose) {
        cerr << endl;
    }
}

int WET::run(int argc, char** argv) {
    using namespace std;
    using namespace WET;
    int ret = 0;
    bool localOnly = false;
    bool globalOnly = false;
    bool verbose = false;

    // main input data fields
    string URLName;
    int maxDepth;
    string timeStampName;

    // read options
    if (argc < 2 || strncmp(argv[1], "-h", 2) == 0) {
        help();
        exit(exitNormal);
    }

    int theArgCounter = 1;
    while (argv[theArgCounter][0] == '-') {
        // read options
        if (strncmp(argv[theArgCounter], "-l", 2) == 0) {
            localOnly = true;
        } else if (strncmp(argv[theArgCounter], "-g", 2) == 0) {
            globalOnly = true;
        } else if (strncmp(argv[theArgCounter], "-v", 2) == 0) {
            verbose = true;
        }
        theArgCounter++;
        if (theArgCounter == argc+1) {
            cerr
                    << "wet: error: after options, cmd line requires URL and maxDepth"
                    << endl;
            exit(exitError);
        }
    }

    URLName = argv[theArgCounter];
    if (URLName.find(WET::protocolTag) == URLName.npos) {
        URLName = WET::protocolTag + URLName;
    }
    theArgCounter++;
    if (theArgCounter == argc+1) {
        cerr << "wet: error: after options and URL, cmd line requires maxDepth"
                << endl;
        exit(exitError);
    }
    maxDepth = atoi(argv[theArgCounter]);

    // validate input data
    if (maxDepth < 1) {
        cerr << "wet: error: maxDepth must be strictly greater than 0" << endl;
        exit(exitError);
    }

    // do it
    Digraph G;
    try {
        retrieveData(URLName, maxDepth, G, localOnly, globalOnly, verbose);
        ofstream myfile;
        myfile.open("wetout.dot");
        cout << G;
        myfile << G;
        myfile.close();
        string cmd = "dot -Tgif -o wetout.gif wetout.dot";
        int status = system(cmd.c_str());
        cmd = "eog wetout.gif";
        status = system(cmd.c_str());
    } catch (TimeStampException) {
        cerr << "wet: exception in TimeStamp object, aborting" << endl;
    } catch (FileParserException) {
        cerr << "wet: exception in FileParser object, aborting" << endl;
    } catch (HTMLPageException) {
        cerr << "wet: exception in HTMLPage object, aborting" << endl;
    } catch (URLException) {
        cerr << "wet: exception in URL object, aborting" << endl;
    } catch (VertexURLException) {
        cerr << "wet: exception in VertexURL object, aborting" << endl;
    } catch (DigraphException) {
        cerr << "wet: exception in Digraph object, aborting" << endl;
    } catch (...) {
        cerr << "wet: caught generic exception, aborting" << endl;
    }

    return ret;
}
