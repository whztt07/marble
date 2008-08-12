/*
    Copyright (C) 2008 Torsten Rahn <rahn@kde.org>

    This file is part of the KDE project

    This library is free software you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    aint with this library see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "GeoSceneMap.h"

#include "GeoSceneLayer.h"
#include "GeoSceneFilter.h"
#include "DgmlAuxillaryDictionary.h"

using namespace Marble::GeoSceneAuxillaryDictionary;

// FIXME: Filters are a Dataset.

class GeoSceneMapPrivate
{
  public:
    GeoSceneMapPrivate()
        : m_backgroundColor( "" )
    {
    }

    ~GeoSceneMapPrivate()
    {
        qDeleteAll( m_layers );
    }

    /// The vector holding all the sections in the legend.
    /// (We want to preserve the order and don't care 
    /// much about speed here), so we don't use a hash
    QVector<GeoSceneLayer*> m_layers;

    /// The vector holding all the filters in the map.
    QVector<GeoSceneFilter*> m_filters;

    QColor m_backgroundColor;
    QColor m_labelColor;
};


GeoSceneMap::GeoSceneMap()
    : d ( new GeoSceneMapPrivate )
{
    /* NOOP */
}

GeoSceneMap::~GeoSceneMap()
{
    delete d;
}

void GeoSceneMap::addLayer( GeoSceneLayer* layer )
{
    // Remove any layer that has the same name
    QVector<GeoSceneLayer*>::iterator it = d->m_layers.begin();
    while (it != d->m_layers.end()) {
        GeoSceneLayer* currentLayer = *it;
        if ( currentLayer->name() == layer->name() ) {
            delete currentLayer;
            it = d->m_layers.erase(it);
        }
        else {
            ++it;
        }
     }

    if ( layer ) {
        d->m_layers.append( layer );
    }
}

GeoSceneLayer* GeoSceneMap::layer( const QString& name )
{
    GeoSceneLayer* layer = 0;

    QVector<GeoSceneLayer*>::const_iterator it = d->m_layers.begin();
    for (it = d->m_layers.begin(); it != d->m_layers.end(); ++it) {
        if ( (*it)->name() == name )
            layer = *it;
    }

    if ( layer ) {
        Q_ASSERT(layer->name() == name);
        return layer;
    }

    layer = new GeoSceneLayer( name );
    addLayer( layer );

    return layer;
}

QVector<GeoSceneLayer*> GeoSceneMap::layers() const
{
    return d->m_layers;
}

void GeoSceneMap::addFilter( GeoSceneFilter* filter )
{
    // Remove any filter that has the same name
    QVector<GeoSceneFilter*>::iterator it = d->m_filters.begin();
    while (it != d->m_filters.end()) {
        GeoSceneFilter* currentFilter = *it;
        if ( currentFilter->name() == filter->name() ) {
            delete currentFilter;
            it = d->m_filters.erase(it);
        }
        else {
            ++it;
        }
     }

    if ( filter ) {
        d->m_filters.append( filter );
    }
}

GeoSceneFilter* GeoSceneMap::filter( const QString& name )
{
    GeoSceneFilter* filter = 0;

    QVector<GeoSceneFilter*>::const_iterator it = d->m_filters.begin();
    for (it = d->m_filters.begin(); it != d->m_filters.end(); ++it) {
        if ( (*it)->name() == name )
            filter = *it;
    }

    if ( filter ) {
        Q_ASSERT(filter->name() == name);
        return filter;
    }

    filter = new GeoSceneFilter( name );
    addFilter( filter );

    return filter;
}

QVector<GeoSceneFilter*> GeoSceneMap::filters() const
{
    return d->m_filters;
}

bool GeoSceneMap::hasTextureLayers() const
{
    QVector<GeoSceneLayer*>::const_iterator it = d->m_layers.begin();
    for (it = d->m_layers.begin(); it != d->m_layers.end(); ++it) {
        if ( (*it)->backend() == dgmlValue_texture && (*it)->datasets().count() > 0 )
            return true;
    }

    return false;
}

bool GeoSceneMap::hasVectorLayers() const
{
    QVector<GeoSceneLayer*>::const_iterator it = d->m_layers.begin();
    for (it = d->m_layers.begin(); it != d->m_layers.end(); ++it) {
        if ( (*it)->backend() == dgmlValue_vector && (*it)->datasets().count() > 0 )
            return true;
    }

    return false;
}

QColor GeoSceneMap::backgroundColor() const
{
    return d->m_backgroundColor;
}

void GeoSceneMap::setBackgroundColor( const QColor& backgroundColor )
{
    d->m_backgroundColor = backgroundColor;
}


QColor GeoSceneMap::labelColor() const
{
    return d->m_labelColor;
}

void GeoSceneMap::setLabelColor( const QColor& backgroundColor )
{
    d->m_labelColor = backgroundColor;
}
