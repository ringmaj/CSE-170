#pragma once
// Ensure the header file is included only once in multi-file projects
#ifndef FLOOR_H
#define FLOOR_H
// Include needed header files
# include <vector>
# include <gsim/gs_array.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include <gsim/gs_color.h>
# include <gsim/gs_material.h>
# include <gsim/gs_light.h>

// Scene objects should be implemented in their own classes; and
// here is an example of how to organize a scene object in a class.
// Scene object axis:
class Floor : public GlObjects
{
private:
	GlShader _vsh, _fsh;
	GlProgram _prog;
	GlShader _vshgou, _fshgou, _vshphong, _fshphong;
	GlProgram _proggouraud, _progphong;
	GsArray<GsVec>   P; // coordinates
	GsArray<GsColor> C; // colors
	GsArray<GsVec>   N; // coordinates
						//std::vector<GsVec2> T; // texture coords
						//GsMaterial _mtl;

	int _numpoints;         // saves the number of points
	GsMaterial _mtl;
public:
	Floor();
	void init();
	void createBox(double x0, double y0, double z0, double length, double width, double height, GsArray<GsVec> &P, GsArray<GsColor> &C, GsColor color);
	void build();
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& l);
	void turnShadow();



};

#endif // FLOOR_H