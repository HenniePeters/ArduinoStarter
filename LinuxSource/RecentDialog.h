/***************************************************************
    Name:      RecentDialog.h
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

#ifndef RECENTDIALOG_H
#define RECENTDIALOG_H

//(*Headers(RecentDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

#include <wx/app.h>

class RecentDialog: public wxDialog {
public:
    RecentDialog( wxApp* TheApp, wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );
    virtual ~RecentDialog();
    void PopulateListbox( void );

    //(*Declarations(RecentDialog)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxButton* Help;
    wxButton* Quit;
    wxButton* cmdOK;
    wxListBox* lbxRecentSketches;
    wxStaticText* StaticText5;
    wxStaticText* StaticText8;
    wxStaticText* txtController;
    wxStaticText* txtRecent;
    //*)

protected:
    //(*Identifiers(RecentDialog)
    static const long ID_STATICTEXT6;
    static const long ID_STATICTEXT11;
    static const long ID_STATICTEXT12;
    static const long ID_STATICTEXT13;
    static const long ID_LISTBOX1;
    static const long ID_BUTTON1;
    static const long ID_BUTTON3;
    static const long ID_BUTTON2;
    //*)

private:
    wxApp* ThisApp;
    //(*Handlers(RecentDialog)
    //void OnQuit( wxCommandEvent& event );
    void OnQuitClick(wxCommandEvent& event);
    void OnOKClick(wxCommandEvent& event);
    //*)
    void OnListboxDblClick(wxCommandEvent &event);
    void OnListboxSelect(wxCommandEvent &event);
    void OnListboxContext(wxCommandEvent &event);
    void OnHelpClick(wxCommandEvent &event);


    DECLARE_EVENT_TABLE()
};

#endif
