//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MixtureModelBiMaterialBase.h"
// #include "AuxiliarySystem.h"
// #include "MooseVariable.h"

template <bool is_ad>
InputParameters
MixtureModelBiMaterialBaseTempl<is_ad>::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription("Compute a material property for bi-materials (consisting of two "
                             "different materials) where the mixture is given by a coupled    "
                             "variable.");
  params.addRequiredCoupledVar(
      "mixture_var", "The variable used to represent the material fraction");
  params.addRequiredParam<std::string>("primary_material_base",
                                       "Base name for the material in region where fraction == 1.");
  params.addRequiredParam<std::string>("secondary_material_base",
                                       "Base name for the material in region where fraction == 0.");
  params.addParam<std::string>("base_name",
                               "Base name for the computed material property (optional)");
  params.addRequiredParam<std::string>("prop_name", "Name for the computed material property.");
  return params;
}

template <bool is_ad>
MixtureModelBiMaterialBaseTempl<is_ad>::MixtureModelBiMaterialBaseTempl(const InputParameters & parameters)
  : Material(parameters),
    _material_ratio(coupledValue("mixture_var")),
    _base_name(isParamValid("base_name") ? getParam<std::string>("base_name") + "_" : ""),
    _prop_name(getParam<std::string>("prop_name"))
{
}

template <bool is_ad>
void
MixtureModelBiMaterialBaseTempl<is_ad>::initQpStatefulProperties()
{
}


// rm: Occurs first at the element level?
template <bool is_ad>
void
MixtureModelBiMaterialBaseTempl<is_ad>::computeProperties()
{
  Material::computeProperties();
}


// rm: Occurs second at the integration point level?
template <bool is_ad>
void
MixtureModelBiMaterialBaseTempl<is_ad>::computeQpProperties()
{
  assignQpPropertiesFromMixtureModel();
}

template class MixtureModelBiMaterialBaseTempl<false>;
template class MixtureModelBiMaterialBaseTempl<true>;
