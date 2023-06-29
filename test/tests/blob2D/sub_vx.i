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
  [./vx]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./psi]
    order = SECOND
    family = LAGRANGE
  [../]
  [./n]
    order = SECOND
    family = LAGRANGE
  [../]
  [./omega]
    order = SECOND
    family = LAGRANGE
  [../]
  [./tx]
    order = SECOND
    family = LAGRANGE
  [../]
  [./qx]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./vx_kernel]
    type = CrossField
    variable = vx
    psi = psi
    component = 0
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
  [./sub_tx]
   type = TransientMultiApp
   input_files = sub_tx.i
   execute_on = 'timestep_end'
  [../]
  [./sub_qx]
   type = TransientMultiApp
   input_files = sub_qx.i
   execute_on = 'timestep_end'
  [../]
[]


[Transfers]

  [./vx_and_n_to_sub_tx]
    type = MultiAppCopyTransfer
    source_variable = 'vx n'
    variable = 'vx n'
    to_multi_app = sub_tx
    execute_on = 'timestep_end'
  [../]

  [./tx_from_sub]
    type = MultiAppCopyTransfer
    source_variable = 'tx'
    variable = 'tx'
    from_multi_app = sub_tx
    execute_on = 'timestep_end'
  [../]

  [./vx_and_omega_to_sub_qx]
    type = MultiAppCopyTransfer
    source_variable = 'vx omega'
    variable = 'vx omega'
    to_multi_app = sub_qx
    execute_on = 'timestep_end'
  [../]

  [./qx_from_sub]
    type = MultiAppCopyTransfer
    source_variable = 'qx'
    variable = 'qx'
    from_multi_app = sub_qx
    execute_on = 'timestep_end'
  [../]

[]





