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

#include "ImageSelectionBox.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QtDebug>

ImageSelectionBox::ImageSelectionBox(QWidget* parent): QGroupBox(parent) {
  setupUi(this);
}

ImageSelectionBox::~ImageSelectionBox() {
}

void ImageSelectionBox::showImageFileDialogST(){
  QString file_name;
  file_name = QFileDialog::getOpenFileName(this, tr("Open file"), tr("./"), tr("All files (*)"));
  if (!file_name.isEmpty())
    imageFileLE->setText(file_name);
}

void ImageSelectionBox::imageFileNameChangedST(QString file_name){
  QFileInfo info(file_name);
  QPixmap pixmap;
  if (info.exists()){
    if (pixmap.load(file_name)){
      imageLB->setPixmap(pixmap);
      emit(imageFileChanged(file_name));
      return;
    }
  }
  imageLB->setPixmap(pixmap);
}

void ImageSelectionBox::loadImageST(QString file_name){
  imageFileLE->setText(file_name);
}
