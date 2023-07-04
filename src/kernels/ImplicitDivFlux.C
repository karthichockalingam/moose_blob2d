//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ImplicitDivFlux.h"

registerMooseObject("zebraApp", ImplicitDivFlux);

InputParameters
ImplicitDivFlux::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("vx", "flux in x-diretion");
  params.addRequiredCoupledVar("vy", "flux in y-diretion");
  return params;
}

ImplicitDivFlux::ImplicitDivFlux(const InputParameters & parameters) : Kernel(parameters),
 _vx(coupledValue("vx")),
 _vy(coupledValue("vy")),
 _vx_var(coupled("vx")),
 _vy_var(coupled("vy"))
{}

Real
ImplicitDivFlux::computeQpResidual()
{
  return -_u[_qp] * (_vx[_qp] * _grad_test[_i][_qp](0) + _vy[_qp] * _grad_test[_i][_qp](1));
}

Real
ImplicitDivFlux::computeQpJacobian()
{
  return -_phi[_j][_qp] * (_vx[_qp] * _grad_test[_i][_qp](0) + _vy[_qp] * _grad_test[_i][_qp](1));
}

Real
ImplicitDivFlux::computeQpOffDiagJacobian(unsigned int jvar)
{
  if ( _vx_var == jvar) 
    return -_u[_qp] * (_phi[_j][_qp] * _grad_test[_i][_qp](0));

  if ( _vy_var == jvar) 
    return -_u[_qp] * (_phi[_j][_qp] * _grad_test[_i][_qp](1));

  return 0.0;
}
