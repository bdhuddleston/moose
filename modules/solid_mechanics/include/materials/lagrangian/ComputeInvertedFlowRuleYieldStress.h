#pragma once

#include "Material.h"

// Forward declarations
class ComputeSimoHughesJ2PlasticityStress;

/**
 * Computes the yield stress sigma_y as a function of the isotropic hardening
 * internal state variable kappa (provided by ComputeIsotropicHardeningISV).
 *
 * Model:
 *   sigma_y(kappa) = sigma_y0 + H * kappa
 *
 * where sigma_y0 is the initial yield stress and H is the linear hardening
 * modulus.  The object also provides the derivative d(sigma_y)/d(delta_gamma)
 * required by the Simo-Hughes return-mapping residual.
 *
 * This object stores a reference to the plasticity object so that it can read
 * delta_gamma directly from the Newton scratch-space variable without
 * introducing a MaterialProperty cycle.
 */
class ComputeInvertedFlowRuleYieldStress : public Material
{
public:
  static InputParameters validParams();

  ComputeInvertedFlowRuleYieldStress(const InputParameters & parameters);

  virtual void initialSetup() override;

protected:
  virtual void computeQpProperties() override;

  /// Reference to the controlling plasticity object
  const ComputeSimoHughesJ2PlasticityStress * _plasticity_model;

  // ---- material parameters ------------------------------------------------
  /// Initial (virgin) yield stress
  const Real _sigma_y0;

  /// Flow rule constant
  const Real _f;

  /// Inverse of flow rule exponent
  const Real _1_over_n;

  // ---- input properties ---------------------------------------------------
  /// Current isotropic hardening variable (declared by ComputeIsotropicHardeningISV)
  const MaterialProperty<Real> & _kappa;

  /// Derivative d(kappa)/d(delta_gamma) (declared by ComputeIsotropicHardeningISV)
  const MaterialProperty<Real> & _dkappa_ddelta_gamma;

  // ---- output properties --------------------------------------------------
  /// Yield stress for the current Newton iteration
  MaterialProperty<Real> & _flow_stress;

  /// d(sigma_y)/d(delta_gamma) — required by the return-mapping residual
  MaterialProperty<Real> & _dyield_stress_ddelta_gamma;
};