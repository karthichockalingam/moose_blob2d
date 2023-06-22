//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"

class BlobMaterial : public Material
{
public:
  BlobMaterial(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

private:
  /// member variable to hold the computed diffusivity coefficient
  const Real _B_value;
  MaterialProperty<Real> & _B;

  const Real _e_value;
  MaterialProperty<Real> & _e;

  const Real _T_value;
  MaterialProperty<Real> & _T;

  const Real _L_value;
  MaterialProperty<Real> & _L;

  const Real _R_value;
  MaterialProperty<Real> & _R;
};