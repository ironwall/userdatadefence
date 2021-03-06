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

#include "KNotificationMessageAlert.h"

#include <QPixmap>
#include <QDebug>

#include "MainWindow.h"
#include "KNotification.h"

KNotificationMessageAlert::KNotificationMessageAlert(): KNotificationMessage(){
}

KNotificationMessageAlert::~KNotificationMessageAlert() {
}

void KNotificationMessageAlert::setCaption(QString caption){
  _caption = caption;
}

void KNotificationMessageAlert::setText(QString message){
  _message = message;
}

void KNotificationMessageAlert::setPixmapBytes(QByteArray pixmap_bytes){
  _imageBytes = pixmap_bytes;
}

QString KNotificationMessageAlert::text(){
  return _message;
}

QString KNotificationMessageAlert::title(){
  return _caption;
}

QByteArray KNotificationMessageAlert::pixmapBytes(){
  return _imageBytes;
}

QStringList KNotificationMessageAlert::actions(){
  QStringList action_list;
  action_list.append("View");
  action_list.append("Inore");
  return action_list;
}

void KNotificationMessageAlert::actionActivated(int action_id){
  if (action_id == 1){
    MainWindow::instance()->setVisible(true);
  }
  else if (action_id == 2){
    KNotification::instance()->closeMessage(this);
  }
}

void KNotificationMessageAlert::setFromMessage(AuditMessage* message){
  setFromMessageNotification(message->messageNotification(), message->formattedMessage());
}

void KNotificationMessageAlert::setFromMessageNotification(AuditMessageNotification* message_notification, QString text){
  setText(text);
  setCaption(message_notification->caption());
  setPixmapBytes(message_notification->pixmapBytes());
}





