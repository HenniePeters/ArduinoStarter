object frmHelp: TfrmHelp
  Left = 325
  Top = 645
  BorderStyle = bsToolWindow
  Caption = ' Help'
  ClientHeight = 601
  ClientWidth = 593
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 593
    Height = 601
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Verdana'
    Font.Style = []
    Lines.Strings = (
      
        'The program tries to find the default Arduino executable for 32 ' +
        'and 64 bits '
      
        'versions. When neither "C:\Program Files\Arduino\Arduino.exe" no' +
        'r "C:\Program '
      
        'Files (x86)\Arduino\Arduino.exe" is found, the program expects t' +
        'he:'
      '.exec=<path to executable name> in preferences.txt'
      'or:'
      'exec=<path to executable name> in preferences.txt'
      'or:'
      '//exec=<path to executable name> in the sketch.'
      ''
      'The '#39'preferences.txt'#39' is expected to reside in: '
      '"%USERPROFILE%\\Documents\\ArduinoData\\"'
      '"%USERPROFILE%\\AppData\\Local\\Arduino15\\".'
      '"%USERPROFILE%\\Local Settings\\Application Data\\Arduino15\\"'
      '"%LOCALAPPDATA%\\Arduino15\\"'
      
        'The program will use the preferences.txt in the first location w' +
        'here it is found in '
      'this order.'
      ''
      
        'When it is located somewhere else, it needs a line in every sket' +
        'ch to point to that '
      'location:'
      '//root=<directory of preference.txt> (ending with a backslash \)'
      'In that case the recent files cannot be located.'
      ''
      
        'To set the correct controller type when opening a sketch, copy a' +
        'll lines from '
      'preferences.txt that start with:'
      'board=...'
      'custom_...'
      'target_...'
      
        'and paste these lines at the top of your sketch with 2 forward s' +
        'lashes in front:'
      '//board=...'
      '//custom_...'
      '//target_...'
      ''
      
        'Keep in mind that the Arduino IDE needs to be closed before you ' +
        'cope the lines '
      'from preferences.txt.'
      
        'Your changes to the board settings in the Arduino IDE will only ' +
        'be saved when '
      'you leave the IDE. '
      '(NOT when you save the sketch!)'
      ''
      
        'Do not add any codelines between these board info lines as the A' +
        'rdunioStarter '
      'will only read the header until the first code line. '
      'Empty lines between the board info lines are accepted.')
    ParentFont = False
    TabOrder = 0
  end
end
