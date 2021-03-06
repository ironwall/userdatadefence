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

#ifndef AUDITMESSAGETIMESTAMP_H_
#define AUDITMESSAGETIMESTAMP_H_

#include <QString>

class AuditMessageTimeStamp {
public:
  AuditMessageTimeStamp();
  virtual ~AuditMessageTimeStamp();
  QString toString();
public:
  unsigned int second;
  unsigned int milliSecond;
  unsigned long serialNumber;
  QString hostName;
};

#endif /* AUDITMESSAGETIMESTAMP_H_ */
