//
// Set up a GLSL shader program.
//
// Requires the name of a vertex program and a fragment
// program.  Returns a handle to the created GLSL program
//
// Arguments:
//	vert - vertex shader program source file
//	frag - fragment shader program source file
//

#ifndef _SHADERSETUP_H_
#define _SHADERSETUP_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

GLuint ShaderSetup( const char *vert, const char *frag );

#endif
