# ArduinoStarter  
  
2022-07-15  
----------  
The Windows version of program tries to find the default executable for both 32 and 64 bits versions.  
A help form was created with all possible keywords for the sketch and the added keywords for preferences.txt (for both Windows and Linux versions).  
A few minor bugfixes to the Linux version.  
  
2022-07-14  
----------  
UPDATE:  
The first version of the Windows program is ready  
  
2022-07-12  
----------  

## Description:
------------
A program to automatically change the controller settings when you open a sketch. Also the list of recent files is much longer than the Arduino IDE shows.  
  
The reason I made this program was because I have a few controller boards that cannot be programmed anymore. I accidently programmed these with the wrong controller settings.  
~~For the moment a Linux version only. I will try to find some time to create a Windows version later.~~  
  
When this program starts an arduino sketch, it will read the arduino sketch and try to locate the board type in the header lines of your program. When found it will use that information to set the board type in the Arduino IDE.  
  
Installing is quite easy. Just copy the executable anywhere on your PC and associate the program to the .ino extension.  
The list of recent files will show when you start the program without arguments. For that you'll need to make a shortcut to the program of course.  
You can also delete files from the recent list by first selecting the items in the listbox with a right click and then a left click to delete (with a confirmation).  
  
The information that you'll need to provide in the top lines of your sketch:  
---------------------------------  
By default the Arduino IDE is started from the command line with the command 'arduino'. On my Linux laptop this works fine but in case the IDE will not come up, try to add a line in the sketch with this text:  
    //exec=<< arduino executable filename >> ( default = //exec=arduino )  
  
You can also put that line in the preferences.txt file (without the two forward slashes)  
    exec=<< arduino executable filename >>  
    or  
    .exec=<< arduino executable filename >>  
    to keep the line on top in preferences.txt  
  
The "exec" or ".exec" settings in preferences.txt take precedence over the exec filename in the sketch.  
  
When the preferences.txt file is not found, set the path to the arduino root:  
    //root=<< the directory where your preferences file is located >> ( default = ~/.arduino15/ )  
  
  
Your sketch compiles correctly for the given controller type when you supply all the lines from preferences.txt that start with:  
board=  
custom_  
target_  
place two forward slashes // in front of the lines to avoid compiler errors in your sketch.  
  
  
Examples for a few boards  
(This information can be extracted from preferences.txt once you've set the correct information in the IDE's menu and close the IDE):  
  
Arduino nano with old bootloader:  
---------------------------------  
//board=nano  
//custom_cpu=nano_atmega328old  
//target_package=arduino  
//target_platform=avr  

Arduino Pro or Pro Mini:  
------------------------  
//board=pro  
//custom_cpu=pro_16MHzatmega328  
//target_package=arduino  
//target_platform=avr  

ESP32 Dev Board  
---------------  
//board=esp32  
//custom_CPUFreq=esp32_240  
//custom_DebugLevel=esp32_none  
//custom_EventsCore=esp32_1  
//custom_FlashFreq=esp32_80  
//custom_FlashMode=esp32_qio  
//custom_FlashSize=esp32_4M  
//custom_LoopCore=esp32_1  
//custom_PSRAM=esp32_disabled  
//custom_PartitionScheme=esp32_default  
//custom_UploadSpeed=esp32_921600  
//target_package=esp32  
//target_platform=esp32  
