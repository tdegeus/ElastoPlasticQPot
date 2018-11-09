/* =================================================================================================

(c - MIT) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/ElastoPlasticQPot

================================================================================================= */

#ifndef XELASTOPLASTICQPOT_H
#define XELASTOPLASTICQPOT_H

// -------------------------------------------------------------------------------------------------

// use "M_PI" from "math.h"
#define _USE_MATH_DEFINES

#include <tuple>
#include <stdexcept>
#include <limits>
#include <math.h>
#include <iostream>
#include <vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xnoalias.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xfixed.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xview.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xoperation.hpp>
#include <xtensor/xsort.hpp>
#include <xtensor/xmath.hpp>

// -------------------------------------------------------------------------------------------------

// dummy operation that can be use to suppress the "unused parameter" warnings
#define UNUSED(p) ( (void)(p) )

// -------------------------------------------------------------------------------------------------

#define ELASTOPLASTICQPOT_WORLD_VERSION 0
#define ELASTOPLASTICQPOT_MAJOR_VERSION 1
#define ELASTOPLASTICQPOT_MINOR_VERSION 2

#define ELASTOPLASTICQPOT_VERSION_AT_LEAST(x,y,z) \
  (ELASTOPLASTICQPOT_WORLD_VERSION>x || (ELASTOPLASTICQPOT_WORLD_VERSION>=x && \
  (ELASTOPLASTICQPOT_MAJOR_VERSION>y || (ELASTOPLASTICQPOT_MAJOR_VERSION>=y && \
                                         ELASTOPLASTICQPOT_MINOR_VERSION>=z))))

#define ELASTOPLASTICQPOT_VERSION(x,y,z) \
  (ELASTOPLASTICQPOT_WORLD_VERSION==x && \
   ELASTOPLASTICQPOT_MAJOR_VERSION==y && \
   ELASTOPLASTICQPOT_MINOR_VERSION==z)

// -------------------------------------------------------------------------------------------------

#include "Cartesian2d.h"
#include "Cartesian2d.hpp"
#include "Cartesian2d_Elastic.hpp"
#include "Cartesian2d_Cusp.hpp"
#include "Cartesian2d_Smooth.hpp"
#include "Cartesian2d_Matrix.hpp"

// -------------------------------------------------------------------------------------------------

#endif
