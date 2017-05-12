
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include "glut_window.h"
# include "so_axis.h"
# include "so_poly.h"
# include "so_curve.h"
# include "curve_eval.h"
# include "gsim/gs_light.h"
# include "so_graph.h"
# include "so_clock.h"

# include "deck.h"
# include "base_plate.h"
#include "axle.h"
# include "wheel.h"
# include "rail.h"
# include "floor.h"

#include <vector>
// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
{
private:
	// OpenGL shaders and programs:
	GlShader _flatvsh, _flatfsh;
	GlProgram _prog;

	// My scene objects:
	SoAxis _axis;
	SoClock _clock;
	

	SoPoly _poly1;
	SoPoly _poly2;
	SoPoly _poly3;
	SoPoly _poly4;

	Curve _curve1;
	Curve _curve2;
	Curve _curve3;
	Curve _curve4;

	SoGraph _graphs;

	Deck _deck;
	BasePlate _baseplate;
	Axle _axleBack;
	Axle _axleFront;
	Wheel _frontWheel;
	Wheel _frontWheel2;

	Wheel _backWheel;
	Wheel _backWheel2;


	Rail _rail;
	Floor _floor;

	

	GsLight _light;


	// App data:
	enum MenuEv { evOption0, evOption1 };

	float _rotx, _roty; // scene transformation data
	GsVec _trans;       // scene transformation data
	GsMat _str;         // scene transformation

	GsVec _eye, _center, _up; // camera data
	GsMat _cam;               // camera transformation
	float _aspect, _znear, _zfar, _fovy; // perspective projection data
	GsMat _proj;              // projection transformation
	GsMat _spr;               // final scene projection _spr=_cam*_proj

	float _pickprec;
	bool _viewaxis;
	bool _oktodrag;
	int _w, _h;

	//	For bezier, controls difference between t in interpolating points
	float interpDiff;
	


	// Select curve, 0 = none, 1 = Lagrange, 2 = Bezier
	int curve;

	bool realTimeUpdate;
	bool regenerate;
	bool displayGraphs;
	bool viewTrickMode;
	bool addedPoints;
	bool resetAxis;
	bool justPressed;
	bool addNewTrick;
	bool findingTrick;

	char selectedKey;

	float xRotation;
	float yRotation;
	float zRotation;

	float yPos;
	float xPos;
	float zPos;

	float t;

	int nfaces;

	
public:
	AppWindow(const char* label, int x, int y, int w, int h);
	void initPrograms();
	GsVec2 windowToScene(const GsVec2& v);
	GsVec rayXYintercept(const GsVec2& v);
	void testTrick();

	struct savedTricks
	{
		int index;
		char key;
	};

	std::vector<savedTricks> trickDictionary;
	GsArray<GsVec> trickCtrlPnts;


private: // functions derived from the base class
	virtual void glutIdle();
	virtual void glutMenu(int m);
	virtual void glutKeyboard(unsigned char key, int x, int y);
	virtual void glutSpecial(int key, int x, int y);
	virtual void glutMouse(int b, int s, int x, int y);
	virtual void glutMotion(int x, int y);
	virtual void glutDisplay();
	virtual void glutReshape(int w, int h);
};

#endif // APP_WINDOW_H
