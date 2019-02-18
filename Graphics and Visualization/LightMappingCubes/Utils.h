#ifndef UTILS_H
#define UTILS_H

#define PI 3.141592
inline float DEG2RAD(float deg) { return (PI * deg / 180.0f); }
inline float RAD2DEG(float rad) { return (rad * (180.0 / PI)); }

#endif