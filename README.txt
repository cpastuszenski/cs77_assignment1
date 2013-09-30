Charles Pastuszenski
Computer Graphics
CS77
Assignment 1 README

Note: I did the Capped Cylinders EC.

ABOUT:
	
	In Assignment 1, students created a simple raytracing program that including a 
	variety of visual effects, such as shadowing, reflections and antialiasing. The
	project was completed by filling in sections of code left blank in a instructor-provided
	framework, which included type and function definitions that aided greatly in the
	process of writing the final program.
	
	The final result of this assignment is a simple ray tracer with support for 
	the following features:

		Algorithm
			Basic ray tracer
			Shadows
			Reflections
			Supersampling to reduce jaggies
		Geometry
			Spheres
			Triangles
			Quads
			Cylinders
			Capped Cylinders
		Materials
			Lambertian
			Blinn with mirror reflections
		Lights
			Point lights
			Directional lights

BUILD NOTES:

	To build the project, simply type "make" in a terminal from the directory in which this
	README is located. To run the test program, type "sh render_all.sh" to run the shell
	script included in the framework that performs 6 separate raytrace tests. test07.png will
	be produced by this test. This image demonstrates that capped cylinders are properly
	implemented in the framework by replacing the cylinder in test06 with a capped cylinder.
