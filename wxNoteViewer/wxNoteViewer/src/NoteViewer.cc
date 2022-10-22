#include "NoteViewer.h"
#include "XPM/xpm_include.h"

BEGIN_EVENT_TABLE(NoteViewer, wxFrame)

END_EVENT_TABLE()

NoteViewer::NoteViewer()
	: wxFrame{ nullptr, wxID_ANY, _T("Note Viewer"), wxDefaultPosition, WINDOW_SIZE, WINDOW_STYLE }
{
	this->SetMinSize(WINDOW_SIZE);
	this->Init();
}

void NoteViewer::Init()
{
	this->SetupBitmaps();
	this->SetupToolBar();
	this->SetupMenuBar();
}

void NoteViewer::SetupBitmaps()
{
	m_cutBmp = wxBitmap(cut_xpm);
	m_copyBmp =	wxBitmap(copy_xpm);
	m_pasteBmp = wxBitmap(paste_xpm);
	m_undoBmp =	wxBitmap(undo_xpm);
	m_redoBmp =	wxBitmap(redo_xpm);
	m_zoomInBmp = wxBitmap(zoomin_xpm);
	m_zoomOutBmp = wxBitmap(zoomout_xpm);
	m_openBmp =	wxBitmap(open_xpm);
	m_saveBmp =	wxBitmap(save_xpm);
	m_saveAsBmp = wxBitmap(saveas_xpm);
}

void NoteViewer::SetupToolBar()
{
	m_pToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);

	// Add tools
	m_pToolBar->AddTool(ID_OPEN, _T("Open"), m_openBmp, _T("Open a text file."));
	m_pToolBar->AddTool(ID_SAVE, _T("Save"), m_saveBmp, _T("Save this file."));
	m_pToolBar->AddTool(ID_SAVEAS, _T("Save"), m_saveAsBmp, _T("Save this file as..."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(ID_CUT, _T("Cut"), m_cutBmp, _T("Cut selected text."));
	m_pToolBar->AddTool(ID_COPY, _T("Copy"), m_copyBmp, _T("Copy selected text."));
	m_pToolBar->AddTool(ID_PASTE, _T("Paste"), m_pasteBmp, _T("Paste selected text."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(ID_UNDO, _T("Undo"), m_undoBmp, _T("Undo  action."));
	m_pToolBar->AddTool(ID_REDO, _T("Redo"), m_redoBmp, _T("Redo action."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(ID_ZOOMIN, _T("Zoom In"), m_zoomInBmp, _T("Zoom in."));
	m_pToolBar->AddTool(ID_ZOOMOUT, _T("Zoom Out"), m_zoomOutBmp, _T("Zoom out."));

	// Set and assign the toolbar
	m_pToolBar->Realize();
	this->SetToolBar(m_pToolBar);
}

void NoteViewer::SetupMenuBar()
{
	m_pMenuBar = new wxMenuBar();
	m_pFileMenu = new wxMenu();
	m_pEditMenu = new wxMenu();

	m_pFileMenu->Append(ID_SAVE, _T("&Save\tCtrl+S"));
	m_pFileMenu->Append(ID_OPEN, _T("&Open...\tCtrl+O"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pEditMenu, _T("&Edit"));
	this->SetMenuBar(m_pMenuBar);
}
