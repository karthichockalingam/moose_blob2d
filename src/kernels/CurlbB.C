//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CurlbB.h"

registerMooseObject("zebraApp", CurlbB);

InputParameters
CurlbB::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("n", "electron density");
  params.addRequiredParam<unsigned>(
      "component",
      "0,1,2 depending on if we are solving the x,y,z component of the Corrector equation");
  return params;
}

CurlbB::CurlbB(const InputParameters & parameters) : Kernel(parameters),
 _grad_n(coupledGradient("n")),
 _e(getMaterialProperty<Real>("e")),
 _T(getMaterialProperty<Real>("T")),
 _R(getMaterialProperty<Real>("R"))
{}

Real
CurlbB::computeQpResidual()
{
  return -((_e[_qp] * _T[_qp])/(_R[_qp] * _R[_qp])) * _grad_n[_qp](1) * _test[_i][_qp];
}

Real
CurlbB::computeQpJacobian()
{
  return 0.0;
}
