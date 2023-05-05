//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "zebraTestApp.h"
#include "zebraApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
zebraTestApp::validParams()
{
  InputParameters params = zebraApp::validParams();
  return params;
}

zebraTestApp::zebraTestApp(InputParameters parameters) : MooseApp(parameters)
{
  zebraTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

zebraTestApp::~zebraTestApp() {}

void
zebraTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  zebraApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"zebraTestApp"});
    Registry::registerActionsTo(af, {"zebraTestApp"});
  }
}

void
zebraTestApp::registerApps()
{
  registerApp(zebraApp);
  registerApp(zebraTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
zebraTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  zebraTestApp::registerAll(f, af, s);
}
extern "C" void
zebraTestApp__registerApps()
{
  zebraTestApp::registerApps();
}
