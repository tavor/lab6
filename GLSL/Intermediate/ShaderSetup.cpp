// ShaderSetup.cpp
//
// Sets up a shader based on supplied source files
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


//
// Read a text file
//
// Returns the contents of the file in a dynamically-allocated
// string buffer, or NULL if an error occurs.
//

static GLchar *readTextFile( const char *name ) {
	FILE *fp;
	GLchar *content = NULL;
	int count=0;

	if( name != NULL ) {

		// Attempt to open the file
		fp = fopen( name, "rt" );
		if( fp != NULL ) {

			// Determine its length
			fseek( fp, 0, SEEK_END );
			count = ftell( fp );
			rewind( fp );

			if( count > 0 ) {

				// Allocate the string buffer
				content = (GLchar *) malloc(
						sizeof(char) * (count+1) );
				// Read the file into the buffer
				count = fread( content, sizeof(char),
						count, fp );
				// Add a NUL terminator
				content[count] = '\0';
			}

			fclose(fp);
		} else {
			perror( name );
		}
	} else {
		fprintf( stderr, "error:  no file name specified\n" );
	}

	return( content );

}

//
// Print the information log from a shader compilation attempt
//

static int print_shader_info_log( const char *msg, GLuint shader ) {
	GLint length = 0;
	GLsizei nchars  = 0;
	char *log;

	// Determine the length of the information log
	glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length );

	if( length > 0 ) {

		// Allocate a buffer for the log
		log = (char *) malloc( length );

		if( log != NULL ) {

			// Retrieve the log
			glGetShaderInfoLog( shader, length, &nchars, log );

			// Report it
			if( log[0] != '\0' ) {
				printf( "%s shader log:  '%s'\n", msg, log );
				return( 1 );
			}

			free( log );
		}


	}

	return( 0 );

}

//
// Print a program information log
//
// This is identical to print_shader_info_log(), except that it uses
// glGetProgramiv() and glGetProgramInfoLog() instead of the *Shader*()
// versions.
//

static int print_program_info_log( const char *msg, GLuint shader ) {
	GLint length = 0;
	GLsizei nchars  = 0;
	char *log;

	// Determine the length of the information log
	glGetProgramiv( shader, GL_INFO_LOG_LENGTH, &length );

	if( length > 0 ) {

		// Allocate a buffer for the log
		log = (char *) malloc( length );

		if( log != NULL ) {

			// Retrieve the log
			glGetProgramInfoLog( shader, length, &nchars, log );

			// Report it
			if( log[0] != '\0' ) {
				printf( "Program %s log:  '%s'\n", msg, log );
				return( 1 );
			}

			free( log );
		}

	}

	return( 0 );

}


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

GLuint ShaderSetup( const char *vert, const char *frag ) {
	GLchar *vsrc = NULL, *fsrc = NULL;
	GLuint vs, fs, prog;
	
	// Create the shader handles
	vs = glCreateShader( GL_VERTEX_SHADER );
	fs = glCreateShader( GL_FRAGMENT_SHADER );
	
	// Read in shader source
	vsrc = readTextFile( vert );
	if( vsrc == NULL ) {
		fprintf( stderr, "Error reading vertex shader file %s\n",
			 vert);
		return( 0 );
	}

	fsrc = readTextFile( frag );
	if( fsrc == NULL ) {
		fprintf( stderr, "Error reading fragment shader file %s\n",
			 frag);
		free( vsrc );
		return( 0 );
	}

	// Attach the source to the shaders
	glShaderSource( vs, 1, (const GLchar **) &vsrc, NULL );
	glShaderSource( fs, 1, (const GLchar **) &fsrc, NULL );

	// We're done with the source code now
	free(vsrc);
	free(fsrc);
	
	// Compile the shaders and report any problems
	glCompileShader( vs );
	if( print_shader_info_log("Vertex",vs) ) {
		fputs( "Error in vertex shader compilation\n", stderr );
		exit( EXIT_FAILURE );
	}

	glCompileShader( fs );
	if( print_shader_info_log("Fragment",fs) ) {
		fputs( "Error in fragment shader compilation\n", stderr );
		exit( EXIT_FAILURE );
	}
	
	// Create the program and attach the shaders
	prog = glCreateProgram();
	glAttachShader( prog, vs );
	glAttachShader( prog, fs );

	// Report any problems that occurred
	if( print_program_info_log("attach",prog) ) {
		fputs( "Error attaching shader\n", stderr );
		exit( EXIT_FAILURE );
	}
	
	// Link the program
	glLinkProgram( prog );

	// Again, report any errors
	if( print_program_info_log("link",prog) ) {
		fputs( "Error linking program\n", stderr );
		exit( EXIT_FAILURE );
	}
	
	return( prog );

}
