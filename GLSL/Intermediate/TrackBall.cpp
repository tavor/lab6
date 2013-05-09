/*
** TrackBall.cpp
**
** These functions implement a simple trackball-like motion control.
*/

#include <math.h>
#include <cstdlib>
#include <unistd.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "TrackBall.h"

float	angle		= 0.0;
float	axis[3];
float	lastPosition[3]	= { 0.0F, 0.0F, 0.0F };
float	trans[3];

bool	redrawContinue	= false;
bool	trackballMove	= false;
bool	trackingMouse	= false;

// these are globals found in the driver program

extern int currentX;
extern int currentY;
extern int startX;
extern int startY;
extern int windowHeight;
extern int windowWidth;

void trackball_ptov( int x, int y, int width, int height, float v[3] ) {

	float 	d;
	float 	a;

	// Project x,y onto a hemi-sphere centered within width, height
	v[0] =  ( 2.0F * x - width ) / width;
	v[1] =  ( height - 2.0F * y ) / height;

	d    =  (float) sqrt( v[0] * v[0] + v[1] * v[1] );
	v[2] =  (float) cos( ( 3.1415 / 2.0F ) * ( ( d < 1.0F ) ? d : 1.0F ) );

	a    =  1.0F / (float) sqrt( v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;

}

/*
 * Idle callback function
 */

void spinCube( void ) {

	if( redrawContinue )
		glutPostRedisplay();

}

/*
 * Callback function for when mouse is in motion
 */

void mouseMotion( int x, int y ) {

	float 	currentPosition[3];
	float 	dx;
	float 	dy;
	float 	dz;

	trackball_ptov( x, y, windowWidth, windowHeight, currentPosition );

	if( trackingMouse ) {

		dx = currentPosition[0] - lastPosition[0];
		dy = currentPosition[1] - lastPosition[1];
		dz = currentPosition[2] - lastPosition[2];

		if (dx || dy || dz) {

			angle = 90.0F * sqrt( dx * dx + dy * dy + dz * dz );

			axis[0] = lastPosition[1] * currentPosition[2]
				  - lastPosition[2] * currentPosition[1];
			axis[1] = lastPosition[2] * currentPosition[0]
				  - lastPosition[0] * currentPosition[2];
			axis[2] = lastPosition[0] * currentPosition[1]
				  - lastPosition[1] * currentPosition[0];

			lastPosition[0] = currentPosition[0];
			lastPosition[1] = currentPosition[1];
			lastPosition[2] = currentPosition[2];

		}

	}

	glutPostRedisplay();

}


/*
 * Function for when motion is beginning
 */

void startMotion( int x, int y ) {

	trackingMouse  = true;
	redrawContinue = false;

	startX 	   = x;
	startY 	   = y;

	currentX 	   = x;
	currentY 	   = y;

	trackballMove  = true;
	trackball_ptov( x, y, windowWidth, windowHeight, lastPosition );

}


/*
 * Function for when motion is ending
 */

void stopMotion( int x, int y ) {

	trackingMouse = false;

	if ( startX != x || startY != y ) {

		redrawContinue = true;

	} else {

		angle          = 0.0F;
		redrawContinue = false;
		trackballMove  = false;

	}

}

/*
 * Callback function for mouse interaction
 */

void mouseButton( int button, int state, int x, int y ) {

	if( button==GLUT_RIGHT_BUTTON )
		exit( 0 );

	if( button==GLUT_LEFT_BUTTON )
		switch( state ) {

			case GLUT_DOWN:
				y=windowHeight - y;
				startMotion( x, y );
				break;

			case GLUT_UP:
				stopMotion( x, y );
				break;

		}

}
