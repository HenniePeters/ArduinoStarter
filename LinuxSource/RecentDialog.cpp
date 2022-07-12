/***************************************************************
    Name:      RecentDialog.cpp
    Author:    Hennie Peters (hennie(dot)peters(at)gmail(dot)com)
    Created:   2022-07-08
    Copyright: Hennie Peters (https://github.com/HenniePeters)
    License:   Do with this code whatever you like best.
               Sell it, give it away for free, change it or don't
               But... when you get filthy rich by distributing
               any part of this program then hopefully you will
               remember my Patreon page:
               https://www.patreon.com/hennep
 **************************************************************/

#include <wx/msgdlg.h>
#include "RecentDialog.h"
#include "FileHandler.h"

//(*InternalHeaders(RecentDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(RecentDialog)
const long RecentDialog::ID_STATICTEXT6 = wxNewId();
const long RecentDialog::ID_STATICTEXT11 = wxNewId();
const long RecentDialog::ID_STATICTEXT12 = wxNewId();
const long RecentDialog::ID_STATICTEXT13 = wxNewId();
const long RecentDialog::ID_LISTBOX1 = wxNewId();
const long RecentDialog::ID_BUTTON1 = wxNewId();
const long RecentDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE( RecentDialog, wxDialog )
    //(*EventTable(RecentDialog)
    //*)
END_EVENT_TABLE()

void RecentDialog::OnListboxDblClick( wxCommandEvent &event ) {
    OnOKClick( event );
}

void RecentDialog::OnQuitClick( wxCommandEvent& event ) {
    Close();
}

RecentDialog::~RecentDialog() {
    //(*Destroy(RecentDialog)
    //*)
}

void RecentDialog::OnOKClick( wxCommandEvent& event ) {
    if( lbxRecentSketches->GetSelection() >= 0 ) {
        wxString cmd = ThisApp->argv[0] + _( " \"" ) + lbxRecentSketches->GetString( lbxRecentSketches->GetSelection() ) + "\" &";
        system( cmd.c_str().AsChar() );
        Close();
    }
}

void RecentDialog::OnListboxContext( wxCommandEvent &event ) {
    if( lbxRecentSketches->GetSelection() >= 0 ) {
        wxMessageDialog dlg( NULL, _( "\nDo you want to remove the selected sketch from the list" ), _T( "Remove from list of recent files" ), wxICON_EXCLAMATION | wxOK | wxCANCEL );
        if( wxID_OK == dlg.ShowModal() ) {
            int iNewSelection;
            if( lbxRecentSketches->GetCount() > 1 ) {
                iNewSelection = lbxRecentSketches->GetSelection();
                if( iNewSelection > 0 ) {
                    iNewSelection--;
                }
            }
            filehandler.WritePrefsExcept( lbxRecentSketches->GetString( lbxRecentSketches->GetSelection() ) );
            PopulateListbox();
            lbxRecentSketches->SetFirstItem( iNewSelection );
            cmdOK->Enable( false );
        }
    }
}

void RecentDialog::OnListboxSelect( wxCommandEvent & event ) {
    wxString wxsIno = lbxRecentSketches->GetString( lbxRecentSketches->GetSelection() );
    txtController->SetLabel( _( "No board information found in sketch" ) );
    cmdOK->Enable( true );
    if( wxFileExists( wxsIno ) ) {
        arduino_sketch.ClearCashedSketch();
        filehandler.ReadSketch( wxsIno );
        if( arduino_sketch.Board.Left( 6 ) == _( "board=" ) ) {
            size_t len = arduino_sketch.Board.Len() - 6;
            txtController->SetLabel( arduino_sketch.Board.substr( 6, len ) );
        }
    }
}

void RecentDialog::PopulateListbox( void ) {
    long counter = 0;
    wxString wxsRecent, wxsLeft, wxsRight;
    wxsRecent = arduino_prefs.Recent;
    while( wxsRecent != _("") ) {
        if( SplitToken( wxsRecent, ',', wxsLeft, wxsRight ) ) {
            if( wxsLeft.Left( 16 ).Lower() == "recent.sketches=" ) {
                lbxRecentSketches->Clear();
                size_t len = wxsLeft.Len() - 16;
                lbxRecentSketches->AppendAndEnsureVisible( wxsLeft.substr( 16, len ) );
            } else {
                lbxRecentSketches->AppendAndEnsureVisible( wxsLeft );
            }
            wxsRecent = wxsRight;
        } else {
            wxsRecent = wxsLeft;
            break;
        }
        counter++;
    }
    wxString wxsLabel = wxString::Format( wxT( "%ld" ), counter ) + _( " sketches found." );
    txtRecent->SetLabel( wxsLabel );
}

RecentDialog::RecentDialog( wxApp * TheApp, wxWindow * parent, wxWindowID id, const wxPoint & pos, const wxSize & size ) {
    ThisApp = TheApp;
    //(*Initialize(RecentDialog)
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxGridSizer* GridSizer1;

    Create(parent, wxID_ANY, _("Arduino sketch loader 1.0 "), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    GridSizer1 = new wxGridSizer(2, 2, 0, 0);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("Controller type:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText5->SetMinSize(wxSize(-1,40));
    StaticText5->SetMaxSize(wxSize(-1,-1));
    wxFont StaticText5Font(14,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Ubuntu"),wxFONTENCODING_DEFAULT);
    StaticText5->SetFont(StaticText5Font);
    GridSizer1->Add(StaticText5, 1, wxALL|wxEXPAND, 5);
    txtController = new wxStaticText(this, ID_STATICTEXT11, _("Select a sketch"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    txtController->SetMinSize(wxSize(400,40));
    txtController->SetMaxSize(wxSize(-1,-1));
    wxFont txtControllerFont(14,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Ubuntu"),wxFONTENCODING_DEFAULT);
    txtController->SetFont(txtControllerFont);
    GridSizer1->Add(txtController, 1, wxALL|wxEXPAND, 5);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT12, _("Recent files:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    StaticText8->SetMinSize(wxSize(-1,40));
    StaticText8->SetMaxSize(wxSize(-1,-1));
    wxFont StaticText8Font(14,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Ubuntu"),wxFONTENCODING_DEFAULT);
    StaticText8->SetFont(StaticText8Font);
    GridSizer1->Add(StaticText8, 1, wxALL|wxEXPAND, 5);
    txtRecent = new wxStaticText(this, ID_STATICTEXT13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    txtRecent->SetMinSize(wxSize(400,40));
    txtRecent->SetMaxSize(wxSize(-1,40));
    wxFont txtRecentFont(14,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Ubuntu"),wxFONTENCODING_DEFAULT);
    txtRecent->SetFont(txtRecentFont);
    GridSizer1->Add(txtRecent, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(GridSizer1, 1, wxALL|wxEXPAND|wxSHAPED, 5);
    lbxRecentSketches = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    lbxRecentSketches->SetMinSize(wxSize(900,500));
    BoxSizer3->Add(lbxRecentSketches, 0, wxEXPAND, 5);
    BoxSizer4->Add(BoxSizer3, 1, wxALL|wxALIGN_TOP, 5);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    cmdOK = new wxButton(this, ID_BUTTON1, _("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    cmdOK->Disable();
    BoxSizer2->Add(cmdOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Quit = new wxButton(this, ID_BUTTON2, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(Quit, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 11);
    BoxSizer4->Add(BoxSizer2, 0, wxEXPAND|wxSHAPED, 0);
    BoxSizer1->Add(BoxSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RecentDialog::OnOKClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RecentDialog::OnQuitClick);
    //*)
    Connect( ID_LISTBOX1, wxEVT_LISTBOX_DCLICK, ( wxObjectEventFunction )&RecentDialog::OnListboxDblClick );
    Connect( ID_LISTBOX1, wxEVT_LISTBOX, ( wxObjectEventFunction )&RecentDialog::OnListboxSelect );
    Connect( ID_LISTBOX1, wxEVT_CONTEXT_MENU, ( wxObjectEventFunction )&RecentDialog::OnListboxContext );
    PopulateListbox();
    if( lbxRecentSketches->GetCount() > 0 ) {
        lbxRecentSketches->SetFirstItem( 0 );
    }

}
