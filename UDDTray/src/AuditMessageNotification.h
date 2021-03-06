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

#ifndef AuditMessageNotification_H_
#define AuditMessageNotification_H_

#include <QPixmap>
#include <QString>
#include <QByteArray>
#include <QIcon>

#include "XMLFileElement.h"

class QStandardItem;
class AuditMessage;
class KNotificationMessageAlert;
class AuditMessageNotificationSettings;

class AuditMessageNotification: public XMLFileElement{
public:
  AuditMessageNotification(AuditMessageNotificationSettings* notification_settings);
  virtual ~AuditMessageNotification();
  bool processAttributes();
  virtual XMLFileElement* newElement(const QString& name, bool& error_flag);
  virtual bool processExtraAttributes() = 0;
  virtual void writeExtraAttributes(QXmlStreamWriter* xml_writer) = 0;
  void writeAttributes(QXmlStreamWriter* xml_writer);
  bool hasSubElements();
  virtual bool checkNotification(AuditMessage* message) = 0;
  virtual QString formatMessage(AuditMessage* message);
  virtual QString filterString();
  virtual void setFilterString(QString filter);
  AuditMessageNotificationSettings* notificationSettings();
  QPixmap pixmap();
  void setPixmap(QPixmap pixmap);
  void loadPixmap(QString file_name);
  QIcon icon();
  QByteArray pixmapBytes();
  QString caption();
  void setCaption(QString caption);
  QString messageFormat();
  void setMessageFormat(QString format);
  QString imagePath();
  int level();
  void setLevel(int level);
  virtual bool needNotification();
protected:
  QString defaultPixmapFile();
  QString defaultCaption();
  QString defaultMessageFormat();
  int defaultLevel();
public:
protected:
  QString _filterString;
private:
  QPixmap _pixmap;
  QIcon _icon;
  QByteArray _pixmapBytes;
  QString _caption;
  QString _messageFormat;
  QString _imagePath;
  int _level;
  AuditMessageNotificationSettings* _notificationSettings;
};

#endif /* NOTIFICATIONMESSAGE_H_ */
