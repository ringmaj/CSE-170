
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include <vector>
# include <gsim/gs_color.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include "glut_window.h"

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private : // My OGL Data
    GlShader _vertexsh, _fragsh;
    GlProgram _prog;
    GlObjects _tris, _pts, _lines;
	std::vector<GsVec>   _tricoords;
    std::vector<GsColor> _tricolors;
    std::vector<GsVec>   _ptcoords;
    std::vector<GsColor> _ptcolors;
    std::vector<GsVec>   _linecoords;
    std::vector<GsColor> _linecolors;

   private : // App Data
    enum MenuEv { evOption0, evOption1 };
    GsColor _markc;
    GsVec2 _mark;
    int _w, _h;


	/*
	double a = -0.9;
	double b = -0.8;
	double c1 = -0.7;
	*/


	double z = -0.9;
	int upDown = 1;
	int leftRight = 1;


	GsColor waveHighlight = GsColor(23, 163, 173, 255);
	GsColor waveColor = GsColor::lightblue;

	//mouseclick Coordinates
	float mouseX = 0;
	float mouseY = 0;


	//Controls animation speed and direction (forward/backward)
	float speed = 0.0009f;


	// Cpntrols the coordinates for the waves, and lines
	double w1 = 0.1;
	double w2 = -0.1;

	double w3y = -0.3;
	double w3x = -0.0;

	double w4y = -0.3;
	double w4x = -0.9;
	

	//Colors
	GsColor c = GsColor::green;
	GsColor g = GsColor::green;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void initPrograms ();
	void buildObjects ();
    GsVec2 windowToScene ( const GsVec2& v );
	void moveM();
	

   private : // functions derived from the base class
	   virtual void glutIdle();
    virtual void glutMenu ( int m );
    virtual void glutKeyboard ( unsigned char key, int x, int y );
    virtual void glutSpecial ( int key, int x, int y );
    virtual void glutMouse ( int b, int s, int x, int y );
    virtual void glutMotion ( int x, int y );
    virtual void glutDisplay ();
    virtual void glutReshape ( int w, int h );
 };

#endif // APP_WINDOW_H
