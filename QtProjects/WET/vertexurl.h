#ifndef VERTEXURL_H
#define VERTEXURL_H

#include<vector>
#include<string>
#include "vertex.h"
#include "url.h"

class VertexURLException {
public:
    VertexURLException();
    ~VertexURLException();
};

class VertexURL: public virtual Vertex {
public:
    VertexURL(int theID, URL* theURLPtr);
    ~VertexURL();

    int getID(void) const;
    int getNumberOfAdjacentVertices(void) const;
    int getAdjacentVertexID(int i) const throw (VertexURLException);
    void addAdjacentVertexID(int ID);
    std::string getText(void);
    URL& getURL(void);

private:

    int id;
    std::vector<int> star;
    URL* urlPtr;
};

#endif // VERTEXURL_H
