//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2013      Dennis Nienhüser <earthwings@gentoo.org>
//

#ifndef MARBLE_MARBLETEST_H
#define MARBLE_MARBLETEST_H

#include "GeoDataDocument.h"
#include "GeoDataParser.h"
#include "GeoDataCoordinates.h"
#include "GeoDataLatLonAltBox.h"

#include <QtTest/QtTest>

namespace QTest
{

bool qCompare(qreal val1, qreal val2, qreal epsilon, const char *actual, const char *expected, const char *file, int line)
{
    return ( qAbs( val1 - val2 ) < epsilon )
        ? compare_helper( true, "COMPARE()", file, line )
        : compare_helper( false, "Compared qreals are not the same", toString( val1 ), toString( val2 ), actual, expected, file, line );
}

template<>
char *toString(const Marble::GeoDataCoordinates &coordinates)
{
    return qstrdup( coordinates.toString( Marble::GeoDataCoordinates::Decimal, 10 ).toAscii().data() );
}

template<>
char *toString(const Marble::GeoDataLatLonBox &box)
{
    const QString string = QString( "North: %1, West: %2, South: %3, East: %4" )
        .arg( box.north( Marble::GeoDataCoordinates::Degree ) )
        .arg( box.west( Marble::GeoDataCoordinates::Degree ) )
        .arg( box.south( Marble::GeoDataCoordinates::Degree ) )
        .arg( box.east( Marble::GeoDataCoordinates::Degree ) );

    return qstrdup( string.toAscii().data() );
}

template<>
char *toString(const Marble::GeoDataLatLonAltBox &box)
{
    const QString string = QString( "North: %1, West: %2, South: %3, East: %4, MinAlt: %5, MaxAlt: %6" )
        .arg( box.north( Marble::GeoDataCoordinates::Degree ) )
        .arg( box.west( Marble::GeoDataCoordinates::Degree ) )
        .arg( box.south( Marble::GeoDataCoordinates::Degree ) )
        .arg( box.east( Marble::GeoDataCoordinates::Degree ) )
        .arg( box.minAltitude() )
        .arg( box.maxAltitude() );

    return qstrdup( string.toAscii().data() );
}

}

#define QFUZZYCOMPARE(actual, expected, epsilon) \
do {\
    if (!QTest::qCompare(actual, expected, epsilon, #actual, #expected, __FILE__, __LINE__))\
        return;\
} while (0)

#define addRow() QTest::newRow( QString("line %1").arg( __LINE__ ).toAscii().data() )
#define addNamedRow(testName) QTest::newRow( QString("line %1: %2").arg( __LINE__ ).arg(testName).toAscii().data() )

namespace Marble {

GeoDataDocument *parseKml(const QString &content)
{
    GeoDataParser parser( GeoData_KML );

    QByteArray array( content.toUtf8() );
    QBuffer buffer( &array );
    buffer.open( QIODevice::ReadOnly );
    //qDebug() << "Buffer content:" << endl << buffer.buffer();
    if ( !parser.read( &buffer ) ) {
        qFatal( "Could not parse data!" );
    }
    GeoDocument* document = parser.releaseDocument();
    Q_ASSERT( document );
    return static_cast<GeoDataDocument*>( document );
}

}

#endif
