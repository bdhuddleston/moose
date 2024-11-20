//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MixtureModelBiMaterialRankFour.h"

registerMooseObject("SolidMechanicsApp", MixtureModelBiMaterialRankFour);
registerMooseObject("SolidMechanicsApp", ADMixtureModelBiMaterialRankFour);

template <bool is_ad> 
InputParameters
MixtureModelBiMaterialRankFourTempl<is_ad>::validParams()
{
    InputParameters params = MixtureModelBiMaterialBase::validParams();
    params.addClassDescription(
        "Compute a RankFour material property for a bi-material problem consisting of two "
        "different materials using a simple rule of mixtures.");
    return params;
}

template <bool is_ad>
MixtureModelBiMaterialRankFourTempl<is_ad>::MixtureModelBiMaterialRankFourTempl(const InputParameters & parameters)
  : MixtureModelBiMaterialBase(parameters),
    _bimaterial_material_prop(2),
    _material_prop(declareGenericProperty<RankFourTensor, is_ad>(_base_name + _prop_name))
{
  _bimaterial_material_prop[0] = &getGenericMaterialProperty<RankFourTensor, is_ad>(
      getParam<std::string>("primary_material_base") + "_" + _prop_name);
  _bimaterial_material_prop[1] = &getGenericMaterialProperty<RankFourTensor, is_ad>(
      getParam<std::string>("secondary_material_base") + "_" + _prop_name);
}

template <bool is_ad> 
void 
MixtureModelBiMaterialRankFourTempl<is_ad>::assignQpPropertiesFromMixtureModel()
{
    const auto ratio = _material_ratio[_qp];
    _material_prop[_qp] = ratio*(*_bimaterial_material_prop[0])[_qp] + 
                    (1 - ratio)*(*_bimaterial_material_prop[1])[_qp];
}

template class MixtureModelBiMaterialRankFourTempl<false>;
template class MixtureModelBiMaterialRankFourTempl<true>;