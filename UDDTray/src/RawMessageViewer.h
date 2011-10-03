/***************************************************************************
 *   Copyright (C) 2011 by Hramchenko                                      *
 *   hramchenko@bk.ru                                                      *
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

#ifndef RAWMESSAGEVIEWER_H_
#define RAWMESSAGEVIEWER_H_

#include "RawMessagesTextEdit.h"

#include <QModelIndex>

class RawMessageViewer: public RawMessagesTextEdit {
  Q_OBJECT
public:
  RawMessageViewer(QWidget* parent);
  virtual ~RawMessageViewer();
public slots:
  //void alertsSelectedST(QModelIndexList indexes);
  void messagesSelectedST(QModelIndexList index_list);
  void appendMessageST();
  bool copyEnabled();
  bool selectionReadActionsEnabled();
signals:
  void messageNeedAppending(QString message);
};

#endif /* RAWMESSAGEVIEWER_H_ */