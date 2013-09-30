#ifndef _SCENE_H_
#define _SCENE_H_

#include "node.h"
#include "camera.h"
#include "light.h"
#include "primitive.h"

struct Scene : Node {
	Camera*              camera = nullptr;
	LightGroup*          lights = nullptr;
	PrimitiveGroup*      prims = nullptr;
    
    LightGroup* _cameralights;
};

#endif
