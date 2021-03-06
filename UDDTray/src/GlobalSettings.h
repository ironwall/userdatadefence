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

#ifndef GLOBALSETTINGS_H_
#define GLOBALSETTINGS_H_

#include <QFont>
#include <QObject>

class QSettings;

class GlobalSettings: public QObject {
  Q_OBJECT
public:
  virtual ~GlobalSettings();
  static GlobalSettings* instance();
  int systemMessagesUpdationTime();
  void setSystemMessagesUpdationTime(int interval);
  int maxAuditMessagesCount();
  int auditMessagesReserve();
  int oldMessagesLoadingDelay();
  bool clearAlertsEditorAfterGeneration();
  void setClearAlertsEditorAfterGeneration(bool value);
  void setMaxAuditMessagesCount(int count);
  void setAuditMessagesReserve(int count);
  void setOldMessagesLoadingDelay(int count);
  int deletionAuditMessagesCount();
  QFont editorsFont();
  void setEditorsFont(QFont font);
  QString lastOpenedFile();
  QString lastOpenedFileDir();
  void setLastOpenedFile(QString path);
  QString getConfigFile(QString local_path);
  QString uddHome();
  QString uddShare();
signals:
  void editorsFontChanged();
protected:
  GlobalSettings(QObject* parent = 0);
private:
  void loadSettings();
  void makeDirIfNeed(QString path);
private:
  static GlobalSettings* _instance;
  QSettings* _settings;
  QFont _editorsFont;
  int _systemMessagesUpdationTime;
  int _maxAuditMessagesCount;
  int _auditMessagesReserve;
  int _oldMessagesLoadingDelay;
  QString _lastOpenedFile;
  bool _clearAlertsEditorAfterGeneration;
};

#endif /* GLOBALSETTINGS_H_ */
