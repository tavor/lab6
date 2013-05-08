/*
** TrackBall
**
** These functions implement a simple trackball-like motion control.
*/

#ifndef _TRACKBALL_H_
#define _TRACKBALL_H_

extern float angle;
extern float axis[3];
extern bool trackballMove;

void trackball_ptov( int x, int y, int width, int height, float v[3] );
void spinCube( void );
void mouseMotion( int x, int y );
void startMotion( int x, int y );
void stopMotion( int x, int y );
void mouseButton( int button, int state, int x, int y );

#endif
