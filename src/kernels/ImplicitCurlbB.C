//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ImplicitCurlbB.h"

registerMooseObject("zebraApp", ImplicitCurlbB);

InputParameters
ImplicitCurlbB::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("n", "electron density");
  return params;
}

ImplicitCurlbB::ImplicitCurlbB(const InputParameters & parameters) : Kernel(parameters),
 _grad_n(coupledGradient("n")),
 _e(getMaterialProperty<Real>("e")),
 _T(getMaterialProperty<Real>("T")),
 _R(getMaterialProperty<Real>("R")),
 _n_var(coupled("n"))
{}

Real
ImplicitCurlbB::computeQpResidual()
{
  return -((_e[_qp] * _T[_qp])/(_R[_qp] * _R[_qp])) * _grad_n[_qp](1) * _test[_i][_qp];
}

Real
ImplicitCurlbB::computeQpJacobian()
{
  return 0.0;
}


Real
ImplicitCurlbB::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (_n_var == jvar) 
    return -((_e[_qp] * _T[_qp])/(_R[_qp] * _R[_qp])) * _grad_phi[_j][_qp](1) * _test[_i][_qp];

  return 0.0;
}
