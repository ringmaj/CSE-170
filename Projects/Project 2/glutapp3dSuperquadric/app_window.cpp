
# include <iostream>
# include <gsim/gs.h>
# include "app_window.h"
# include <irrklang/include/irrKlang.h>
#pragma comment(lib, "irrKlang.lib").
# define M_PI           3.14159265358979323846 

using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();


AppWindow::AppWindow(const char* label, int x, int y, int w, int h)
	:GlutWindow(label, x, y, w, h)
{
	initPrograms();
	addMenuEntry("Option 0", evOption0);
	addMenuEntry("Option 1", evOption1);
	_viewaxis = true;
	_fovy = GS_TORAD(60.0f);
	_rotx = _roty = 0;
	_w = w;
	_h = h;
	_pickprec = 0.035f;
	_pickprec = 0.035f;
	_poly1.select(-1, _pickprec);
	_oktodrag = false;

	_eye.set(0, 0, 2);
	_center.set(0, 0, 0);
	_up.set(0, 1, 0);
	_aspect = 1.0f; _znear = 0.1f; _zfar = 50.0f;

	interpDiff = 0.05;
	curve = 2;

	realTimeUpdate = false;
	regenerate = false;
	displayGraphs = true;
	viewTrickMode = true;
	addedPoints = false;
	resetAxis = false;
	justPressed = true;
	addNewTrick = false;
	bool findingTrick = false;

	selectedKey = '0';

	xRotation = 0.0;
	yRotation = 0.0;
	zRotation = 0.0;
		
	xPos = 0.0;
	yPos = 0.0;
	zPos = 0.0;

	t = -0.01;

	nfaces = 16;

	

}

float degToRadian(float deg)
{
	return deg * (M_PI / 180);
}

void AppWindow::initPrograms()
{
	// Load your shaders and link your programs here:
	_flatvsh.load_and_compile(GL_VERTEX_SHADER, "../vsh_mcol_flat.glsl");
	_flatfsh.load_and_compile(GL_FRAGMENT_SHADER, "../fsh_flat.glsl");
	_prog.init_and_link(_flatvsh, _flatfsh);


	// Init my scene objects:
	_axis.init();


	GsVec pt1 = GsVec(0.425, 0.60, 0.0);
	GsVec pt2 = GsVec(0.75, 1.0, 0.0);
	GsVec pt3 = GsVec(1.075, 0.60, 0.0);

	_poly1.init( GsColor::darkblue, pt1, pt2, pt3, GsColor::darkred);


	 pt1 = GsVec(0.425, 0.10, 0.0);
	 pt2 = GsVec(0.75, 0.30, 0.0);
	 pt3 = GsVec(1.075, 0.50, 0.0);

	_poly2.init(GsColor::darkblue, pt1, pt2, pt3, GsColor::darkred);



	pt1 = GsVec(0.425, -0.40, 0.0);
	pt2 = GsVec(0.75, -0.20, 0.0);
	pt3 = GsVec(1.075, 0.0, 0.0);

	_poly3.init(GsColor::darkblue, pt1, pt2, pt3, GsColor::darkred);



	pt1 = GsVec(0.425, -0.90, 0.0);
	pt2 = GsVec(0.75, -0.70, 0.0);
	pt3 = GsVec(1.075, -0.50, 0.0);

	_poly4.init(GsColor::darkblue, pt1, pt2, pt3, GsColor::darkred);




	_curve1.init();
	_curve2.init();
	_curve3.init();
	_curve4.init();

	_graphs.init();
	_clock.init();

	_deck.init();
	_baseplate.init();
	_axleBack.init();
	_axleFront.init();
	_frontWheel.init();
	_frontWheel2.init();

	_backWheel.init();
	_backWheel2.init();


	_rail.init();
	_floor.init();

	// set light :
	_light.set(GsVec(0, -10, 0), GsColor(90, 90, 90, 255), GsColor::white, GsColor::white);


	// Build some of my scene objects:
	_axis.build(1.0f); // axis has radius 1.0
	_graphs.build();
	_clock.build(t);
	

}

// mouse events are in window coordinates, but your 2D scene is in [-1,1]x[-1,1],
// so make here the conversion when needed
GsVec2 AppWindow::windowToScene(const GsVec2& v)
{
	// GsVec2 is a lighteweight class suitable to return by value:
	return GsVec2((2.0f*(v.x / float(_w))) - 1.0f,
		1.0f - (2.0f*(v.y / float(_h))));
}

void AppWindow::testTrick()
{

	if (t == 0)
		SoundEngine->play2D("pop.mp3", GL_FALSE);

	if (t <= 1.0 && t >= 0.0)
	{
		if (displayGraphs == true)
			t = t + 0.01;
		else
			t = t + 0.005;
	}
		
}




// Called every time there is a window event
void AppWindow::glutKeyboard(unsigned char key, int x, int y)
{





	switch (key)
	{
		//case ' ': _viewaxis = !_viewaxis; redraw(); break;

	case 127: // Del pressed
		if (_poly1.selection() >= 0) // there is a selection
		{
			_poly1.del(_poly1.selection());
			redraw();
		}


		if (_poly2.selection() >= 0) // there is a selection
		{
			_poly2.del(_poly2.selection());
			redraw();
		}



		break;

	case 27: // Esc was pressed
		if (_poly1.selection() >= 0) // there is a selection
		{
			_poly1.select(-1, _pickprec);
			redraw();
			break;
		}

		if (_poly2.selection() >= 0) // there is a selection
		{
			_poly2.select(-1, _pickprec);
			redraw();
			break;
		}

		if (_poly3.selection() >= 0) // there is a selection
		{
			_poly3.select(-1, _pickprec);
			redraw();
			break;
		}

		if (_poly4.selection() >= 0) // there is a selection
		{
			_poly4.select(-1, _pickprec);
			redraw();
			break;
		}

	/*	exit(1);
		break;*/



	case 'a': if (interpDiff <= 1.0) interpDiff += 0.01f; std::cout << "Interpolate Diff " << interpDiff << std::endl;  redraw(); break;
	case 'q': if (interpDiff >= 0.01) interpDiff -= 0.01f; std::cout << "Interpolate Diff " << interpDiff << std::endl;  redraw(); break;



	case 'z': displayGraphs = !displayGraphs;  if (displayGraphs == false) SoundEngine->play2D("wheels.mp3", GL_TRUE); else SoundEngine->stopAllSounds(); redraw(); break;
	case 'x': resetAxis = !resetAxis; redraw(); break;

		// Test trick
	case ' ':  t = 0;   break;

		// Save trick
	case 's': std::cout << "Saving Selected Trick:\t Press key to map, or ESC to quit " << std::endl; addNewTrick = true; break;







	case 'n': nfaces++; redraw();  break;
	case 'r': t = 0.0; redraw();  break;


	default:
		selectedKey = key; findingTrick = true;
	}

}


void AppWindow::glutSpecial(int key, int x, int y)
{
	bool rd = true;
	const float incr = GS_TORAD(2.5f);
	const float inct = 0.1f;
	const float incf = 0.05f;
	bool ctrl = glutGetModifiers()&GLUT_ACTIVE_CTRL ? true : false;
	bool alt = glutGetModifiers()&GLUT_ACTIVE_ALT ? true : false;
	//std::cout<<ctrl<<gsnl;

	switch (key)
	{
	case GLUT_KEY_LEFT:        if (ctrl)_roty -= incr;   _trans.x += inct; break;
	case GLUT_KEY_RIGHT:       if (ctrl)_roty += incr; _trans.x -= inct; break;
	case GLUT_KEY_UP:        if (ctrl)_rotx += incr; else if (alt)_trans.y += inct;  break;
	case GLUT_KEY_DOWN:      if (ctrl)_rotx -= incr;   else if (alt)_trans.y -= inct;  break;
	case GLUT_KEY_PAGE_UP:   if (ctrl)_fovy -= incf; else if (alt)_trans.z += inct; break;
	case GLUT_KEY_PAGE_DOWN: if (ctrl)_fovy += incf; else if (alt)_trans.z -= inct; break;
	default: return; // return without rendering
	}
	if (rd) redraw(); // ask the window to be rendered when possible
}

static GsVec plane_intersect(const GsVec& c, const GsVec& n, const GsVec& p1, const GsVec& p2)
{
	GsVec coords = n;
	float coordsw = -dot(n, c);
	float nl = n.norm();
	if (nl == 0.0) return GsVec::null;
	coords /= nl; coordsw /= nl;
	float fact = dot(coords, p1 - p2);
	if (fact == 0.0) return GsVec::null;
	float k = (coordsw + dot(coords, p1)) / fact;
	return mix(p1, p2, k);
}

GsVec AppWindow::rayXYintercept(const GsVec2& v)
{
	// Recall that a mouse click in the screen corresponds to a ray traversing the 3D scene
	// Here we intersect this ray with the XY plane:
	GsVec m(windowToScene(v));
	GsVec p1(m.x, m.y, _znear); // mouse click in the near plane
	GsMat M(_spr); M.invert();
	p1 = M * p1;          // mouse click in camera coordinates
	GsVec p2 = p1 - _eye;
	p2.normalize();
	p2 *= (_zfar + _znear); // zfar and znear are >0
	p2 += p1;             // p1,p2 ray in camera coordinates
	M = _str; M.invert();
	p1 = M * p1;
	p2 = M * p2;          // p1,p2 ray in scene coordinates
	return plane_intersect(GsVec::null, GsVec::k, p1, p2); // intersect p1,p2 ray with XY plane
}

void AppWindow::glutMouse(int button, int state, int x, int y)
{
	GsVec m = rayXYintercept(GsVec2(x, y));
	//std::cout<<m<<gsnl;



	// Check if a vertex is being selected, ie, if m is very close to a vertex:
	int i;
	const GsArray<GsVec>& V = _poly1.vertexarray();
	for (i = 0; i<V.size(); i++)
		if (dist(V[i], m) <= _pickprec) break;

	if (i<V.size()) // vertex selected
	{
		_poly1.select(i, _pickprec);
		_oktodrag = true;
		redraw();
	}


	// Check if a vertex is being selected, ie, if m is very close to a vertex:
	
	const GsArray<GsVec>& V1 = _poly2.vertexarray();
	for (i = 0; i<V1.size(); i++)
		if (dist(V1[i], m) <= _pickprec) break;

	if (i<V1.size()) // vertex selected
	{
		_poly2.select(i, _pickprec);
		_oktodrag = true;
		redraw();
	}


	const GsArray<GsVec>& V2 = _poly3.vertexarray();
	for (i = 0; i<V2.size(); i++)
		if (dist(V2[i], m) <= _pickprec) break;

	if (i<V2.size()) // vertex selected
	{
		_poly3.select(i, _pickprec);
		_oktodrag = true;
		redraw();
	}

	const GsArray<GsVec>& V3 = _poly4.vertexarray();
	for (i = 0; i<V3.size(); i++)
		if (dist(V3[i], m) <= _pickprec) break;

	if (i<V3.size()) // vertex selected
	{
		_poly4.select(i, _pickprec);
		_oktodrag = true;
		redraw();
	}



	else if (state == GLUT_UP)
	{ // At this point no selection was detected and we will add a new vertex:
		//_poly1.add(m);
		_oktodrag = false;
		redraw();
	}




}

void AppWindow::glutMotion(int x, int y)
{
	//std::cout<<"Motion"<<std::endl;
	if (!_oktodrag) { return; }
	GsVec m = rayXYintercept(GsVec2(x, y));
	if (_poly1.selection() >= 0) { _poly1.move(_poly1.selection(), m); redraw(); }
	if (_poly2.selection() >= 0) { _poly2.move(_poly2.selection(), m); redraw(); }
	if (_poly3.selection() >= 0) { _poly3.move(_poly3.selection(), m); redraw(); }
	if (_poly4.selection() >= 0) { _poly4.move(_poly4.selection(), m); redraw(); }
}

void AppWindow::glutMenu(int m)
{
	std::cout << "Menu Event: " << m << std::endl;
}

void AppWindow::glutReshape(int w, int h)
{
	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);
	_w = w; _h = h;
}


void AppWindow::glutIdle() {
	testTrick();

	redraw();
}


// here we will redraw the scene according to the current state of the application.
void AppWindow::glutDisplay()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Define our scene transformation:
	GsMat rx, ry;

	if (displayGraphs == true)
	{
		rx.rotx(_rotx);
		ry.roty(_roty);
	}
	else
	{
		rx.rotx(0.436332);
		ry.roty(_roty);
	}
	
	_str = rx*ry;
	//_str.setrans(_trans);

	

	// Define our projection transformation:
	// (see gltutors example projection.exe, we are replicating the same behavior here)




	_cam.lookat(_eye, _center, _up);


	if(displayGraphs == true)
		_proj.perspective(_fovy, _aspect, _znear, _zfar);
	else
		_proj.perspective(1.659, _aspect, _znear, _zfar);
	_spr = _proj * _cam; // final scene projection

						 // Draw:
	//if (_viewaxis) _axis.draw(_str, _spr);






	if (displayGraphs == true)
	{
		// Build and draw curves

		_poly1.draw(_str, _spr);
		_poly2.draw(_str, _spr);
		_poly3.draw(_str, _spr);
		_poly4.draw(_str, _spr);

		_clock.build(t);
		_clock.draw(_str, _spr);


		_curve1.build(interpDiff, curve, _poly1.vertexarray());
		_curve1.draw(_str, _spr, _light);

		_curve2.build(interpDiff, curve, _poly2.vertexarray());
		_curve2.draw(_str, _spr, _light);

		_curve3.build(interpDiff, curve, _poly3.vertexarray());
		_curve3.draw(_str, _spr, _light);

		_curve4.build(interpDiff, curve, _poly4.vertexarray());
		_curve4.draw(_str, _spr, _light);

		_graphs.draw(_str, _spr);

	
	
	}
		


	if (resetAxis == true)
	{
		_poly2.vertexarray()[0] = GsVec(0.425, 0.10, 0.0);
		_poly2.vertexarray()[1] = GsVec(0.75, 0.30 - 0.2, 0.0);
		_poly2.vertexarray()[2] = GsVec(1.075, 0.50 - 0.4, 0.0);

		_poly3.vertexarray()[0] = GsVec(0.425, -0.40, 0.0);
		_poly3.vertexarray()[1] = GsVec(0.75, -0.20 - 0.2, 0.0);
		_poly3.vertexarray()[2] = GsVec(1.075, 0.0 - 0.4, 0.0);

		_poly4.vertexarray()[0] = GsVec(0.425, -0.90, 0.0);
		_poly4.vertexarray()[1] = GsVec(0.75, -0.70 - 0.2, 0.0);
		_poly4.vertexarray()[2] = GsVec(1.075, -0.50 - 0.4, 0.0);

		redraw();

		resetAxis = false;
	}


	if (addNewTrick == true)
	{


		char answer;

		std::cin >> answer;

		if (answer == 27)
		{

		}
		else
		{

			std::cout << "Trick saved to : " << answer << std::endl;
			savedTricks newTrick;
			newTrick.key = answer;
			newTrick.index = trickCtrlPnts.size();
			trickDictionary.push_back(newTrick);


			for (int i = 0; i < 3; i++)
				trickCtrlPnts.push(_poly1.vertexarray()[i]);

			for (int i = 0; i < 3; i++)
				trickCtrlPnts.push(_poly2.vertexarray()[i]);

			for (int i = 0; i < 3; i++)
				trickCtrlPnts.push(_poly3.vertexarray()[i]);

			for (int i = 0; i < 3; i++)
				trickCtrlPnts.push(_poly4.vertexarray()[i]);
		}





	

		addNewTrick = false;

	}


	if (findingTrick == true)
	{
		std::cout << "size: dictionary: " << trickDictionary.size() << std::endl;

		if (trickDictionary.size() != 0)
		{
			// See if custom trick is selected
			for (int i = 0; i < trickDictionary.size(); i++)
			{

				std::cout << "selectedKey : " << selectedKey << "\t trickDictionary:  " << trickDictionary[i].key << std::endl;

				if (selectedKey == trickDictionary[i].key)
				{

					std::cout << "found trick" << std::endl;
					for (int i = 0; i < 3; i++)
					{
						_poly1.vertexarray()[0] = trickCtrlPnts[i];
						_poly1.vertexarray()[1] = trickCtrlPnts[i];
						_poly1.vertexarray()[2] = trickCtrlPnts[i];
					}


					for (int i = 3; i < 6; i++)
					{
						_poly2.vertexarray()[0] = trickCtrlPnts[i];
						_poly2.vertexarray()[1] = trickCtrlPnts[i];
						_poly2.vertexarray()[2] = trickCtrlPnts[i];
					}


					for (int i = 6; i < 9; i++)
					{
						_poly3.vertexarray()[0] = trickCtrlPnts[i];
						_poly3.vertexarray()[1] = trickCtrlPnts[i];
						_poly3.vertexarray()[2] = trickCtrlPnts[i];
					}


					for (int i = 9; i < 12; i++) {

						_poly4.vertexarray()[0] = trickCtrlPnts[i];
						_poly4.vertexarray()[1] = trickCtrlPnts[i];
						_poly4.vertexarray()[2] = trickCtrlPnts[i];
					}





					std::cout << "changed points" << std::endl;
					redraw();
				}
			}
		}


		findingTrick = false;

	}




		
		// x is z axis
		_deck.build();
		_baseplate.build();
		_axleBack.build(nfaces, 1.0f, 1.0f, 0.5);
		_axleFront.build(nfaces, 1.0f, 1.0f, 0.5);

		_frontWheel.build(nfaces, 1.0f, 1.0f, 0.5);
		_frontWheel2.build(nfaces, 1.0f, 1.0f, 0.5);
		_backWheel.build(nfaces, 1.0f, 1.0f, 0.5);
		_backWheel2.build(nfaces, 1.0f, 1.0f, 0.5);

		_floor.build();
		_rail.build();

		GsMat rotX, rotY, rotZ, T, translation, transY, rotation, init, scale;

		
		translation.translation(-0.3, 0.0, 0.0);

	

		// Find rotations
		init.roty(degToRadian(90));


		GsVec point = eval_bezier(t, _poly2.vertexarray());
		xRotation = 0.5 - point.y;
		rotX.rotx(degToRadian(xRotation * 900));


		point = eval_bezier(t, _poly3.vertexarray());
		yRotation = 0.0 - point.y;
		rotY.roty(degToRadian(yRotation * 900));


		point = eval_bezier(t, _poly4.vertexarray());
		zRotation = -0.5 - point.y;
		rotZ.rotz(degToRadian(zRotation * 900));


		rotation = rotY * rotX * rotZ * init;



		//  Find y position
		point = eval_bezier(t, _poly1.vertexarray());
		yPos = point.y - 0.60;
	//	std::cout << "t: " << t << std::endl;




		transY.translation(0.0, 0.0 + yPos * 2, 0.0);


		
		T = _str  *  transY *  translation * rotation;

		_deck.draw(T, _spr, _light);





		translation.translation(0.0, -0.01, 0.25);
		rotation.rotx(degToRadian(180));
		T = T * translation * rotation;
		_baseplate.draw(T, _spr, _light);



		rotation.rotz(degToRadian(90));
		scale.scale(0.25, 0.025, 0.025);
		translation.translation(0.0, 2.0, 22.5);
		T = T * scale *  translation * rotation;
		_axleBack.draw(T, _spr, _light);



		translation.translation(0.0, 0.0, -25.0);
		T = T * translation;
		_axleFront.draw(T, _spr, _light);


		translation.translation(0.4, 0.5, 0.0);
		scale.scale(2, 0.25, 2);
		T = T * translation * scale;
		_frontWheel.draw(T, _spr, _light);
		


		translation.translation(0.0, -4.0, 0.0);
		T = T * translation;
		_frontWheel2.draw(T, _spr, _light);


		translation.translation(0.0, 0.0, 12.5);
		T = T * translation;
		_backWheel.draw(T, _spr, _light);


		translation.translation(0.0, 4.0, 0.0);
		T = T * translation;
		_backWheel2.draw(T, _spr, _light);




		translation.translation(3.0, 0.0, 0.0);
		rotation.roty(degToRadian(90));
		scale.scale(1.5, 1.5, 1.5);
	


		if (displayGraphs == false)
		{
			_trans.x -= 0.01f;
			_str.setrans(_trans);

			T = _str  * rotation * scale;
			_rail.draw(T, _spr, _light);
			_floor.draw(_str, _spr, _light);

			redraw();
		}
		


	
	












	


	// Swap buffers and draw:
	glFlush();         // flush the pipeline (usually not necessary)
	glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

