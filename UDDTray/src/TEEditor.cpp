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

#include "TEEditor.h"

#include "TEHighlighter.h"

TEEditor::TEEditor(QWidget* parent): PolicyEditor(parent) {
  _highlighter = 0;
}

TEEditor::~TEEditor() {
  deleteHighlighter();
}

void TEEditor::deleteHighlighter(){
  if (_highlighter)
    delete _highlighter;
}

void TEEditor::setFile(QString file_path){
  bool flag = file_path.endsWith(".te") || file_path.endsWith(".if");
  enableHighlighting(flag);
  PolicyEditor::setFile(file_path);
}

void TEEditor::enableHighlighting(bool flag){
  deleteHighlighter();
  if (flag){
    _highlighter = new TEHighlighter(document());
  }
}

bool TEEditor::closeEnabled(){
  return true;
}

bool TEEditor::isEditable(){
  return true;
}
