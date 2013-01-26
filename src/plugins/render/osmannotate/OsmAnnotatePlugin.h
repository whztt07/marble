//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009 Andrew Manson <g.real.ate@gmail.com>
//

//
// This class is a test plugin.
//

#ifndef MARBLEOSMANNOTATEPLUGIN_H
#define MARBLEOSMANNOTATEPLUGIN_H

#include <QtCore/QObject>
#include <QtGui/QActionGroup>
#include <QtGui/QErrorMessage>
#include <QtGui/QToolBar>
#include <QtGui/QGroupBox>

class QNetworkAccessManager;
class QNetworkReply;

#include "RenderPlugin.h"
#include "SceneGraphicsItem.h"

namespace Marble
{

    class MarbleWidget;
    class PlacemarkTextAnnotation;
    class GeoDataDocument;
    class GeoDataLinearRing;
    class GeoDataLineString;

/**
 * @short The class that specifies the Marble layer interface of a plugin.
 *
 */

class OsmAnnotatePlugin :  public RenderPlugin
{
    Q_OBJECT
    Q_INTERFACES( Marble::RenderPluginInterface )
    MARBLE_PLUGIN( OsmAnnotatePlugin )

 public:
    OsmAnnotatePlugin();
    explicit OsmAnnotatePlugin(const MarbleModel *model);
    virtual ~OsmAnnotatePlugin();

    QStringList backendTypes() const;

    QString renderPolicy() const;

    QStringList renderPosition() const;

    QString name() const;

    QString guiString() const;

    QString nameId() const;

    QString version() const;

    QString description() const;

    QIcon icon () const;

    QString copyrightYears() const;

    QList<PluginAuthor> pluginAuthors() const;

    void initialize ();

    bool isInitialized () const;

    virtual QString runtimeTrace() const;

    virtual const QList<QActionGroup*>* actionGroups() const;
    virtual const QList<QActionGroup*>* toolbarActionGroups() const;

    bool render( GeoPainter *painter, ViewportParams *viewport,
                 const QString& renderPos, GeoSceneLayer * layer = 0 );

    bool    widgetInitalised;


signals:
    void redraw();
    void placemarkAdded();
    void itemRemoved();

public slots:
    void enableModel( bool enabled );

    void setAddingPlacemark( bool );
    void setDrawingPolygon( bool );
    void setRemovingItems( bool );

    void receiveNetworkReply( QNetworkReply* );
    void downloadOsmFile();

    void clearAnnotations();
    void saveAnnotationFile();
    void loadAnnotationFile();

protected:
    bool eventFilter(QObject* watched, QEvent* event);
private:
    void setupActions(MarbleWidget* m);
    void readOsmFile( QIODevice* device, bool flyToFile );

    MarbleWidget* m_marbleWidget;

    QList<QActionGroup*>    m_actions;
    QList<QActionGroup*>    m_toolbarActions;

    GeoDataDocument *m_AnnotationDocument;
    QList<SceneGraphicsItem*> m_graphicsItems;

    //used while creating new polygons
    GeoDataLineString* m_tmp_lineString;
    GeoDataLinearRing* m_tmp_linearRing;
    SceneGraphicsItem *m_selectedItem;

    bool m_addingPlacemark;
    bool m_drawingPolygon;
    bool m_removingItem;
    QNetworkAccessManager* m_networkAccessManager;
    QErrorMessage m_errorMessage;
    bool m_isInitialized;
};

}

#endif // MARBLEOSMANNOTATEPLUGIN_H
