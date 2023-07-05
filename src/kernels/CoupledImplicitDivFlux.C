//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CoupledImplicitDivFlux.h"

registerMooseObject("zebraApp", CoupledImplicitDivFlux);

InputParameters
CoupledImplicitDivFlux::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("psi", "flux in x-diretion");
  return params;
}

CoupledImplicitDivFlux::CoupledImplicitDivFlux(const InputParameters & parameters) : Kernel(parameters),
 _grad_psi(coupledGradient("psi")),
 _B(getMaterialProperty<Real>("B")),
 _psi_var(coupled("psi"))
{}

Real
CoupledImplicitDivFlux::computeQpResidual()
{

  Real vx = (1.0/_B[_qp]) * _grad_psi[_qp](1);
  Real vy = -(1.0/_B[_qp]) * _grad_psi[_qp](0);

  return -_u[_qp] * (vx * _grad_test[_i][_qp](0) + vy * _grad_test[_i][_qp](1));
}

Real
CoupledImplicitDivFlux::computeQpJacobian()
{
  Real vx = (1.0/_B[_qp]) * _grad_psi[_qp](1);
  Real vy = -(1.0/_B[_qp]) * _grad_psi[_qp](0);

  return -_phi[_j][_qp] * (vx * _grad_test[_i][_qp](0) + vy * _grad_test[_i][_qp](1));
}

Real
CoupledImplicitDivFlux::computeQpOffDiagJacobian(unsigned int jvar)
{
  if ( _psi_var == jvar) 
  {
     Real vx = (1.0/_B[_qp]) *  _grad_phi[_j][_qp](1);
     Real vy = -(1.0/_B[_qp]) *  _grad_phi[_j][_qp](0);

    return -_u[_qp] * (vx * _grad_test[_i][_qp](0) + vy * _grad_test[_i][_qp](1));
  }

  return 0.0;
}
