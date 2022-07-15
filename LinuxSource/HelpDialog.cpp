#include "HelpDialog.h"

//(*InternalHeaders(HelpDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(HelpDialog)
const long HelpDialog::ID_RICHTEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HelpDialog,wxDialog)
	//(*EventTable(HelpDialog)
	//*)
END_EVENT_TABLE()

HelpDialog::HelpDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(HelpDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(760,672));
	Move(wxDefaultPosition);
	RichTextCtrl1 = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, _("The program tries to start the default Arduino executable with the \'arduino\' command. When your Arduino IDE is started otherwise try that command in a console and when that works, add a line to either preferences.txt or to your sketch:\n.exec=<path to executable name> in preferences.txt (.exec will always stay on top.)\nor:\nexec=<path to executable name> in preferences.txt\nor:\n//exec=<path to executable name> in the sketch.\n\nThe \'preferences.txt\' is expected to reside in: ~/Arduino15/.\n   \nWhen it is located somewhere else, you will need a line in the sketch to point to that location:\n//root=<directory of preference.txt> (ending with a forward slash )\n      \nTo set the correct controller type for the sketch, copy all lines from preferences.txt that start with:\n      board=...\n      custom_...\n      target_...\nand paste these lines at the top of your sketch with 2 forward slashes in front:\n      //board=...\n      //custom_...\n      //target_...\n      \nKeep in mind that the Arduino IDE needs to be closed before you can copy the lines from preferences.txt.\nYour changes to the board settings in the Arduino IDE will only be saved to preferences.txt when you leave the IDE, NOT when you save the sketch!\n      \nDo not place any lines of code between the board info data as the ArdunioStarter will only read comment lines in the header until the first code line. \nEmpty lines between the board info lines are accepted."), wxPoint(8,8), wxSize(744,656), wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);

	Connect(ID_RICHTEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&HelpDialog::OnRichTextCtrl1Text);
	//*)
}

HelpDialog::~HelpDialog()
{
	//(*Destroy(HelpDialog)
	//*)
}


void HelpDialog::OnRichTextCtrl1Text(wxCommandEvent& event)
{
}
