#include "Segment.hpp"

namespace ProjectLibrary{

void Segment::connectTriangle(Triangle* t){
    if (c == 0 || adj1 == nullptr){adj1 = t;c++;}
    else{adj2 = t;c++;}

}

void Segment::disconnectTriangle(Triangle* t){
    if (adj1 == t) {adj1 = nullptr;c--;}
    if (adj2 == t) {adj2 = nullptr;c--;}
}

}
