//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FileHandler.h"
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmMain);
USEFORM("help.cpp", frmHelp);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int) {
    try {
        Application->Initialize();
        Application->Title = "ArduinoStarter";
        //Application->MessageBoxA( lpCmdLine, "DEBUG", 0 );
        AnsiString asCmdLine = lpCmdLine;
        if( *lpCmdLine == '\"' ) {
            asCmdLine = asCmdLine.SubString( 2, asCmdLine.Length() -2 );
            lpCmdLine = asCmdLine.c_str();
        }
        if( ! *lpCmdLine ) {
            filehandler.ReadPreferences("");
            Application->CreateForm(__classid(TfrmMain), &frmMain);
            Application->CreateForm(__classid(TfrmHelp), &frmHelp);
            Application->Run();
        } else {
            // tested with ....\ArduinoStarter\TestFiles\Weegschaal.ino
            if( filehandler.ReadSketch( lpCmdLine ) ) {
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
            filehandler.CommandLine = asCmdLine;
            AnsiString cmd = filehandler.BannedCharacters( filehandler.Executable );
            AnsiString arg = AnsiString("\"") + asCmdLine + AnsiString("\"");
            ShellExecute( Application->Handle, NULL, cmd.c_str(), arg.c_str(), "C:\\", 1 );
        }
    } catch (Exception &exception) {
        Application->ShowException(&exception);
    } catch (...) {
        try {
            throw Exception("");
        } catch (Exception &exception) {
            Application->ShowException(&exception);
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
// C:\Documents and Settings\hennep\Mijn documenten\Arduino\Magweg\Magweg.ino
