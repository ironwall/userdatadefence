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

#include "AuditMessageNotificationSettings.h"

#include <QRegExp>

#include <QStandardItem>
#include <QVariant>
#include <QtDebug>
#include <QDir>

#include "NotificationConfigParser.h"
#include "functions.h"
#include "AuditMessageTypeFilterNotification.h"
#include "GlobalSettings.h"

AuditMessageNotificationSettings* AuditMessageNotificationSettings::_currentSettings = 0;
AuditMessageNotificationSettings* AuditMessageNotificationSettings::_configurationSettings = 0;


AuditMessageNotificationSettings::AuditMessageNotificationSettings() {
  _defaultNotification = 0;
  loadSettings();
}

AuditMessageNotificationSettings::~AuditMessageNotificationSettings() {
  if (_defaultNotification)
    delete _defaultNotification;
  clearListOfPointers<AuditMessageNotification*>(_typeFilterNotificationsList);
  clearListOfPointers<AuditMessageNotification*>(_regExpFilterNotificationsList);
}

AuditMessageNotificationSettings* AuditMessageNotificationSettings::currentSettings(){
  if (!_currentSettings){
    _currentSettings = new AuditMessageNotificationSettings();
  }
  return _currentSettings;
}

AuditMessageNotificationSettings* AuditMessageNotificationSettings::configurationSettings(){
  if (!_configurationSettings)
    _configurationSettings = new AuditMessageNotificationSettings();
  return _configurationSettings;
}

void AuditMessageNotificationSettings::clearConfigurationSettings(){
  if (!_configurationSettings)
    return;
  delete _configurationSettings;
  _configurationSettings = 0;
}

void AuditMessageNotificationSettings::applyConfigurationSettings(){
  if (!_configurationSettings)
    return;
  delete _currentSettings;
  _currentSettings = configurationSettings();
  _configurationSettings = 0;
}

QString AuditMessageNotificationSettings::configFile(){
  QString file_name = GlobalSettings::instance()->getConfigFile("config/udd_notifications.xml");
  return file_name;
}


void AuditMessageNotificationSettings::loadSettings(){
  NotificationConfigParser parser(this);
  parser.read(configFile());
}


bool AuditMessageNotificationSettings::processAttributes(){
  return true;
}

XMLFileElement* AuditMessageNotificationSettings::newElement(const QString& name, bool& error_flag){
  if (name == "default_settings"){
    _defaultNotification = new AuditMessageDefaultNotification(this);
    return _defaultNotification;
  }
  if (name == "event"){
    AuditMessageNotification* events_type = new AuditMessageTypeFilterNotification(this);
    _typeFilterNotificationsList.push_back(events_type);
    return events_type;
  }
  if (name == "event_pattern"){
    AuditMessageNotification* event_pattern = new AuditMessageRegExpFilterNotification(this);
    _regExpFilterNotificationsList.push_back(event_pattern);
    return event_pattern;
  }
  if (name == "multiple_events"){
    _multipleEventsNotification = new AuditMessageMultipleEventsNotification(this);
    return _multipleEventsNotification;
  }
  error_flag = true;
  return 0;
}

QString AuditMessageNotificationSettings::elementName(){
  return "notification_config";
}

void AuditMessageNotificationSettings::writeSubElements(QXmlStreamWriter* xml_writer){
  defaultNotification()->writeElement(xml_writer);
  multipleEventsNotification()->writeElement(xml_writer);
  writeMessageNotificationsList(xml_writer, typeFilterNotificationsList());
  writeMessageNotificationsList(xml_writer, regExpFilterNotificationsList());
}

void AuditMessageNotificationSettings::writeMessageNotificationsList(QXmlStreamWriter* xml_writer, QList<AuditMessageNotification*>& list){
  QListIterator<AuditMessageNotification*> iter(list);
  AuditMessageNotification* notification;
  while (iter.hasNext()){
    notification = iter.next();
    notification->writeElement(xml_writer);
  }
}

AuditMessageNotification* AuditMessageNotificationSettings::searchNotificationMessage(AuditMessage* message){
  AuditMessageNotification* result = 0;
  result = searchNotificationWithEventsList(_regExpFilterNotificationsList, message);
  if (result)
    return result;
  result = searchNotificationWithEventsList(_typeFilterNotificationsList, message);
  if (result)
    return result;
  return _defaultNotification;
}

AuditMessageNotification* AuditMessageNotificationSettings::searchNotificationWithEventsList(QList<AuditMessageNotification*>& list, AuditMessage* message){
  AuditMessageNotification* result = 0;
  QListIterator<AuditMessageNotification*> iter(list);
  while (iter.hasNext()){
    result = iter.next();
    if (result->checkNotification(message))
      return result;
  }
  return 0;
}

AuditMessageDefaultNotification* AuditMessageNotificationSettings::defaultNotification(){
  return _defaultNotification;
}

AuditMessageMultipleEventsNotification* AuditMessageNotificationSettings::multipleEventsNotification(){
  return _multipleEventsNotification;
}

QList<AuditMessageNotification*>& AuditMessageNotificationSettings::typeFilterNotificationsList(){
  return _typeFilterNotificationsList;
}

QList<AuditMessageNotification*>& AuditMessageNotificationSettings::regExpFilterNotificationsList(){
  return _regExpFilterNotificationsList;
}

