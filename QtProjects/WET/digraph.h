#ifndef DIGRAPH_H
#define DIGRAPH_H
#include<vector>
#include "vertex.h"
#include "vertexurl.h"
#include "arc.h"
#include "timestamp.h"

class DigraphException {
public:
    DigraphException();
    ~DigraphException();
};

class Digraph {
public:
    Digraph();
    ~Digraph();

    void setTimeStamp(TimeStamp& ts);
    TimeStamp& getTimeStamp(void);
    int getNumberOfVertices(void) const;
    int getNumberOfArcs(void) const;
    void addVertex(Vertex& theVertex);
    void addArc(Arc& theArc);
    Vertex& getVertex(int i) throw (DigraphException);
    Arc& getArc(int i) throw (DigraphException);

private:
    std::vector<Vertex*> vertexPtr;
    std::vector<Arc*> arcPtr;
    TimeStamp ts;

};

std::ostream& operator<<(std::ostream& out, Digraph& G);


#endif // DIGRAPH_H
