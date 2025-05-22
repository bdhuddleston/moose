//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FunctorMaterial.h"
#include "DerivativeMaterialPropertyNameInterface.h"
#include "Function.h"

class SinglePhaseFluidProperties;
class Function;

/**
 * Computes fluid properties in (P, T) formulation using functor material properties
 */
template <bool is_ad>
class GeneralFunctorFluidPropsTempl : public FunctorMaterial,
                                      public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();
  GeneralFunctorFluidPropsTempl(const InputParameters & parameters);

protected:
  const SinglePhaseFluidProperties & _fluid;

  /// Porosity
  const Moose::Functor<GenericReal<is_ad>> & _eps;

  /**
   * Characteristic length $d$ used in computing the Reynolds number
   * $Re=\rho_fVd/\mu_f$.
   */
  const Moose::Functor<Real> & _d;

  /// Whether the input pressure is the dynamic pressure
  const bool _pressure_is_dynamic;
  /// Where the static pressure rho*g*(z-z0) term is 0
  const Point _reference_pressure_point;
  /// The value of pressure at that point
  const Real _reference_pressure_value;
  /// The gravity vector
  const Point _gravity_vec;

  /// variables
  const Moose::Functor<GenericReal<is_ad>> & _pressure;
  const Moose::Functor<GenericReal<is_ad>> & _T_fluid;
  const Moose::Functor<GenericReal<is_ad>> & _speed;

  /// A parameter to force definition of a functor material property for density
  const bool _force_define_density;

  /// Density as a functor, which could be from the variable set or the property
  const Moose::Functor<GenericReal<is_ad>> & _rho;

  /// Function to ramp down the viscosity, useful for relaxation transient
  const Function & _mu_rampdown;

  /// Whether to neglect the contributions to the Jacobian of the density time derivative
  const bool _neglect_derivatives_of_density_time_derivative;

  using DerivativeMaterialPropertyNameInterface::derivativePropertyNameFirst;
  using UserObjectInterface::getUserObject;
};

typedef GeneralFunctorFluidPropsTempl<false> NonADGeneralFunctorFluidProps;
typedef GeneralFunctorFluidPropsTempl<true> GeneralFunctorFluidProps;
