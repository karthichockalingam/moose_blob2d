//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DivCurrentSource.h"

registerMooseObject("zebraApp", DivCurrentSource);

InputParameters
DivCurrentSource::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredCoupledVar("div_current", "div_current");
  params.addRequiredParam<Real>("e_value", "Value of e");
  return params;
}

DivCurrentSource::DivCurrentSource(const InputParameters & parameters) : Kernel(parameters),
 _div_current(coupledValue("div_current")),
 _e_value(getParam<Real>("e_value")),
 _div_current_var(coupled("div_current"))
{}

Real
DivCurrentSource::computeQpResidual()
{
  return -(1.0/_e_value) * _div_current[_qp] * _test[_i][_qp];
}

Real
DivCurrentSource::computeQpJacobian()
{
  return 0.0;
}


Real
DivCurrentSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if ( _div_current_var == jvar) 
    return -(1.0/_e_value) * _phi[_j][_qp] * _test[_i][_qp];

  return 0.0;
}
