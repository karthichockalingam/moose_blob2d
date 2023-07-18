[Mesh]
    type = GeneratedMesh
    dim = 2
    xmin = -0.5
    xmax =  0.5
    ymin = -0.5
    ymax =  0.5
    nx = 128
    ny = 128
    elem_type = QUAD9
[]

[Variables]
  [./master_n]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./master_omega]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_psi]
    order = SECOND
    family = LAGRANGE
  [../]
[]



[Kernels]

  [./trans_n]
    type = TimeDerivative
    variable = master_n
  [../]

  [./divFlux_kernel_n]
    type = CoupledImplicitDivFlux
    variable = master_n
    psi = master_psi
  [../]

  [./source_kernel_n]
    type = ElectronDensityImplicitDivCurrent
    variable = master_n
    psi = master_psi
  [../]

[]

[ICs]
 [./ic_u]
    type = ConstantIC
    variable = master_omega
    value = 0.0
  [../]
  [./ic_n]
    type = FunctionIC
    variable = master_n
    function = n_func
  [../]
[]

[Functions]
  # A ParsedFunction allows us to supply analytic expressions
  # directly in the input file
  [./n_func]
    type = ParsedFunction
    expression = '1.0 + h*exp(-(x*x+y*y)/(w*w))'
    symbol_names =  'h         w'
    symbol_values = '0.5     0.05'
  [../]
[]

[Materials]
  [mat]
    type = BlobMaterial
    B_value = 0.35
    e_value = -1.0
    T_value = 5.0
    L_value = 10.0
    R_value = 1.5
  []
[]

[BCs]
  [./Periodic]
    [./all]
      variable = master_n
      auto_direction = 'x y'
    [../]
  [../]
[]



# Transient (time-dependent) details for simulations go here:
[Executioner]
  type = Transient   # Here we use the Transient Executioner (instead of steady)
  solve_type = 'NEWTON'
  num_steps = 3

  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_pc_side -ksp_norm_type'
  petsc_options_value = 'hypre    boomeramg      left         preconditioned'

  dt = 1e-4 # each time step will have duration "1"
  l_tol = 1e-4 # Relative tolerance for linear solves
  nl_max_its = 40 # Max number of nonlinear iterations
  nl_abs_tol = 1e-11 # Relative tolerance for nonlienar solves
  nl_rel_tol = 1e-6 # Absolute tolerance for nonlienar solves


  picard_max_its = 5

  picard_rel_tol = 1e-6
  picard_abs_tol = 1e-10
[]


[Outputs]
  # execute_on = 'timestep_end'
  exodus = true
  interval = 1
[]




[MultiApps]
 [./app_omega]
   type = TransientMultiApp
   input_files = app_omega.i
   execute_on = 'timestep_end'
  [../]

  
  [./app_psi]
   type = TransientMultiApp
   input_files = app_psi.i
   execute_on = 'timestep_end'
  [../]


[]

[Transfers]

 [./omega_to_sub]
    type = MultiAppCopyTransfer
    source_variable = 'master_omega'
    variable = 'omega'
    to_multi_app = app_psi
    execute_on = 'timestep_end'
  [../]

  [./from_sub]
    type = MultiAppCopyTransfer
    source_variable = 'psi'
    variable = 'master_psi'
    from_multi_app = app_psi
    execute_on = 'timestep_end'
  [../]

  [./n_psi_to_sub]
    type = MultiAppCopyTransfer
    source_variable = 'master_n master_psi'
    variable = 'n  psi'
    to_multi_app = app_omega
    execute_on = 'timestep_end'
  [../]

  [./from_sub_omega]
    type = MultiAppCopyTransfer
    source_variable = 'omega'
    variable = 'master_omega'
    from_multi_app = app_omega
    execute_on = 'timestep_end'
  [../]

[]