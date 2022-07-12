/***************************************************************
    Name:      FileHandler.h
    Author:    Hennie Peters (hennie(dot)peters(at)gmail(dot)com)
    Created:   2022-07-08
    Copyright: Hennie Peters (https://github.com/HenniePeters)
    License:   Do with this code whatever you like best.
               Sell it, give it away for free, change it or don't
               But... when you get filthy rich by distributing
               any part of this program then hopefully you will
               remember my Patreon page:
               https://www.patreon.com/hennep
 **************************************************************/#ifndef FILEHANDLER_H

#define FILEHANDLER_H

#include <vector>
#include <wx/app.h>
#include <wx/msgdlg.h>

extern class FileHandler filehandler;
extern class ArduinoPrefs arduino_prefs;
extern class ArduinoSketch arduino_sketch;
extern bool SplitToken( const wxString & input, const wxChar & sep, wxString & rLeft, wxString & rRight );

class ArduinoSketch {
public:
    wxString Exec;
    wxString Root;
    wxString Board;
    std::vector <wxString> Custom;
    std::vector <wxString> Target;
    std::vector <wxString> Header;
    std::vector <wxString> Lines;
    void ClearCashedSketch(void);
};

class ArduinoPrefs {
public:
    wxString Path;
    wxString Board;
    std::vector <wxString> BeforeCustom;
    std::vector <wxString> Custom;
    std::vector <wxString> AfterCustom;
    wxString Exec;
    std::vector <wxString> AfterExec;
    wxString Recent;
    std::vector <wxString> AfterRecent;
    std::vector <wxString> Target;
    std::vector <wxString> AfterTarget;
};

class FileHandler {
public:
    bool bExecFixed;
    bool bDotExec;
    wxString Executable;
    FileHandler();
    bool ReadPreferences( wxString wxsPrefsParam );
    bool ReadSketch( wxString wxsIno );
    void WriteNewPrefs( void );
    void WritePrefsExcept( wxString );
    wxString BannedCharacters( wxString );
private:
};

#endif // FILEHANDLER_H
