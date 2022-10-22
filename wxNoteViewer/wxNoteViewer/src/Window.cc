#include "Window.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(ID_NOTE, Frame::OnNote)
	EVT_MENU(wxID_EXIT, Frame::OnExit)
END_EVENT_TABLE()

Frame::Frame()
	: wxFrame(nullptr, wxID_ANY, _T("wxNoteViewer"), wxDefaultPosition, wxSize(340, 180))
{
	this->Init();
}

void Frame::Init()
{
	this->SetupMenuBar();
}

void Frame::SetupMenuBar()
{
	m_menuBar = new wxMenuBar();
	m_fileMenu = new wxMenu();

	m_fileMenu->Append(ID_NOTE, _T("&Note Viewer\tCtrl+T"));
	m_fileMenu->AppendSeparator();
	m_fileMenu->Append(wxID_EXIT, _T("&Exit"));

	m_menuBar->Append(m_fileMenu, _T("&File"));
	this->SetMenuBar(m_menuBar);
}

void Frame::OnExit(wxCommandEvent& event)
{
	this->Destroy();
}

void Frame::OnNote(wxCommandEvent& event)
{
	m_pNoteViewer = new NoteViewer();
	m_pNoteViewer->Show(true);
}