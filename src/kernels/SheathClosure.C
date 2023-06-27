//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SheathClosure.h"

registerMooseObject("zebraApp", SheathClosure);

InputParameters
SheathClosure::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("w", "vorticity");
  return params;
}

SheathClosure::SheathClosure(const InputParameters & parameters) : Kernel(parameters),
 _w_old(coupledValueOld("w_old")),
 _B(getMaterialProperty<Real>("B"))
{}

Real
SheathClosure::computeQpResidual()
{
  return (1.0/(_B[_qp] * _B[_qp])) * _grad_u[_qp] * _grad_test[_i][_qp] + _w_old[_qp] * _test[_i][_qp];
}

Real
SheathClosure::computeQpJacobian()
{
  return (1.0/(_B[_qp] * _B[_qp])) * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
