//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MeshGenerator.h"
#include "SubChannelEnums.h"

/**
 * Mesh class for triangular, edge and corner subchannels for hexagonal lattice fuel assemblies
 */
class SCMTriInterWrapperMeshGenerator : public MeshGenerator
{
public:
  SCMTriInterWrapperMeshGenerator(const InputParameters & parameters);

  std::unique_ptr<MeshBase> generate() override;

protected:
  /// unheated length of the fuel Pin at the entry of the assembly
  const Real _unheated_length_entry;
  /// heated length of the fuel Pin
  const Real _heated_length;
  /// unheated length of the fuel Pin at the exit of the assembly
  const Real _unheated_length_exit;
  /// Lateral form loss coefficient
  const Real & _kij;
  /// axial location of nodes
  std::vector<Real> _z_grid;
  /// axial form loss coefficient per computational cell
  std::vector<std::vector<Real>> _k_grid;
  /// Distance between the neighbor fuel pins, assembly_pitch
  const Real _assembly_pitch;
  /// number of axial cells
  const unsigned int _n_cells;
  /// number of rings of fuel pins
  const unsigned int _n_rings;
  /// number of subchannels
  unsigned int _n_channels;
  /// the distance between flat surfaces of the duct facing each other
  const Real _flat_to_flat;
  /// the gap thickness between the duct and peripheral fuel pins
  const Real _duct_to_pin_gap;
  /// whether the side bypass shape follows the hexagonal shape of the assemblies
  /// TODO: add a picture in the documentation of both tight and non-tight layouts
  const bool _tight_side_bypass;

  /// nodes
  std::vector<std::vector<Node *>> _nodes;
  /// stores the channel pairs for each gap
  std::vector<std::pair<unsigned int, unsigned int>> _gap_to_chan_map;
  /// stores the fuel pin pairs for each gap each gap
  std::vector<std::pair<unsigned int, unsigned int>> _gap_to_pin_map;
  /// stores the gaps that forms each interstice
  std::vector<std::vector<unsigned int>> _chan_to_gap_map;
  /// Defines the global cross-flow direction -1 or 1 for each interstice and
  /// for all gaps that are belonging to the corresponding interstice.
  /// Given a interstice and a gap, if the neighbor interstice index belonging to the same gap is lower,
  /// set it to -1, otherwise set it to 1.
  std::vector<std::vector<Real>> _sign_id_crossflow_map;
  /// gap size
  std::vector<Real> _gij_map;
  /// x,y coordinates of the interstices
  std::vector<std::vector<Real>> _subchannel_position;
  /// x,y coordinates of the fuel pins
  std::vector<Point> _pin_position;
  /// fuel pins that are belonging to each ring
  std::vector<std::vector<Real>> _pins_in_rings;
  /// stores the fuel pins belonging to each interstice
  std::vector<std::vector<unsigned int>> _chan_to_pin_map;
  /// number of assemblies
  unsigned int _n_assemblies;
  /// number of gaps
  unsigned int _n_gaps;
  /// interstice type
  std::vector<EChannelType> _subch_type;
  /// gap type
  std::vector<EChannelType> _gap_type;
  /// sweeping flow model gap pairs per channel to specify directional edge flow
  std::vector<std::pair<unsigned int, unsigned int>> _gap_pairs_sf;
  /// sweeping flow model channel pairs to specify directional edge flow
  std::vector<std::pair<unsigned int, unsigned int>> _chan_pairs_sf;

public:
  static InputParameters validParams();
};
