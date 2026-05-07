#include "ComputeIsotropicHardeningISV.h"
#include "ComputeSimoHughesJ2PlasticityStress.h"

registerMooseObject("SolidMechanicsApp", ComputeIsotropicHardeningISV);

InputParameters
ComputeIsotropicHardeningISV::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription(
      "Computes and evolves an isotropic hardening internal state variable "
      "(kappa) for use with ComputeSimoHughesJ2PlasticityStress. The variable "
      "is updated implicitly using the current Newton-iteration value of the "
      "plastic multiplier increment delta_gamma.");

  params.addRequiredParam<MaterialName>(
      "plasticity_model",
      "Name of the ComputeSimoHughesJ2PlasticityStress material object that "
      "provides the plastic multiplier increment delta_gamma.");

  params.addParam<Real>(
      "hardening_modulus", 0.0,
      "Linear isotropic hardening modulus H. Set to zero for perfect plasticity.");

  params.addParam<Real>(
    "dynamic_recovery", 0.0,
    "Dynamic recovery coefficient that scales recovery with kappa to saturate hardening.");

  return params;
}

ComputeIsotropicHardeningISV::ComputeIsotropicHardeningISV(const InputParameters & parameters)
  : Material(parameters),
    _plasticity_model(nullptr),
    _hardening_modulus(getParam<Real>("hardening_modulus")),
    _dynamic_recovery(getParam<Real>("dynamic_recovery")),
    _kappa(declareProperty<Real>("kappa")),
    _kappa_old(getMaterialPropertyOld<Real>("kappa")),
    _dkappa_ddelta_gamma(declareProperty<Real>("dkappa_ddelta_gamma"))
{
}

void 
ComputeIsotropicHardeningISV::initialSetup()
{
  _plasticity_model = dynamic_cast<ComputeSimoHughesJ2PlasticityStress *>
              (&getMaterial("plasticity_model"));
              // (&getMaterialByName(getParam<MaterialName>("plasticity_model")));
}

void
ComputeIsotropicHardeningISV::initQpStatefulProperties()
{
  _kappa[_qp] = 0.0;
}

void
ComputeIsotropicHardeningISV::computeQpProperties()
{
  // sqrt(2/3) prefactor from the von Mises equivalent plastic strain increment
  // definition:  d(eps_p_eq) = sqrt(2/3) * ||dev(d_eps_p)||
  // For J2 plasticity with the Simo-Hughes formulation, delta_gamma maps to
  // the equivalent plastic strain increment via this factor.
  constexpr Real sqrt_2_over_3 = 0.8164965809277261; // std::sqrt(2.0 / 3.0)

  const Real dg = _plasticity_model->getCurrentDeltaEp();

  // Fully implicit (backward-Euler) update:
  //   kappa_{n+1} = kappa_n + sqrt(2/3) * delta_gamma
  _kappa[_qp] = _kappa_old[_qp] + sqrt_2_over_3 * dg * (_hardening_modulus - _dynamic_recovery * _kappa_old[_qp]);

  // Derivative of kappa w.r.t. delta_gamma (constant for linear evolution)
  _dkappa_ddelta_gamma[_qp] = sqrt_2_over_3 * (_hardening_modulus - _dynamic_recovery * _kappa_old[_qp]);
}