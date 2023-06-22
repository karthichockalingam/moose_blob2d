//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Convective.h"

registerMooseObject("zebraApp", Convective);

InputParameters
Convective::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("u", "x-velocity");
  return params;
}

Convective::Convective(const InputParameters & parameters) : Kernel(parameters),
 _u_old(coupledValueOld("u")),
 _grad_u_old(coupledGradientOld("u"))
{}

Real
Convective::computeQpResidual()
{
  return (_u_old[_qp] * _grad_u_old[_qp](0)) * _test[_i][_qp];
}

Real
Convective::computeQpJacobian()
{
  return 0.0;
}
