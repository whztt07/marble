PROJECT( QtComponentsPlugin )

INCLUDE_DIRECTORIES(
 ${CMAKE_CURRENT_SOURCE_DIR}/src/plugins/qt-components
 ${CMAKE_BINARY_DIR}/src/plugins/qt-components
 ${QT_INCLUDE_DIR}
)

set( my_SRCS
QtComponentsPlugin.cpp
)

QT4_ADD_RESOURCES(my_SRCS qtcomponents.qrc)

MARBLE_ADD_DECLARATIVE_PLUGIN( QtComponentsPlugin qtcomponents ${my_SRCS} )
QT4_AUTOMOC(${my_SRCS})
TARGET_LINK_LIBRARIES( QtComponentsPlugin ${QT_QTDECLARATIVE_LIBRARY} ${QT_QTWEBKIT_LIBRARY} )
INSTALL( FILES qmldir DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES MainWidget.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES ConfigurationActivityPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES ConnectionSettingsPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES MapThemeSelectionPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES NavigationSettingsPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES ViewSettingsPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES SearchBar.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES RouteRequestView.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES WaypointView.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES RoutingDialog.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES SearchResultSelectionDialog.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES ActivitySelectionView.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES VirtualGlobeActivityPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES SearchActivityPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES GeocachingActivityPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES GuidanceActivityPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )
INSTALL( FILES WeatherActivityPage.qml DESTINATION ${MARBLE_QT_IMPORTS_DIR}/org/kde/edu/marble/qtcomponents )