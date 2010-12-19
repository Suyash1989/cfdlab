/*
 *  interpolate_1d.cc
 *  uqtool
 *
 *  Created by Praveen Chandrashekar on 16/12/10.
 *  Copyright 2010 TIFR-CAM, Bangalore. All rights reserved.
 *
 */

#include <iostream>
#include <cassert>
#include "interpolate.h"

using namespace std;

// Lagrange interpolate of primal and adjoint solution in 1-D
template <>
void Interpolate<1>::execute (const double* x)
{
   // TBD Later, we will implement linear elements also
   assert (order == 2);
   
   double a0, a1, a2;
   unsigned int n = n_var * n_cell;

   // Linear interpolation
   a0 = (x[0] - dof[1]->x[0]) / (dof[0]->x[0] - dof[1]->x[0]);
   a1 = (x[0] - dof[0]->x[0]) / (dof[1]->x[0] - dof[0]->x[0]);
   
   for(unsigned int i=0; i<n; ++i)
   {
      primal1[i]  = a0 * dof[0]->primal[i] +
                    a1 * dof[1]->primal[i];
      adjoint1[i] = a0 * dof[0]->adjoint[i] +
                    a1 * dof[1]->adjoint[i];
   }

   // Quadratic interpolation
   a0 = (x[0] - dof[1]->x[0]) * (x[0] - dof[2]->x[0]);
   a0 = a0 / (dof[0]->x[0] - dof[1]->x[0]);
   a0 = a0 / (dof[0]->x[0] - dof[2]->x[0]);
   a1 = (x[0] - dof[0]->x[0]) * (x[0] - dof[2]->x[0]);
   a1 = a1 / (dof[1]->x[0] - dof[0]->x[0]);
   a1 = a1 / (dof[1]->x[0] - dof[2]->x[0]);
   a2 = (x[0] - dof[0]->x[0]) * (x[0] - dof[1]->x[0]);
   a2 = a2 / (dof[2]->x[0] - dof[0]->x[0]);
   a2 = a2 / (dof[2]->x[0] - dof[1]->x[0]);
   
   for(unsigned int i=0; i<n; ++i)
   {
      primal2[i]  = a0 * dof[0]->primal[i] +
                    a1 * dof[1]->primal[i] +
                    a2 * dof[2]->primal[i];
      adjoint2[i] = a0 * dof[0]->adjoint[i] +
                    a1 * dof[1]->adjoint[i] +
                    a2 * dof[2]->adjoint[i];
   }
   
}
