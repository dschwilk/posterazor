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

#include "PosteRazor.h"
#include "PosteRazorImageIO.h"
#include <QSettings>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
  #include <windows.h>
#else
  #include <stdlib.h>
#endif
#include <math.h>

const QLatin1String settingsKey_PosterSizeMode("PosterSizeMode");
const QLatin1String settingsKey_PosterDimension("PosterDimension");
const QLatin1String settingsKey_PosterDimensionIsWidth("PosterDimensionIsWidth");
const QLatin1String settingsKey_PosterHorizontalAlignment("PosterHorizontalAlignment");
const QLatin1String settingsKey_PosterVerticalAlignment("PosterVerticalAlignment");
const QLatin1String settingsKey_UseCustomPaperSize("UseCustomPaperSize");
const QLatin1String settingsKey_PaperFormat("paperFormat");
const QLatin1String settingsKey_PaperOrientation("PaperOrientation");
const QLatin1String settingsKey_PaperBorderTop("PaperBorderTop");
const QLatin1String settingsKey_PaperBorderRight("PaperBorderRight");
const QLatin1String settingsKey_PaperBorderBottom("PaperBorderBottom");
const QLatin1String settingsKey_PaperBorderLeft("PaperBorderLeft");
const QLatin1String settingsKey_CustomPaperWidth("CustomPaperWidth");
const QLatin1String settingsKey_CustomPaperHeight("CustomPaperHeight");
const QLatin1String settingsKey_OverlappingWidth("OverlappingWidth");
const QLatin1String settingsKey_OverlappingHeight("OverlappingHeight");
const QLatin1String settingsKey_OverlappingPosition("overlappingPosition");
const QLatin1String settingsKey_UnitOfLength("unitOfLength");
const QLatin1String settingsKey_PosterOutputFormat("PosterOutputFormat");

class PosteRazorImplementation: public PosteRazor
{
private:
	PosteRazorImageIO*                      m_imageIO;

	PosteRazorEnums::ePosterSizeModes       m_posterSizeMode;
	double                                  m_posterDimension;
	bool                                    m_posterDimensionIsWidth;
	PosteRazorEnums::eHorizontalAlignments  m_posterHorizontalAlignment;
	PosteRazorEnums::eVerticalAlignments    m_posterVerticalAlignment;

	bool                                    m_useCustomPaperSize;
	PaperFormats::ePaperFormats             m_paperFormat;
	PaperFormats::ePaperOrientations        m_paperOrientation;
	double                                  m_paperBorderTop;
	double                                  m_paperBorderRight;
	double                                  m_paperBorderBottom;
	double                                  m_paperBorderLeft;
	double                                  m_customPaperWidth;
	double                                  m_customPaperHeight;

	double                                  m_overlappingWidth;
	double                                  m_overlappingHeight;
	PosteRazorEnums::eOverlappingPositions  m_overlappingPosition;

	UnitsOfLength::eUnitsOfLength           m_unitOfLength;

	ImageIOTypes::eImageFormats             m_posterOutputFormat;

public:
	PosteRazorImplementation()
		: m_posterSizeMode(PosteRazorEnums::ePosterSizeModePages)
		, m_posterDimension(2.0)
		, m_posterDimensionIsWidth(true)
		, m_posterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentLeft)
		, m_posterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentTop)

		, m_useCustomPaperSize(false)
		, m_paperFormat(PaperFormats::ePaperFormatA4)
		, m_paperOrientation(PaperFormats::ePaperOrientationPortrait)
		, m_paperBorderTop(1.5)
		, m_paperBorderRight(1.5)
		, m_paperBorderBottom(1.5)
		, m_paperBorderLeft(1.5)
		, m_customPaperWidth(20)
		, m_customPaperHeight(20)

		, m_overlappingWidth(1.0)
		, m_overlappingHeight(1.0)
		, m_overlappingPosition(PosteRazorEnums::eOverlappingPositionBottomRight)

		, m_unitOfLength(UnitsOfLength::eUnitOfLengthCentimeter)

		, m_posterOutputFormat(ImageIOTypes::eImageFormatPDF)
	{
		m_imageIO = PosteRazorImageIO::createPosteRazorImageIO();
	}

	~PosteRazorImplementation()
	{
		delete m_imageIO;
	}

	virtual bool readSettings(const QSettings *settings)
	{
		bool returnValue = true;

		m_posterSizeMode               = (PosteRazorEnums::ePosterSizeModes)settings->value(settingsKey_PosterSizeMode, (int)m_posterSizeMode).toInt();
		m_posterDimension              = settings->value(settingsKey_PosterDimension, m_posterDimension).toDouble();
		m_posterDimensionIsWidth       = settings->value(settingsKey_PosterDimensionIsWidth, m_posterDimensionIsWidth).toBool();
		m_posterHorizontalAlignment    = (PosteRazorEnums::eHorizontalAlignments)settings->value(settingsKey_PosterHorizontalAlignment, (int)m_posterHorizontalAlignment).toInt();
		m_posterVerticalAlignment      = (PosteRazorEnums::eVerticalAlignments)settings->value(settingsKey_PosterVerticalAlignment, (int)m_posterVerticalAlignment).toInt();
		m_useCustomPaperSize           = settings->value(settingsKey_UseCustomPaperSize, m_useCustomPaperSize).toBool();
		m_paperFormat                  = (PaperFormats::ePaperFormats)settings->value(settingsKey_PaperFormat, (int)m_paperFormat).toInt();
		m_paperOrientation             = (PaperFormats::ePaperOrientations)settings->value(settingsKey_PaperOrientation, (int)m_paperOrientation).toInt();
		m_paperBorderTop               = settings->value(settingsKey_PaperBorderTop, m_paperBorderTop).toDouble();
		m_paperBorderRight             = settings->value(settingsKey_PaperBorderRight, m_paperBorderRight).toDouble();
		m_paperBorderBottom            = settings->value(settingsKey_PaperBorderBottom, m_paperBorderBottom).toDouble();
		m_paperBorderLeft              = settings->value(settingsKey_PaperBorderLeft, m_paperBorderLeft).toDouble();
		m_customPaperWidth             = settings->value(settingsKey_CustomPaperWidth, m_customPaperWidth).toDouble();
		m_customPaperHeight            = settings->value(settingsKey_CustomPaperHeight, m_customPaperHeight).toDouble();
		m_overlappingWidth             = settings->value(settingsKey_OverlappingWidth, m_overlappingWidth).toDouble();
		m_overlappingHeight            = settings->value(settingsKey_OverlappingHeight, m_overlappingHeight).toDouble();
		m_overlappingPosition          = (PosteRazorEnums::eOverlappingPositions)settings->value(settingsKey_OverlappingPosition, (int)m_overlappingPosition).toInt();
		m_unitOfLength                 = (UnitsOfLength::eUnitsOfLength)settings->value(settingsKey_UnitOfLength, (int)m_unitOfLength).toInt();
		m_posterOutputFormat           = (ImageIOTypes::eImageFormats)settings->value(settingsKey_PosterOutputFormat, (int)m_posterOutputFormat).toInt();

		return returnValue;
	}

	virtual bool writeSettings(QSettings *settings) const
	{
		bool returnValue = true;

		settings->setValue(settingsKey_PosterSizeMode, (int)m_posterSizeMode);
		settings->setValue(settingsKey_PosterDimension, m_posterDimension);
		settings->setValue(settingsKey_PosterDimensionIsWidth, m_posterDimensionIsWidth);
		settings->setValue(settingsKey_PosterHorizontalAlignment, (int)m_posterHorizontalAlignment);
		settings->setValue(settingsKey_PosterVerticalAlignment, (int)m_posterVerticalAlignment);
		settings->setValue(settingsKey_UseCustomPaperSize, m_useCustomPaperSize);
		settings->setValue(settingsKey_PaperFormat, (int)m_paperFormat);
		settings->setValue(settingsKey_PaperOrientation, (int)m_paperOrientation);
		settings->setValue(settingsKey_PaperBorderTop, m_paperBorderTop);
		settings->setValue(settingsKey_PaperBorderRight, m_paperBorderRight);
		settings->setValue(settingsKey_PaperBorderBottom, m_paperBorderBottom);
		settings->setValue(settingsKey_PaperBorderLeft, m_paperBorderLeft);
		settings->setValue(settingsKey_CustomPaperWidth, m_customPaperWidth);
		settings->setValue(settingsKey_CustomPaperHeight, m_customPaperHeight);
		settings->setValue(settingsKey_OverlappingWidth, m_overlappingWidth);
		settings->setValue(settingsKey_OverlappingHeight, m_overlappingHeight);
		settings->setValue(settingsKey_OverlappingPosition, (int)m_overlappingPosition);
		settings->setValue(settingsKey_UnitOfLength, (int)m_unitOfLength);
		settings->setValue(settingsKey_PosterOutputFormat, (int)m_posterOutputFormat);

		return returnValue;
	}

	PosteRazorImageIO *GetImageIO(void)
	{
		return m_imageIO;
	}

	double convertDistanceToCm(double distance) const
	{
		return UnitsOfLength::convertBetweenUnitsOfLength(distance, getUnitOfLength(), UnitsOfLength::eUnitOfLengthCentimeter);
	}

	double convertCmToDistance(double cm) const
	{
		return UnitsOfLength::convertBetweenUnitsOfLength(cm, UnitsOfLength::eUnitOfLengthCentimeter, getUnitOfLength());
	}

	bool loadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		return m_imageIO->loadInputImage(imageFileName, errorMessage, errorMessageSize);
	}

	bool getIsImageLoaded(void) const
	{
		return m_imageIO->isImageLoaded();
	}

	int getInputImageWidthPixels(void) const
	{
		return m_imageIO->getWidthPixels();
	}

	int getInputImageHeightPixels(void) const
	{
		return m_imageIO->getHeightPixels();
	}

	double getInputImageHorizontalDpi(void) const
	{
		return m_imageIO->getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
	}

	double getInputImageVerticalDpi(void) const
	{
		return m_imageIO->getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
	}

	double getInputImageWidth(void) const
	{
		return m_imageIO->getWidth(m_unitOfLength);
	}

	double getInputImageHeight(void) const
	{
		return m_imageIO->getHeight(m_unitOfLength);
	}

	int getInputImageBitsPerPixel(void) const
	{
		return m_imageIO->getBitsPerPixel();
	}

	ColorTypes::eColorTypes getInputImageColorType(void) const
	{
		return m_imageIO->getColorDataType();
	}

	void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
	{
		m_unitOfLength = unit;
	}

	UnitsOfLength::eUnitsOfLength getUnitOfLength(void) const
	{
		return m_unitOfLength;
	}

	const char* getUnitOfLengthName(void) const
	{
		return UnitsOfLength::getUnitOfLengthName(m_unitOfLength);
	}

	void setPaperFormat(PaperFormats::ePaperFormats format)
	{
		m_paperFormat = format;
	}

	void setPaperOrientation(PaperFormats::ePaperOrientations orientation)
	{
		m_paperOrientation = orientation;
	}

	void setPaperBorderTop(double border)
	{
		m_paperBorderTop = convertDistanceToCm(border);
	}

	void setPaperBorderRight(double border)
	{
		m_paperBorderRight = convertDistanceToCm(border);
	}

	void setPaperBorderBottom(double border)
	{
		m_paperBorderBottom = convertDistanceToCm(border);
	}

	void setPaperBorderLeft(double border)
	{
		m_paperBorderLeft = convertDistanceToCm(border);
	}

	PaperFormats::ePaperFormats getPaperFormat(void) const
	{
		return m_paperFormat;
	}

	PaperFormats::ePaperOrientations getPaperOrientation(void) const
	{
		return m_paperOrientation;
	}

	double getPaperBorderTop(void) const
	{
		return qBound(.0, convertCmToDistance(m_paperBorderTop), getMaximalHorizontalPaperBorder());
	}

	double getPaperBorderRight(void) const
	{
		return qBound(.0, convertCmToDistance(m_paperBorderRight), getMaximalVerticalPaperBorder());
	}

	double getPaperBorderBottom(void) const
	{
		return qBound(.0, convertCmToDistance(m_paperBorderBottom), getMaximalHorizontalPaperBorder());
	}

	double getPaperBorderLeft(void) const
	{
		return qBound(.0, convertCmToDistance(m_paperBorderLeft), getMaximalVerticalPaperBorder());
	}

	double getMaximalVerticalPaperBorder(void) const
	{
		return getPaperWidth() / 2.0 - convertCmToDistance(1.0);
	}

	double getMaximalHorizontalPaperBorder(void) const
	{
		return getPaperHeight() / 2.0 - convertCmToDistance(1.0);
	}

	void setCustomPaperWidth(double width)
	{
		m_customPaperWidth = convertDistanceToCm(width);
	}

	void setCustomPaperHeight(double height)
	{
		m_customPaperHeight = convertDistanceToCm(height);
	}

	double getCustomPaperWidth(void) const
	{
		return qBound(getCustomMinimalPaperWidth(), convertCmToDistance(m_customPaperWidth), getCustomMaximalPaperWidth());
	}

	double getCustomPaperHeight(void) const
	{
		return qBound(getCustomMinimalPaperHeight(), convertCmToDistance(m_customPaperHeight), getCustomMaximalPaperHeight());
	}

	double getCustomMinimalPaperWidth(void) const
	{
		return convertCmToDistance(4.0);
	}

	double getCustomMinimalPaperHeight(void) const
	{
		return convertCmToDistance(4.0);
	}

	double getCustomMaximalPaperWidth(void) const
	{
		return convertCmToDistance(500.0); // Maximum of PDF page
	}

	double getCustomMaximalPaperHeight(void) const
	{
		return convertCmToDistance(500.0);
	}

	void setUseCustomPaperSize(bool useIt)
	{
		m_useCustomPaperSize = useIt;
	}

	bool getUseCustomPaperSize(void) const
	{
		return m_useCustomPaperSize;
	}

	double getPaperWidth(void) const
	{
		return getUseCustomPaperSize()?getCustomPaperWidth():PaperFormats::getPaperWidth(getPaperFormat(), getPaperOrientation(), m_unitOfLength);
	}

	double getPaperHeight(void) const
	{
		return getUseCustomPaperSize()?getCustomPaperHeight():PaperFormats::getPaperHeight(getPaperFormat(), getPaperOrientation(), m_unitOfLength);
	}

	double getPrintablePaperAreaWidth(void) const
	{
		return getPaperWidth() - getPaperBorderLeft() - getPaperBorderRight();
	}

	double getPrintablePaperAreaHeight(void) const
	{
		return getPaperHeight() - getPaperBorderTop() - getPaperBorderBottom();
	}

	double convertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width) const
	{
		double posterDimension = dimension;

		const double printablePaperAreaWidth = getPrintablePaperAreaWidth();
		const double printablePaperAreaHeight = getPrintablePaperAreaHeight();
		const double printablePaperAreaDimension = convertDistanceToCm(width?printablePaperAreaWidth:printablePaperAreaHeight);
		const double overlappingDimension = convertDistanceToCm(width?getOverlappingWidth():getOverlappingHeight());

		if (pagesToAbsolute) {
			double posterDimensionAbsolute = 0;
			if (posterDimension >= 1.0) {
				posterDimension -= 1.0;
				posterDimensionAbsolute += printablePaperAreaDimension;
			} else {
				posterDimensionAbsolute = posterDimension * printablePaperAreaDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
				posterDimensionAbsolute += (posterDimension * (printablePaperAreaDimension - overlappingDimension));

			posterDimension = posterDimensionAbsolute;
		} else {
			double posterDimensionPages = 0;
			if (posterDimension >= printablePaperAreaDimension) {
				posterDimension -= printablePaperAreaDimension;
				posterDimensionPages += 1.0;
			} else if (posterDimension < printablePaperAreaDimension) {
				posterDimensionPages = posterDimension / printablePaperAreaDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
				posterDimensionPages += (posterDimension / (printablePaperAreaDimension - overlappingDimension));

			posterDimension = posterDimensionPages;
		}

		return posterDimension;
	}

	// Since m_posterDimension holds only height or width of the poster,
	// here we calculate the other dimension considering the aspect ratio.
	double calculateOtherPosterDimension() const
	{
		double otherDimension = 0;

		if (getPosterSizeMode() != PosteRazorEnums::ePosterSizeModePercentual) {
			const double sourceReference = m_posterDimensionIsWidth?getInputImageWidth():getInputImageHeight();
			const double targetReference = m_posterDimensionIsWidth?getInputImageHeight():getInputImageWidth();
			const double aspectRatio = sourceReference/targetReference;

			if (getPosterSizeMode() != PosteRazorEnums::ePosterSizeModePages) {
				otherDimension = m_posterDimension / aspectRatio;
			} else {
				const double sourceAbsolute = convertBetweenAbsoluteAndPagesPosterDimension(m_posterDimension, true, m_posterDimensionIsWidth);
				const double targetAbsolute = sourceAbsolute/aspectRatio;
				otherDimension = convertBetweenAbsoluteAndPagesPosterDimension(targetAbsolute, false, !m_posterDimensionIsWidth);
			}
		}
		else
			otherDimension = m_posterDimension;

		return otherDimension;
	}

	void setPosterDimension(PosteRazorEnums::ePosterSizeModes mode, double dimension, bool dimensionIsWidth)
	{
		setPosterSizeMode(mode);

		if (getPosterSizeMode() == PosteRazorEnums::ePosterSizeModeAbsolute)
			dimension = convertDistanceToCm(dimension);

		m_posterDimension = dimension;
		m_posterDimensionIsWidth = dimensionIsWidth;
	}

	void setOverlappingWidth(double width)
	{
		m_overlappingWidth = convertDistanceToCm(width);
	}

	void setOverlappingHeight(double height)
	{
		m_overlappingHeight = convertDistanceToCm(height);
	}

	double getOverlappingWidth(void) const
	{
		return qBound(.0, convertCmToDistance(m_overlappingWidth), getMaximalOverLappingWidth());
	}

	double getOverlappingHeight(void) const
	{
		return qBound(.0, convertCmToDistance(m_overlappingHeight), getMaximalOverLappingHeight());
	}

	double getMaximalOverLappingWidth(void) const
	{
		return getPaperWidth() - getPaperBorderLeft() - getPaperBorderRight() - convertCmToDistance(1.0);
	}

	double getMaximalOverLappingHeight(void) const
	{
		return getPaperHeight() - getPaperBorderTop() - getPaperBorderBottom() - convertCmToDistance(1.0);
	}

	void setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
	{
		m_overlappingPosition = position;
	}

	PosteRazorEnums::eOverlappingPositions getOverlappingPosition(void) const
	{
		return m_overlappingPosition;
	}

	void setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
	{
		setPosterDimension(mode, width, true);
	}

	void setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
	{
		setPosterDimension(mode, height, false);
	}

	void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
	{
		m_posterSizeMode = mode;
	}

	double getPosterDimension(PosteRazorEnums::ePosterSizeModes mode, bool width) const
	{
		double posterDimension = (width==m_posterDimensionIsWidth)?m_posterDimension:calculateOtherPosterDimension();
		
		posterDimension = qMax(
			(mode == PosteRazorEnums::ePosterSizeModeAbsolute)?0.001
			:(mode == PosteRazorEnums::ePosterSizeModePages)?0.001
			:0.001
			, posterDimension
		);

		// anything to convert?
		if (getPosterSizeMode() != mode){
			// These are needed for conversion from and to ePosterSizeModePercentual
			const double inputImageDimension = convertDistanceToCm(width?getInputImageWidth():getInputImageHeight());

			// First convert to absolute size mode (cm)
			if (getPosterSizeMode() == PosteRazorEnums::ePosterSizeModePages) {
				posterDimension = convertBetweenAbsoluteAndPagesPosterDimension(posterDimension, true, width);
			} else if (getPosterSizeMode() == PosteRazorEnums::ePosterSizeModePercentual) {
				posterDimension *= inputImageDimension;
				posterDimension /= 100.0;
			}

			// Then convert to the wanted size mode
			if (mode == PosteRazorEnums::ePosterSizeModePages) {
				posterDimension = convertBetweenAbsoluteAndPagesPosterDimension(posterDimension, false, width);
			} else if (mode == PosteRazorEnums::ePosterSizeModePercentual) {
				posterDimension /= inputImageDimension;
				posterDimension *= 100.0;
			}
		}

		if (mode == PosteRazorEnums::ePosterSizeModeAbsolute)
			posterDimension = convertCmToDistance(posterDimension);

		return posterDimension;
	}

	double getPosterWidth(PosteRazorEnums::ePosterSizeModes mode) const
	{
		return getPosterDimension(mode, true);
	}

	double getPosterHeight(PosteRazorEnums::ePosterSizeModes mode) const
	{
		return getPosterDimension(mode, false);
	}

	PosteRazorEnums::ePosterSizeModes getPosterSizeMode(void) const
	{
		return m_posterSizeMode;
	}

	void setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment) 
	{
		m_posterHorizontalAlignment = alignment;
	}

	void setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
	{
		m_posterVerticalAlignment = alignment;
	}

	PosteRazorEnums::eHorizontalAlignments getPosterHorizontalAlignment(void) const
	{
		return m_posterHorizontalAlignment;
	}

	PosteRazorEnums::eVerticalAlignments getPosterVerticalAlignment(void) const
	{
		return m_posterVerticalAlignment;
	}

	void getPreviewSize(double imageWidth, double imageHeight, int boxWidth, int boxHeight, int &previewWidth, int &previewHeight, bool enlargeToFit) const
	{
		const double aspectRatio = imageWidth / imageHeight;

		if (enlargeToFit) {
			const double widthFactor = imageWidth/(double)boxWidth;
			const double heightFactor = imageHeight/(double)boxHeight;
			const double factor = widthFactor<heightFactor?widthFactor:heightFactor;
			imageWidth /= factor;
			imageHeight /= factor;
		}

		previewWidth = qMin((int)imageWidth, boxWidth);
		previewHeight = (int)((double)previewWidth / aspectRatio);

		if (previewHeight > boxHeight) {
			previewWidth = (int)((double)boxHeight * aspectRatio);
			previewHeight = boxHeight;
		}
	}

	void getInputImagePreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight) const
	{
		getPreviewSize(getInputImageWidthPixels(), getInputImageHeightPixels(), boxWidth, boxHeight, previewWidth, previewHeight, false);
	}

	virtual void getPaperPreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight) const
	{
		getPreviewSize(getPaperWidth(), getPaperHeight(), boxWidth, boxHeight, previewWidth, previewHeight, true);
	}
	
	void getImage(PaintCanvasInterface *paintCanvas, double maxWidth, double maxHeight) const
	{
		int imageWidth;
		int imageHeight;
		getInputImagePreviewSize((int)maxWidth, (int)maxHeight, imageWidth, imageHeight);
		const size_t rgbDataBytesCount = imageWidth * imageHeight * 3;
		unsigned char *rgbData = new unsigned char[rgbDataBytesCount];
		if (!m_imageIO->getImageAsRGB(rgbData, imageWidth, imageHeight))
			// If preview fails because of low memory...
			memset(rgbData, 0x66, rgbDataBytesCount);
		paintCanvas->setImage(rgbData, imageWidth, imageHeight);
		delete[] rgbData;
	}

	void paintImageOnCanvas(PaintCanvasInterface *paintCanvas) const
	{
		if (getIsImageLoaded()) {
			double canvasWidth = 0, canvasHeight = 0;
			paintCanvas->getSize(canvasWidth, canvasHeight);
			int boxWidth = 0, boxHeight = 0;
			double x_offset, y_offset;

			getPreviewSize(getInputImageWidthPixels(), getInputImageHeightPixels(), (int)canvasWidth, (int)canvasHeight, boxWidth, boxHeight, false);
			x_offset = (canvasWidth - boxWidth) / 2;
			y_offset = (canvasHeight - boxHeight) / 2;
			
			// If the image is not downscaled, make sure that the coordinates are integers in order
			// to prevent unneeded blurring (especially in OpenGL)
			if (canvasWidth >= getInputImageWidthPixels() && canvasHeight >= getInputImageHeightPixels()) {
				x_offset = floor(x_offset);
				y_offset = floor(y_offset);
			}			

			paintCanvas->drawImage(0 + x_offset, 0 + y_offset, boxWidth, boxHeight);
		}
	}

	void paintPaperOnCanvas(PaintCanvasInterface *paintCanvas, bool paintOverlapping) const
	{
		double canvasWidth = 0, canvasHeight = 0;
		paintCanvas->getSize(canvasWidth, canvasHeight);
		int boxWidth = 0, boxHeight = 0;

		const double paperWidth = getPaperWidth();
		const double paperHeight = getPaperHeight();
		getPreviewSize(paperWidth, paperHeight, (int)canvasWidth, (int)canvasHeight, boxWidth, boxHeight, true);
		const double x_offset = (canvasWidth - (double)boxWidth) / 2.0;
		const double y_offset = (canvasHeight - (double)boxHeight) / 2.0;
		const double UnitOfLengthToPixelfactor = (double)boxWidth/paperWidth;
		const double borderTop = getPaperBorderTop() * UnitOfLengthToPixelfactor;
		const double borderRight = getPaperBorderRight() * UnitOfLengthToPixelfactor;
		const double borderBottom = getPaperBorderBottom() * UnitOfLengthToPixelfactor;
		const double borderLeft = getPaperBorderLeft() * UnitOfLengthToPixelfactor;
		const double printableAreaWidth = boxWidth - borderLeft - borderRight;
		const double printableAreaHeight = boxHeight - borderTop - borderBottom;
		
		paintCanvas->drawFilledRect(0 + x_offset, 0 + y_offset, boxWidth, boxHeight, 128, 128, 128, 255);
		paintCanvas->drawFilledRect(0 + borderLeft + x_offset, 0 + borderTop + y_offset, printableAreaWidth, printableAreaHeight, 230, 230, 230, 255);

		if (paintOverlapping) {
			const double overlappingWidth = getOverlappingWidth() * UnitOfLengthToPixelfactor;
			const double overlappingHeight = getOverlappingHeight() * UnitOfLengthToPixelfactor;
			const PosteRazorEnums::eOverlappingPositions overlappingPosition = getOverlappingPosition();
			const double overlappingTop =
				(overlappingPosition == PosteRazorEnums::eOverlappingPositionTopLeft || overlappingPosition == PosteRazorEnums::eOverlappingPositionTopRight)?
				borderTop
				:boxHeight - borderBottom - overlappingHeight;
			const double overlappingLeft = 
				(overlappingPosition == PosteRazorEnums::eOverlappingPositionTopLeft || overlappingPosition == PosteRazorEnums::eOverlappingPositionBottomLeft)?
				borderLeft
				:boxWidth - borderRight - overlappingWidth;
			
			paintCanvas->drawFilledRect(borderLeft + x_offset, overlappingTop + y_offset, printableAreaWidth, overlappingHeight, 255, 128, 128, 255);
			paintCanvas->drawFilledRect(overlappingLeft + x_offset, borderTop + y_offset, overlappingWidth, printableAreaHeight, 255, 128, 128, 255);
		}
	}

	void paintPosterOnCanvas(PaintCanvasInterface *paintCanvas) const
	{
		double canvasWidth = 0, canvasHeight = 0;
		paintCanvas->getSize(canvasWidth, canvasHeight);
		int boxWidth = 0, boxHeight = 0;

		double pagePrintableAreaWidth = getPrintablePaperAreaWidth();
		double pagePrintableAreaHeight = getPrintablePaperAreaHeight();
		const int pagesHorizontal = (int)ceil(getPosterWidth(PosteRazorEnums::ePosterSizeModePages));
		const int pagesVertical = (int)ceil(getPosterHeight(PosteRazorEnums::ePosterSizeModePages));
		const double posterWidth = pagesHorizontal*pagePrintableAreaWidth - (pagesHorizontal-1)*getOverlappingWidth() + getPaperBorderLeft() + getPaperBorderRight();
		const double posterHeight = pagesVertical*pagePrintableAreaHeight - (pagesVertical-1)*getOverlappingHeight() + getPaperBorderTop() + getPaperBorderBottom();
		getPreviewSize(posterWidth, posterHeight, (int)canvasWidth, (int)canvasHeight, boxWidth, boxHeight, true);
		const double x_offset = (canvasWidth - boxWidth) / 2;
		const double y_offset = (canvasHeight - boxHeight) / 2;
		const double UnitOfLengthToPixelfactor = (double)boxWidth/posterWidth;

		const double borderTop = getPaperBorderTop() * UnitOfLengthToPixelfactor;
		const double borderRight = getPaperBorderRight() * UnitOfLengthToPixelfactor;
		const double borderBottom = getPaperBorderBottom() * UnitOfLengthToPixelfactor;
		const double borderLeft = getPaperBorderLeft() * UnitOfLengthToPixelfactor;
		const double posterPrintableAreaWidth = boxWidth - borderLeft - borderRight;
		const double posterPrintableAreaHeight = boxHeight - borderTop - borderBottom;

		paintCanvas->drawFilledRect(x_offset, y_offset, boxWidth, boxHeight, 128, 128, 128, 255);
		paintCanvas->drawFilledRect(borderLeft + x_offset, borderTop + y_offset, posterPrintableAreaWidth, posterPrintableAreaHeight, 230, 230, 230, 255);

		const double imageWidth = getPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute) * UnitOfLengthToPixelfactor;
		const double imageHeight = getPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute) * UnitOfLengthToPixelfactor;

		const PosteRazorEnums::eVerticalAlignments verticalAlignment = getPosterVerticalAlignment();
		const PosteRazorEnums::eHorizontalAlignments horizontalAlignment = getPosterHorizontalAlignment();

		paintCanvas->drawImage(
			(
				horizontalAlignment == PosteRazorEnums::eHorizontalAlignmentLeft?borderLeft
				:horizontalAlignment == PosteRazorEnums::eHorizontalAlignmentCenter?
					qBound(borderLeft, ((double)boxWidth - imageWidth) / 2, borderLeft + posterPrintableAreaWidth - imageWidth)
				:(borderLeft + posterPrintableAreaWidth - imageWidth)
			)
			+ x_offset,

			(
				verticalAlignment == PosteRazorEnums::eVerticalAlignmentTop?borderTop
				:verticalAlignment == PosteRazorEnums::eVerticalAlignmentMiddle?
					qBound(borderTop, ((double)boxHeight - imageHeight) / 2, borderTop + posterPrintableAreaHeight - imageHeight)
				:(borderTop + posterPrintableAreaHeight - imageHeight)
				)
			+ y_offset,
			imageWidth, imageHeight
		);

		const double overlappingHeight = getOverlappingHeight() * UnitOfLengthToPixelfactor;
		const double overlappingWidth = getOverlappingWidth() * UnitOfLengthToPixelfactor;
		pagePrintableAreaWidth *= UnitOfLengthToPixelfactor;
		pagePrintableAreaHeight *= UnitOfLengthToPixelfactor;

		double overlappingRectangleYPosition = borderTop;
		for (int pagesRow = 0; pagesRow < pagesVertical - 1; pagesRow++) {
			overlappingRectangleYPosition += pagePrintableAreaHeight - overlappingHeight;
			paintCanvas->drawFilledRect(x_offset, overlappingRectangleYPosition + y_offset, boxWidth, overlappingHeight, 255, 128, 128, 128);
		}

		double overlappingRectangleXPosition = borderLeft;
		for (int pagesColumn = 0; pagesColumn < pagesHorizontal - 1; pagesColumn++) {
			overlappingRectangleXPosition += pagePrintableAreaWidth - overlappingWidth;
			paintCanvas->drawFilledRect(overlappingRectangleXPosition + x_offset, y_offset, overlappingWidth, boxHeight, 255, 128, 128, 128);
		}
	}

	void paintPosterPageOnCanvas(PaintCanvasInterface *paintCanvas, int page) const
	{
		const int columsCount = (int)(ceil(getPosterWidth(PosteRazorEnums::ePosterSizeModePages)));
		const int rowsCount = (int)(ceil(getPosterHeight(PosteRazorEnums::ePosterSizeModePages)));
		const int column = page % columsCount;
		const int row = ((int)(floor((double)page / (double)columsCount)));

		const double posterImageWidthCm = convertDistanceToCm(getPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute));
		const double posterImageHeightCm = convertDistanceToCm(getPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute));
		const double printablePaperAreaWidthCm = convertDistanceToCm(getPrintablePaperAreaWidth());
		const double printablePaperAreaHeightCm = convertDistanceToCm(getPrintablePaperAreaHeight());
		const double overlappingWidthCm = convertDistanceToCm(getOverlappingWidth());
		const double overlappingHeightCm = convertDistanceToCm(getOverlappingHeight());
		const double printablePosterAreaWidthCm = columsCount * printablePaperAreaWidthCm - (columsCount - 1) * overlappingWidthCm;
		const double printablePosterAreaHeightCm = rowsCount * printablePaperAreaHeightCm - (rowsCount - 1) * overlappingHeightCm;
		const double borderTopCm = convertDistanceToCm(getPaperBorderTop());
		const double borderRightCm = convertDistanceToCm(getPaperBorderRight());
		const double borderBottomCm = convertDistanceToCm(getPaperBorderBottom());
		const double borderLeftCm = convertDistanceToCm(getPaperBorderLeft());
		const double posterTotalWidthCm = printablePosterAreaWidthCm + borderLeftCm + borderRightCm;
		const double posterTotalHeightCm = printablePosterAreaHeightCm + borderTopCm + borderBottomCm;
		double imageOffsetFromLeftPosterBorderCm = (
			getPosterHorizontalAlignment() == PosteRazorEnums::eHorizontalAlignmentRight?posterTotalWidthCm - posterImageWidthCm - borderLeftCm
			:getPosterHorizontalAlignment() == PosteRazorEnums::eHorizontalAlignmentCenter?(posterTotalWidthCm - posterImageWidthCm)/2 - borderLeftCm
			:-borderLeftCm
		);
		imageOffsetFromLeftPosterBorderCm = qBound(.0, imageOffsetFromLeftPosterBorderCm, posterTotalWidthCm - posterImageWidthCm - borderLeftCm - borderRightCm);
		double imageOffsetFromTopPosterBorderCm = (
			getPosterVerticalAlignment() == PosteRazorEnums::eVerticalAlignmentBottom?posterTotalHeightCm - posterImageHeightCm - borderTopCm
			:getPosterVerticalAlignment() == PosteRazorEnums::eVerticalAlignmentMiddle?(posterTotalHeightCm - posterImageHeightCm)/2 - borderTopCm
			:-borderTopCm
		);
		imageOffsetFromTopPosterBorderCm = qBound(.0, imageOffsetFromTopPosterBorderCm, posterTotalHeightCm - posterImageHeightCm - borderTopCm - borderBottomCm);
		const double pageOffsetToImageFromLeftCm = column * (printablePaperAreaWidthCm - overlappingWidthCm) - imageOffsetFromLeftPosterBorderCm;
		const double pageOffsetToImageFromTopCm = row * (printablePaperAreaHeightCm - overlappingHeightCm) - imageOffsetFromTopPosterBorderCm;
		
		paintCanvas->drawImage(-pageOffsetToImageFromLeftCm, -pageOffsetToImageFromTopCm, posterImageWidthCm, posterImageHeightCm);
	}

	void paintOnCanvas(PaintCanvasInterface *paintCanvas, void* options = 0) const
	{
		const char* const state = (const char*)options;
		
		if (strcmp(state, "image") == 0) {
			paintImageOnCanvas(paintCanvas);
		} else if (strcmp(state, "paper") == 0 || strcmp(state, "overlapping") == 0) {
			paintPaperOnCanvas(paintCanvas, strcmp(state, "overlapping") == 0);
		} else if (strcmp(state, "poster") == 0) {
			paintPosterOnCanvas(paintCanvas);
		} else if (strncmp(state, "posterpage", strlen("posterpage")) == 0) {
			int page;
			sscanf(state, "posterpage %d", &page);
			paintPosterPageOnCanvas(paintCanvas, page);
		}
	}

	void setPosterOutputFormat(ImageIOTypes::eImageFormats format)
	{
		m_posterOutputFormat = format;
	}

	ImageIOTypes::eImageFormats getPosterOutputFormat(void) const
	{
		return m_posterOutputFormat;
	}

	int savePoster(const char *fileName) const
	{
		const int pagesCount = (int)(ceil(getPosterWidth(PosteRazorEnums::ePosterSizeModePages))) * (int)(ceil(getPosterHeight(PosteRazorEnums::ePosterSizeModePages)));
		return m_imageIO->savePoster(fileName, getPosterOutputFormat(), this, pagesCount, convertDistanceToCm(getPrintablePaperAreaWidth()), convertDistanceToCm(getPrintablePaperAreaHeight()));
	}
};

PosteRazor* PosteRazor::createPosteRazor()
{
	return (PosteRazor*)new PosteRazorImplementation();
}