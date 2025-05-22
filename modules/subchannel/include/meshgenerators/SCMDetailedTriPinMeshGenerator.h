//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "DetailedPinMeshGeneratorBase.h"

/**
 * Mesh generator for fuel pins in a triangular lattice
 */
class SCMDetailedTriPinMeshGenerator : public DetailedPinMeshGeneratorBase
{
public:
  SCMDetailedTriPinMeshGenerator(const InputParameters & parameters);

  virtual std::unique_ptr<MeshBase> generate() override;

protected:
  /// Mesh that comes from another generator
  std::unique_ptr<MeshBase> & _input;
  /// Number of rings in the fuel assembly
  const unsigned int & _n_rings;

public:
  static InputParameters validParams();
};
