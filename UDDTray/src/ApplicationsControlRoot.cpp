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

#include "ApplicationsControlRoot.h"

#include <QDir>

#include "functions.h"
#include "ApplicationsGroup.h"
#include "ApplicationsParser.h"
#include "TrayIcon.h"
#include "MainWindow.h"
#include "GlobalSettings.h"

ApplicationsControlRoot* ApplicationsControlRoot::_currentApplications = 0;
ApplicationsControlRoot* ApplicationsControlRoot::_configurationApplications = 0;

ApplicationsControlRoot::ApplicationsControlRoot() {
  loadSettings();
}

ApplicationsControlRoot::~ApplicationsControlRoot() {
  clearListOfPointers<ApplicationsSettingsParameter*>(applicationsGroups);
}

ApplicationsControlRoot* ApplicationsControlRoot::currentApplications(){
  if (!_currentApplications){
    _currentApplications = new ApplicationsControlRoot();
  }
  return _currentApplications;
}

QString ApplicationsControlRoot::configFile(){
  QString file_name = GlobalSettings::instance()->getConfigFile("config/udd_applications.xml");
  return file_name;
}

void ApplicationsControlRoot::loadSettings(){
  ApplicationsParser parser(this);
  parser.read(configFile());
}


ApplicationsControlRoot* ApplicationsControlRoot::configurationApplications(){
  if (!_configurationApplications){
    _configurationApplications = new ApplicationsControlRoot();
  }
  return _configurationApplications;
}

void ApplicationsControlRoot::applyConfiguration(){
  if (!_configurationApplications)
    return;
  delete _currentApplications;
  _currentApplications = configurationApplications();
  _configurationApplications = 0;
  TrayIcon::instance()->reloadMenu();
  MainWindow::instance()->reloadAlertsList();
}

void ApplicationsControlRoot::clearConfiguration(){
  if (!_configurationApplications)
    return;
  delete _configurationApplications;
  _configurationApplications = 0;
}

bool ApplicationsControlRoot::processAttributes(){
  return true;
}

XMLFileElement* ApplicationsControlRoot::newElement(const QString& name, bool& error_flag){
  if (name != "applications_group"){
    error_flag = true;
    return 0;
  }
  return appendNewItem();
}

void ApplicationsControlRoot::appendMenuItems(QMenu* menu){
  QListIterator<ApplicationsSettingsParameter*> iter(applicationsGroups);
  while (iter.hasNext()){
    ApplicationsGroup* group = (ApplicationsGroup*)iter.next();
    group->appendMenuItems(menu);
  }
}

QString ApplicationsControlRoot::elementName(){
  return "controllable_applications";
}

void ApplicationsControlRoot::writeSubElements(QXmlStreamWriter* xml_writer){
  QListIterator<ApplicationsSettingsParameter*> iter(applicationsGroups);
  ApplicationsGroup* group;
  while (iter.hasNext()){
    group = (ApplicationsGroup*)iter.next();
    group->writeElement(xml_writer);
  }
}

QList<ApplicationsSettingsParameter*>* ApplicationsControlRoot::subElements(){
  return &applicationsGroups;
}

ApplicationsSettingsParameter* ApplicationsControlRoot::appendNewItem(){
  ApplicationsGroup* group = new ApplicationsGroup();
  group->text = "<new>";
  applicationsGroups.push_back(group);
  return group;
}

