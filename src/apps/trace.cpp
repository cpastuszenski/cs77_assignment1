/*
 * File: trace.cpp
 *
 * A testing program for the raytracer coded for Assignment 1. Originally coded by Jon Denning for CS77.
 */

#include "igl/serialize.h"
#include "igl/scene.h"
#include "igl/intersect.h"
#include "tclap/CmdLine.h"

#include "igl/intersect.h"
#include "igl/raytrace.h"

#include <thread>

Scene* scene;
RaytraceOptions opts;

string filename_scene;
string filename_image;

void parse_args(int argc, char** argv) {
	try {  
        TCLAP::CmdLine cmd("trace", ' ', "0.0");

        TCLAP::ValueArg<int> resolutionArg("r","resolution","Image resolution",false,0,"int",cmd);
        TCLAP::ValueArg<int> samplesArg("s","samples","Pixel samples",false,0,"int",cmd);
        TCLAP::ValueArg<int> progressiveArg("p","progressive","Progressive skip rows",false,0,"int",cmd);
        
        TCLAP::SwitchArg mirrorArg("m","mirror","Mirror reflection off.",cmd,true);
        TCLAP::SwitchArg shadowArg("w","shadow","Shadow test off.",cmd,true);
        
        TCLAP::SwitchArg threadedArg("t","threaded","Use multithreading.",cmd,false);
        
        TCLAP::UnlabeledValueArg<string> filenameScene("scene","Scene filename",true,"","filename",cmd);
        TCLAP::UnlabeledValueArg<string> filenameImage("image","Image filename",false,"","filename",cmd);
        
        cmd.parse( argc, argv );

        if(resolutionArg.isSet()) opts.res = resolutionArg.getValue();
        if(samplesArg.isSet()) opts.samples = samplesArg.getValue();
        if(mirrorArg.isSet()) opts.reflections = false;
        if(shadowArg.isSet()) opts.shadows = false;
        
        filename_scene = filenameScene.getValue();
        if(filenameImage.isSet()) filename_image = filenameImage.getValue();
        else { filename_image = filename_scene.substr(0,filename_scene.length()-4)+"png"; }
	} catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }
}

int main(int argc, char** argv) {
    parse_args(argc,argv);
    Serializer::read_json(scene, filename_scene);
    image3f img(camera_image_width(scene->camera, opts.res),camera_image_height(scene->camera, opts.res));
    raytrace_scene(img,scene,opts);
    imageio_write_png(filename_image, img, false);
}
