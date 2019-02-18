/**************************************************
 *
 *                 Shaders.h
 *
 *  Utility functions that make constructing shaders
 *  a bit easier.
 *
 ***************************************************/

int buildShader(int type, char *filename);
int buildProgram(int first, ...);
int linkProgram(int program);
void dumpProgram(int program, char *description);