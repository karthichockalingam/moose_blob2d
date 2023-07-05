//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "OmegaImplicitDivCurrent.h"

registerMooseObject("zebraApp", OmegaImplicitDivCurrent);

InputParameters
OmegaImplicitDivCurrent::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("n", "electron density");
  params.addRequiredCoupledVar("psi", "sheath closure");
  return params;
}

OmegaImplicitDivCurrent::OmegaImplicitDivCurrent(const InputParameters & parameters) : Kernel(parameters),
 _n(coupledValue("n")),
 _psi(coupledValue("psi")),
 _L(getMaterialProperty<Real>("L")),
 _psi_var(coupled("psi")),
 _n_var(coupled("n"))
{}

Real
OmegaImplicitDivCurrent::computeQpResidual()
{
  return - (1.0/_L[_qp]) * _n[_qp] * _psi[_qp] * _test[_i][_qp];
}

Real
OmegaImplicitDivCurrent::computeQpJacobian()
{
  return 0.0;
}


Real
OmegaImplicitDivCurrent::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (_psi_var == jvar) 
    return - (1.0/_L[_qp]) * _n[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 

  if (_n_var == jvar) 
    return - (1.0/_L[_qp]) * _psi[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 
  
  return 0.0;
}