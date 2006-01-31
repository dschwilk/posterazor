/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/
// generated by Fast Light User Interface Designer (fluid) version 1.0107

#ifndef PosteRazorDialogUI_h
#define PosteRazorDialogUI_h
#include <FL/Fl.H>
#include "Fl_Paint_Canvas_Group.h"
#include "Fl_Image_Text_Button.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Check_Button.H>

class PosteRazorDialogUI : public Fl_Double_Window {
  void _PosteRazorDialogUI();
public:
  PosteRazorDialogUI(int X, int Y, int W, int H, const char *L = 0);
  PosteRazorDialogUI(int W, int H, const char *L = 0);
  Fl_Button *m_nextButton;
private:
  void cb_m_nextButton_i(Fl_Button*, void*);
  static void cb_m_nextButton(Fl_Button*, void*);
public:
  Fl_Button *m_prevButton;
private:
  void cb_m_prevButton_i(Fl_Button*, void*);
  static void cb_m_prevButton(Fl_Button*, void*);
public:
  Fl_Image_Text_Button *m_settingsButton;
private:
  void cb_m_settingsButton_i(Fl_Image_Text_Button*, void*);
  static void cb_m_settingsButton(Fl_Image_Text_Button*, void*);
public:
  Fl_Box *m_settingsButtonLabel;
  Fl_Wizard *m_wizard;
  Fl_Group *m_loadInputImageStep;
  Fl_Group *m_imageLoadGroup;
  Fl_Button *m_imageLoadButton;
private:
  void cb_m_imageLoadButton_i(Fl_Button*, void*);
  static void cb_m_imageLoadButton(Fl_Button*, void*);
public:
  Fl_Box *m_inputFileNameLabel;
  Fl_Group *m_imageInfoGroup;
  Fl_Box *m_imageInfoValuesLabel;
  Fl_Box *m_imageInfoKeysLabel;
  Fl_Group *m_paperSizeStep;
  Fl_Tabs *m_paperFormatTypeTabs;
private:
  void cb_m_paperFormatTypeTabs_i(Fl_Tabs*, void*);
  static void cb_m_paperFormatTypeTabs(Fl_Tabs*, void*);
public:
  Fl_Group *m_paperFormatStandardGroup;
  Fl_Choice *m_paperFormatChoice;
  Fl_Group *m_paperOrientationGroup;
  Fl_Round_Button *m_paperOrientationPortraitRadioButton;
private:
  void cb_m_paperOrientationPortraitRadioButton_i(Fl_Round_Button*, void*);
  static void cb_m_paperOrientationPortraitRadioButton(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *m_paperOrientationLandscapeRadioButton;
private:
  void cb_m_paperOrientationLandscapeRadioButton_i(Fl_Round_Button*, void*);
  static void cb_m_paperOrientationLandscapeRadioButton(Fl_Round_Button*, void*);
public:
  Fl_Group *m_paperFormatCustomGroup;
  Fl_Value_Input *m_paperCustomWidthInput;
private:
  void cb_m_paperCustomWidthInput_i(Fl_Value_Input*, void*);
  static void cb_m_paperCustomWidthInput(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *m_paperCustomHeightInput;
private:
  void cb_m_paperCustomHeightInput_i(Fl_Value_Input*, void*);
  static void cb_m_paperCustomHeightInput(Fl_Value_Input*, void*);
public:
  Fl_Box *m_paperCustomWidthDimensionUnitLabel;
  Fl_Box *m_paperCustomHeightDimensionUnitLabel;
  Fl_Group *m_paperBordersGroup;
  Fl_Value_Input *m_paperBorderTopInput;
private:
  void cb_m_paperBorderTopInput_i(Fl_Value_Input*, void*);
  static void cb_m_paperBorderTopInput(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *m_paperBorderRightInput;
private:
  void cb_m_paperBorderRightInput_i(Fl_Value_Input*, void*);
  static void cb_m_paperBorderRightInput(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *m_paperBorderBottomInput;
private:
  void cb_m_paperBorderBottomInput_i(Fl_Value_Input*, void*);
  static void cb_m_paperBorderBottomInput(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *m_paperBorderLeftInput;
private:
  void cb_m_paperBorderLeftInput_i(Fl_Value_Input*, void*);
  static void cb_m_paperBorderLeftInput(Fl_Value_Input*, void*);
public:
  Fl_Group *m_overlappingStep;
  Fl_Group *m_overlappingSizeGroup;
  Fl_Value_Input *m_overlappingWidthInput;
private:
  void cb_m_overlappingWidthInput_i(Fl_Value_Input*, void*);
  static void cb_m_overlappingWidthInput(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *m_overlappingHeightInput;
private:
  void cb_m_overlappingHeightInput_i(Fl_Value_Input*, void*);
  static void cb_m_overlappingHeightInput(Fl_Value_Input*, void*);
public:
  Fl_Box *m_overlappingWidthDimensionUnitLabel;
  Fl_Box *m_overlappingHeightDimensionUnitLabel;
  Fl_Group *m_overlappingPositionGroup;
  Fl_Button *m_overlappingPositionTopLeftButton;
private:
  void cb_m_overlappingPositionTopLeftButton_i(Fl_Button*, void*);
  static void cb_m_overlappingPositionTopLeftButton(Fl_Button*, void*);
public:
  Fl_Button *m_overlappingPositionTopRightButton;
private:
  void cb_m_overlappingPositionTopRightButton_i(Fl_Button*, void*);
  static void cb_m_overlappingPositionTopRightButton(Fl_Button*, void*);
public:
  Fl_Button *m_overlappingPositionBottomLeftButton;
private:
  void cb_m_overlappingPositionBottomLeftButton_i(Fl_Button*, void*);
  static void cb_m_overlappingPositionBottomLeftButton(Fl_Button*, void*);
public:
  Fl_Button *m_overlappingPositionBottomRightButton;
private:
  void cb_m_overlappingPositionBottomRightButton_i(Fl_Button*, void*);
  static void cb_m_overlappingPositionBottomRightButton(Fl_Button*, void*);
public:
  Fl_Group *m_posterSizeStep;
  Fl_Group *m_posterSizeGroup;
  Fl_Round_Button *m_posterSizeAbsoluteRadioButton;
private:
  void cb_m_posterSizeAbsoluteRadioButton_i(Fl_Round_Button*, void*);
  static void cb_m_posterSizeAbsoluteRadioButton(Fl_Round_Button*, void*);
public:
  Fl_Group *m_posterSizeAbsoluteGroup;
  Fl_Value_Input *m_posterAbsoluteWidthInput;
private:
  void cb_m_posterAbsoluteWidthInput_i(Fl_Value_Input*, void*);
  static void cb_m_posterAbsoluteWidthInput(Fl_Value_Input*, void*);
public:
  Fl_Box *m_posterAbsoluteWidthDimensionUnitLabel;
  Fl_Value_Input *m_posterAbsoluteHeightInput;
private:
  void cb_m_posterAbsoluteHeightInput_i(Fl_Value_Input*, void*);
  static void cb_m_posterAbsoluteHeightInput(Fl_Value_Input*, void*);
public:
  Fl_Box *m_posterAbsoluteHeightDimensionUnitLabel;
  Fl_Round_Button *m_posterSizeInPagesRadioButton;
private:
  void cb_m_posterSizeInPagesRadioButton_i(Fl_Round_Button*, void*);
  static void cb_m_posterSizeInPagesRadioButton(Fl_Round_Button*, void*);
public:
  Fl_Group *m_posterSizeInPagesGroup;
  Fl_Value_Input *m_posterPagesWidthInput;
private:
  void cb_m_posterPagesWidthInput_i(Fl_Value_Input*, void*);
  static void cb_m_posterPagesWidthInput(Fl_Value_Input*, void*);
public:
  Fl_Box *m_posterPagesWidthLabel;
  Fl_Value_Input *m_posterPagesHeightInput;
private:
  void cb_m_posterPagesHeightInput_i(Fl_Value_Input*, void*);
  static void cb_m_posterPagesHeightInput(Fl_Value_Input*, void*);
public:
  Fl_Box *m_posterPagesHeightLabel;
  Fl_Round_Button *m_posterSizePercentualRadioButton;
private:
  void cb_m_posterSizePercentualRadioButton_i(Fl_Round_Button*, void*);
  static void cb_m_posterSizePercentualRadioButton(Fl_Round_Button*, void*);
public:
  Fl_Group *m_posterSizePercentualGroup;
  Fl_Value_Input *m_posterPercentualSizeInput;
private:
  void cb_m_posterPercentualSizeInput_i(Fl_Value_Input*, void*);
  static void cb_m_posterPercentualSizeInput(Fl_Value_Input*, void*);
public:
  Fl_Box *m_posterPercentualWidthLabel;
  Fl_Group *m_imageAlignmentGroup;
  Fl_Button *m_posterAlignmentTopButton;
private:
  void cb_m_posterAlignmentTopButton_i(Fl_Button*, void*);
  static void cb_m_posterAlignmentTopButton(Fl_Button*, void*);
public:
  Fl_Button *m_posterAlignmentMiddleButton;
private:
  void cb_m_posterAlignmentMiddleButton_i(Fl_Button*, void*);
  static void cb_m_posterAlignmentMiddleButton(Fl_Button*, void*);
public:
  Fl_Button *m_posterAlignmentBottomButton;
private:
  void cb_m_posterAlignmentBottomButton_i(Fl_Button*, void*);
  static void cb_m_posterAlignmentBottomButton(Fl_Button*, void*);
public:
  Fl_Button *m_posterAlignmentLeftButton;
private:
  void cb_m_posterAlignmentLeftButton_i(Fl_Button*, void*);
  static void cb_m_posterAlignmentLeftButton(Fl_Button*, void*);
public:
  Fl_Button *m_posterAlignmentCenterButton;
private:
  void cb_m_posterAlignmentCenterButton_i(Fl_Button*, void*);
  static void cb_m_posterAlignmentCenterButton(Fl_Button*, void*);
public:
  Fl_Button *m_posterAlignmentRightButton;
private:
  void cb_m_posterAlignmentRightButton_i(Fl_Button*, void*);
  static void cb_m_posterAlignmentRightButton(Fl_Button*, void*);
public:
  Fl_Group *m_savePosterStep;
  Fl_Group *m_savePosterGroup;
private:
  void cb_14filesave_i(Fl_Button*, void*);
  static void cb_14filesave(Fl_Button*, void*);
public:
  Fl_Check_Button *m_setLaunchPDFApplicationCheckButton;
private:
  void cb_m_setLaunchPDFApplicationCheckButton_i(Fl_Check_Button*, void*);
  static void cb_m_setLaunchPDFApplicationCheckButton(Fl_Check_Button*, void*);
public:
  Fl_Paint_Canvas_Group *m_paintCanvasGroup;
  Fl_Box *m_stepInfoBox;
private:
  void cb__i(Fl_Button*, void*);
  static void cb_(Fl_Button*, void*);
public:
  virtual void OpenSettingsDialog(void) = 0;
  virtual void next(void) = 0;
  virtual void prev(void) = 0;
  virtual void UpdateNavigationButtons(void) = 0;
  virtual void OpenHelpDialog(void) = 0;
  virtual void LoadInputImage(const char *fileName) = 0;
  virtual void SetPaperSizeFields(void) = 0;
  virtual void HandlePaperSizeChangement(Fl_Widget* sourceWidget) = 0;
  virtual void SetOverlappingFields(void) = 0;
  virtual void HandleOverlappingChangement(Fl_Widget* sourceWidget) = 0;
  virtual void UpdatePosterSizeGroupsState(void) = 0;
  virtual void UpdatePosterSizeFields(Fl_Valuator* sourceWidget) = 0;
  virtual void HandlePosterImageAlignment(void) = 0;
  virtual void SavePoster(void) = 0;
  virtual void SetLaunchPDFApplication(void) = 0;
};
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Return_Button.H>

class PosteRazorHelpDialogUI : public Fl_Double_Window {
  void _PosteRazorHelpDialogUI();
public:
  PosteRazorHelpDialogUI(int X, int Y, int W, int H, const char *L = 0);
  PosteRazorHelpDialogUI(int W, int H, const char *L = 0);
  Fl_Help_View *m_help_view;
private:
  void cb_OK_i(Fl_Return_Button*, void*);
  static void cb_OK(Fl_Return_Button*, void*);
public:
  Fl_Button *m_homepageButton;
private:
  void cb_m_homepageButton_i(Fl_Button*, void*);
  static void cb_m_homepageButton(Fl_Button*, void*);
public:
  virtual void JumpToAnchor(const char *anchor) = 0;
  virtual void SetHtmlContent(const char *content) = 0;
  virtual void HandleHomepageButtonClick(void) = 0;
  virtual void UpdateLanguage(void) = 0;
  void SetHomepageButtonLabel(const char *label);
};

class PosteRazorSettingsDialogUI : public Fl_Double_Window {
  void _PosteRazorSettingsDialogUI();
public:
  PosteRazorSettingsDialogUI(int X, int Y, int W, int H, const char *L = 0);
  PosteRazorSettingsDialogUI(int W, int H, const char *L = 0);
  bool m_okWasPressed;
  Fl_Group *m_unitOfLengthGroup;
  Fl_Group *m_unitOfLengthButtonsGroup;
  Fl_Box *m_unitOfLengthExplanationBox;
  Fl_Group *m_useOpenGLGroup;
  Fl_Check_Button *m_useOpenGLCheckButton;
private:
  void cb_m_useOpenGLCheckButton_i(Fl_Check_Button*, void*);
  static void cb_m_useOpenGLCheckButton(Fl_Check_Button*, void*);
public:
  Fl_Box *m_useOpenGLExplanationBox;
  Fl_Group *m_languageGroup;
  Fl_Group *m_languageButtonsGroup;
  Fl_Box *m_languageExplanationBox;
private:
  void cb_OK1_i(Fl_Return_Button*, void*);
  static void cb_OK1(Fl_Return_Button*, void*);
public:
  Fl_Button *m_cancelButton;
private:
  void cb_m_cancelButton_i(Fl_Button*, void*);
  static void cb_m_cancelButton(Fl_Button*, void*);
public:
  virtual void HandleUseOpenGLChangement(void) = 0;
  bool show_modal(void);
};
#endif
