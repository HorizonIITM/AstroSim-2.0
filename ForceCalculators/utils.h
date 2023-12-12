#pragma once
/*
 * UTILS.H
 */
#ifndef UTILS_H_
#define UTILS_H_

#include "../defs.h"
#include <vector>
#include <cmath>

long double Q_rsqrt(long double);
double      Q_rsqrt(double);

valtype distSquare(std::vector<valtype> const &p1, std::vector<valtype> const &p2);
#endif