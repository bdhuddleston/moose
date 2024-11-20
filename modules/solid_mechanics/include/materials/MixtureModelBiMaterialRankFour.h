//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once 

#include "MixtureModelBiMaterialBase.h"
#include "RankFourTensor.h"

/**
 * Compute a RankTwo material property based on a mixture of two materials
 * based on a simple rule of mixtures.
 */
template <bool is_ad> 
class MixtureModelBiMaterialRankFourTempl : public MixtureModelBiMaterialBase
{
public: 
  static InputParameters validParams(); 

  MixtureModelBiMaterialRankFourTempl(const InputParameters & parameters); 

protected: 
  virtual void assignQpPropertiesFromMixtureModel() override;

  /// RankTwo Material properties for the two separate materials in the bi-material system
  std::vector<const GenericMaterialProperty<RankFourTensor, is_ad> *> _bimaterial_material_prop;

  /// Global RankTwo material property 
  GenericMaterialProperty<RankFourTensor, is_ad> & _material_prop;
}; 

typedef MixtureModelBiMaterialRankFourTempl<false> MixtureModelBiMaterialRankFour; 
typedef MixtureModelBiMaterialRankFourTempl<true> ADMixtureModelBiMaterialRankFour; 
