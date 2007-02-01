/****************************************************************************/
/// @file    GUIParam_PopupMenu.cpp
/// @author  Daniel Krajzewicz
/// @date    Mai 2003
/// @version $Id: $
///
// The popup-menu which appears hen pressing right mouse button over a
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// copyright : (C) 2001-2007
//  by DLR (http://www.dlr.de/) and ZAIK (http://www.zaik.uni-koeln.de/AFS)
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
// ===========================================================================
// compiler pragmas
// ===========================================================================
#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif


// ===========================================================================
// included modules
// ===========================================================================
#ifdef WIN32
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <iostream>
#include <string>
#include "GUIParameterTableWindow.h"
#include <utils/gui/globjects/GUIGlObject.h>
#include "GUIParam_PopupMenu.h"
#include <utils/gui/tracker/GUIParameterTracker.h>
#include <utils/gui/tracker/TrackerValueDesc.h>
#include <utils/gui/windows/GUIAppEnum.h>
#include <utils/gui/windows/GUIMainWindow.h>
#include <microsim/MSNet.h>

#ifdef _DEBUG
#include <utils/dev/debug_new.h>
#endif // _DEBUG


// ===========================================================================
// used namespaces
// ===========================================================================
using namespace std;


// ===========================================================================
// FOX callback mapping
// ===========================================================================
FXDEFMAP(GUIParam_PopupMenu) GUIParam_PopupMenuMap[]=
    {
        FXMAPFUNC(SEL_COMMAND,  MID_OPENTRACKER, GUIParam_PopupMenu::onCmdOpenTracker),
    };

// Object implementation
FXIMPLEMENT(GUIParam_PopupMenu, FXMenuPane, GUIParam_PopupMenuMap, ARRAYNUMBER(GUIParam_PopupMenuMap))


// ===========================================================================
// method definitions
// ===========================================================================
GUIParam_PopupMenu::GUIParam_PopupMenu(GUIMainWindow &app,
                                       //                                 GUIParameterTable &parent,
                                       GUIParameterTableWindow &parentWindow,
                                       GUIGlObject &o,
                                       const std::string &varName,
                                       ValueSource<SUMOReal> *src)
        : FXMenuPane(&parentWindow), myObject(&o), //myParent(&parent),
        myParentWindow(&parentWindow), myApplication(&app), myVarName(varName),
        mySource(src)
{}


GUIParam_PopupMenu::~GUIParam_PopupMenu()
{
    delete mySource;
}


long
GUIParam_PopupMenu::onCmdOpenTracker(FXObject*,FXSelector,void*)
{
    string trackerName = myVarName + " from " + myObject->getFullName();
    GUIParameterTracker *tr = new GUIParameterTracker(*myApplication,
                              trackerName, *myObject, 0, 0);
    TrackerValueDesc *newTracked = new TrackerValueDesc(
                                       myVarName, RGBColor(0, 0, 0), myObject, myApplication->getCurrentSimTime());
    tr->addTracked(*myObject, mySource->copy(), newTracked);
    tr->create();
    tr->show();
    return 1;
}



/****************************************************************************/

