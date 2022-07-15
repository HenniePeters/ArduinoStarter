#ifndef HELPDIALOG_H
#define HELPDIALOG_H

//////////////////////////////////////////////
// DON'T FORGET!: wx-config --libs std,richtext
//////////////////////////////////////////////

//(*Headers(HelpDialog)
#include <wx/dialog.h>
#include <wx/richtext/richtextctrl.h>
//*)

class HelpDialog: public wxDialog
{
	public:

		HelpDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HelpDialog();

		//(*Declarations(HelpDialog)
		wxRichTextCtrl* RichTextCtrl1;
		//*)

	protected:

		//(*Identifiers(HelpDialog)
		static const long ID_RICHTEXTCTRL1;
		//*)

	private:

		//(*Handlers(HelpDialog)
		void OnRichTextCtrl1Text(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
