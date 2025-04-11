//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "QuadInterWrapperBaseIC.h"
#include <Eigen/Dense>

/**
 * Sets the axial heat rate for each pin according to a radial power distribution
 * and a user defined axial power shape.
 */
class QuadInterWrapperPowerIC : public QuadInterWrapperBaseIC
{
public:
  QuadInterWrapperPowerIC(const InputParameters & params);
  Real value(const Point & p) override;
  virtual void initialSetup() override;

protected:
  /// The total power of the assembly
  Real _power;
  /// The number of lines associated with the radial power profile .txt file
  unsigned int _numberoflines;
  /// The name of the radial power profile file
  std::string _filename;
  /// matrix that holds the values of the relative pin power
  Eigen::MatrixXd _power_dis;
  const Function & _axial_heat_rate;
  /// Average linear heat rate over the inter wrapper assembly [W/m]
  Eigen::MatrixXd _ref_qprime;
  /// Actual assembly power directly heating the inter-wrapper [W]
  Eigen::MatrixXd _ref_power;
  /// The correction that will be applied to the estimated calculation [unitless]
  Eigen::MatrixXd _assembly_power_correction;
  /// Matrix which will hold the total estimated power of each fuel assembly [W]
  Eigen::MatrixXd _estimate_power;

public:
  static InputParameters validParams();
};
