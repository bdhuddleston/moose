#include "ComputeInvertedFlowRuleYieldStress.h"
#include "ComputeSimoHughesJ2PlasticityStress.h"

registerMooseObject("SolidMechanicsApp", ComputeInvertedFlowRuleYieldStress);

InputParameters
ComputeInvertedFlowRuleYieldStress::validParams()
{
    InputParameters params = Material::validParams();
    params.addClassDescription(
        "Computes the isotropic-hardening yield stress "
        "sigma_y = sigma_y0 + H * kappa "
        "and its derivative w.r.t. the plastic multiplier increment delta_gamma "
        "for use with ComputeSimoHughesJ2PlasticityStress.");

    params.addRequiredParam<MaterialName>(
        "plasticity_model",
        "Name of the ComputeSimoHughesJ2PlasticityStress material object that "
        "provides the plastic multiplier increment delta_gamma.");

    params.addRequiredParam<Real>(
        "yield_stress",
        "Initial (virgin) yield stress sigma_y0.");

    params.addParam<Real>(
        "flow_rule_constant", 1.0,
        "Proportionality constant (f) in EMMI (Bammann) style flow rule.");

    params.addParam<Real>(
        "flow_rule_exponent", 1.0,
        "Exponent (n) in EMMI (Bammann) style flow rule.");

  return params;
}

ComputeInvertedFlowRuleYieldStress::ComputeInvertedFlowRuleYieldStress(
    const InputParameters & parameters)
  : Material(parameters),
    _plasticity_model(nullptr),
    _sigma_y0(getParam<Real>("yield_stress")),
    _f(getParam<Real>("flow_rule_constant")),
    _1_over_n(1 / getParam<Real>("flow_rule_exponent")),
    _kappa(getMaterialProperty<Real>("kappa")),
    _dkappa_ddelta_gamma(getMaterialProperty<Real>("dkappa_ddelta_gamma")),
    _flow_stress(declareProperty<Real>("flow_stress")),
    _dyield_stress_ddelta_gamma(declareProperty<Real>("dflow_stress/deffective_plastic_strain"))
{
}

void 
ComputeInvertedFlowRuleYieldStress::initialSetup()
{
  _plasticity_model = dynamic_cast<ComputeSimoHughesJ2PlasticityStress *>
              (&getMaterialByName(getParam<MaterialName>("plasticity_model")));
}

void
ComputeInvertedFlowRuleYieldStress::computeQpProperties()
{

    const Real dg = _plasticity_model->getCurrentDeltaEp();

    // sigma_y(kappa) = sigma_y0 + H * kappa
    auto ref_yield = _kappa[_qp] + _sigma_y0; 
    auto rate_dep = std::asinh(std::pow(dg / _f, _1_over_n)) + 1;
    _flow_stress[_qp] = ref_yield * rate_dep;

    // Chain rule:
    //   d(sigma_y)/d(delta_gamma) = H * d(kappa)/d(delta_gamma)
    auto d_rate_dep = _1_over_n * std::pow(dg / _f, _1_over_n - 1) / std::sqrt(1 + std::pow(dg/_f, 2*_1_over_n));
    _dyield_stress_ddelta_gamma[_qp] = d_rate_dep * ref_yield + rate_dep * _dkappa_ddelta_gamma[_qp];
}