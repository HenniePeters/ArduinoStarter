/***************************************************************
    Name:      ArduinoLoaderApp.h
    Purpose:   Defines Application Class
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

#ifndef ARDUINOLOADERAPP_H
#define ARDUINOLOADERAPP_H

#include <wx/app.h>

class ArduinoLoaderApp : public wxApp {
public:
    virtual bool OnInit();
};

#endif // ARDUINOLOADERAPP_H
