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

#ifndef ALERTSWATCHER_H_
#define ALERTSWATCHER_H_

#include <QObject>
#include <QList>

#include "AVCVisitor.h"

class KNotification;
class QDBusInterface;
class AVCAnalyzer;
class AuditMessageViewer;
class AuditMessage;
class UDDaemonInterface;
class AuditMessageNotificationSettings;

class AlertsWatcher: public QObject, public AVCVisitor{
  Q_OBJECT
public:
  virtual ~AlertsWatcher();
  static AlertsWatcher* instance();
  void closeAllAlerts();
  void setLastMessage(AuditMessage* message);
  void processNewMessage(AuditMessage* message);
  void connectToInterface();
  void connectSignals();
  QString generatePolicy();
  void process(AuditMessage*& message);
protected:
  AlertsWatcher();
  bool needNotifications();
  void showIndividualNotification(AuditMessage* message);
  void collectNotificationStatistics(AuditMessage* message);
signals:
  void messageReceived(AuditMessage* message);
  void modeChanged(QString mode, int max_level);
public slots:
  void AVCAlert(QString text);
  void clearLogST();
  void loadOldAlertsST();
private:
  void showLastAlerts(QMutableListIterator<AuditMessage*>& iter);
  void saveSettings();
  void clearStatistics();
  void checkIndividualAlerts();
  void showMultipleNotification();
public:
  bool loadingOldAlerts;
  bool showIndividualAlerts;
private:
  KNotification* notificationManager;
  UDDaemonInterface* avcbusInterface;
  AVCAnalyzer* analyzer;
  AuditMessageViewer* messagesViewer;
  AuditMessageNotificationSettings* notificationSettings;
  static AlertsWatcher* _instance;
};

#endif /* ALERTSWATCHER_H_ */
