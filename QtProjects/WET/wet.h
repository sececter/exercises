#ifndef WET_H
#define WET_H

#include<string>

#include "timestamp.h"
#include "fileparser.h"
#include "htmlpage.h"
#include "url.h"
#include "vertex.h"
#include "vertexurl.h"
#include "digraph.h"

namespace WET {
  void help(void);

  // compare two strings, case insensitive
  int compareCaseInsensitive(const std::string& s1, const std::string& s2);
  // is the head of the string equal to the substring? case insensitive
  bool isHeadCaseInsensitive(const std::string& s1, const std::string& s2);
  // check whether an (absolute) URL name is local
  bool isLocalURL(const std::string& theURL);
  // check whether URL name promises to be a text file from extension
  bool isTextOrDirURL(const std::string& theURL);
  // get relative URL given the full one
  std::string getRelativeURL(const std::string& theURL);

  // retrieve the data, driver
  void retrieveData(std::string URL, int maxDepth, Digraph& G,
                    bool localOnly, bool globalOnly, bool verbose);
  // retrieve the data, recursive
  void retrieveData(std::string URL, int maxDepth, Digraph& G,
                    bool localOnly, bool globalOnly, bool verbose,
                    int currentDepth, VertexURL* vParent);

  int run(int argc, char** argv);

  extern const std::string protocolTag;
};

#endif // WET_H
