//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "InputParameters.h"
#include "Material.h"


/**
 * Base class for calculating a property based on a mixture of two materials
 * based on a simple rule of mixtures.
 */
template <bool is_ad>
class MixtureModelBiMaterialBaseTempl : public Material
{
public:
  static InputParameters validParams();

  MixtureModelBiMaterialBaseTempl(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeProperties() override;
  virtual void computeQpProperties() override;

  /**
   * assign the material properties based on the material ratio
   */
  virtual void assignQpPropertiesFromMixtureModel() = 0;

  /// Coupled variable for defining mixture ratio
  const VariableValue & _material_ratio;

  /// global material properties
  const std::string _base_name;

  /// Property name
  std::string _prop_name;
};

typedef MixtureModelBiMaterialBaseTempl<false> MixtureModelBiMaterialBase;
typedef MixtureModelBiMaterialBaseTempl<true> ADMixtureModelBiMaterialBase;
