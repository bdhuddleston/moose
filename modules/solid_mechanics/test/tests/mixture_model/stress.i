[Mesh]
  [generated]
    type = GeneratedMeshGenerator
    # three elements in z direction, 1 in x and y
    dim = 3
    nz = 3
    zmax = 3.0
  []
  [genxset]
    type = ParsedGenerateNodeset
    input = generated 
    new_nodeset_name = 'xset'
    expression = 'x = 0 & z = 0'
  []
  [genorigin]
    type = ParsedGenerateNodeset
    input = genxset
    new_nodeset_name = 'origin'
    expression = 'x = 0 & y = 0 & z = 0'
  []
[]

[GlobalParams]
  displacements = 'disp_x disp_y disp_z'
[]

[Functions] 
  [material_init]
    type = ParsedFunction
    expression = 'if(z > 1 & z < 2, 1, 0)'
  []
[]

[AuxVariables]
  [material_fraction]
    order = CONSTANT
    family = MONOMIAL
    [InitialCondition]
      type = FunctionIC 
      function = material_init
    []
  []
[]

[Physics/SolidMechanics/QuasiStatic]
  [./all]
    strain = SMALL
    add_variables = true
    generate_output = 'stress_zz strain_zz strain_xx'
  [../]
[]

[BCs]
  [pullz]
    type = FunctionDirichletBC
    variable = disp_z
    boundary = 5
    function = '0.003*t'
  []
  [holdz]
    type = DirichletBC
    variable = disp_z
    boundary = 0
    value = 0.0
  []

  [fix_x]
    type = DirichletBC
    variable = disp_x
    boundary = xset
    value = 0.0
  []

  [fix_origin]
    type = DirichletBC
    variable = disp_y
    boundary = origin
    value = 0.0
  []
[]

[Materials]
  [elasticity_tensor_steel]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 210e9
    poissons_ratio = 0.27
    base_name = "steel"
  []
  [strain_steel]
    type = ComputeSmallStrain
    base_name = "steel"
  []
  [stress_steel]
    type = ComputeLinearElasticStress 
    base_name = "steel"
  []

  [elastic_tensor_aluminum]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 70e9
    poissons_ratio = 0.33
    base_name = "al"
  []
  [strain_aluminum]
    type = ComputeSmallStrain 
    base_name = "al"
  []
  [stress_aluminum]
    type = ComputeLinearElasticStress
    base_name = "al"
  []

  [stress]
    type = MixtureModelBiMaterialRankTwo
    primary_material_base = 'steel'
    secondary_material_base = 'al'
    prop_name = stress
    mixture_var = material_fraction
  []
  [jacmult]
    type = MixtureModelBiMaterialRankFour
    primary_material_base = 'steel'
    secondary_material_base = 'al'
    prop_name = Jacobian_mult
    mixture_var = material_fraction
  []
[]

[Executioner]
  type = Transient

  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_factor_mat_solver_package'
  petsc_options_value = '101                lu        superlu_dist'

  line_search = 'none'
  l_max_its = 100
  l_tol = 1e-6

  nl_max_its = 10
  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6

  start_time = 0.0
  dt = 0.05
  dtmin = 0.001
  end_time = 0.5
[]

[Outputs]
  exodus = true
[]
