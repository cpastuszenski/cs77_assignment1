#include "serialize.h"          

#include "raytrace.h"

Serializer::_Registry Serializer::_registry;

void Serializer::register_object_types() {
    static bool done = false;
    if(done) return;
    register_object_type<Sphere>();
    register_object_type<Cylinder>();
    register_object_type<CappedCylinder>();
    register_object_type<Quad>();
    register_object_type<Triangle>();
    register_object_type<Lambert>();
    register_object_type<Blinn>();
    register_object_type<Material>();
    register_object_type<Camera>();
    register_object_type<LightGroup>();
    register_object_type<PointLight>();
    register_object_type<DirectionalLight>();
    register_object_type<Surface>();
    register_object_type<PrimitiveGroup>();
    register_object_type<Scene>();
    register_object_type<RaytraceOptions>();
    done = true;
}

const char* serialize_typename(Node* node) {
    if(not node) return nullptr;
    else if(is<Shape>(node)) {
        if(not node) return nullptr;
        else if(is<Sphere>(node)) return "Sphere";
        else if(is<Cylinder>(node)) return "Cylinder";
        else if(is<CappedCylinder>(node)) return "CappedCylinder";
        else if(is<Quad>(node)) return "Quad";
        else if(is<Triangle>(node)) return "Triangle";
        else return "Shape";
    }
    else if(is<Material>(node)) {
        if(not node) return nullptr;
        else if(is<Lambert>(node)) return "Lambert";
        else if(is<Blinn>(node)) return "Blinn";
        else return "Material";
    }
    else if(is<Camera>(node)) return "Camera";
    else if(is<LightGroup>(node)) return "LightGroup";
    else if(is<Light>(node)) {
        if(not node) return nullptr;
        else if(is<PointLight>(node)) return "PointLight";
        else if(is<DirectionalLight>(node)) return "DirectionalLight";
        else return "Light";
    }
    else if(is<Primitive>(node)) {
        if(not node) return nullptr;
        else if(is<Surface>(node)) return "Surface";
        else return "Primitive";
    }
    else if(is<PrimitiveGroup>(node)) return "PrimitiveGroup";
    else if(is<Scene>(node)) return "Scene";
    else if(is<RaytraceOptions>(node)) return "RaytraceOptions";
    else return "Node";
}

void serialize_members(Node* node, Serializer& ser) {
    if(not node) warning("node is null");
    else if(is<Shape>(node)) {
        auto shape = cast<Shape>(node);
        if(not shape) error("node is null");
        else if(is<Sphere>(node)) {
            auto sphere = cast<Sphere>(node);
            ser.serialize_member("r",sphere->r);
        }
        else if(is<Cylinder>(node)) {
            auto cylinder = cast<Cylinder>(node);
            ser.serialize_member("r",cylinder->r);
            ser.serialize_member("h",cylinder->h);
        }
        else if(is<CappedCylinder>(node)) {
            auto cylinder = cast<CappedCylinder>(node);
            ser.serialize_member("r",cylinder->r);
            ser.serialize_member("h",cylinder->h);
        }
        else if(is<Quad>(node)) {
            auto quad = cast<Quad>(node);
            ser.serialize_member("w",quad->w);
            ser.serialize_member("h",quad->h);
        }
        else if(is<Triangle>(node)) {
            auto triangle = cast<Triangle>(node);
            ser.serialize_member("v0",triangle->v0);
            ser.serialize_member("v1",triangle->v1);
            ser.serialize_member("v2",triangle->v2);
        }
        else not_implemented_error();
    }
    else if(is<Material>(node)) {
        auto material = cast<Material>(node);
        if(not material) error("node is null");
        else if(is<Lambert>(node)) {
            auto lambert = cast<Lambert>(node);
            ser.serialize_member("kd",lambert->kd);
        }
        else if(is<Blinn>(node)) {
            auto blinn = cast<Blinn>(node);
            ser.serialize_member("kd",blinn->kd);
            ser.serialize_member("ks",blinn->ks);
            ser.serialize_member("kr",blinn->kr);
            ser.serialize_member("n",blinn->n);
        }
        else not_implemented_error();
    }
    else if(is<Camera>(node)) {
        auto camera = cast<Camera>(node);
        ser.serialize_member("f",camera->f);
        ser.serialize_member("l",camera->l);
        ser.serialize_member("w",camera->w);
        ser.serialize_member("h",camera->h);
        ser.serialize_member("d",camera->d);
    }
    else if(is<Light>(node)) {
        auto light = cast<Light>(node);
        ser.serialize_member("f",light->f);
        if(is<PointLight>(node)) {
            auto points = cast<PointLight>(node);
            ser.serialize_member("intensity",points->intensity);
        }
        else if(is<DirectionalLight>(node)) {
            auto directional = cast<DirectionalLight>(node);
            ser.serialize_member("intensity",directional->intensity);
        }
        else not_implemented_error();
    }
    else if(is<LightGroup>(node)) {
        auto lights = cast<LightGroup>(node);
        ser.serialize_member("lights",lights->lights);
    }
    else if(is<Primitive>(node)) {
        auto prim = cast<Primitive>(node);
        ser.serialize_member("f",prim->f);
        ser.serialize_member("material",prim->material);
        if(not prim) error("node is null");
        else if(is<Surface>(node)) {
            auto surface = cast<Surface>(node);
            ser.serialize_member("shape",surface->shape);
        }
        else not_implemented_error();
    }
    else if(is<PrimitiveGroup>(node)) {
        auto group = cast<PrimitiveGroup>(node);
        ser.serialize_member("prims",group->prims);
    }
    else if(is<Scene>(node)) {
        auto scene = cast<Scene>(node);
        ser.serialize_member("camera",scene->camera);
        ser.serialize_member("lights",scene->lights);
        ser.serialize_member("prims",scene->prims);
    }
    else if(is<RaytraceOptions>(node)) {
        auto opts = cast<RaytraceOptions>(node);
        ser.serialize_member("res", opts->res);
        ser.serialize_member("samples", opts->samples);
        ser.serialize_member("doublesided", opts->doublesided);
        ser.serialize_member("time", opts->time);
        ser.serialize_member("background", opts->background);
        ser.serialize_member("ambient", opts->ambient);
        ser.serialize_member("shadows", opts->shadows);
        ser.serialize_member("reflections", opts->reflections);
    }
    else not_implemented_error();
}
