//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010      Dennis Nienhüser <earthwings@gentoo.org>
//

#include "MonavRunner.h"
#include "signals.h"

#include "MarbleDebug.h"
#include "MarbleDirs.h"
#include "routing/RouteRequest.h"
#include "routing/instructions/InstructionTransformation.h"
#include "GeoDataDocument.h"
#include "GeoDataData.h"
#include "GeoDataExtendedData.h"

#include <QtCore/QProcess>
#include <QtCore/QTime>
#include <QtNetwork/QLocalSocket>

namespace Marble
{

class MonavRunnerPrivate
{
public:
    QDir m_mapDir;

    MonavRunnerPrivate();

    GeoDataLineString* retrieveRoute( RouteRequest *route, QVector<GeoDataPlacemark*> *instructions ) const;

    GeoDataDocument* createDocument( GeoDataLineString* geometry, const QVector<GeoDataPlacemark*> &instructions  ) const;
};

MonavRunnerPrivate::MonavRunnerPrivate() :
        m_mapDir( MarbleDirs::localPath() + "/maps/earth/monav/" )
{
    // nothing to do
}

GeoDataLineString* MonavRunnerPrivate::retrieveRoute( RouteRequest *route, QVector<GeoDataPlacemark*> *instructions ) const
{
    GeoDataLineString* geometry = new GeoDataLineString;

    QLocalSocket socket;
    socket.connectToServer( "MoNavD" );
    if ( socket.waitForConnected() ) {
        RoutingDaemonCommand command;
        QVector<RoutingDaemonNode> waypoints;

        for ( int i = 0; i < route->size(); ++i ) {
            RoutingDaemonNode coordinate;
            coordinate.longitude = route->at( i ).longitude( GeoDataCoordinates::Degree );
            coordinate.latitude = route->at( i ).latitude( GeoDataCoordinates::Degree );
            waypoints << coordinate;
        }

        command.dataDirectory = m_mapDir.absolutePath();
        command.lookupRadius = 1500;
        command.waypoints = waypoints;
        command.lookupStrings = true;

        command.post( &socket );
        socket.flush();

        RoutingDaemonResult reply;
        if ( reply.read( &socket ) ) {
            switch ( reply.type ) {
            case RoutingDaemonResult::LoadFailed:
                mDebug() << "failed to load monav map from " << m_mapDir.absolutePath();
                break;
            case RoutingDaemonResult::RouteFailed:
                mDebug() << "failed to retrieve route from monav daemon";
                break;
            case RoutingDaemonResult::TypeLookupFailed:
                mDebug() << "failed to lookup type from monav daemon";
                break;
            case RoutingDaemonResult::NameLookupFailed:
                mDebug() << "failed to lookup name from monav daemon";
                break;
            case RoutingDaemonResult::Success:
                /** @todo: make use of reply.seconds, the estimated travel time */
                for ( int i = 0; i < reply.pathNodes.size(); ++i ) {
                    qreal lon = reply.pathNodes[i].longitude;
                    qreal lat = reply.pathNodes[i].latitude;
                    GeoDataCoordinates coordinates( lon, lat, 0, GeoDataCoordinates::Degree );
                    geometry->append( coordinates );
                }

                RoutingWaypoints waypoints;
                int k = 0;
                for ( int i = 0; i < reply.pathEdges.size(); ++i ) {
                    QString road = reply.nameStrings[reply.pathEdges[i].name];
                    QString type = reply.typeStrings[reply.pathEdges[i].type];
                    for ( unsigned int l = 0; l < reply.pathEdges[i].length; ++k, ++l ) {
                        qreal lon = reply.pathNodes[k].longitude;
                        qreal lat = reply.pathNodes[k].latitude;
                        RoutingPoint point( lon, lat );
                        RoutingWaypoint waypoint( point, RoutingWaypoint::Other, "", type, -1, road );
                        waypoints.push_back( waypoint );
                    }
                }

                RoutingInstructions directions = InstructionTransformation::process( waypoints );
                for ( int i = 0; i < directions.size(); ++i ) {
                    GeoDataPlacemark* placemark = new GeoDataPlacemark( directions[i].instructionText() );
                    GeoDataExtendedData extendedData;
                    GeoDataData turnType;
                    turnType.setName( "turnType" );
                    turnType.setValue( qVariantFromValue<int>( int( directions[i].turnType() ) ) );
                    extendedData.addValue( turnType );
                    placemark->setExtendedData( extendedData );
                    Q_ASSERT( !directions[i].points().isEmpty() );
                    GeoDataLineString* geometry = new GeoDataLineString;
                    QVector<RoutingWaypoint> items = directions[i].points();
                    for ( int j = 0; j < items.size(); ++j ) {
                        RoutingPoint point = items[j].point();
                        GeoDataCoordinates coordinates( point.lon(), point.lat(), 0.0, GeoDataCoordinates::Degree );
                        geometry->append( coordinates );
                    }
                    placemark->setGeometry( geometry );
                    instructions->push_back( placemark );
                }
                break;
            }
        } else {
            mDebug() << "Failed to read reply";
        }
    } else {
        mDebug() << "No connection to MoNavD";
    }

    return geometry;
}

GeoDataDocument* MonavRunnerPrivate::createDocument( GeoDataLineString *geometry, const QVector<GeoDataPlacemark*> &instructions ) const
{
    if ( !geometry || geometry->isEmpty() ) {
        return 0;
    }

    GeoDataDocument* result = new GeoDataDocument;
    GeoDataPlacemark* routePlacemark = new GeoDataPlacemark;
    routePlacemark->setName( "Route" );
    routePlacemark->setGeometry( geometry );
    result->append( routePlacemark );

    QString name = "%1 %2 (Monav)";
    QString unit = "m";
    qreal length = geometry->length( EARTH_RADIUS );
    if ( length >= 1000 ) {
        length /= 1000.0;
        unit = "km";
    }

    foreach( GeoDataPlacemark* placemark, instructions ) {
        result->append( placemark );
    }

    result->setName( name.arg( length, 0, 'f', 1 ).arg( unit ) );
    return result;
}

MonavRunner::MonavRunner( QObject *parent ) :
        MarbleAbstractRunner( parent ),
        d( new MonavRunnerPrivate )
{
    // nothing to do
}

MonavRunner::~MonavRunner()
{
    delete d;
}

GeoDataFeature::GeoDataVisualCategory MonavRunner::category() const
{
    return GeoDataFeature::OsmSite;
}

void MonavRunner::retrieveRoute( RouteRequest *route )
{
    QVector<GeoDataPlacemark*> instructions;
    GeoDataLineString* waypoints = d->retrieveRoute( route, &instructions );
    GeoDataDocument* result = d->createDocument( waypoints, instructions );
    emit routeCalculated( result );
}

} // namespace Marble

#include "MonavRunner.moc"