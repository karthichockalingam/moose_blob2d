//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CrossField.h"

registerMooseObject("zebraApp", CrossField);

InputParameters
CrossField::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("psi", "sheath closure");
  params.addRequiredParam<unsigned>(
      "component",
      "0,1,2 depending on if we are solving the x,y,z component of the Corrector equation");
  return params;
}

CrossField::CrossField(const InputParameters & parameters) : Kernel(parameters),
 _grad_psi(coupledGradient("psi")),
 _B(getMaterialProperty<Real>("B")),
 _component(getParam<unsigned>("component")),
 _psi_var(coupled("psi"))
{}

Real
CrossField::computeQpResidual()
{
  int i, j;

  if(_component == 0)
  {
    i = 1;
    j = 1;
  }

  if(_component == 1)
  {
    i = 0;
    j = -1;
  }

  return _u[_qp] * _test[_i][_qp] - (1.0/_B[_qp]) * j * _grad_psi[_qp](i) * _test[_i][_qp];
}

Real
CrossField::computeQpJacobian()
{
  return _phi[_j][_qp] * _test[_i][_qp];
}


Real
CrossField::computeQpOffDiagJacobian(unsigned int jvar)
{
    int i, j;

    if(_component == 0)
  {
    i = 1;
    j = 1;
  }

  if(_component == 1)
  {
    i = 0;
    j = -1;
  }

  if (_psi_var == jvar) 
    return - (1.0/_B[_qp]) * j * _grad_phi[_j][_qp](i) * _test[_i][_qp];
  
  return 0.0;
}
