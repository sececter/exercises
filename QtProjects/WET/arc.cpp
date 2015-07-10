#include "arc.h"

Arc::Arc(int fromID, int toID) :
        from(fromID), to(toID) {
}
Arc::~Arc() {
}

int Arc::getFrom(void) const {
    return from;
}

int Arc::getTo(void) const {
    return to;
}
