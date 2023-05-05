#include "zebraApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
zebraApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  return params;
}

zebraApp::zebraApp(InputParameters parameters) : MooseApp(parameters)
{
  zebraApp::registerAll(_factory, _action_factory, _syntax);
}

zebraApp::~zebraApp() {}

void
zebraApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"zebraApp"});
  Registry::registerActionsTo(af, {"zebraApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
zebraApp::registerApps()
{
  registerApp(zebraApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
zebraApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  zebraApp::registerAll(f, af, s);
}
extern "C" void
zebraApp__registerApps()
{
  zebraApp::registerApps();
}
