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
  [./divJ]
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
[]

[Kernels]
  [./divJ_kernel]
    type = DivCurrent
    variable = divJ
    n = n
    psi = psi
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



