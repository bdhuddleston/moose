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
class SCMTriSubChannelMeshGenerator : public MeshGenerator
{
public:
  SCMTriSubChannelMeshGenerator(const InputParameters & parameters);

  std::unique_ptr<MeshBase> generate() override;

protected:
  /// unheated length of the fuel Pin at the entry of the assembly
  const Real _unheated_length_entry;
  /// heated length of the fuel Pin
  const Real _heated_length;
  /// unheated length of the fuel Pin at the exit of the assembly
  const Real _unheated_length_exit;
  /// block index
  const unsigned int _block_id;
  /// axial location of nodes
  std::vector<Real> _z_grid;
  /// axial form loss coefficient per computational cell
  std::vector<std::vector<Real>> _k_grid;
  /// axial location of the spacers
  const std::vector<Real> & _spacer_z;
  /// form loss coefficient of the spacers
  const std::vector<Real> & _spacer_k;
  /// axial location of blockage (inlet, outlet) [m]
  const std::vector<Real> _z_blockage;
  /// index of subchannels affected by blockage
  const std::vector<unsigned int> _index_blockage;
  /// area reduction of subchannels affected by blockage
  const std::vector<Real> _reduction_blockage;
  /// form loss coefficient of subchannels affected by blockage
  const std::vector<Real> _k_blockage;
  /// Distance between the neighbor fuel pins, pitch
  const Real _pitch;
  /// Lateral form loss coefficient
  const Real & _kij;
  /// fuel Pin diameter
  const Real _pin_diameter;
  /// number of axial cells
  const unsigned int _n_cells;
  /// number of rings of fuel pins
  const unsigned int _n_rings;
  /// number of subchannels
  unsigned int _n_channels;
  /// the distance between flat surfaces of the duct facing each other
  const Real _flat_to_flat;
  /// wire diameter
  const Real _dwire;
  /// wire lead length
  const Real _hwire;
  /// the gap thickness between the duct and peripheral fuel pins
  const Real _duct_to_pin_gap;

  /// nodes
  std::vector<std::vector<Node *>> _nodes;
  /// stores the channel pairs for each gap
  std::vector<std::pair<unsigned int, unsigned int>> _gap_to_chan_map;
  /// stores the fuel pin pairs for each gap each gap
  std::vector<std::pair<unsigned int, unsigned int>> _gap_to_pin_map;
  /// stores the gaps that forms each subchannel
  std::vector<std::vector<unsigned int>> _chan_to_gap_map;
  /// Defines the global cross-flow direction -1 or 1 for each subchannel and
  /// for all gaps that are belonging to the corresponding subchannel.
  /// Given a subchannel and a gap, if the neighbor subchannel index belonging to the same gap is lower,
  /// set it to -1, otherwise set it to 1.
  std::vector<std::vector<Real>> _sign_id_crossflow_map;
  /// gap size
  std::vector<std::vector<Real>> _gij_map;
  /// x,y coordinates of the subchannel centroids
  std::vector<std::vector<Real>> _subchannel_position;
  /// x,y coordinates of the fuel pins
  std::vector<Point> _pin_position;
  /// fuel pins that are belonging to each ring
  std::vector<std::vector<Real>> _pins_in_rings;
  /// stores the fuel pins belonging to each subchannel
  std::vector<std::vector<unsigned int>> _chan_to_pin_map;
  /// stores the map from pins to channels
  std::vector<std::vector<unsigned int>> _pin_to_chan_map;
  /// number of fuel pins
  unsigned int _npins;
  /// number of gaps
  unsigned int _n_gaps;
  /// subchannel type
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
