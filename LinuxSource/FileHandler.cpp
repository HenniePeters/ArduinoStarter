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

#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

#include "FileHandler.h"

class ArduinoPrefs arduino_prefs;
class ArduinoSketch arduino_sketch;
class FileHandler filehandler;

void ArduinoSketch::ClearCashedSketch( void ) {
    Exec = _( "" );
    Root = _( "" );
    Board = _( "" );
    Custom.clear();
    Target.clear();
    Header.clear();
    Lines.clear();
}

FileHandler::FileHandler() {
    bExecFixed = false;
    Executable = "arduino";
}

bool FileHandler::ReadSketch( wxString wxsIno ) {
    // TODO: is the "custom" section in preferences required ? for now, ignore the compiler warnings
    bool bBoard = false, bCustom = false, bRoot = false, bTarget = false;
    if( wxFileExists( wxsIno ) ) {
        std::ifstream inofile( wxsIno.c_str().AsChar() );
        std::string line;
        if ( inofile.is_open() ) { // always check whether the file is open
            wxString wxsPrev = _( "" );
            while ( inofile.good() ) {
                size_t len;
                std::getline ( inofile, line );
                wxString wxsLine = line;
                wxsLine.Trim();
                if( wxsLine == _( "" ) ) {
                    arduino_sketch.Header.push_back( wxsLine );
                    // empty line OK, skip
                } else if( wxsLine.Left( 2 ) == _( "//" ) ) {
                    if( wxsLine.Left( 7 ).Lower() == _( "//exec=" ) ) {
                        len = wxsLine.Len() - 7;
                        arduino_sketch.Exec = wxsLine.substr( 7, len );
                        if( ! bExecFixed ) { // executable from preferences takes precedence over sketch version
                            Executable = arduino_sketch.Exec;
                        }
                        bRoot = true;
                    } else if( wxsLine.Left( 7 ).Lower() == _( "//root=" ) ) {
                        len = wxsLine.Len() - 7;
                        arduino_sketch.Root = wxsLine.substr( 7, len );
                        bRoot = true;
                    } else if( wxsLine.Left( 8 ) == _( "//board=" ) ) {
                        len = wxsLine.Len() - 2;
                        arduino_sketch.Header.push_back( wxsLine.substr( 2, len ) );
                        arduino_sketch.Board = wxsLine.substr( 2, len );
                        bBoard = true;
                    } else if( wxsLine.Left( 9 ) == _( "//custom_" ) ) {
                        len = wxsLine.Len() - 2;
                        arduino_sketch.Header.push_back( wxsLine.substr( 2, len ) );
                        arduino_sketch.Custom.push_back( wxsLine.substr( 2, len ) );
                        bCustom = true;
                    } else if( wxsLine.Left( 9 ) == _( "//target_" ) ) {
                        len = wxsLine.Len() - 2;
                        arduino_sketch.Header.push_back( wxsLine.substr( 2, len ) );
                        arduino_sketch.Target.push_back( wxsLine.substr( 2, len ) );
                        bTarget = true;
                    } else {
                        wxsLine = line; // only header lines are trimmed
                        arduino_sketch.Lines.push_back( wxsLine );
                        break;
                    }
                } else {
                    wxsLine = line; // only header lines are trimmed
                    arduino_sketch.Lines.push_back( wxsLine );
                    break;
                }
            }
            do {
                std::getline ( inofile, line );
                wxString wxsLine = line;
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

bool FileHandler::ReadPreferences( wxString param ) {
    arduino_prefs.Path = _( "" );
    wxString wxsPrefs = param;
    if( wxsPrefs == _( "" ) ) {
        wxsPrefs = "~/.arduino15/";
    }
    wxsPrefs.Replace( _( "~" ), getenv( "HOME" ) );
    if( wxsPrefs.Right( 1 ) != _( "/" ) ) {
        wxsPrefs += _( "/" );
    }
    wxString wxsBak = wxsPrefs + _( "preferences.bak.txt" );
    wxsPrefs += ( "preferences.txt" );
    if( ! wxFileExists( wxsBak ) ) {
        wxCopyFile( wxsPrefs, wxsBak, false );
    }
    bool bBoard = false, bCustom = false, bBeforeCustom = false, bAfterCustom = false, bAfterRecent = false, bRecent = false, bTarget = false, bAfterTarget = false, bAfterExec = false;
    if( wxFileExists( wxsPrefs ) ) {
        std::ifstream prefsfile( wxsPrefs.c_str().AsChar() );
        std::string line;
        if ( prefsfile.is_open() ) { // always check whether the file is open
            wxString wxsPrev = _( "" );
            while ( prefsfile.good() ) {
                size_t len;
                std::getline ( prefsfile, line );
                wxString wxsLine = line;
                if( wxsLine == _( "" ) ) {
                    // skip empty lines
                } else if( wxsLine.Left( 6 ) == _( ".exec=" ) ) {
                    arduino_prefs.Exec = wxsLine;
                    len = wxsLine.Len() - 6;
                    Executable = wxsLine.substr( 6, len );
                    bDotExec = true;
                    bExecFixed = true;
                } else if( wxsLine.Left( 6 ) == _( "board=" ) ) {
                    arduino_prefs.Board = wxsLine;
                    bBoard = true;
                } else if( wxsLine.Left( 7 ) < _( "custom_" ) ) {
                    arduino_prefs.BeforeCustom.push_back( wxsLine );
                    bBeforeCustom = true;
                } else if( wxsLine.Left( 7 ) == _( "custom_" ) ) {
                    arduino_prefs.Custom.push_back( wxsLine );
                    bCustom = true;
                } else if( wxsLine.Left( 7 ) > _( "custom_" ) ) {
                    if( wxsLine.Left( 5 ) < _( "exec=" ) ) {
                        arduino_prefs.AfterCustom.push_back( wxsLine );
                        bAfterCustom = true;
                    } else if( wxsLine.Left( 5 ) == _( "exec=" ) ) {
                        arduino_prefs.Exec = wxsLine;
                        len = wxsLine.Len() - 5;
                        Executable = wxsLine.substr( 5, len );
                        bDotExec = false;
                        bExecFixed = true;
                    } else if( wxsLine.Left( 5 ) > _( "exec=" ) ) {
                        if( wxsLine.Left( 16 ) < _( "recent.sketches=" ) ) {
                            arduino_prefs.AfterExec.push_back( wxsLine );
                            bAfterExec = true;
                        } else if( wxsLine.Left( 16 ) == _( "recent.sketches=" ) ) {
                            arduino_prefs.Recent = wxsLine;
                            bRecent = true;
                        } else if( wxsLine.Left( 16 ) > _( "recent.sketches=" ) ) {
                            if( wxsLine.Left( 16 ) < _( "target_" ) ) {
                                arduino_prefs.AfterRecent.push_back( wxsLine );
                                bAfterRecent = true;
                            } else if( wxsLine.Left( 7 ) == _( "target_" ) ) {
                                arduino_prefs.Target.push_back( wxsLine );
                                bTarget = true;
                            } else if( wxsLine.Left( 7 ) > _( "target_" ) ) {
                                arduino_prefs.AfterTarget.push_back( wxsLine );
                                bAfterTarget = true;
                            }
                        }
                    }
                }
            }
            prefsfile.close();
        }
    } else {
        return false;
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

void FileHandler::WriteNewPrefs( void ) {
    wxString wxsPrefs = arduino_prefs.Path;
    if( wxsPrefs != _( "" ) && wxFileExists( wxsPrefs ) ) {
        std::ofstream prefsfile( wxsPrefs.c_str().AsChar() );
        if( bDotExec && arduino_prefs.Exec != _( "" ) ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        prefsfile << arduino_sketch.Board << std::endl;
        for ( std::vector<wxString>::iterator it = arduino_prefs.BeforeCustom.begin(); it != arduino_prefs.BeforeCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_sketch.Custom.begin(); it != arduino_sketch.Custom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterCustom.begin(); it != arduino_prefs.AfterCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        if( ! bDotExec && arduino_prefs.Exec != _( "" ) ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterExec.begin(); it != arduino_prefs.AfterExec.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        prefsfile << arduino_prefs.Recent << std::endl;
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterRecent.begin(); it != arduino_prefs.AfterRecent.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_sketch.Target.begin(); it != arduino_sketch.Target.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterTarget.begin(); it != arduino_prefs.AfterTarget.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        prefsfile.close();
    }
}

void FileHandler::WritePrefsExcept( wxString wxsExcept ) {
    wxString wxsPrefs = arduino_prefs.Path;
    if( wxsPrefs != _( "" ) && wxFileExists( wxsPrefs ) ) {
        std::ofstream prefsfile( wxsPrefs.c_str().AsChar() );
        if( bDotExec && arduino_prefs.Exec != _( "" ) ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        prefsfile << arduino_prefs.Board << std::endl;
        for ( std::vector<wxString>::iterator it = arduino_prefs.BeforeCustom.begin(); it != arduino_prefs.BeforeCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.Custom.begin(); it != arduino_prefs.Custom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterCustom.begin(); it != arduino_prefs.AfterCustom.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        if( ! bDotExec && arduino_prefs.Exec != _( "" ) ) {
            prefsfile <<  arduino_prefs.Exec << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterExec.begin(); it != arduino_prefs.AfterExec.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        wxString wxsRecent = arduino_prefs.Recent;
        wxString wxsLeft, wxsRight, wxsItem,  wxsCollect = _( "" );
        while( wxsRecent != _("") ) {
            if( SplitToken( wxsRecent, ',', wxsLeft, wxsRight ) ) {
                if( wxsLeft.Left( 16 ).Lower() == _( "recent.sketches=" ) ) {
                    size_t len = wxsLeft.Len() - 16;
                    wxsItem = wxsLeft.substr( 16, len );
                } else {
                    wxsItem = wxsLeft;
                }
                wxsRecent = wxsRight;
            } else {
                wxsItem = wxsLeft;
                wxsRecent = _("");
            }
            if( wxsItem != wxsExcept ) {
                if( wxsCollect == _( "" ) ) {
                    wxsCollect = _( "recent.sketches=" ) +  wxsItem;
                } else {
                    wxsCollect += _( "," ) +  wxsItem;
                }
            }
        }
        arduino_prefs.Recent = wxsCollect;
        prefsfile << arduino_prefs.Recent << std::endl;
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterRecent.begin(); it != arduino_prefs.AfterRecent.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.Target.begin(); it != arduino_prefs.Target.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        for ( std::vector<wxString>::iterator it = arduino_prefs.AfterTarget.begin(); it != arduino_prefs.AfterTarget.end(); ++it ) {
            prefsfile <<  ( *it ) << std::endl;
        }
        prefsfile.close();
    }
}

wxString FileHandler::BannedCharacters( wxString param ) {
    if( param.Left( 3 ) == _("rm ") ) {
        return _("");
    }
    if( param.Left( 3 ) == _("rm\t") ) {
        return _("");
    }
    if( param.Left( 4 ) == _("del ") ) {
        return _("");
    }
    if( param.Left( 4 ) == _("del\t") ) {
        return _("");
    }
    if( param.Left( 7 ) == _("delete ") ) {
        return _("");
    }
    if( param.Left( 7 ) == _("delete\t") ) {
        return _("");
    }
    if( param.Find( _("|") ) > 0 ) {
        return _("");
    }
    if( param.Find( _("`") ) > 0 ) {
        return _("");
    }
    if( param.Find( _("<") ) > 0 ) {
        return _("");
    }
    if( param.Find( _(">") ) > 0 ) {
        return _("");
    }
    if( param.Find( _("&") ) > 0 ) {
        return _("");
    }
    if( param.Find( _("*") ) > 0 ) {
        return _("");
    }
    return param;
}

// returns false if separator was not found. In this case rLeft contains input string
bool SplitToken( const wxString & input, const wxChar & sep, wxString & rLeft, wxString & rRight ) {
    rLeft = input.BeforeFirst( sep );
    if ( rLeft == input )
        return false;
    rRight = input.AfterFirst( sep );
    if ( rRight.IsEmpty() )
        return false;
    return true;
}
