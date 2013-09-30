#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "node.h"
#include "shape.h"
#include "material.h"

struct Primitive : Node {
    frame3f              f;
    Material*            material = nullptr;
};

struct PrimitiveGroup : Node {
	vector<Primitive*>       prims;
};

struct Surface : Primitive {
    Shape*               shape = nullptr;
};


#endif
