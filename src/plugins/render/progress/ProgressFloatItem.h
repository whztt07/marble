//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010 Dennis Nienhüser <earthwings@gentoo.org>
//

#ifndef PROGRESS_FLOAT_ITEM_H
#define PROGRESS_FLOAT_ITEM_H

#include "AbstractFloatItem.h"

#include <QtCore/QMutex>
#include <QtCore/QObject>
#include <QtCore/QTimer>

namespace Marble
{

class MarbleWidget;

/**
 * @brief A float item that shows a pie-chart progress
 * indicator when downloads are active
 */
class ProgressFloatItem  : public AbstractFloatItem
{
    Q_OBJECT

    Q_INTERFACES( Marble::RenderPluginInterface )

    MARBLE_PLUGIN( ProgressFloatItem )

 public:
    explicit ProgressFloatItem ( const QPointF &point = QPointF( -150.0, -10.0 ),
                                const QSizeF &size = QSizeF( 40.0, 40.0 ) );
    ~ProgressFloatItem ();

    QStringList backendTypes() const;

    QString name() const;

    QString guiString() const;

    QString nameId() const;

    QString description() const;

    QIcon icon () const;

    void initialize ();

    bool isInitialized () const;

    QPainterPath backgroundShape() const;

    void paintContent( GeoPainter *painter, ViewportParams *viewport,
                       const QString& renderPos, GeoSceneLayer * layer = 0 );

    bool eventFilter(QObject *object, QEvent *e);

private Q_SLOTS:
    void addProgressItem();

    void removeProgressItem();

    void resetProgress();

    void show();

 private:
    Q_DISABLE_COPY( ProgressFloatItem )

    bool active() const;

    void setActive( bool active );

    bool m_isInitialized;

    MarbleWidget *m_marbleWidget;

    int m_totalJobs;

    int m_completedJobs;

    QTimer m_progressResetTimer;

    QTimer m_progressShowTimer;

    QMutex m_jobMutex;

    bool m_active;

    QIcon m_icon;
};

}

#endif