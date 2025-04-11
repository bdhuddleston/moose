//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "LayeredSideAverageBase.h"
#include "SideIntegralFunctorUserObject.h"

/**
 * Computes layered side averages of a functor.
 */
class LayeredSideAverageFunctor : public LayeredSideAverageBase<SideIntegralFunctorUserObject>
{
public:
  static InputParameters validParams();

  LayeredSideAverageFunctor(const InputParameters & parameters);
};
