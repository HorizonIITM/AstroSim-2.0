#pragma once
/*
 * UTILS.H
 */
#ifndef UTILS_H_
#define UTILS_H_

#include "../defs.h"
#include <cmath>
#include "vector3.h"

long double Q_rsqrt(long double);
double      Q_rsqrt(double);

valtype distSquare(vector3 const &p1, vector3 const &p2);
#endif