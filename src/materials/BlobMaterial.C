#include "BlobMaterial.h"

registerMooseObject("zebraApp", BlobMaterial);

InputParameters
BlobMaterial::validParams()
{
  InputParameters params = Material::validParams();
  params.addRequiredParam<Real>("B_value", "Value of B");
  params.addRequiredParam<Real>("e_value", "Value of e");
  params.addRequiredParam<Real>("T_value", "Value of T");
  params.addRequiredParam<Real>("L_value", "Value of L");
  params.addRequiredParam<Real>("R_value", "Value of R");
  return params;
}

BlobMaterial::BlobMaterial(const InputParameters & parameters)
  : Material(parameters),
  _B_value(getParam<Real>("B_value")),
  _B(declareProperty<Real>("B")),
  _e_value(getParam<Real>("e_value")),
  _e(declareProperty<Real>("e")),
  _T_value(getParam<Real>("T_value")),
  _T(declareProperty<Real>("T")),
  _L_value(getParam<Real>("L_value")),
  _L(declareProperty<Real>("L")),
  _R_value(getParam<Real>("R_value")),
  _R(declareProperty<Real>("R"))
{
}
void
BlobMaterial::computeQpProperties()
{
  _B[_qp] = _B_value;
  _e[_qp] = _e_value;
  _T[_qp] = _T_value;
  _L[_qp] = _L_value;
  _R[_qp] = _R_value;
}