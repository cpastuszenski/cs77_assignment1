cs77_assignment1
================

Simple raytracing program for Dartmouth CS77 (Graphics) course.

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
			Capped Cylinders (EXTRA CREDIT)
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
