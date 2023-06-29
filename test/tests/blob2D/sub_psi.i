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
  [./psi]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./omega]
    order = SECOND
    family = LAGRANGE
  [../]
  [./n]
    order = SECOND
    family = LAGRANGE
  [../]
  [./divJ]
    order = SECOND
    family = LAGRANGE
  [../]
  [./vx]
    order = SECOND
    family = LAGRANGE
  [../]
  [./vy]
    order = SECOND
    family = LAGRANGE
  [../]
  [./tx]
    order = SECOND
    family = LAGRANGE
  [../]
  [./ty]
    order = SECOND
    family = LAGRANGE
  [../]
  [./qx]
    order = SECOND
    family = LAGRANGE
  [../]
  [./qy]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./psi_kernel]
    type = SheathClosure
    variable = psi
    w = omega
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
  active = 'bnd'
  [./Periodic]
    [./all]
      variable = psi
      auto_direction = 'x y'
    [../]
  [../]

  [bnd]
    type = DirichletBC
    variable = psi
    boundary = 'right left bottom top'
    value = 0
  []
[]

# Transient (time-dependent) details for simulations go here:
[Executioner]
  type = Transient   # Here we use the Transient Executioner (instead of steady)
  solve_type = 'NEWTON'
  num_steps = 1
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_pc_side -ksp_norm_type'
  petsc_options_value = 'hypre    boomeramg      left         preconditioned'

  dt = 1 # each time step will have duration "1"
  l_tol = 1e-4 # Relative tolerance for linear solves
  nl_max_its = 40 # Max number of nonlinear iterations
  nl_abs_tol = 1e-11 # Relative tolerance for nonlienar solves
  nl_rel_tol = 1e-6 # Absolute tolerance for nonlienar solves
[]


[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  interval = 1
[]

[MultiApps]
  [./sub_divJ]
   type = TransientMultiApp
   input_files = sub_divJ.i
   execute_on = 'timestep_end'
  [../]
  [./sub_vx]
   type = TransientMultiApp
   input_files = sub_vx.i
   execute_on = 'timestep_end'
  [../]
  [./sub_vy]
   type = TransientMultiApp
   input_files = sub_vy.i
   execute_on = 'timestep_end'
  [../]
[]

[Transfers]

  [./psi_and_n_to_sub_divJ]
    type = MultiAppCopyTransfer
    source_variable = 'psi n'
    variable = 'psi n'
    to_multi_app = sub_divJ
    execute_on = 'timestep_end'
  [../]

    [./divJ_from_sub]
    type = MultiAppCopyTransfer
    source_variable = divJ
    variable = divJ
    from_multi_app = sub_divJ
    execute_on = 'timestep_end'
  [../]


  [./omega_psi_and_n_to_sub_vx]
    type = MultiAppCopyTransfer
    source_variable = 'omega psi n'
    variable = 'omega psi n'
    to_multi_app = sub_vx
    execute_on = 'timestep_end'
  [../]

  [./omega_psi_and_n_to_sub_vy]
    type = MultiAppCopyTransfer
    source_variable = 'omega psi n'
    variable = 'omega psi n'
    to_multi_app = sub_vy
    execute_on = 'timestep_end'
  [../]

  [./vx_tx_qx_from_sub]
    type = MultiAppCopyTransfer
    source_variable = 'vx tx qx'
    variable = 'vx tx qx'
    from_multi_app = sub_vx
    execute_on = 'timestep_end'
  [../]

  [./vy_ty_qy_from_sub]
    type = MultiAppCopyTransfer
    source_variable = 'vy ty qy'
    variable = 'vy ty qy'
    from_multi_app = sub_vy
    execute_on = 'timestep_end'
  [../]

[]

