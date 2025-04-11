//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADReal.h"

#include "libmesh/libmesh_common.h"

using namespace libMesh;

namespace fp
{

/**
 * Compute Reynolds number
 *
 * @param rho  Density [kg/m^3]
 * @param vel  Velocity [m/s]
 * @param L  Characteristic length [m]
 * @param mu  Dynamic viscosity [Pa-s]
 * @return Reynolds number
 */
Real reynolds(Real rho, Real vel, Real L, Real mu);
ADReal reynolds(const ADReal & rho, const ADReal & vel, const ADReal & L, const ADReal & mu);

/**
 * Compute Prandtl number
 *
 * @param cp  Isobaric specific heat [J/K]
 * @param mu  Dynamic viscosity [Pa-s]
 * @param k  Thermal conductivity [W/m-K]
 * @return Prandtl number
 */
Real prandtl(Real cp, Real mu, Real k);
ADReal prandtl(const ADReal & cp, const ADReal & mu, const ADReal & k);

/**
 * Compute Grashof number
 *
 * @param beta  Thermal expansion coefficient [1/K]
 * @param T_s  Surface temperature [K]
 * @param T_bulk  Bulk temperature [K]
 * @param L  Characteristic length [m]
 * @param rho  Density [kg/m^3]
 * @param mu  Dynamic viscosity [Pa-s]
 * @param gravity_magnitude  Gravitational acceleration magnitude
 * @return Grashof number
 */
Real grashof(Real beta, Real T_s, Real T_bulk, Real L, Real rho, Real mu, Real gravity_magnitude);
ADReal grashof(const ADReal & beta,
               const ADReal & T_s,
               const ADReal & T_bulk,
               const ADReal & L,
               const ADReal & rho,
               const ADReal & mu,
               const ADReal & gravity_magnitude);

/**
 * Compute Laplace number
 *
 * @param sigma  Surface tension [N/m]
 * @param rho  Density [kg/m^3]
 * @param L  Characteristic length [m]
 * @param mu  Dynamic viscosity [Pa-s]
 * @return Laplace number
 */
Real laplace(Real sigma, Real rho, Real L, Real mu);
ADReal laplace(const ADReal & sigma, const ADReal & rho, const ADReal & L, const ADReal & mu);

/**
 * Compute thermal diffusivity
 *
 * @param k Thermal conductivity [W/m-K]
 * @param rho Density [kg/m^3]
 * @param cp Isobaric specific heat [J/K]
 * @return Thermal diffusivity
 */
Real thermalDiffusivity(Real k, Real rho, Real cp);
ADReal thermalDiffusivity(const ADReal & k, const ADReal & rho, const ADReal & cp);

/**
 * Compute Peclet number
 *
 * @param vel Velocity [m/s]
 * @param L  Characteristic length [m]
 * @param diffusivity Diffusivity
 * @return Peclet number
 */
Real peclet(Real vel, Real L, Real diffusivity);
ADReal peclet(const ADReal & vel, const ADReal & L, const ADReal & diffusivity);

} // namespace fp
