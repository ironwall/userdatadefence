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
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QList>
#include <QMap>
#include <QString>

template<class T> void clearListOfPointers(QList<T>& list){
  while (!list.isEmpty())
    delete list.takeFirst();
}

template<class T> void deleteListOfPointers(QList<T>*& list){
  if (!list)
    return;
  clearListOfPointers<T>(*list);
  delete list;
  list = 0;
}

template<class K, class T> void clearMapOfPointers(QMap<K, T>& map){
  QMapIterator<K, T> iter(map);
   while (iter.hasNext()){
       iter.next();
       delete iter.value();
   }
   map.clear();
}

template<class K, class T> void deleteMapOfPointers(QMap<K, T>*& map){
  if (!map)
    return;
  clearMapOfPointers<K, T>(*map);
  delete map;
  map = 0;
}

#endif
