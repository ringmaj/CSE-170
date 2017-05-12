
# include <iostream>
# include "app_window.h"

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   initPrograms ();
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );
   _markc = GsColor::yellow;
   _w=w; _h=h;
 }

void AppWindow::initPrograms ()
 {
   // We are following the OpenGL API version 4, 
   // see docs at: http://www.opengl.org/sdk/docs/man/

   // Load your shaders and link your programs here:
   _vertexsh.load_and_compile ( GL_VERTEX_SHADER, "2dcolored.vert" );
   _fragsh.load_and_compile ( GL_FRAGMENT_SHADER, "flat.frag" );
   _prog.init_and_link ( _vertexsh, _fragsh );

   // Define buffers needed for each of your OpenGL objects:
   // (here they all use the same definitions because we are using the same shaders)
   // Program for rendering triangles:
   { GlObjects& o = _tris;
     o.set_program ( _prog );
     o.gen_vertex_arrays ( 1 );
     o.gen_buffers ( 2 );
     o.uniform_locations ( 2 );
     o.uniform_location ( 0, "vTransf" );
     o.uniform_location ( 1, "vLocf" );
   }

   // Define buffers needed for each of your OpenGL objects:
   { GlObjects& o = _pts;
     o.set_program ( _prog );
     o.gen_vertex_arrays ( 1 );
     o.gen_buffers ( 2 );
     o.uniform_locations ( 2 );
     o.uniform_location ( 0, "vTransf" );
     o.uniform_location ( 1, "vLocf" );
   }

   // Define buffers needed for each of your OpenGL objects:
   { GlObjects& o = _lines;
     o.set_program ( _prog );
     o.gen_vertex_arrays ( 1 );
     o.gen_buffers ( 2 );
     o.uniform_locations ( 2 );
     o.uniform_location ( 0, "vTransf" );
     o.uniform_location ( 1, "vLocf" );
   }
 }


// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
GsVec2 AppWindow::windowToScene ( const GsVec2& v )
 {
   // GsVec2 is a lighteweight class suitable to return by value:
   return GsVec2 ( (2.0f*(v.x/float(_w))) - 1.0f,
                    1.0f - (2.0f*(v.y/float(_h))) );
 }

// Called every time there is a window event
void AppWindow::glutKeyboard ( unsigned char key, int x, int y )
 {
   switch ( key )
    { 
   
	case ' ': // space bar
	   std::cout << "Space pressed.\n";
	  
	  // a -= 0.1; b -= 0.1; c1 -= 0.1;
	   //std::cout << "a: " << a << "    b: " << b << "    c: " << c << std::endl;
	   std::cout <<"z: " << z << std::endl;
       _mark.set ( 1.5, 1.5 );
       redraw();
	   _tris.changed = true;
	   _lines.changed = true;
	   _pts.changed = true;
	   break;

	case 'r': // Press r was pressed
		waveColor = GsColor::red; waveHighlight = GsColor::red; break;

	case 'b': // Press b was pressed
		waveColor = GsColor::blue; waveHighlight = GsColor::blue; break;

	case 'g': // Press g was pressed
		waveColor = GsColor::green; waveHighlight = GsColor::green; break;


	case 'o': // Press o was pressed
		waveColor = GsColor::orange; waveHighlight = GsColor::orange; break;




	case 'y': // Press y was pressed
		waveColor = GsColor::yellow; waveHighlight = GsColor::yellow; break;


	case 'z': // Press r was pressed
		waveColor.setrandom(); waveHighlight.setrandom(); break;

		



	case 27: // Esc was pressed
	   exit(1);
	}

   redraw();
 }

void AppWindow::glutSpecial ( int key, int x, int y )
 {
   bool rd=true;
   const float incx=0.02f;
   const float incy=0.02f;
   switch ( key )
   {
   case GLUT_KEY_LEFT:  speed -= 0.001f; break;
   case GLUT_KEY_RIGHT: speed += 0.001f; break;
	  case GLUT_KEY_UP:      break;
      case GLUT_KEY_DOWN:  _mark.y-=incy; break;
      default: rd=true; // no redraw
	}

   if (rd) 
    { _lines.changed = true; // mark that new lines have to be generated
      redraw(); // ask the window to be rendered when possible
	  std::cout << "speed: " << speed << std::endl;
    }
 }

void AppWindow::glutMouse ( int b, int s, int x, int y )
 {
   _markc = GsColor::yellow;
   _mark = windowToScene ( GsVec2(x,y) );
   _lines.changed = true; // mark that new lines have to be generated
   // note: a better design would be to only change the geometry when really needed so
   // that we minimize overhead with buffer definition and transfer, for example here
   // we could just send a transformation to our shader and keep the geometry the same.
   std::cout << "x: " << _mark.x << "   y: " << _mark.y << std::endl;
   

   mouseX = _mark.x;
   mouseY = _mark.y;


   redraw();
 }

void AppWindow::glutMotion ( int x, int y )
 {
   _markc = GsColor::red;
   _mark = windowToScene ( GsVec2(x,y) );
   _lines.changed = true; // mark that new lines have to be generated
   redraw();
 }

void AppWindow::glutMenu ( int m )
 {
   std::cout<<"Menu Event: "<<m<<std::endl;
 }

void AppWindow::glutReshape ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

void AppWindow::moveM() {



	mouseX += speed;
		mouseY += speed;




	if ( w1 < 1.0 && leftRight == 1)
	{

		w1 += speed;

		w2 -= speed;

		w3x -= speed;

		w4x += speed;



		if(w4y + speed < -0.2)
		w4y += speed;

	}

	else

	{
		leftRight = 0;

	}


	if (w1 >= 0 && leftRight == 0)
	{
		w1 -= speed;
		w2 += speed;
		w3x += speed;
		w4x -= speed;


		if (w4y + speed  > -0.6)
			w4y -= speed;
	
		
		
	}
	else
	{
		leftRight = 1;
	}















	/*

	if (upDown == 1 && ((z + 13.0) + 0.02f) < 1.0)
	{
		z = z + 0.02f;
	}

	else
	{
		upDown = 0;
		z = z - 0.02f;
	}


	if (upDown == 0 && (z - 0.02f) > -1.0)
	{
		z = z - 0.02f;
	}

	else
	{
		upDown = 1;
		z = z + 0.02f;
	}

	*/
	//glutIdleFunc(NULL);
}

void AppWindow::glutIdle() {
	moveM();
	_pts.changed = true;
	_lines.changed = true;
	_tris.changed = true;
	redraw();
}

// here we will redraw the scene according to the current state of the application.
void AppWindow::buildObjects()
{
	
moveM();

	// Define a cross with some lines:
	if (_lines.changed) // needs update
	{
		_linecoords.clear(); _linecolors.clear();
		// Encode our lines in buffers according to _mark position, _markc color and size s:
		const float s = 0.05f;

		/*
		_linecoords.push_back(GsVec(_mark.x - s, _mark.y, 0)); _linecolors.push_back(_markc);
		_linecoords.push_back(GsVec(_mark.x + s, _mark.y, 0)); _linecolors.push_back(_markc);
		_linecoords.push_back(GsVec(_mark.x, _mark.y - s, 0)); _linecolors.push_back(_markc);
		_linecoords.push_back(GsVec(_mark.x, _mark.y + s, 0)); _linecolors.push_back(_markc);
		*/





		//O design
		_linecoords.push_back(GsVec(0.3f, 0.55f, -1)); _linecolors.push_back(GsColor::red);
		_linecoords.push_back(GsVec(0.5f, 0.55f, -1)); _linecolors.push_back(GsColor::red);

		_linecoords.push_back(GsVec(0.3f, 0.17f, -1)); _linecolors.push_back(GsColor::blue);
		_linecoords.push_back(GsVec(0.5f, 0.17f, -1)); _linecolors.push_back(GsColor::blue);


		_linecoords.push_back(GsVec(0.3f, 0.55f, -1)); _linecolors.push_back(GsColor::yellow);
		_linecoords.push_back(GsVec(0.3f, 0.17f, -1)); _linecolors.push_back(GsColor::yellow);


		_linecoords.push_back(GsVec(0.5f, 0.55f, -1)); _linecolors.push_back(g);
		_linecoords.push_back(GsVec(0.5f, 0.17f, -1)); _linecolors.push_back(g);


		_linecoords.push_back(GsVec(0.5f, 0.55f, -1)); _linecolors.push_back(GsColor::black);
		_linecoords.push_back(GsVec(0.4f, 0.35f, -1)); _linecolors.push_back(GsColor::black);

		_linecoords.push_back(GsVec(0.4f, 0.35f, -1)); _linecolors.push_back(GsColor::black);
		_linecoords.push_back(GsVec(0.3f, 0.55f, -1)); _linecolors.push_back(GsColor::black);

		




		//Wave highlights
		_linecoords.push_back(GsVec(-1.0f, -0.3f, 0)); _linecolors.push_back(GsColor::white);
		_linecoords.push_back(GsVec((float) w1 , -1.0f, 0)); _linecolors.push_back(GsColor::white);



		



		//--------------------------------------------------------------------------------------------------------------------------------------------------------
		//line animation

		//beam1
		_linecoords.push_back(GsVec(mouseX , mouseY, 0)); _linecolors.push_back(_markc);
		_linecoords.push_back(GsVec(mouseX + 0.1f, mouseY+ 0.1f, 0)); _linecolors.push_back(_markc);




		//--------------------------------------------------------------------------------------------------------------------------------------------------------
		//Add border to name


		//bottom border
		_linecoords.push_back(GsVec(-0.95f, -0.1f, 0)); _linecolors.push_back(g);
		_linecoords.push_back(GsVec(0.7f, -0.1f, 0)); _linecolors.push_back(g);


		//right border 

		_linecoords.push_back(GsVec(0.7f, -0.1f, 0)); _linecolors.push_back(g);
		_linecoords.push_back(GsVec( 0.7f, 0.9f, 0)); _linecolors.push_back(g);

		//top border
		_linecoords.push_back(GsVec(-0.95f, 0.9f, 0)); _linecolors.push_back(g);
		_linecoords.push_back(GsVec(0.7f, 0.9f, 0)); _linecolors.push_back(g);

		//left border
		_linecoords.push_back(GsVec(-0.95f, -0.1f, 0)); _linecolors.push_back(g);
		_linecoords.push_back(GsVec(-0.95f, 0.9f, 0)); _linecolors.push_back(g);





		// send data to OpenGL buffers:
		glBindBuffer(GL_ARRAY_BUFFER, _lines.buf[0]);
		glBufferData(GL_ARRAY_BUFFER, _linecoords.size() * 3 * sizeof(float), &_linecoords[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, _lines.buf[1]);
		glBufferData(GL_ARRAY_BUFFER, _linecolors.size() * 4 * sizeof(gsbyte), &_linecolors[0], GL_STATIC_DRAW);
		// mark that data does not need more changes:
		_lines.changed = false;
	}

	// Define some white points:
	if (_pts.changed) // needs update
	{
		_ptcoords.clear(); _ptcolors.clear();
		// Encode some white points in buffers:

		/*
		_ptcoords.push_back(GsVec(0.5, 0.5, 0.0)); _ptcolors.push_back(GsColor::white);
		_ptcoords.push_back(GsVec(-0.5, -0.5, 0.0)); _ptcolors.push_back(GsColor::white);
		_ptcoords.push_back(GsVec(0.5, -0.5, 0.0)); _ptcolors.push_back(GsColor::white);
		_ptcoords.push_back(GsVec(-0.5, 0.5, 0.0)); _ptcolors.push_back(GsColor::white);
		*/



		_ptcoords.push_back(GsVec(w1 ,  w1 , 0.0)); _ptcolors.push_back(GsColor::white);

		_ptcoords.push_back(GsVec(w1 - 0.1, w1, 0.0)); _ptcolors.push_back(GsColor::white);


		_ptcoords.push_back(GsVec(w1 + 0.3, w1, 0.0)); _ptcolors.push_back(GsColor::white);



		_ptcoords.push_back(GsVec(w1 - 0.5, w1, 0.0)); _ptcolors.push_back(GsColor::white);


		_ptcoords.push_back(GsVec(w1 - 0.9, w1, 0.0)); _ptcolors.push_back(GsColor::white);



		_ptcoords.push_back(GsVec(w1 - 0.9, w1, 0.0)); _ptcolors.push_back(GsColor::white);


		_ptcoords.push_back(GsVec(w1 - 0.7, w1, 0.0)); _ptcolors.push_back(GsColor::white);




		// send data to OpenGL buffers:
		glBindBuffer(GL_ARRAY_BUFFER, _pts.buf[0]);
		glBufferData(GL_ARRAY_BUFFER, _ptcoords.size() * 3 * sizeof(float), &_ptcoords[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, _pts.buf[1]);
		glBufferData(GL_ARRAY_BUFFER, _ptcolors.size() * 4 * sizeof(gsbyte), &_ptcolors[0], GL_STATIC_DRAW);
		// mark that data does not need more changes:
		_pts.changed = false;
	}

	// Define some triangles:
	if (_tris.changed) // needs update
	{
		_tricoords.clear(); _tricolors.clear();


		//Code for the waves

	







		/*
		double a = -0.9;
		double b = -0.8;
		double c1 = -0.7;
		*/





		//M

		//black

		/*
		_tricoords.push_back(GsVec(a, z, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(b, z + 13.0, 0.0));  _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(c1, z, 0.0));  _tricolors.push_back(GsColor::black);



		// Encode some overlapping triangles, red:
		_tricoords.push_back(GsVec(a, z + 4.0, 0.0)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(b, z + 17.0, 0.0));  _tricolors.push_back(c);
		_tricoords.push_back(GsVec(c1, z + 4.0, 0.0));  _tricolors.push_back(c);


		//black
		_tricoords.push_back(GsVec(a + 0.2, z, 0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(b + 0.2, z + 13.0, -0.1));  _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(c1 + 0.2, z, -0.1));  _tricolors.push_back(GsColor::black);



		// green:
		_tricoords.push_back(GsVec(a + 0.2, z + 4.0, 0.1)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(b + 0.2, z + 17.0, -0.1)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(c1 + 0.2, z + 4.0, -0.1)); _tricolors.push_back(c);*/



		

		//M

		/*
		//black
		_tricoords.push_back(GsVec(-0.9, z, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.8, z + 13.0, 0.0));  _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.7, z, 0.0));  _tricolors.push_back(GsColor::black);



		// Encode some overlapping triangles, red:
		_tricoords.push_back(GsVec(-0.9, -0.5, 0.0)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.8, 0.8, 0.0));  _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.7, -0.5, 0.0));  _tricolors.push_back(c);


		//black
		_tricoords.push_back(GsVec(-0.7, -0.9, 0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.6, 0.4, -0.1));  _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.5, -0.9, -0.1));  _tricolors.push_back(GsColor::black);



		// green:
		_tricoords.push_back(GsVec(-0.7, -0.5, 0.1)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.6, 0.8, -0.1)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.5, -0.5, -0.1)); _tricolors.push_back(c);
		


		*/







		
		
		//M

		//black
		_tricoords.push_back(GsVec(z, -0.25, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.8, 0.4, 0.0));  _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.7, -0.25, 0.0));  _tricolors.push_back(GsColor::black);


		
		// Encode some overlapping triangles, red:
		_tricoords.push_back(GsVec(-0.9, -0.03, 0.0)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.8, 0.8, 0.0));  _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.7, -0.03, 0.0));  _tricolors.push_back(c);


		//black
		_tricoords.push_back(GsVec(-0.7, -0.25, 0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.6, 0.4, -0.1));  _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.5, -0.25, -0.1));  _tricolors.push_back(GsColor::black);


	
		// green:
		_tricoords.push_back(GsVec(-0.7, -0.03, 0.1)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.6, 0.8, -0.1)); _tricolors.push_back(c);
		_tricoords.push_back(GsVec(-0.5, -0.03, -0.1)); _tricolors.push_back(c);
		

		

		//--------------------------------------------------------------------------------------------------


		// A:

		_tricoords.push_back(GsVec(-0.4, -0.03, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.3, 0.6, -0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.2, -0.03, -0.1)); _tricolors.push_back(GsColor::black);

		
		_tricoords.push_back(GsVec(-0.4, -0.03, 0.0)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(-0.3, 0.8, -0.1)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(-0.2, -0.03, -0.1)); _tricolors.push_back(GsColor::white);

		
		/*
		_tricoords.push_back(GsVec(-0.4, -0.5, 0.0)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(-0.3, 0.8, -0.1)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(-0.2, -0.5, -0.1)); _tricolors.push_back(GsColor::white);
	
		_tricoords.push_back(GsVec(-0.35, -0.5, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.3, 0.6, -0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(-0.2, -0.5, -0.1)); _tricolors.push_back(GsColor::black);



		*/

		// J:





		_tricoords.push_back(GsVec(-0.14, 0.35, 0.0)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(-0.08, -0.02, -0.1)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(-0.09, .35, -0.1)); _tricolors.push_back(GsColor::blue);

		_tricoords.push_back(GsVec(-0.0, 0.35, 0.0)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(-0.08, -0.02, -0.1)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(0.06, .35, -0.1)); _tricolors.push_back(GsColor::blue);

		_tricoords.push_back(GsVec(-0.0, 0.35, 0.0)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(0.03, 0.8, -0.1)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(0.06, .35, -0.1)); _tricolors.push_back(GsColor::blue);





		/*
			_tricoords.push_back(GsVec(-0.1, 0.15, 0.0)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(0.0, -0.5, -0.1)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(0.1, 0.15, -0.1)); _tricolors.push_back(GsColor::blue);


		_tricoords.push_back(GsVec(0.0, 0.15, 0.0)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(0.05, 0.6, -0.1)); _tricolors.push_back(GsColor::blue);
		_tricoords.push_back(GsVec(0.1, 0.15, -0.1)); _tricolors.push_back(GsColor::blue);



		_tricoords.push_back(GsVec(-0.05, 0.15, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(0.015, -0.6, -0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(0.0, 0.15, -0.1)); _tricolors.push_back(GsColor::black);

		*/


		// O:


		_tricoords.push_back(GsVec(0.2, 0.35, 0.0)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(0.4, 0.8, -0.1)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(0.6, 0.35, -0.1)); _tricolors.push_back(GsColor::white);


		_tricoords.push_back(GsVec(0.2, 0.35, 0.0)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(0.4, -0.05, -0.1)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(0.6, 0.35, -0.1)); _tricolors.push_back(GsColor::white);


	






		//Draw waves

		//left wave
		_tricoords.push_back(GsVec(w1, -1.0, 0.0));  _tricolors.push_back(waveColor);
		_tricoords.push_back(GsVec(-1.0, -0.3, 0.0)); _tricolors.push_back(waveColor);
		_tricoords.push_back(GsVec(-1.0, -1.0, 0.0));  _tricolors.push_back(waveColor);


		//left wave reflection




		//right wave
		_tricoords.push_back(GsVec(w2, -1.0, 0.0));  _tricolors.push_back(waveHighlight);
		_tricoords.push_back(GsVec(1.0, -0.3, 0.0)); _tricolors.push_back(waveHighlight);
		_tricoords.push_back(GsVec(1.0, -1.0, 0.0)); _tricolors.push_back(waveHighlight);


		//right highlight
		_tricoords.push_back(GsVec(w2 - 0.4f, -1.0, 0.0));  _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(1.0, -0.3, 0.0)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(1.0, -1.0, 0.0));  _tricolors.push_back(GsColor::white);




		//moving center wave


		//wave
		_tricoords.push_back(GsVec(w3x, -1.0, 0.0));  _tricolors.push_back(waveColor);
		_tricoords.push_back(GsVec(w3x + 0.8,  w3y, 0.0)); _tricolors.push_back(waveColor);
		_tricoords.push_back(GsVec(w3x + 1.6, -1.0, 0.0));  _tricolors.push_back(waveColor);

		//highlight
		_tricoords.push_back(GsVec(w3x - 0.4f, -1.0, 0.0));  _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(w3x + 0.8, w3y, 0.0)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(w3x + 1.6, -1.0, 0.0));  _tricolors.push_back(GsColor::white);




		//wave
		_tricoords.push_back(GsVec(w4x, -1.0, 0.0));  _tricolors.push_back(waveColor);
		_tricoords.push_back(GsVec(w4x + 0.8, w4y, 0.0)); _tricolors.push_back(waveColor);
		_tricoords.push_back(GsVec(w4x + 1.6, -1.0, 0.0));  _tricolors.push_back(waveColor);

		//highlight
		_tricoords.push_back(GsVec(w4x - 0.4f, -1.0, 0.0));  _tricolors.push_back(waveHighlight);
		_tricoords.push_back(GsVec(w4x + 0.8, w4y, 0.0)); _tricolors.push_back(waveHighlight);
		_tricoords.push_back(GsVec(w4x + 1.6, -1.0, 0.0)); _tricolors.push_back(waveHighlight);




		



/*
		_tricoords.push_back(GsVec(0.25, 0.35, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(0.4, 0.5, -0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(0.6, 0.35, -0.1)); _tricolors.push_back(GsColor::black);


		_tricoords.push_back(GsVec(0.2, 0.1, 0.0)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(0.4, -0.4, -0.1)); _tricolors.push_back(GsColor::black);
		_tricoords.push_back(GsVec(0.6, 0.1, -0.1)); _tricolors.push_back(GsColor::black);
		*/




		/*
		_tricoords.push_back(GsVec(-0.4, -0.5, 0.0)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(-0.3, 0.8, -0.1)); _tricolors.push_back(GsColor::white);
		_tricoords.push_back(GsVec(-0.2, -0.5, -0.1)); _tricolors.push_back(GsColor::white);
		*/
		

	


		



		// send data to OpenGL buffers:
		glBindBuffer(GL_ARRAY_BUFFER, _tris.buf[0]);
		glBufferData(GL_ARRAY_BUFFER, _tricoords.size() * 3 * sizeof(float), &_tricoords[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, _tris.buf[1]);
		glBufferData(GL_ARRAY_BUFFER, _tricolors.size() * 4 * sizeof(gsbyte), &_tricolors[0], GL_STATIC_DRAW);
		// mark that data does not need more changes:
		_tris.changed = false;

	}
 }

void AppWindow::glutDisplay ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Update objects if needed:
   buildObjects();

   // Define some identity transformations - our shaders require them but in this
   // example code we do not need to use them, so just let them be GsMat::id:
   GsMat vtransf(GsMat::id), vproj(GsMat::id); // transformations

   // Draw Lines:
   glUseProgram ( _lines.prog );
   glBindVertexArray ( _lines.va[0] );

   glBindBuffer ( GL_ARRAY_BUFFER, _lines.buf[0] ); // positions
   glEnableVertexAttribArray ( 0 );
   glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

   glBindBuffer ( GL_ARRAY_BUFFER, _lines.buf[1] ); // colors
   glEnableVertexAttribArray ( 1 );
   glVertexAttribPointer ( 1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0 );

   glUniformMatrix4fv ( _lines.uniloc[0], 1, GL_FALSE, vtransf.e );
   glUniformMatrix4fv ( _lines.uniloc[1], 1, GL_FALSE, vproj.e );

   glDrawArrays ( GL_LINES, 0, _linecoords.size() );
   // (see documentation at: https://www.opengl.org/sdk/docs/man/html/glDrawArrays.xhtml)

   // Draw Points:
   glUseProgram ( _pts.prog );
   glBindVertexArray ( _pts.va[0] );

   glBindBuffer ( GL_ARRAY_BUFFER, _pts.buf[0] ); // positions
   glEnableVertexAttribArray ( 0 );
   glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

   glBindBuffer ( GL_ARRAY_BUFFER, _pts.buf[1] ); // colors
   glEnableVertexAttribArray ( 1 );
   glVertexAttribPointer ( 1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0 );

   glUniformMatrix4fv ( _pts.uniloc[0], 1, GL_FALSE, vtransf.e );
   glUniformMatrix4fv ( _pts.uniloc[1], 1, GL_FALSE, vproj.e );

   glDrawArrays ( GL_POINTS, 0, _ptcoords.size() );

   // Draw Triangles:
   glUseProgram ( _tris.prog );
   glBindVertexArray ( _tris.va[0] );

   glBindBuffer ( GL_ARRAY_BUFFER, _tris.buf[0] ); // positions
   glEnableVertexAttribArray ( 0 );
   glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

   glBindBuffer ( GL_ARRAY_BUFFER, _tris.buf[1] ); // colors
   glEnableVertexAttribArray ( 1 );
   glVertexAttribPointer ( 1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0 );

   glUniformMatrix4fv ( _tris.uniloc[0], 1, GL_FALSE, vtransf.e );
   glUniformMatrix4fv ( _tris.uniloc[1], 1, GL_FALSE, vproj.e );

   glDrawArrays ( GL_TRIANGLES, 0, _tricoords.size() );

   // Swap buffers and draw:
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

