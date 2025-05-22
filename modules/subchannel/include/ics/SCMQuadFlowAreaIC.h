//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "QuadSubChannelBaseIC.h"

class SubChannelMesh;

/**
 * This class calculates the cross-sectional flow area of the quadrilateral subchannel
 */
class SCMQuadFlowAreaIC : public QuadSubChannelBaseIC
{
public:
  SCMQuadFlowAreaIC(const InputParameters & params);
  Real value(const Point & p) override;
  static InputParameters validParams();

protected:
  const SubChannelMesh & _subchannel_mesh;
};
