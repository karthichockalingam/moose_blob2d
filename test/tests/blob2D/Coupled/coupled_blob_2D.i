[Mesh]
    type = GeneratedMesh
    dim = 2
    xmin = -0.5
    xmax =  0.5
    ymin = -0.5
    ymax =  0.5
    nx = 64
    ny = 64
    elem_type = QUAD9
[]

[Variables]
  [./omega]
    order = SECOND
    family = LAGRANGE
  [../]
  [./psi]
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

[ICs]
 [./ic_u]
    type = ConstantIC
    variable = omega
    value = 0.0
  [../]
  [./ic_n]
    type = FunctionIC
    variable = n
    function = n_func
  [../]
[]

[Kernels]

 [./trans_omega]
    type = TimeDerivative
    variable = omega
  [../]

  [./divFlux_kernel_omega]
    type = DivFlux
    variable = omega
    jx = qx
    jy = qy
  [../]

  [./curl_kernel]
    type = CurlbB
    variable = omega
    n = n
  [../]

  [./source_kernel_omega]
    type = DivCurrentSource
    variable = omega
    div_current = divJ
    e_value = 1.0
  [../]


  [./psi_kernel]
    type = SheathClosure
    variable = psi
    w = omega
  [../]

   [./trans_n]
    type = TimeDerivative
    variable = n
  [../]

  [./divFlux_kernel_n]
    type = DivFlux
    variable = n
    jx = tx
    jy = ty
  [../]

  [./source_kernel_n]
    type = DivCurrentSource
    variable = n
    div_current = divJ
    e_value = -1.0
  [../]

  [./divJ_kernel]
    type = DivCurrent
    variable = divJ
    n = n
    psi = psi
  [../]

  [./vx_kernel]
    type = CrossField
    variable = vx
    psi = psi
    component = 0
  [../]

  [./vy_kernel]
    type = CrossField
    variable = vy
    psi = psi
    component = 1
  [../]

  [./qx_kernel]
    type = Flux
    variable = qx
    cross_field_component = vx
    couple_variable = omega
  [../]

  [./qy_kernel]
    type = Flux
    variable = qy
    cross_field_component = vy
    couple_variable = omega
  [../]

  [./tx_kernel]
    type = Flux
    variable = tx
    cross_field_component = vx
    couple_variable = n
  [../]

  [./ty_kernel]
    type = Flux
    variable = ty
    cross_field_component = vy
    couple_variable = n
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
      variable = 'psi omega n'
      auto_direction = 'x y'
    [../]
  [../]

[]

# Transient (time-dependent) details for simulations go here:
[Executioner]
  type = Transient   # Here we use the Transient Executioner (instead of steady)
  solve_type = 'NEWTON'
  num_steps = 10

  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_norm_type'
  petsc_options_value = 'hypre    boomeramg         preconditioned'

  dt = 1e-4 # each time step will have duration "1"
  l_tol = 1e-4 # Relative tolerance for linear solves
  nl_max_its = 40 # Max number of nonlinear iterations
  nl_abs_tol = 1e-9 # Relative tolerance for nonlienar solves
  nl_rel_tol = 1e-6 # Absolute tolerance for nonlienar solves

[]


[Outputs]
  # execute_on = 'timestep_end'
  exodus = true
  interval = 1
[]


