/***************************************************************
    Name:      FileHandler.cpp
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

#include <Windows.h>
#include <fstream>
#include <iostream>
//#include <filesystem>
//#include <algorithm>
#pragma hdrstop

#include "FileHandler.h"

#pragma package(smart_init)

// #define DEFAULT_EXECUTABLE "arduino" // Linux
#define DEFAULT_EXECUTABLE "C:\\Program Files\\Arduino\\Arduino.exe" // Windows 64
#define DEFAULT_EXECUTABLE_x86 "C:\\Program Files (x86)\\Arduino\\Arduino.exe" // Windows 32

class ArduinoPrefs arduino_prefs;
class ArduinoSketch arduino_sketch;
class FileHandler filehandler;
//---------------------------------------------------------------------------
void ArduinoSketch::ClearCashedSketch( void ) {
    Exec = "";
    Root = "";
    Board = "";
    Custom.clear();
    Target.clear();
    Header.clear();
    Lines.clear();
}
//---------------------------------------------------------------------------
FileHandler::FileHandler() {
    bExecFixed = false;
    Message = "";
    if( FileExists(DEFAULT_EXECUTABLE) ) {
        Executable = DEFAULT_EXECUTABLE;
    } else if(FileExists(DEFAULT_EXECUTABLE_x86)) {
        Executable = DEFAULT_EXECUTABLE_x86;
    } else {
        Message += AnsiString("The default Arduino executable was not found, expecting the 'exec=' line in preferences.");
    }
}
//---------------------------------------------------------------------------
bool FileHandler::ReadSketch( AnsiString wxsIno ) {
    // TODO: is the "custom" section in preferences required ? for now, ignore the compiler warnings
    bool bBoard = false, bCustom = false, bRoot = false, bTarget = false;
    if( wxsIno.SubString(1,1) == "\"" ) {
        wxsIno = wxsIno.SubString(2,wxsIno.Length()-2);
    }
    if( FileExists( wxsIno ) ) {
        std::ifstream inofile( wxsIno.c_str() );
        std::string line;
        if ( inofile.is_open() ) { // always check whether the file is open
            AnsiString wxsPrev = "";
            while ( inofile.good() ) {
                size_t len;
                std::getline ( inofile, line );
                AnsiString wxsLine = line.c_str();
                wxsLine.Trim();
                if( wxsLine == "" ) {
                    arduino_sketch.Header.push_back( wxsLine );
                    // empty line OK, skip
                } else if( wxsLine.SubString( 1, 2 ) == "//" ) {
                    if( wxsLine.SubString( 1, 7 ).LowerCase() == "//exec=" ) {
                        len = wxsLine.Length() - 7;
                        arduino_sketch.Exec = wxsLine.SubString( 8, len );
                        if( ! bExecFixed ) { // executable from preferences takes precedence over sketch version
                            Executable = arduino_sketch.Exec;
                        }
                        bRoot = true;
                    } else if( wxsLine.SubString( 1, 7 ).LowerCase() == "//root=" ) {
                        len = wxsLine.Length() - 7;
                        arduino_sketch.Root = wxsLine.SubString( 8, len );
                        bRoot = true;
                    } else if( wxsLine.SubString( 1, 8 ) == "//board=" ) {
                        len = wxsLine.Length() - 2;
                        arduino_sketch.Header.push_back( wxsLine.SubString( 3, len ) );
                        arduino_sketch.Board = wxsLine.SubString( 3, len );
                        bBoard = true;
                    } else if( wxsLine.SubString( 1, 9 ) == "//custom_" ) {
                        len = wxsLine.Length() - 2;
                        arduino_sketch.Header.push_back( wxsLine.SubString( 3, len ) );
                        arduino_sketch.Custom.push_back( wxsLine.SubString( 3, len ) );
                        bCustom = true;
                    } else if( wxsLine.SubString( 1, 9 ) == "//target_" ) {
                        len = wxsLine.Length() - 2;
                        arduino_sketch.Header.push_back( wxsLine.SubString( 3, len ) );
                        arduino_sketch.Target.push_back( wxsLine.SubString( 3, len ) );
                        bTarget = true;
                    } else {
                        wxsLine = line.c_str(); // only header lines are trimmed
                        arduino_sketch.Lines.push_back( wxsLine );
                        break;
                    }
                } else {
                    wxsLine = line.c_str(); // only header lines are trimmed
                    arduino_sketch.Lines.push_back( wxsLine );
                    break;
                }
            }
            do {
                std::getline ( inofile, line );
                AnsiString wxsLine = line.c_str();
                arduino_sketch.Lines.push_back( wxsLine );
            } while( inofile.good() );
            inofile.close();
        }
    }
    if( ! bBoard || ! bTarget ) {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
bool FileHandler::ReadPreferences( AnsiString param ) {
    char buf[1024];
    arduino_prefs.Path = "";
    AnsiString wxsPrefs = param;
    AnsiString PossibleLocation[] = { "%USERPROFILE%\\Local Settings\\Application Data\\Arduino15\\", "%LOCALAPPDATA%\\Arduino15\\", "" };
    if( wxsPrefs == "" ) {
        int i=0;
        do {
            wxsPrefs = PossibleLocation[i];
            ExpandEnvironmentStringsA( wxsPrefs.c_str(), buf, 1024 );
            wxsPrefs = buf;
            if( wxsPrefs.SubString( wxsPrefs.Length(), 1 ) != "\\" ) {
                wxsPrefs += "\\";
            }
            AnsiString Temp = wxsPrefs;
            Temp += "preferences.txt";
            if( Temp != "" && FileExists( Temp ) ) {
                break;
            }
            i++;
        } while( PossibleLocation[i] != "" );
    }
    ExpandEnvironmentStringsA( wxsPrefs.c_str(), buf, 1024 );
    wxsPrefs = buf;
    AnsiString wxsBak = wxsPrefs + "preferences.bak.txt";
    wxsPrefs += ( "preferences.txt" );
    if( ! FileExists( wxsBak ) ) {
        CopyFile( wxsPrefs.c_str(), wxsBak.c_str(), false );
    }
    bool bBoard = false, bCustom = false, bBeforeCustom = false, bAfterCustom = false, bAfterRecent = false, bRecent = false, bTarget = false, bAfterTarget = false, bAfterExec = false;
    if( ! FileExists( wxsPrefs ) ) {
        Application->MessageBoxA( "The file 'preferences.txt' was NOT found", "ERROR", 0 ); 
        return false;
    } else {
        std::ifstream prefsfile( wxsPrefs.c_str() );
        std::string line;
        if ( prefsfile.is_open() ) { // always check whether the file is open
            AnsiString wxsPrev = "";
            while ( prefsfile.good() ) {
                size_t len;
                std::getline ( prefsfile, line );
                AnsiString wxsLine = line.c_str();
                if( wxsLine == "" ) {
                    // skip empty lines
                } else if( wxsLine.SubString( 1, 6 ) == ".exec=" ) {
                    arduino_prefs.Exec = wxsLine;
                    len = wxsLine.Length() - 6;
                    Executable = wxsLine.SubString( 7, len );
                    bDotExec = true;
                    bExecFixed = true;
                } else if( wxsLine.SubString( 1, 6 ) == "board=" ) {
                    arduino_prefs.Board = wxsLine;
                    bBoard = true;
                } else if( wxsLine.SubString( 1, 7 ) < "custom_" ) {
                    arduino_prefs.BeforeCustom.push_back( wxsLine );
                    bBeforeCustom = true;
                } else if( wxsLine.SubString( 1, 7 ) == "custom_" ) {
                    arduino_prefs.Custom.push_back( wxsLine );
                    bCustom = true;
                } else if( wxsLine.SubString( 1, 7 ) > "custom_" ) {
                    if( wxsLine.SubString( 1, 5 ) < "exec=" ) {
                        arduino_prefs.AfterCustom.push_back( wxsLine );
                        bAfterCustom = true;
                    } else if( wxsLine.SubString( 1, 5 ) == "exec=" ) {
                        arduino_prefs.Exec = wxsLine;
                        len = wxsLine.Length() - 5;
                        Executable = wxsLine.SubString( 5, len );
                        bDotExec = false;
                        bExecFixed = true;
                    } else if( wxsLine.SubString( 1, 5 ) > "exec=" ) {
                        if( wxsLine.SubString( 1, 16 ) < "recent.sketches=" ) {
                            arduino_prefs.AfterExec.push_back( wxsLine );
                            bAfterExec = true;
                        } else if( wxsLine.SubString( 1, 16 ) == "recent.sketches=" ) {
                            arduino_prefs.Recent = wxsLine;
                            bRecent = true;
                        } else if( wxsLine.SubString( 1, 16 ) > "recent.sketches=" ) {
                            if( wxsLine.SubString( 1, 16 ) < "target_" ) {
                                arduino_prefs.AfterRecent.push_back( wxsLine );
                                bAfterRecent = true;
                            } else if( wxsLine.SubString( 1, 7 ) == "target_" ) {
                                arduino_prefs.Target.push_back( wxsLine );
                                bTarget = true;
                            } else if( wxsLine.SubString( 1, 7 ) > "target_" ) {
                                arduino_prefs.AfterTarget.push_back( wxsLine );
                                bAfterTarget = true;
                            }
                        }
                    }
                }
            }
            prefsfile.close();
        }
    }
    if( ! bBoard || ! bBeforeCustom || ! bTarget || ! bAfterTarget ) {
        return false;
    }
    if( bCustom &&  ! bAfterCustom ) {
        return false;
    }
    if( bRecent && ! bAfterRecent ) {
        return false;
    }
    // Arrived at this point, it seems that everything went fine. Store the filename for writing
    arduino_prefs.Path = wxsPrefs;
    return true;
}
//---------------------------------------------------------------------------
void FileHandler::WriteNewPrefs( void ) {
    AnsiString wxsPrefs = arduino_prefs.Path;
    if( wxsPrefs != "" && FileExists( wxsPrefs ) ) {
        std::ofstream prefsfile( wxsPrefs.c_str() );
        if( bDotExec && arduino_prefs.Exec != "" ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        prefsfile << arduino_sketch.Board << std::endl;
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.BeforeCustom.begin(); it != arduino_prefs.BeforeCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_sketch.Custom.begin(); it != arduino_sketch.Custom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterCustom.begin(); it != arduino_prefs.AfterCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        if( ! bDotExec && arduino_prefs.Exec != "" ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterExec.begin(); it != arduino_prefs.AfterExec.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        prefsfile << arduino_prefs.Recent << std::endl;
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterRecent.begin(); it != arduino_prefs.AfterRecent.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_sketch.Target.begin(); it != arduino_sketch.Target.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterTarget.begin(); it != arduino_prefs.AfterTarget.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        prefsfile.close();
    }
}
//---------------------------------------------------------------------------
void FileHandler::WritePrefsExcept( AnsiString wxsExcept ) {
    AnsiString wxsPrefs = arduino_prefs.Path;
    if( wxsPrefs != "" && FileExists( wxsPrefs ) ) {
        std::ofstream prefsfile( wxsPrefs.c_str() );
        if( bDotExec && arduino_prefs.Exec != "" ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        prefsfile << arduino_prefs.Board << std::endl;
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.BeforeCustom.begin(); it != arduino_prefs.BeforeCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.Custom.begin(); it != arduino_prefs.Custom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterCustom.begin(); it != arduino_prefs.AfterCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        if( ! bDotExec && arduino_prefs.Exec != "" ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterExec.begin(); it != arduino_prefs.AfterExec.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        AnsiString wxsRecent = arduino_prefs.Recent;
        AnsiString wxsLeft, wxsRight, wxsItem,  wxsCollect = "";
        while( wxsRecent != "" ) {
            if( SplitToken( wxsRecent, ',', wxsLeft, wxsRight ) ) {
                if( wxsLeft.SubString( 1, 16 ).LowerCase() == "recent.sketches=" ) {
                    size_t len = wxsLeft.Length() - 16;
                    wxsItem = wxsLeft.SubString( 17, len );
                } else {
                    wxsItem = wxsLeft;
                }
                wxsRecent = wxsRight;
            } else {
                wxsItem = wxsRight;
                wxsRecent = "";
            }
            if( wxsItem != wxsExcept ) {
                if( wxsCollect == "" ) {
                    wxsCollect = "recent.sketches=" +  wxsItem;
                } else {
                    wxsCollect += "," +  wxsItem;
                }
            }
        }
        arduino_prefs.Recent = wxsCollect;
        prefsfile << arduino_prefs.Recent << std::endl;
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterRecent.begin(); it != arduino_prefs.AfterRecent.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.Target.begin(); it != arduino_prefs.Target.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<AnsiString>::iterator it = arduino_prefs.AfterTarget.begin(); it != arduino_prefs.AfterTarget.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        prefsfile.close();
    }
}
//---------------------------------------------------------------------------
AnsiString FileHandler::BannedCharacters( AnsiString param ) {
    if( param.SubString( 1, 3 ) == "rm " ) {
        return "";
    }
    if( param.SubString( 1, 3 ) == "rm\t" ) {
        return "";
    }
    if( param.SubString( 1, 4 ) == "del " ) {
        return "";
    }
    if( param.SubString( 1, 4 ) == "del\t" ) {
        return "";
    }
    if( param.SubString( 1, 7 ) == "delete " ) {
        return "";
    }
    if( param.SubString( 1, 7 ) == "delete\t" ) {
        return "";
    }
    string p = param.c_str();
    if( p.find( "|" ) != string::npos ) {
        return "";
    }
    if( p.find( "`" ) != string::npos ) {
        return "";
    }
    if( p.find( "<" ) != string::npos ) {
        return "";
    }
    if( p.find( ">" ) != string::npos ) {
        return "";
    }
    if( p.find( "&" ) != string::npos ) {
        return "";
    }
    if( p.find( "*" ) != string::npos ) {
        return "";
    }
    return param;
}
//---------------------------------------------------------------------------
// returns false if separator was not found. In this case rLeft contains input string
bool SplitToken( AnsiString input, AnsiString sep, AnsiString & rLeft, AnsiString & rRight ) {
    string i = input.c_str();
    int pos = i.find_first_of(sep.c_str());
    rLeft = input.SubString( 1, pos );
    if( rLeft == input ) {
        return false;
    }
    rRight = input.SubString( pos+2, input.Length() );
    if( pos == string::npos ) {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------

