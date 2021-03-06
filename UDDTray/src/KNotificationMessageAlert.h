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
#ifndef KNOTIFICATIONMESSAGEALERT_H_
#define KNOTIFICATIONMESSAGEALERT_H_

#include <QString>
#include <QByteArray>

#include "KNotificationMessage.h"

class AuditMessage;
class AuditMessageNotification;

class KNotificationMessageAlert: public KNotificationMessage{
public:
  KNotificationMessageAlert();
  virtual ~KNotificationMessageAlert();
  virtual QString title();
  virtual QString text();
  virtual QByteArray pixmapBytes();
  virtual QStringList actions();
  virtual void actionActivated(int action_id);
  void setCaption(QString caption);
  void setText(QString message);
  void setPixmapBytes(QByteArray pixmap_bytes);
  void setFromMessage(AuditMessage* message);
  void setFromMessageNotification(AuditMessageNotification* message_notification, QString text);
private:
  QString _caption;
  QString _message;
  QByteArray _imageBytes;
};

#endif /* KNOTIFICATIONMESSAGEALERT_H_ */
