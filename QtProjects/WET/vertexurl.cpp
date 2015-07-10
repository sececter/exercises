#include<iostream>
#include "vertexurl.h"

VertexURLException::VertexURLException() {
}
VertexURLException::~VertexURLException() {
}

VertexURL::VertexURL(int theID, URL* theURLPtr) :
        id(theID), urlPtr(theURLPtr) {
}
VertexURL::~VertexURL() {
#ifdef DEBUG
    std::cerr << "** destroying VertexURL " << this << std::endl;
#endif
    delete urlPtr;
}

int VertexURL::getID(void) const {
    return id;
}

int VertexURL::getNumberOfAdjacentVertices(void) const {
    return star.size();
}

int VertexURL::getAdjacentVertexID(int i) const throw (VertexURLException) {
    if (i < 0 || i >= star.size()) {
        throw VertexURLException();
    }
    return star[i];
}

void VertexURL::addAdjacentVertexID(int ID) {
    star.push_back(ID);
}

std::string VertexURL::getText(void) {
    return getURL().getHostName();
}

URL& VertexURL::getURL(void) {
    return *urlPtr;
}
