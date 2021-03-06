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

#include "ApplicationsMenuItem.h"

#include "MainWindow.h"

ApplicationsMenuItem::ApplicationsMenuItem() {
  icon = 0;
}

ApplicationsMenuItem::~ApplicationsMenuItem() {
  if (icon)
    delete icon;
}

bool ApplicationsMenuItem::processAttributes(){
  setName(readXMLAttribute("name"));
  text = readXMLAttribute("text");
  loadIcon();
  bool result;
  result = processExtraAttributes();
  return result;
}

void ApplicationsMenuItem::loadIcon(){
  setIcon(readXMLAttribute("icon"));
}

void ApplicationsMenuItem::setIcon(QString file_name){
  iconFile = file_name;
  if (!iconFile.isEmpty())
    icon = new QIcon(iconFile);
}

bool ApplicationsMenuItem::endElement(){
  return true;
}

void ApplicationsMenuItem::writeAttributes(QXmlStreamWriter* xml_writer){
  xml_writer->writeAttribute("name", name());
  xml_writer->writeAttribute("text", text);
  xml_writer->writeAttribute("icon", iconFile);
}

