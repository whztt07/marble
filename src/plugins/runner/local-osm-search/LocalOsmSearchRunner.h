//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011 Dennis Nienhüser <earthwings@gentoo.org>
// Copyright 2013      Bernhard Beschow <bbeschow@cs.tu-berlin.de>
//

#ifndef MARBLE_LOCALOSMSEARCHRUNNER_H
#define MARBLE_LOCALOSMSEARCHRUNNER_H

#include "SearchRunner.h"

#include "OsmDatabase.h"
#include "OsmPlacemark.h"
#include "GeoDataFeature.h"

#include <QtCore/QMap>

namespace Marble
{

class LocalOsmSearchRunner : public SearchRunner
{
    Q_OBJECT
public:
    explicit LocalOsmSearchRunner( const QStringList &databaseFiles, QObject *parent = 0 );

    ~LocalOsmSearchRunner();

    virtual void search( const QString &searchTerm, const GeoDataLatLonAltBox &preferred );

private:
    OsmDatabase m_database;

    static QMap<OsmPlacemark::OsmCategory, GeoDataFeature::GeoDataVisualCategory> m_categoryMap;
};

}

#endif
