#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <wx/wx.h>
#include "NoteViewer.h"

class App : public wxApp
{
public:
	virtual bool OnInit();
};

enum
{
	ID_NOTE = wxID_HIGHEST + 100
};

class Frame : public wxFrame
{
	DECLARE_EVENT_TABLE()

private:
	wxMenuBar* m_menuBar;
	wxMenu* m_fileMenu;

	NoteViewer* m_pNoteViewer;

public:
	Frame();

	// Setup
	void Init();
	void SetupMenuBar();

	// Events
	void OnExit(wxCommandEvent& event);
	void OnNote(wxCommandEvent& event);
};

#endif