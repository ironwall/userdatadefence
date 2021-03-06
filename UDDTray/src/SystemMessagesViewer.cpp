/***************************************************************************
 *   Copyright (C) 2011 by Hramchenko                                      *
 *   v.hramchenko@gmail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ***************************************************************************/

#include "SystemMessagesViewer.h"

#include <QTimer>
#include <QtDebug>

#include "AlertsDepositary.h"
#include "MainWindow.h"
#include "UDDaemonInterface.h"
#include "GlobalSettings.h"

SystemMessagesViewer::SystemMessagesViewer(QWidget* parent): PolicyEditor(parent) {
  updationTimer = new QTimer();
  connect(updationTimer, SIGNAL(timeout()), this, SLOT(updateST()));
  lastLogLine = AlertsDepositary::instance()->lastSystemMessage;
}

SystemMessagesViewer::~SystemMessagesViewer() {
  delete updationTimer;
}

void SystemMessagesViewer::setTimerInterval(){
  int interval = GlobalSettings::instance()->systemMessagesUpdationTime();
  updationTimer->setInterval(interval);
}

void SystemMessagesViewer::updateST(){
  QString last_messages;
  last_messages = UDDaemonInterface::instance()->loadLastMessages(lastLogLine);
  if ((!last_messages.isEmpty()) && (last_messages != oldMessage))
    append(last_messages);
  oldMessage = last_messages;
  lastLogLine = UDDaemonInterface::instance()->loadLastMessagesLines(1);
  setTimerInterval();
}

void SystemMessagesViewer::activated(){
  updateST();
  updationTimer->start();
}

void SystemMessagesViewer::deactivated(){
  updationTimer->stop();
}
