//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once


#include "Kernel.h"

/**
 * This kernel implements the Laplacian operator:
 * $\nabla u \cdot \nabla \phi_i$
 */
class ImplicitCurlbB : public Kernel
{ 
public:
  static InputParameters validParams();

  ImplicitCurlbB(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  virtual Real computeQpOffDiagJacobian(unsigned jvar) override;

  const VariableGradient & _grad_n;
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _T;
  const MaterialProperty<Real> & _R;
  
  unsigned int _n_var;
};
