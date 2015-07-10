#include<iostream>
#include "digraph.h"

DigraphException::DigraphException() {
}
DigraphException::~DigraphException() {
}

Digraph::Digraph() {
}
Digraph::~Digraph() {
    using namespace std;
    // delete vertices and arcs
    for (vector<Vertex*>::iterator vi = vertexPtr.begin();
            vi != vertexPtr.end(); vi++) {
        delete *vi;
    }
    for (vector<Arc*>::iterator vi = arcPtr.begin(); vi != arcPtr.end(); vi++) {
        delete *vi;
    }
#ifdef DEBUG
    std::cerr << "** destroying Digraph " << this << std::endl;
#endif
}

int Digraph::getNumberOfVertices(void) const {
    return vertexPtr.size();
}

int Digraph::getNumberOfArcs(void) const {
    return arcPtr.size();
}

void Digraph::addVertex(Vertex& theVertex) {
    vertexPtr.push_back(&theVertex);
}

void Digraph::addArc(Arc& theArc) {
    arcPtr.push_back(&theArc);
}

Vertex& Digraph::getVertex(int i) throw (DigraphException) {
    using namespace std;
    if (i < 0 || i >= vertexPtr.size()) {
        cerr << "Digraph::getVertex(" << i << "): index out of bounds" << endl;
        throw DigraphException();
    }
    return *vertexPtr[i];
}

Arc& Digraph::getArc(int i) throw (DigraphException) {
    using namespace std;
    if (i < 0 || i >= arcPtr.size()) {
        cerr << "Digraph::getArc(" << i << "): index out of bounds" << endl;
        throw DigraphException();
    }
    return *arcPtr[i];
}

void Digraph::setTimeStamp(TimeStamp& theTs) {
    ts = theTs;
}

TimeStamp& Digraph::getTimeStamp(void) {
    return ts;
}

std::ostream& operator<<(std::ostream& out, Digraph& G) {
    using namespace std;
    out << "# graphviz output by WET (L. Liberti 2006)" << endl;
    out << "digraph www_" << G.getTimeStamp().get() << " {" << endl;
    int n = G.getNumberOfVertices();
    for (int i = 0; i < n; i++) {
        Vertex& v = G.getVertex(i);
        VertexURL* vptr = dynamic_cast<VertexURL*>(&v);
        out << "  " << i << " [ label = \"" << G.getVertex(i).getText()
                << "\" ];" << endl;
    }
    out << "  " << n << " [ label = \"" << G.getTimeStamp()
            << "\", color = red ];" << endl;
    int m = G.getNumberOfArcs();
    int from, to;
    for (int i = 0; i < m; i++) {
        from = G.getArc(i).getFrom();
        to = G.getArc(i).getTo();
        out << "   " << from << " -> " << to << ";" << endl;
    }
    out << "}" << endl;
}
