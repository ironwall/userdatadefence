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

#ifndef GENERATEDPOLICYTEXTEDIT_H_
#define GENERATEDPOLICYTEXTEDIT_H_

#include "TEEditor.h"
#include <QProcess>

class GeneratedPolicyTextEdit: public TEEditor{
  Q_OBJECT
public:
  GeneratedPolicyTextEdit(QWidget* parent);
  virtual ~GeneratedPolicyTextEdit();
  bool closeEnabled();
public slots:
  void clearLogST();
  void generatePolicyAllST();
  void generatePolicyEditorST();
  void generatePolicySystemST();
  void audit2AllowFinishedST (int exitCode, QProcess::ExitStatus exitStatus);
private:
  void runAudit2Allow(QString messages);
  QString auditMessages();
  QString editorMessages();
  QString systemMessages();
  void clearAlertsEditorIfNeed();
private:
  QProcess* audit2Allow;
};

#endif /* GENERATEDPOLICYTEXTEDIT_H_ */
