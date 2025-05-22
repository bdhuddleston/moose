//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

// MOOSE includes
#include "LayeredVolumeIntegralBase.h"
#include "ElementIntegralVariableUserObject.h"

/**
 * This UserObject computes volume integrals of a variable storing partial sums for the specified
 * number of intervals in a direction (x,y,z).
 */
class LayeredIntegral : public LayeredVolumeIntegralBase<ElementIntegralVariableUserObject>
{
public:
  static InputParameters validParams();

  LayeredIntegral(const InputParameters & parameters);
};
