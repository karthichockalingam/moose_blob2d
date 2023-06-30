//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Flux.h"

registerMooseObject("zebraApp", Flux);

InputParameters
Flux::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("cross_field_component", "cross field");
  params.addRequiredCoupledVar("couple_variable", "couple_variable");
  return params;
}

Flux::Flux(const InputParameters & parameters) : Kernel(parameters),
 _cross_field(coupledValue("cross_field_component")),
 _coupled_variable(coupledValue("couple_variable")),
 _cross_field_var(coupled("cross_field_component")),
 _cross_coupled_var(coupled("couple_variable"))
{}

Real
Flux::computeQpResidual()
{
  return _u[_qp] * _test[_i][_qp] - _coupled_variable[_qp] * _cross_field[_qp] * _test[_i][_qp];
}

Real
Flux::computeQpJacobian()
{
  return _phi[_j][_qp] * _test[_i][_qp];
}


Real
Flux::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (_cross_field_var == jvar) 
    return - _coupled_variable[_qp] * _phi[_j][_qp] * _test[_i][_qp];

   if (_cross_coupled_var == jvar) 
    return - _cross_field[_qp] * _phi[_j][_qp] * _test[_i][_qp];
  
  return 0.0;
}