//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010      Bastian Holst <bastianholst@gmx.de>
//

#ifndef WIDGETGRAPHICSITEMPRIVATE_H
#define WIDGETGRAPHICSITEMPRIVATE_H

#include "WidgetGraphicsItem.h"

#include <QtGui/QWidget>

#include <QtCore/QDebug>

namespace Marble
{

class WidgetGraphicsItemPrivate
{
 public:
    WidgetGraphicsItemPrivate() {
    }
    
    ~WidgetGraphicsItemPrivate() {
        delete m_widget;
    }
    
    QWidget *m_widget;
    QWidget *m_marbleWidget;
};

}

#endif // SCREENGRAPHICSITEMPRIVATE_H