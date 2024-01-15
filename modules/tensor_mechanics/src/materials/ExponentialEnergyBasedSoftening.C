//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ExponentialEnergyBasedSoftening.h" 

#include "MooseMesh.h"

registerMooseObject("TensorMechanicsApp", ExponentialEnergyBasedSoftening);

InputParameters
ExponentialEnergyBasedSoftening::validParams()
{
  InputParameters params = SmearedCrackSofteningBase::validParams();
  params.addClassDescription(
      "Softening model with an exponential softening response upon cracking. This "
      "class is intended to be used with ComputeSmearedCrackingStress.");
  params.addRangeCheckedParam<Real>(
      "residual_stress",
      0.0,
      "residual_stress <= 1 & residual_stress >= 0",
      "The fraction of the cracking stress allowed to be maintained following a crack.");
  params.addRequiredRangeCheckedParam<Real>(
      "fracture_toughness",
      "fracture_toughness > 0",
      "Fracture toughness used to calculate the softening slope. ");
  params.addRequiredRangeCheckedParam<Real>(
      "poissons_ratio",
      "poissons_ratio >= 0 & poissons_ratio <= 0.5",
      "Poisson's ratio needed for fracture energy calculation. ");
  // params.addRangeCheckedParam<unsigned int>(
  //     "dimension",
  //     3,
  //     "dimension > 0 & dimension < 4",
  //     "Variable indicating problem dimension for calcuating element size. Defaults "
  //     "to 3 dimensional. "); //TODO: get dimension of the problem from mesh? mesh.dim
  return params;
}

ExponentialEnergyBasedSoftening::ExponentialEnergyBasedSoftening(const InputParameters & parameters)
  : SmearedCrackSofteningBase(parameters),
    _residual_stress(getParam<Real>("residual_stress")),
    _fracture_toughness(getParam<Real>("fracture_toughness")),
    _nu(getParam<Real>("poissons_ratio"))
{
}

void
ExponentialEnergyBasedSoftening::computeCrackingRelease(Real & stress,
                                             Real & stiffness_ratio,
                                             const Real /*strain*/,
                                             const Real crack_initiation_strain,
                                             const Real crack_max_strain,
                                             const Real cracking_stress,
                                             const Real youngs_modulus, 
                                             const Real poissons_ratio)
{
  mooseAssert(crack_max_strain >= crack_initiation_strain,
              "crack_max_strain must be >= crack_initiation_strain");
  
  unsigned int dim = _current_elem->dim();
  
  // Get estimate of element size
  Real ele_len = 0.0;
  if (dim == 3) {
    ele_len = std::cbrt(_current_elem->volume());
  } else {
    ele_len = std::sqrt(_current_elem->volume());
  }

  // Calculate initial slope of exponential curve
  Real energy_release_rate = (_fracture_toughness * _fracture_toughness) * (1 - _nu * _nu) / youngs_modulus;  
  const Real frac_stress_sqr = cracking_stress * cracking_stress; 
  const Real l_max = 2 * energy_release_rate * youngs_modulus / frac_stress_sqr;

  //check against maximum allowed element size - avoid the divide by zero by capping at a large slope
  Real initial_slope = -1e5*youngs_modulus;
  if (ele_len < l_max) 
    initial_slope = -frac_stress_sqr / (energy_release_rate / ele_len - frac_stress_sqr / (2*youngs_modulus)); 

  // Compute stress that follows exponental curve
  stress = cracking_stress *
           (_residual_stress +
            (1.0 - _residual_stress) * std::exp(initial_slope / cracking_stress *
                                                (crack_max_strain - crack_initiation_strain)));
  // Compute ratio of current stiffness to original stiffness
  stiffness_ratio = stress * crack_initiation_strain / (crack_max_strain * cracking_stress);
}
