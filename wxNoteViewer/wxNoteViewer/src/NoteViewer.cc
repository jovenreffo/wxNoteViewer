#include <wx/statline.h>
#include "NoteViewer.h"
#include "XPM/xpm_include.h"

BEGIN_EVENT_TABLE(NoteViewer, wxFrame)
	EVT_DROP_FILES(NoteViewer::OnDropFile)
	EVT_TEXT(wxID_ANY, NoteViewer::OnText)
	EVT_BUTTON(ID_CLEAR_TEXT, NoteViewer::OnClearText)
	EVT_BUTTON(ID_CHANGE_FONT, NoteViewer::OnChangeFont)
	// Menu events
	EVT_MENU(ID_FULLSCREEN, NoteViewer::OnFullScreen)
	EVT_MENU(wxID_EXIT, NoteViewer::OnExit)
	EVT_MENU(ID_CUT, NoteViewer::OnCut)
	EVT_MENU(ID_COPY, NoteViewer::OnCopy)
	EVT_MENU(ID_PASTE, NoteViewer::OnPaste)
	EVT_MENU(ID_SELECT_ALL, NoteViewer::OnSelectAll)
	EVT_MENU(ID_UNDO, NoteViewer::OnUndo)
	EVT_MENU(ID_REDO, NoteViewer::OnRedo)
	EVT_MENU(ID_ZOOMIN, NoteViewer::OnZoomIn)
	EVT_MENU(ID_ZOOMOUT, NoteViewer::OnZoomOut)
	EVT_MENU(ID_OPEN, NoteViewer::OnOpen)
	EVT_MENU(ID_SAVE, NoteViewer::OnSave)
	EVT_MENU(ID_SAVEAS, NoteViewer::OnSaveAs)
	// Tool events
	EVT_TOOL(ID_CUT, NoteViewer::OnCut)
	EVT_TOOL(ID_COPY, NoteViewer::OnCopy)
	EVT_TOOL(ID_PASTE, NoteViewer::OnPaste)
	EVT_TOOL(ID_UNDO, NoteViewer::OnUndo)
	EVT_TOOL(ID_REDO, NoteViewer::OnRedo)
	EVT_TOOL(ID_ZOOMIN, NoteViewer::OnZoomIn)
	EVT_TOOL(ID_ZOOMOUT, NoteViewer::OnZoomOut)
	EVT_TOOL(ID_OPEN, NoteViewer::OnOpen)
	EVT_TOOL(ID_SAVE, NoteViewer::OnSave)
	EVT_TOOL(ID_SAVEAS, NoteViewer::OnSaveAs)
END_EVENT_TABLE()

NoteViewer::NoteViewer()
	: wxFrame{ nullptr, wxID_ANY, _T("Note Viewer"), wxDefaultPosition, WINDOW_SIZE, WINDOW_STYLE }
{
	this->Init();
	this->SetMinSize(WINDOW_SIZE);
}

void NoteViewer::Init()
{
	this->SetupBitmaps();
	this->SetupToolBar();
	this->SetupMenuBar();
	this->SetupControls();
	this->SetupSizers();
}

void NoteViewer::SetupBitmaps()
{
	m_cutBmp = wxBitmap(cut_xpm);
	m_copyBmp = wxBitmap(copy_xpm);
	m_pasteBmp = wxBitmap(paste_xpm);
	m_undoBmp = wxBitmap(undo_xpm);
	m_redoBmp = wxBitmap(redo_xpm);
	m_zoomInBmp = wxBitmap(zoomin_xpm);
	m_zoomOutBmp = wxBitmap(zoomout_xpm);
	m_openBmp = wxBitmap(open_xpm);
	m_saveBmp = wxBitmap(save_xpm);
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
	m_pViewMenu = new wxMenu();

	m_pFileMenu->Append(ID_SAVE, _T("&Save\tCtrl+S"));
	m_pFileMenu->Append(ID_SAVEAS, _T("&Save As...\tCtrl+Shift+S"));
	m_pFileMenu->Append(ID_OPEN, _T("&Open...\tCtrl+O"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit"));

	m_pEditMenu->Append(ID_UNDO, _T("&Undo\tCtrl+Z"));
	m_pEditMenu->Append(ID_REDO, _T("&Redo\tCtrl+Shift+Z"));
	m_pEditMenu->AppendSeparator();
	m_pEditMenu->Append(ID_CUT, _T("&Cut\tCtrl+X"));
	m_pEditMenu->Append(ID_COPY, _T("&Copy\tCtrl+C"));
	m_pEditMenu->Append(ID_PASTE, _T("&Paste\tCtrl+V"));
	m_pEditMenu->Append(ID_SELECT_ALL, _T("&Select All\tCtrl+A"));

	m_pViewMenu->Append(ID_FULLSCREEN, _T("&Toggle Fullscreen\tF11"));
	m_pViewMenu->AppendSeparator();
	m_pViewMenu->Append(ID_ZOOMIN, _T("&Zoom In\tCtrl+Shift++"));
	m_pViewMenu->Append(ID_ZOOMOUT, _T("&Zoom Out\tCtrl+Shift+-"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pEditMenu, _T("&Edit"));
	m_pMenuBar->Append(m_pViewMenu, _T("&View"));
	this->SetMenuBar(m_pMenuBar);
}

void NoteViewer::SetupControls()
{
	m_clearButton = new wxButton(this, ID_CLEAR_TEXT, _T("Clear Text"), wxDefaultPosition, wxDefaultSize);
	m_fontButton = new wxButton(this, ID_CHANGE_FONT, _T("Change Font"), wxDefaultPosition, wxDefaultSize);
	m_pTextBox = new wxTextCtrl(this, wxID_ANY, _T("Open (Ctrl + 0) or drag in a text file.\n"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

	m_pTextBox->DragAcceptFiles(true);
	m_pTextBox->Bind(wxEVT_MOUSEWHEEL, &NoteViewer::OnMouse, this); // Connect the mouse event handler so zooming is not processed outside of the textbox.
}

void NoteViewer::SetupSizers()
{
	// Sizer setup
	m_topSizer = new wxBoxSizer(wxVERTICAL);
	m_buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(m_topSizer);
	m_topSizer->Add(m_buttonSizer);

	// Add elements
	m_buttonSizer->Add(m_clearButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_buttonSizer->Add(m_fontButton, 0, wxALIGN_LEFT | wxALL, 5);
	//m_topSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_topSizer->Add(m_pTextBox, 1, wxEXPAND | wxALL, 5);
}

// Zooming

void NoteViewer::ZoomIn()
{
	// Add text zoom by getting the current font size and changing it accordingly, and keeping the font the user selected
	m_nFontSize = m_pTextBox->GetFont().GetPointSize();
	++m_nFontSize;
	m_pTextBox->SetFont(wxFont(m_nFontSize, m_pTextBox->GetFont().GetFamily(), m_pTextBox->GetFont().GetStyle(), m_pTextBox->GetFont().GetWeight(), false));
}

void NoteViewer::ZoomOut()
{
	m_nFontSize = m_pTextBox->GetFont().GetPointSize();
	--m_nFontSize;
	m_pTextBox->SetFont(wxFont(m_nFontSize, m_pTextBox->GetFont().GetFamily(), m_pTextBox->GetFont().GetStyle(), m_pTextBox->GetFont().GetWeight(), false));
}

// Events

void NoteViewer::OnFullScreen(wxCommandEvent& event)
{
	this->ShowFullScreen(!IsFullScreen(), wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
}

void NoteViewer::OnDropFile(wxDropFilesEvent& event)
{
}

void NoteViewer::OnMouse(wxMouseEvent& event)
{
	if (event.ControlDown() && event.GetWheelRotation() > 0)
	{
		this->ZoomIn();
#ifdef _DEBUG
		//m_pTextBox->AppendText(wxString() << "Delta: " << event.GetWheelRotation() << '\n');
#endif
	}

	if (event.ControlDown() && event.GetWheelRotation() < 0)
	{
		this->ZoomOut();
#ifdef _DEBUG
		//m_pTextBox->AppendText(wxString() << "Delta: " << event.GetWheelRotation() << '\n');
#endif
	}
}

void NoteViewer::OnExit(wxCommandEvent& event)
{
	this->Destroy();
}

void NoteViewer::OnText(wxCommandEvent& event)
{
	m_bFileSaved = false;
}

void NoteViewer::OnClearText(wxCommandEvent& event)
{
	m_pTextBox->Clear();
}

void NoteViewer::OnChangeFont(wxCommandEvent& event)
{
}

void NoteViewer::OnOpen(wxCommandEvent& event)
{
	wxFileDialog* openDialog = new wxFileDialog(this, _T("Open text file"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	// Check if the user has loaded a file and confirm they want to overwrite its contents.
	if (m_bCurrentFile && !m_bFileSaved)
		if (wxMessageBox(_T("Current file has not been saved. Would you like to proceed?"), _T("Confirm"), wxICON_WARNING | wxYES_NO) == wxNO)
			return;

	if (openDialog->ShowModal() == wxID_OK)
	{
		// Overwrite the current text with the new text and change the window title.
		m_currentFilePath = openDialog->GetPath();
		m_currentFileName = openDialog->GetFilename();
		m_pTextBox->LoadFile(m_currentFilePath);
		this->SetLabel(wxString("Note Viewer - ") << m_currentFileName);
		m_bCurrentFile = true;
	}

	openDialog->Destroy();
}

void NoteViewer::OnSave(wxCommandEvent& event)
{
	m_pTextBox->SaveFile(m_saveFilePath);
	m_bFileSaved = true;
}

void NoteViewer::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog* saveDialog = new wxFileDialog(this, _T("Save text file"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveDialog->ShowModal() == wxID_OK)
	{
		m_saveFilePath = saveDialog->GetPath();
		m_currentFileName = saveDialog->GetFilename();
		m_pTextBox->SaveFile(m_saveFilePath);
		this->SetLabel(wxString("Note Viewer - ") << m_currentFileName);
		m_bFileSaved = true;
	}

	saveDialog->Destroy();
}

void NoteViewer::OnCut(wxCommandEvent& event)
{
	if (m_pTextBox->CanCut())
		m_pTextBox->Cut();
}

void NoteViewer::OnCopy(wxCommandEvent& event)
{
	if (m_pTextBox->CanCopy())
		m_pTextBox->Copy();
}

void NoteViewer::OnPaste(wxCommandEvent& event)
{
	if (m_pTextBox->CanPaste())
		m_pTextBox->Paste();
}

void NoteViewer::OnSelectAll(wxCommandEvent& event)
{
	m_pTextBox->SelectAll();
}

void NoteViewer::OnUndo(wxCommandEvent& event)
{
	if (m_pTextBox->CanUndo())
		m_pTextBox->Undo();
}

void NoteViewer::OnRedo(wxCommandEvent& event)
{
	if (m_pTextBox->CanRedo())
		m_pTextBox->Redo();
}

void NoteViewer::OnZoomIn(wxCommandEvent& event)
{
	this->ZoomIn();
}

void NoteViewer::OnZoomOut(wxCommandEvent& event)
{
	this->ZoomOut();
}
