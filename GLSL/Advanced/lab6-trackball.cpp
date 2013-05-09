/* 
 * lab6-trackball.cpp
 *
 * Template application for Procedural Shading textures lab.
 *
 * This version uses the trackball simulation code in TrackBall.cpp.
 *
 */

#include <math.h>
#include <assert.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "ShaderSetup.h"

#define	bool	int
#define	false	0
#define	true	1

int	currentX;		// Current location of X
int	currentY;		// Current location of Y
int	startX;			// Starting location of X
int	startY;			// Starting location of Y
int	windowHeight;		// Current height of window
int	windowWidth;		// Current width of window

#include "TrackBall.h"

// handle for our shader
GLuint texShader;

// Scene will mimic the basic scene used in RenderMan exercises
//  Vertices and colors for drawing the objects in the scene
GLfloat WallColors[][3] = {
    { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, 
    { 1.0, 0.0, 0.0 }
};

GLfloat WallVertices[][3] = {
    { -5.0,  5.0,  0.0 }, {  5.0, 5.0,  0.0 }, { 5.0,  -5.0,  0.0 }, 
    { -5.0,  -5.0,  0.0 }
};

GLfloat WallTexCoords[][2] = {
    { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 }
};

GLfloat FloorColors[][3] = {
    { 1.0, 1.0, 0.5 }, { 1.0, 1.0, 0.5 }, { 1.0, 1.0, 0.5 }, 
    { 1.0, 1.0, 0.5 }
};

GLfloat FloorVertices[][3] = {
    { -5.0, -5.0,  5.0 }, {  5.0, -5.0,  5.0 }, { 5.0,  -5.0,  -5.0 }, 
    { -5.0, -5.0, -5.0 }
};

GLUquadricObj *sphere1 = NULL;
GLUquadricObj *sphere2 = NULL;
GLUquadricObj *sphere3 = NULL;
GLUquadricObj *sphere4 = NULL;


// Some global material properties
GLfloat no_mat[]            = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[]       = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.5, 0.5, 0.05, 1.0 };
GLfloat mat_diffuse[]       = { 0.5, 0.5, 0.05, 1.0 };
GLfloat mat_specular[]      = { 0.8, 0.8, 0.8, 1.0 };
GLfloat no_shininess[]      = { 0.0 };
GLfloat low_shininess[]     = { 5.0 };
GLfloat high_shininess[]    = { 100.0 };
GLfloat mat_emission[]      = { 0.3, 0.2, 0.2, 0.0 };

GLfloat mat_yellow[]        = { 0.8, 0.8, 0.6, 1.0 };
GLfloat mat_red[]           = { 0.5, 0.0, 0.0, 1.0 };
GLfloat mat_green[]         = { 0.0, 0.5, 0.0, 1.0 };
GLfloat mat_blue[]          = { 0.0, 0.0, 0.5, 1.0 };


GLfloat cam_Position[]      = { 0.0, 15.0, -11.0 };
GLfloat fudgeFactor          = 50.0;
GLfloat fudgeExponent            = 32.0;
GLfloat stepsize            = 0.1;
/*
 *  The function draws your scene.  It should also apply the shader
 *  and attach it to the correct primitives.
 */

void drawscene( void ) {
    GLfloat loc;
    
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Insert code here to use your shader
    glUseProgram (texShader);
    
    // Set eye position into shader
    loc = glGetUniformLocation(texShader, "eye");
    glUniform3f(loc, cam_Position[0], cam_Position[1], cam_Position[2]);
    
    // Send in from, to, intensity, field, and beam along with boolean for distance attentuation
    loc = glGetUniformLocation(texShader, "fudgeFactor");
    glUniform1f(loc, fudgeFactor);
    
    loc = glGetUniformLocation(texShader, "fudgeExponent");
    glUniform1f(loc, fudgeExponent);
    
    loc = glGetUniformLocation(texShader, "stepsize");
    glUniform1f(loc, fudgeExponent);

	// common material properties
	glMaterialfv( GL_FRONT, GL_SPECULAR,  mat_specular );
	glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
	glMaterialfv( GL_FRONT, GL_EMISSION,  no_mat );		

	// the yellow sphere
	if (!sphere1) {
		sphere1 = gluNewQuadric();
		gluQuadricDrawStyle(sphere1, GLU_FILL);
	}

	glPushMatrix();
	  glTranslatef (0.0, 0.0, 0.0);

	  // Apply material properties here and then use your
	  // shader program.
	  glMaterialfv( GL_FRONT, GL_AMBIENT, mat_yellow );
	  glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_yellow );

	  gluSphere (sphere1, 2, 100, 100);
	glPopMatrix();

	// the red sphere
	if (!sphere2) {
		sphere2 = gluNewQuadric();
		gluQuadricDrawStyle(sphere2, GLU_FILL);
	}

	glPushMatrix();
	  glTranslatef (-5.0, 0.0, 3.0);

	  // Apply material properties here and then use your
	  // shader program.
	  glMaterialfv( GL_FRONT, GL_AMBIENT, mat_red );
	  glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_red );

	  gluSphere (sphere2, 2, 100, 100);
	glPopMatrix();

	// the green sphere
	if (!sphere3) {
		sphere3 = gluNewQuadric();
		gluQuadricDrawStyle(sphere3, GLU_FILL);
	}

	glPushMatrix();
	  glTranslatef (4.0, 0.0, 6.0);

	  // Apply material properties here and then use your
	  // shader program.
	  glMaterialfv( GL_FRONT, GL_AMBIENT, mat_green );
	  glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_green );

	  gluSphere (sphere3, 2, 100, 100);
	glPopMatrix();

	// the blue sphere
	if (!sphere4) {
		sphere4 = gluNewQuadric();
		gluQuadricDrawStyle(sphere4, GLU_FILL);
	}

	glPushMatrix();
	  glTranslatef (0.0, 0.0, 8.0);

	  // Apply material properties here and then use your
	  // shader program.
	  glMaterialfv( GL_FRONT, GL_AMBIENT, mat_blue );
	  glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_blue );

	  gluSphere (sphere4, 2, 100, 100);
	glPopMatrix();

}


/*
 * Display callback function - used for redisplay as well
 */

void display( void ) {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// View transform 
	if ( trackballMove ) {
		glRotatef( angle, axis[0], axis[1], axis[2] );
	}

	drawscene();

	glutSwapBuffers();

}



/*
 * Callback function for screen window resizing/reshaping
 */

void myReshape( int width, int height ) {

	glViewport( 0, 0, width, height );
	windowWidth = width;
	windowHeight = height;

}


/*
 *  OpenGL initialization
 */

void init( void ) {

	// lighting params
	GLfloat ambient[]        = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[]        = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[]       = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[]       = { 0.0, 10.0, -8.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[]     = { 0.0 };

	glClearColor( 0.0, 0.1, 0.1, 0.0 );

	// enable depth testing
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );

	// some basic lighting setup
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_POSITION, position );
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel_ambient );
	glLightModelfv( GL_LIGHT_MODEL_LOCAL_VIEWER, local_view );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	// Camera stuff - matrix initialization
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective (45, 1.0, 1.0, 100.0);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	gluLookAt (0.0, 15.0, -11.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// set up your shaders with code like this:
	//
	texShader = ShaderSetup( "fog.vert", "fog.frag" );
	if( texShader == 0 ) {
	      fputs( "Error in shader setup - exiting\n", stderr );
	      exit( 1 );
	}

}


/*
 * Main routine - GLUT setup and initialization
 */

int main( int argc, char **argv ) {

	// Initialize GLUT
	glutInit( &argc, argv );

	// Enable double buffering and depth buffering
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( argv[0] );

	// Callback functions are specified 
	glutReshapeFunc( myReshape );
	glutDisplayFunc( display );
	glutIdleFunc( spinCube );
	glutMouseFunc( mouseButton );
	glutMotionFunc( mouseMotion );

	// Do OpenGL initialization
	init();
	
	// enter your display loop.
	glutMainLoop();
	
	return 0;
}
