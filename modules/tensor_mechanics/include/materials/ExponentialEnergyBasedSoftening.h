//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "SmearedCrackSofteningBase.h"

/**
 * ExponentialEnergyBasedSoftening is a smeared crack softening model that
 * uses an exponential softening curve where the softening slope is 
 * dependent on each element size and the fracture toughness.
 */
class ExponentialEnergyBasedSoftening : public SmearedCrackSofteningBase
{
public:
  static InputParameters validParams();

  ExponentialEnergyBasedSoftening(const InputParameters & parameters);

  virtual void computeCrackingRelease(Real & stress,
                                      Real & stiffness_ratio,
                                      const Real strain,
                                      const Real crack_initiation_strain,
                                      const Real crack_max_strain,
                                      const Real cracking_stress,
                                      const Real youngs_modulus, 
                                      const Real poissons_ratio) override;

protected:

  /// Fracture toughness
  const Real & _fracture_toughness;

  /// poisson's ratio
  const Real & _nu; 

  /// Problem dimension controls how to estimate the element size
  //const Real & _dimension;

  /// Residual stress after full softening
  const Real & _residual_stress;
};
