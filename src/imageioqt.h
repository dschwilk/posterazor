/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2008 by Alessandro Portale
    http://posterazor.sourceforge.net/

    This file is part of PosteRazor

    PosteRazor is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    PosteRazor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with PosteRazor; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef IMAGEIOQT_H
#define IMAGEIOQT_H

#include "imageiointerface.h"
#include <QObject>

class ImageIOQt: public QObject, public ImageIOInterface
{
public:
    ImageIOQt(QObject *parent = 0);

    bool loadInputImage(const QString &imageFileName, QString &errorMessage);
    bool isImageLoaded() const;
    bool isJpeg() const;
    QString getFileName() const;
    QSize getSizePixels() const;
    double getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const;
    double getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const;
    QSizeF getSize(UnitsOfLength::eUnitsOfLength unit) const;
    const QImage getImageAsRGB(const QSize &size) const;
    int getBitsPerPixel() const;
    ColorTypes::eColorTypes getColorDataType() const;
    int savePoster(const QString &fileName, const PainterInterface *painter, int pagesCount, const QSizeF &sizeCm) const;
    const QByteArray getBits() const;
    const QVector<QRgb> getColorTable() const;

private:
    QImage m_image;
    QString m_imageFileName;
};

#endif // IMAGEIOQT_H
