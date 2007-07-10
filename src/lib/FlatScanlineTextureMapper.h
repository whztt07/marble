#ifndef __MARBLE__FLATSCANLINETEXTUREMAPPER_H
#define __MARBLE__FLATSCANLINETEXTUREMAPPER_H


#include <QtCore/QString>

#include "AbstractScanlineTextureMapper.h"


class FlatScanlineTextureMapper : public AbstractScanlineTextureMapper {
 public:
    explicit FlatScanlineTextureMapper(const QString& path, QObject * parent = 0);
    void mapTexture(QImage* canvasImage, const int&, Quaternion& planetAxis);
 private:
    float  m_oldCenterLng;
    int    m_oldYPaintedTop;
};
#endif
