#ifndef FILEHANDLER_H
#define FILEHANDLER_H
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
 **************************************************************/


#include <vcl.h>
#include <vector>
//#include <wx/app.h>
//#include <wx/msgdlg.h>

extern class FileHandler filehandler;
extern class ArduinoPrefs arduino_prefs;
extern class ArduinoSketch arduino_sketch;
extern bool SplitToken( AnsiString input, AnsiString sep, AnsiString & rLeft, AnsiString & rRight );

class ArduinoSketch {
public:
    AnsiString Exec;
    AnsiString Root;
    AnsiString Board;
    std::vector <AnsiString> Custom;
    std::vector <AnsiString> Target;
    std::vector <AnsiString> Header;
    std::vector <AnsiString> Lines;
    void ClearCashedSketch(void);
};

class ArduinoPrefs {
public:
    AnsiString Path;
    AnsiString Board;
    std::vector <AnsiString> BeforeCustom;
    std::vector <AnsiString> Custom;
    std::vector <AnsiString> AfterCustom;
    AnsiString Exec;
    std::vector <AnsiString> AfterExec;
    AnsiString Recent;
    std::vector <AnsiString> AfterRecent;
    std::vector <AnsiString> Target;
    std::vector <AnsiString> AfterTarget;
};

class FileHandler {
public:
    bool bExecFixed;
    bool bDotExec;
    AnsiString Executable;
    FileHandler();
    bool ReadPreferences( AnsiString wxsPrefsParam );
    bool ReadSketch( AnsiString wxsIno );
    void WriteNewPrefs( void );
    void WritePrefsExcept( AnsiString );
    AnsiString BannedCharacters( AnsiString );
    AnsiString CommandLine; // Windows ONLY
private:
};

#endif // FILEHANDLER_H





