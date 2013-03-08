#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

double log_sum(double log_a, double log_b);
double trigamma(double x);
double digamma(double x);
void make_directory(const std::string & name);
int argmax(double* x, int n);
int map_idx(int row, int col, int dim); 

#endif

