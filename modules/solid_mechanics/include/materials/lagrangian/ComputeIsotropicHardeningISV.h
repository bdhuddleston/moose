#pragma once

#include "Material.h"

// Forward declarations
class ComputeSimoHughesJ2PlasticityStress;

/**
 * Evolves an isotropic hardening internal state variable (kappa) based on
 * the plastic multiplier increment delta_gamma obtained from the plasticity
 * object during the return-mapping Newton solve.
 *
 * Evolution law:
 *   kappa_{n+1} = kappa_n + sqrt(2/3) * delta_gamma
 *
 * kappa and kappa_old are declared as stateful MaterialProperties and are
 * updated after convergence of the Newton loop.
 */
class ComputeIsotropicHardeningISV : public Material
{
public:
  static InputParameters validParams();

  ComputeIsotropicHardeningISV(const InputParameters & parameters);

  virtual void initialSetup() override;

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  /// Reference to the plasticity object that owns delta_gamma
  const ComputeSimoHughesJ2PlasticityStress * _plasticity_model;

  /// Linear hardening modulus H (optional; set to 0 for perfect plasticity)
  const Real _hardening_modulus;
  const Real _dynamic_recovery;

  /// Current value of the isotropic hardening variable kappa
  MaterialProperty<Real> & _kappa;

  /// Value of kappa from the previous converged time step
  const MaterialProperty<Real> & _kappa_old;

  /// Derivative of kappa w.r.t. delta_gamma (made available as a property
  /// so the yield-stress object can form dσ_y/d(delta_gamma) if needed)
  MaterialProperty<Real> & _dkappa_ddelta_gamma;
};