#ifndef CHAOSEQUATIONS_OPENGL_H
#define CHAOSEQUATIONS_OPENGL_H

//#define GLFW_INCLUDE_GLU

#if defined(__APPLE__)
// Yoinked from the beginning of glfw. Apple warns if gl.h and gl3.h are both included:
// warning: gl.h and gl3.h are both included.  Compiler will not invoke errors if using removed OpenGL functionality.

#include <OpenGL/gl3.h>

// glu includes gl.h, so if I end up using glu, I'll have to define this
//#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#ifdef GLFW_INCLUDE_GLU
#include <OpenGL/glu.h>
#endif

// disable glfw including gl.h on its own
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#endif // CHAOSEQUATIONS_OPENGL_H
