
# include "so_capsule.h"

SoCapsule::SoCapsule()
{
	_numpoints = 0;
}

void SoCapsule::init(const GlProgram& prog)
{
	// Define buffers needed:
	set_program(prog);
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(2);       // will use 2 buffers: one for coordinates and one for colors
	uniform_locations(2); // will send 2 variables: the 2 matrices below
	uniform_location(0, "vTransf");
	uniform_location(1, "vProj");
}

void SoCapsule::build(double nfaces, double rt,double rb, double len)
{
	//initialize neccessary variables/values
	int i;
	double pi = 3.1495;
	double rad = 0.5;


	//Creation of tube element

	for (double t = -0.5; t < 0.5; t += 0.1) {
		for (double k = 0; k <= 360; k += 360 / nfaces) { 
	//Use even number as increment so spacing remains even

	
	//Create points for cylinder verticies.
	// Also able to change num faces

			P.push_back(GsVec((rt)*cos(k*(pi / 180.0)), 0.5, (rt)*sin(k*(pi / 180.0))));
			P.push_back(GsVec((rb)*cos(k*(pi / 180.0)), -0.5, (rb)*sin(k*(pi / 180.0))));

			P.push_back(GsVec((rt)*cos(k*(pi / 180.0)), 0.5, (rt)*sin(k*(pi / 180.0))));
			P.push_back(GsVec((rb)*cos(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180)), -0.5, (rb)*sin(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180))));


			P.push_back(GsVec((rb)*cos(k*(pi / 180.0)), -0.5, (rb)*sin(k*(pi / 180.0))));
			P.push_back(GsVec((rt)*cos(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180)), 0.5, (rt)*sin(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180))));



			//Build cylinder's top connections
			P.push_back(GsVec((rt)*cos(k*(pi / 180.0)), 0.5, (rt)*sin(k*(pi / 180.0))));
			P.push_back(GsVec((rt)*cos(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180)), 0.5, (rt)*sin(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180))));

			//Build cylinder's bottom connetions
			P.push_back(GsVec((rb)*cos(k*(pi / 180.0)), -0.5, (rb)*sin(k*(pi / 180.0))));
			P.push_back(GsVec((rb)*cos(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180)), -0.5, (rb)*sin(k*(pi / 180.0) + (360.0 / nfaces)*(pi / 180))));

			//Yellow coloring for the center tube
			for (i = 0; i < 6; i++) C.push_back(GsColor::yellow);

		}
	}

	//Tube element complete



	//Now build the upper and lower hemispheres for the cylinder 

	
	
	//initialize neccessary variables/values
	double theta = 0.0;
	double thetaPlus = (2 * pi) / nfaces;
	double phi = 0.0;
	double phiPlus = (pi) / (2 * nfaces);

	for (int t = 0; t< nfaces; t++) {
		for (i = 0; i < 6; i++) C.push_back(GsColor::gray);
		
		for (int j = 0; j < nfaces; j++) {


			//Build capsule's top hemishpere



			//Use x=rcos(t)sin(p) y=rsin(t)sin(t) z= cos(p) as parametrizations
			//Angles are changed here for each axis


			P.push_back(GsVec(rt * cos(theta) * sin(phi), (rt * cos(phi)) + len / 2, rt * sin(theta) * sin(phi)));
			P.push_back(GsVec(rt * cos(theta) * sin(phi + phiPlus), (rt * cos(phi + phiPlus)) + len / 2, rt * sin(theta) * sin(phi + phiPlus)));
			P.push_back(GsVec(rt * cos(theta) * sin(phi), (len / 2) + (rt*cos(phi)), rt* sin(theta) * sin(phi)));
			P.push_back(GsVec(rt * cos(theta + thetaPlus) * sin(phi), (len / 2) + (rt*cos(phi)), rt* sin(theta + thetaPlus) * sin(phi)));

			//Build capsule's bottom hemispere

			P.push_back(GsVec(rb * cos(theta) * sin(phi), (-rb * cos(phi)) - len / 2, rb * sin(theta) * sin(phi)));
			P.push_back(GsVec(rb * cos(theta) * sin(phi + phiPlus), (-rb * cos(phi + phiPlus)) - len / 2, rb * sin(theta) * sin(phi + phiPlus)));
			P.push_back(GsVec(rb * cos(theta) * sin(phi), (-rb * cos(phi)) - len / 2, rb * sin(theta) * sin(phi)));
			P.push_back(GsVec(rb * cos(theta + thetaPlus) * sin(phi), (-rb * cos(phi)) - len / 2, rb * sin(theta + thetaPlus) * sin(phi)));

			for (i = 0; i < 6; i++) C.push_back(GsColor::gray);


			//increment the phi value using the phi angle, else phi would stay the same
			phi += phiPlus; 

			for (i = 0; i < 6; i++) C.push_back(GsColor::gray);

		}
		theta += thetaPlus; 
		//increment the theta value using the phi angle, else theta would stay the same
		phi = 0;
	}

	

	// send data to OpenGL buffers:
	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, P.size() * 3 * sizeof(float), &P[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, C.size() * 4 * sizeof(gsbyte), &C[0], GL_STATIC_DRAW);

	// save size so that we can free our buffers and later just draw the OpenGL arrays:
	_numpoints = P.size();

	// free non-needed memory:
	P.resize(0); C.resize(0);
}

void SoCapsule::draw(GsMat& tr, GsMat& pr)
{
	// Draw Lines:
	glUseProgram(prog);
	glBindVertexArray(va[0]);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]); // positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]); // colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0);

	glUniformMatrix4fv(uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(uniloc[1], 1, GL_FALSE, pr.e);

	glDrawArrays(GL_LINES, 0, _numpoints);
}
