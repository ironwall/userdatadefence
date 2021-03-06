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

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "ui_mainwindow.h"

#include "AuditMessageNotificationSettings.h"

class AlertsWatcher;
class AuditMessage;
class MainTab;
class TrayIcon;

class MainWindow: public QMainWindow, public Ui::MainWindow{
    Q_OBJECT
public:
  MainWindow(QWidget* parent = 0);
  virtual ~MainWindow();
  static MainWindow* instance();
  void createTrayIcon();
  void setVisible(bool is_visible);
  QString alertsEditorText();
  void offPolicyGenerationActions();
  void reloadAlertsList();
protected:
  void initAlertsWatcher();
  virtual void closeEvent(QCloseEvent*);
public slots:
  void changeVisibleST();
  void quitST();
  void clearLogST();
  void editPreferencesST();
signals:
  void visibleChanged(bool is_visible);
  void logCleared();
  void editorsFontChanged(QFont font);
public:
private:
  TrayIcon* trayIcon;
  AlertsWatcher* alertsWatcher;
  bool iconSwitched;
  static MainWindow* _instance;
  bool _visible;
private:
  friend class MainTab;
};

#endif /* MAINWINDOW_H_ */
