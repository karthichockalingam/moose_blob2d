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

[AuxVariables]
  [./master_omega]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_psi]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_n]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_divJ]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_vx]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_vy]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_tx]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_ty]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_qx]
    order = SECOND
    family = LAGRANGE
  [../]
  [./master_qy]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[ICs]
 [./ic_u]
    type = ConstantIC
    variable = master_omega
    value = 0.01
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


[Problem]
  type = FEProblem
  solve = false
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
  # execute_on = 'timestep_end'
  exodus = true
  interval = 1
[]




[MultiApps]
  [./sub_psi]
   type = TransientMultiApp
   input_files = sub_psi.i
   execute_on = 'timestep_begin'
  [../]
[]

[Transfers]

 [./omega_and_n_to_sub]
    type = MultiAppCopyTransfer
    source_variable = 'master_omega master_n'
    variable = 'omega n'
    to_multi_app = sub_psi
    execute_on = 'timestep_begin'
  [../]

  [./from_sub]
    type = MultiAppCopyTransfer
    source_variable = 'psi divJ vx vy tx qx ty qy'
    variable = 'master_psi master_divJ master_vx master_vy master_tx master_qx master_ty master_qy'
    from_multi_app = sub_psi
    execute_on = 'timestep_end'
  [../]

[]