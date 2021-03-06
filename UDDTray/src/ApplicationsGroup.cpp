/***************************************************************************
 *   Copyright (C) 2011 by Hramchenko                                      *
 *   v.hramchenko@gmail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ***************************************************************************/

#include "ApplicationsGroup.h"

#include "ApplicationsGroupMode.h"
#include "MainWindow.h"
#include "TrayIcon.h"
#include "functions.h"

ApplicationsGroup::ApplicationsGroup() {
  traySubMenu = 0;
}

ApplicationsGroup::~ApplicationsGroup() {
  clearListOfPointers<ApplicationsSettingsParameter*>(modes);
}

bool ApplicationsGroup::processExtraAttributes(){
  return true;
}

XMLFileElement* ApplicationsGroup::newElement(const QString& name, bool& error_flag){
  if (name != "group_mode"){
    error_flag = true;
    return 0;
  }
  return appendNewItem();
}

bool ApplicationsGroup::endElement(){
  return true;
}

QString ApplicationsGroup::elementName(){
  return "applications_group";
}

void ApplicationsGroup::writeSubElements(QXmlStreamWriter* xml_writer){
  QListIterator<ApplicationsSettingsParameter*> iter(modes);
  ApplicationsGroupMode* mode;
  while (iter.hasNext()){
    mode = (ApplicationsGroupMode*)iter.next();
    mode->writeElement(xml_writer);
  }

}

void ApplicationsGroup::appendMenuItems(QMenu* menu){
  traySubMenu = new QMenu(text, menu);
  if (icon)
    traySubMenu->setIcon(*icon);
  menu->addMenu(traySubMenu);
  QListIterator<ApplicationsSettingsParameter*> iter(modes);
  while (iter.hasNext()){
    ApplicationsGroupMode* mode = (ApplicationsGroupMode*)iter.next();
    mode->appendMenuItems(traySubMenu);
  }
  ApplicationsGroupMode* front = (ApplicationsGroupMode*)modes.front();
  if (modes.count())
    front->setActive(true);
}

QList<ApplicationsSettingsParameter*>* ApplicationsGroup::subElements(){
  return &modes;
}

ApplicationsSettingsParameter* ApplicationsGroup::appendNewItem(){
  ApplicationsGroupMode* mode = new ApplicationsGroupMode(this);
  modes.push_back(mode);
  return mode;
}
