object frmMain: TfrmMain
  Left = 1499
  Top = 602
  Width = 1043
  Height = 735
  BorderIcons = []
  Caption = ' Arduino starter'
  Color = clWindow
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100001000400E80200001600000028000000200000004000
    0000010004000000000000000000000000000000000000000000000000000A02
    FD00231BAE001C17BD002C269B00312F8F003D368000433D75004B465D005652
    3B00646113004E4BF0007573E100C4C2BF00E8E7C200FCFEF90000000000FFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9F9F9FFFFFFFFFFFFFFFFF
    FFFFFFF99998999999FFFFFFFFFFFFFFFFFF999766666666899F9FFFFFFFFFFF
    FFF99766666666666679FFFFFFFFFFFFFF986666666666666666899FFFFFFFFF
    F9866656666666666666589FFFFFFFFF9866666666666666665666899FFFFFF9
    866565666566656566666668FFFFFF887556565556565656555556569FFFFFF8
    65555555555555555555565588FFFF875550DEEEDA5555ADEEED054678FFFF85
    54AEEEDEEEC55CEEECEEEA5558FFFF8442EEC254AEECCEEA452CEE25488FF874
    4BED545440EEEE04AD44DEB447FFF8744DE04DDDA4AEEB3AEED40ED4478FF873
    3DE04BBB03BEEB40DEB30ED337FFFF733BED113330EEEE03AD13DEB3378FF871
    12EEC231AEEDCEEA112CEE2117FFFF8111AEEEDEEED11DEEEDEEEA11187FFF74
    2110DEEEDA1111ADEEED012147FFFF762222222221222212222212226FFFFFF7
    3222222222222222222222237FFFFFFF6122222222222222222222267FFFFFFF
    F42222222222222222222247FFFFFFFFF7521112111212121112157FFFFFFFFF
    FF74313131313131311356FFFFFFFFFFFF6764333333433344466FFFFFFFFFFF
    FFFFF666666665666666FFFFFFFFFFFFFFFFFF66666666666F6FFFFFFFFFFFFF
    FFFFFFFFF6F6F6FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFFFD5FFFFFE003FFFF00017FFE0000FFFC00001FF800001FF0000007E000
    000FC0000007E0000003C0000003C0000003C000000180000003800000018000
    0003C000000180000003C0000001C0000003C0000007E0000007F0000007F800
    000FF800001FFC00003FFC00007FFF8000FFFFC005FFFFFABFFFFFFFFFFF}
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1035
    Height = 708
    Align = alClient
    BevelOuter = bvNone
    Caption = ' '
    TabOrder = 0
    object Label5: TLabel
      Left = 0
      Top = 81
      Width = 1035
      Height = 4
      Align = alTop
      AutoSize = False
      Caption = ' '
    end
    object ListBox1: TListBox
      Left = 0
      Top = 85
      Width = 1035
      Height = 623
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Verdana'
      Font.Style = []
      ItemHeight = 18
      ParentFont = False
      TabOrder = 0
      OnClick = ListBox1Click
      OnDblClick = ListBox1DblClick
      OnMouseUp = ListBox1MouseUp
    end
    object Panel2: TPanel
      Left = 0
      Top = 0
      Width = 1035
      Height = 81
      Align = alTop
      BevelOuter = bvNone
      BorderStyle = bsSingle
      Caption = ' '
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 1
      object Label2: TLabel
        Left = 8
        Top = 47
        Width = 104
        Height = 18
        Caption = 'Recent files:'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object lblRecent: TLabel
        Left = 160
        Top = 47
        Width = 7
        Height = 18
        Caption = '-'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 160
        Top = 15
        Width = 7
        Height = 18
        Caption = '-'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 8
        Top = 15
        Width = 129
        Height = 18
        Caption = 'Controller type:'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object cmdOpen: TButton
        Left = 915
        Top = 4
        Width = 115
        Height = 33
        Caption = '&Open'
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = cmdOpenClick
      end
      object cmdCancel: TButton
        Left = 915
        Top = 43
        Width = 115
        Height = 33
        Caption = '&Cancel'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = cmdCancelClick
      end
    end
  end
end
