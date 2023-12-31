//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DivFlux.h"

registerMooseObject("zebraApp", DivFlux);

InputParameters
DivFlux::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("jx", "flux in x-diretion");
  params.addRequiredCoupledVar("jy", "flux in y-diretion");
  return params;
}

DivFlux::DivFlux(const InputParameters & parameters) : Kernel(parameters),
 _grad_jx(coupledGradient("jx")),
 _grad_jy(coupledGradient("jy"))
{}

Real
DivFlux::computeQpResidual()
{
  return (_grad_jx[_qp](0) + _grad_jy[_qp](1)) * _test[_i][_qp];
}

Real
DivFlux::computeQpJacobian()
{
  return 0.0;
}
