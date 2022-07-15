/***************************************************************
    Name:      ArduinoLoaderApp.cpp
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

#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

#include <wx/msgdlg.h>

#include "ArduinoStarterApp.h"
#include "RecentDialog.h"
#include "FileHandler.h"

//(*AppHeaders
#include <wx/image.h>
//*)

IMPLEMENT_APP( ArduinoLoaderApp );

bool ArduinoLoaderApp::OnInit() {
    bool wxsOK = true;
    if( wxTheApp->argc == 1 ) {
        filehandler.ReadPreferences( _( "" ) ); //
        //(*AppInitialize
        wxInitAllImageHandlers();
        if ( wxsOK ) {
            RecentDialog Dlg( wxTheApp, 0 );
            SetTopWindow( &Dlg );
            Dlg.ShowModal();
            wxsOK = false;
        }
        //*)
        wxTheApp->Exit();
    } else if( wxTheApp->argc >= 2 && wxTheApp->argv[1].Left( 6 ).Lower() == "-root=" ) {
        size_t len = wxTheApp->argv[1].Len() - 6;
        wxString txt = wxTheApp->argv[1].Right( len );
        filehandler.ReadPreferences( txt );
        wxTheApp->Exit();
    } else if( wxTheApp->argc >= 2 && wxTheApp->argv[1].Left( 6 ).Lower() != "-root=" ) {
        if( filehandler.ReadSketch( wxTheApp->argv[1] ) ) {
            wxString txt = arduino_sketch.Root;
            if( filehandler.ReadPreferences( txt ) ) {
                filehandler.WriteNewPrefs(); // everything read correctly, start updating prefeeces.txt
            } else {  // preferences do not contain "board=", "custom_" or "target_", just open the sketch
                wxMessageBox( _( "Error while processing preferences.txt\nCheck the board settings before uploading." ), _( "Warning" ) );
            }
        } else { // sketch does not contain header information, just open the sketch
            wxMessageBox( _( "There was no controller type (//board= and //target=) found in the sketch.\nCheck the board settings before uploading." ), _( "Warning" ) );
        }
        wxString cmd = filehandler.BannedCharacters( filehandler.Executable );
        cmd += _( "  " ) + wxTheApp->argv[1] + _( "  &" );
        system( cmd.c_str().AsChar() ); // Execute the IDE
        wxTheApp->Exit(); // and exit the loader
    }
    return wxsOK;
}
