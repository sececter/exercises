#ifndef VERTEX_H
#define VERTEX_H

#include<iostream>
#include<string>

class Vertex {
public:
    virtual ~Vertex() {
#ifdef DEBUG
        std::cerr << "** destroying Vertex " << this << std::endl;
#endif
    }
    virtual int getID(void) const = 0;
    virtual int getNumberOfAdjacentVertices(void) const = 0;
    virtual int getAdjacentVertexID(int i) const = 0;
    virtual std::string getText(void) = 0;
    virtual void addAdjacentVertexID(int ID) = 0;
};


#endif // VERTEX_H
