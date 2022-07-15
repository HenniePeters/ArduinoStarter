//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#pragma hdrstop
#include "FileHandler.h"
#include "main.h"
#include "help.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//------------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender) {
    frmMain->Position = poDefault;
    PopulateListbox();
    if( ListBox1->Count > 0 ) {
        ListBox1->Selected[0] = true;
        ListBox1Click(Sender);
    }
}
//------------------------------------------------------------------------------
void __fastcall TfrmMain::cmdOpenClick(TObject *Sender) {
    if( ListBox1->Count > 0 ) {
        AnsiString cmd = AnsiString("\"") + filehandler.Executable +  AnsiString("\"");
        AnsiString arg = AnsiString("\"");
        for( int Index = 0; Index < ListBox1->Count; ++Index) {
            if( ListBox1->Selected[Index]) {
                arg += ListBox1->Items->Strings[Index];
                break;
            }
        }
        arg += AnsiString("\"");
        if( filehandler.ReadSketch( arg ) ) {
            if( arduino_sketch.Board.SubString( 1, 6 ) == "board=" ) {
                size_t len = arduino_sketch.Board.Length() - 6;
                Label3->Caption = arduino_sketch.Board.SubString( 7, len );
            }
            AnsiString txt = arduino_sketch.Root;
            if( filehandler.ReadPreferences( txt ) ) {
                filehandler.WriteNewPrefs(); // everything read correctly, start updating prefeeces.txt
            } else {  // preferences do not contain "board=", "custom_" or "target_", just open the sketch
                Application->MessageBoxA( "Error while processing preferences.txt\nCheck the board settings before uploading.", "Warning" );
            }
        } else { // sketch does not contain header information, just open the sketch
            AnsiString msg = AnsiString("There was no controller type (//board= and //target=) found in the sketch.\nCheck the board settings before uploading.");
            Application->MessageBoxA( msg.c_str(), "Warning" );
            filehandler.ReadPreferences("");
        }
        ShellExecute( Application->Handle, NULL, cmd.c_str(), arg.c_str(), "C:\\", 1 );
        Application->Terminate();
    }
}
//------------------------------------------------------------------------------
void __fastcall TfrmMain::cmdCancelClick(TObject *Sender) {
    Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ListBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
    if( Button == TMouseButton(mbRight) ) {
        int iNewSelection;
        if( IDYES  == Application->MessageBoxA( "\nDo you want to remove the selected sketch from the list"
                                              , "Remove from list of recent files"
                                              , MB_YESNO ) ) {
            if( ListBox1->Count >= 1 ) {
                AnsiString file;
                for( int Index = 0; Index < ListBox1->Count; ++Index) {
                    if( ListBox1->Selected[Index]) {
                        iNewSelection = Index;
                        if( iNewSelection > 0 ) {
                            iNewSelection--;
                        }
                        file = ListBox1->Items->Strings[Index];
                        break;
                    }
                }
                filehandler.WritePrefsExcept( file );
                PopulateListbox();
                if( ListBox1->Count > 0 ) {
                    ListBox1->Selected[iNewSelection] = true;
                    ListBox1Click(Sender);
                }
            }
        }
    }
}
//------------------------------------------------------------------------------
void __fastcall TfrmMain::ListBox1Click(TObject *Sender) {
    AnsiString wxsIno;
    long counter = 0;
    Label3->Caption = "No board information found in sketch";
    cmdOpen->Enabled = true;
    if( ListBox1->Count > 0 ) {
        for( int Index = 0; Index < ListBox1->Count; ++Index) {
            if( ListBox1->Selected[Index] ) {
                wxsIno = ListBox1->Items->Strings[Index];
                counter++;
            }
        }
    }
    if( counter == 1 ) {
        cmdOpen->Enabled = true;
        arduino_sketch.ClearCashedSketch();
        if( FileExists (wxsIno.c_str()) ) {
            filehandler.ReadSketch( wxsIno );
            if( arduino_sketch.Board.SubString( 1, 6 ) == "board=" ) {
                size_t len = arduino_sketch.Board.Length() - 6;
                Label3->Caption = arduino_sketch.Board.SubString( 7, len );
            }
        } else {
             Label3->Caption = "Sketch is no longer available";
             cmdOpen->Enabled = false;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ListBox1DblClick(TObject *Sender) {
    cmdOpenClick( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::PopulateListbox( void ) {
    long counter = 0;
    AnsiString wxsRecent, wxsLeft, wxsRight;
    wxsRecent = arduino_prefs.Recent;
    while( wxsRecent != "" ) {
        if( SplitToken( wxsRecent, ',', wxsLeft, wxsRight ) ) {
            if( wxsLeft.SubString( 1, 16 ).LowerCase() == "recent.sketches=" ) {
                ListBox1->Clear();
                size_t len = wxsLeft.Length() - 16;
                ListBox1->Items->Add( wxsLeft.SubString( 17, len ) );
            } else {
                ListBox1->Items->Add( wxsLeft );
            }
            wxsRecent = wxsRight;
        } else {
            if( wxsRight.SubString( 1, 16 ).LowerCase() == "recent.sketches=" ) {
                size_t len = wxsRight.Length() - 16;
                ListBox1->Items->Add( wxsRight.SubString( 17, len ) );
            } else {
                ListBox1->Items->Add( wxsRight );
            }
            break;
        }
        counter++;
    }
    char buf[16];
    sprintf( buf, "%ld", counter );
    AnsiString wxsLabel = buf;
    wxsLabel += " sketches found.";
    lblRecent->Caption = wxsLabel;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmdHelpClick(TObject *Sender) {
    frmHelp->Position = poDefault;
    frmHelp->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormResize(TObject *Sender) {
    if( frmMain->Width != 1043 ) {
        frmMain->Width = 1043;
    }
}
//---------------------------------------------------------------------------

