#ifndef _NOTEVIEWER_H_
#define _NOTEVIEWER_H_

#include <wx/wx.h>
#include <wx/textctrl.h>

#define WINDOW_SIZE (wxSize(670, 500))
#define WINDOW_STYLE (wxDEFAULT_FRAME_STYLE)

enum
{
	ID_CUT,
	ID_COPY,
	ID_PASTE,
	ID_UNDO,
	ID_REDO,
	ID_ZOOMIN,
	ID_ZOOMOUT,
	ID_OPEN,
	ID_SAVE,
	ID_SAVEAS
};

class NoteViewer: public wxFrame
{
	DECLARE_EVENT_TABLE()

private:
	wxTextCtrl* m_pTextBox;
	wxToolBar* m_pToolBar;
	wxMenuBar* m_pMenuBar;
	wxMenu* m_pFileMenu;
	wxMenu* m_pEditMenu;

	wxBitmap m_cutBmp;
	wxBitmap m_copyBmp;
	wxBitmap m_pasteBmp;
	wxBitmap m_undoBmp;
	wxBitmap m_redoBmp;
	wxBitmap m_zoomInBmp;
	wxBitmap m_zoomOutBmp;
	wxBitmap m_openBmp;
	wxBitmap m_saveBmp;
	wxBitmap m_saveAsBmp;

public:
	NoteViewer();

	// Window functions
	void Init();
	void SetupBitmaps();
	void SetupToolBar();
	void SetupMenuBar();

	// Events
	void OnExit(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);
	void OnZoomIn(wxCommandEvent& event);
	void OnZoomOut(wxCommandEvent& event);
};

#endif