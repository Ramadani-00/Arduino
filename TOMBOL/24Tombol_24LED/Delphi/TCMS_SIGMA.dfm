object frmTCMS_SIGMA: TfrmTCMS_SIGMA
  Left = 0
  Top = 0
  Caption = '`'
  ClientHeight = 657
  ClientWidth = 1126
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1126
    Height = 457
    Align = alTop
    TabOrder = 1
    object GroupBox9: TGroupBox
      Left = 16
      Top = 71
      Width = 153
      Height = 169
      Caption = 'Connect'
      TabOrder = 0
      object lblPort: TLabel
        Left = 16
        Top = 42
        Width = 53
        Height = 13
        Caption = 'COM Port :'
      end
      object btnConnect: TButton
        Left = 16
        Top = 80
        Width = 117
        Height = 41
        Caption = ' Connect'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        OnClick = btnConnectClick
      end
      object edtCOMPort: TEdit
        Left = 75
        Top = 39
        Width = 58
        Height = 21
        TabOrder = 1
        Text = 'COM3'
      end
    end
    object btno01Off: TButton
      Left = 462
      Top = 71
      Width = 103
      Height = 33
      Caption = 'LED OFF'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Lucida Fax'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = btno01OffClick
    end
    object btn01On: TButton
      Left = 317
      Top = 71
      Width = 108
      Height = 33
      Caption = 'LED ON'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Lucida Fax'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = btn01OnClick
    end
    object LED01: TGroupBox
      Left = 216
      Top = 140
      Width = 89
      Height = 84
      Caption = 'LED 01'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      object shapeLed01: TShape
        Left = 19
        Top = 24
        Width = 46
        Height = 49
        Shape = stCircle
      end
    end
    object LED02: TGroupBox
      Left = 319
      Top = 140
      Width = 90
      Height = 84
      Caption = 'LED 02'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      object shapeLed02: TShape
        Left = 19
        Top = 24
        Width = 46
        Height = 49
        Shape = stCircle
      end
    end
    object LED03: TGroupBox
      Left = 426
      Top = 138
      Width = 90
      Height = 86
      Caption = 'LED 03'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      object shapeLed03: TShape
        Left = 19
        Top = 21
        Width = 46
        Height = 50
        Shape = stCircle
      end
    end
    object LED04: TGroupBox
      Left = 535
      Top = 138
      Width = 89
      Height = 86
      Caption = 'LED 04'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      object shapeLed04: TShape
        Left = 27
        Top = 13
        Width = 41
        Height = 62
        Shape = stCircle
      end
    end
    object LED05: TGroupBox
      Left = 643
      Top = 140
      Width = 91
      Height = 84
      Caption = 'LED 05'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      object shapeLed05: TShape
        Left = 19
        Top = 19
        Width = 46
        Height = 49
        Shape = stCircle
      end
    end
    object LED06: TGroupBox
      Left = 756
      Top = 140
      Width = 93
      Height = 84
      Caption = 'LED 06'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      object shapeLed06: TShape
        Left = 23
        Top = 19
        Width = 48
        Height = 49
        Shape = stCircle
      end
    end
    object LED07: TGroupBox
      Left = 872
      Top = 140
      Width = 90
      Height = 84
      Caption = 'LED 07'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      object shapeLed07: TShape
        Left = 16
        Top = 21
        Width = 57
        Height = 46
        Shape = stCircle
      end
    end
    object LED08: TGroupBox
      Left = 981
      Top = 140
      Width = 89
      Height = 84
      Caption = 'LED 08'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 10
      object shapeLed08: TShape
        Left = 27
        Top = 21
        Width = 44
        Height = 44
        Shape = stCircle
      end
    end
    object LED09: TGroupBox
      Left = 216
      Top = 230
      Width = 90
      Height = 84
      Caption = 'LED 09'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 11
      object shapeLed09: TShape
        Left = 20
        Top = 19
        Width = 46
        Height = 57
        Shape = stCircle
      end
    end
    object LED10: TGroupBox
      Left = 319
      Top = 230
      Width = 90
      Height = 84
      Caption = 'LED 10'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 12
      object shapeLed10: TShape
        Left = 17
        Top = 22
        Width = 57
        Height = 45
        Shape = stCircle
      end
    end
    object LED11: TGroupBox
      Left = 426
      Top = 230
      Width = 90
      Height = 84
      Caption = 'LED 11'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 13
      object shapeLed11: TShape
        Left = 25
        Top = 18
        Width = 45
        Height = 49
        Shape = stCircle
      end
    end
    object LED12: TGroupBox
      Left = 535
      Top = 230
      Width = 89
      Height = 84
      Caption = 'LED 12'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 14
      object shapeLed12: TShape
        Left = 24
        Top = 22
        Width = 49
        Height = 44
        Shape = stCircle
      end
    end
    object LED13: TGroupBox
      Left = 643
      Top = 230
      Width = 91
      Height = 84
      Caption = 'LED 13'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 15
      object shapeLed13: TShape
        Left = 18
        Top = 19
        Width = 57
        Height = 49
        Shape = stCircle
      end
    end
    object LED14: TGroupBox
      Left = 756
      Top = 230
      Width = 93
      Height = 84
      Caption = 'LED 14'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 16
      object shapeLed14: TShape
        Left = 18
        Top = 19
        Width = 57
        Height = 49
        Shape = stCircle
      end
    end
    object LED15: TGroupBox
      Left = 872
      Top = 230
      Width = 94
      Height = 84
      Caption = 'LED 15'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 17
      object shapeLed15: TShape
        Left = 21
        Top = 19
        Width = 57
        Height = 49
        Shape = stCircle
      end
    end
    object LED16: TGroupBox
      Left = 981
      Top = 230
      Width = 90
      Height = 84
      Caption = 'LED 16'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 18
      object shapeLed16: TShape
        Left = 17
        Top = 19
        Width = 57
        Height = 49
        Shape = stCircle
      end
    end
    object LED17: TGroupBox
      Left = 216
      Top = 323
      Width = 90
      Height = 84
      Caption = 'LED 17'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 19
      object shapeLed17: TShape
        Left = 20
        Top = 19
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
    object LED18: TGroupBox
      Left = 319
      Top = 323
      Width = 90
      Height = 84
      Caption = 'LED 18'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 20
      object shapeLed18: TShape
        Left = 21
        Top = 19
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
    object LED19: TGroupBox
      Left = 426
      Top = 320
      Width = 90
      Height = 84
      Caption = 'LED 19'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 21
      object shapeLed19: TShape
        Left = 25
        Top = 22
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
    object LED20: TGroupBox
      Left = 535
      Top = 323
      Width = 89
      Height = 84
      Caption = 'LED 20'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 22
      object shapeLed20: TShape
        Left = 24
        Top = 19
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
    object LED21: TGroupBox
      Left = 643
      Top = 323
      Width = 91
      Height = 84
      Caption = 'LED 21'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 23
      object shapeLed21: TShape
        Left = 26
        Top = 19
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
    object LED22: TGroupBox
      Left = 756
      Top = 323
      Width = 93
      Height = 84
      Caption = 'LED 22'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 24
      object shapeLed22: TShape
        Left = 28
        Top = 19
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
    object LED23: TGroupBox
      Left = 870
      Top = 323
      Width = 96
      Height = 84
      Caption = 'LED 23'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 25
      object shapeLed23: TShape
        Left = 31
        Top = 19
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
    object LED24: TGroupBox
      Left = 982
      Top = 320
      Width = 89
      Height = 84
      Caption = 'LED 24'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 26
      object shapeLed24: TShape
        Left = 24
        Top = 19
        Width = 49
        Height = 49
        Shape = stCircle
      end
    end
  end
  object Log: TMemo
    Left = 0
    Top = 457
    Width = 1126
    Height = 200
    Align = alClient
    ScrollBars = ssVertical
    TabOrder = 0
    ExplicitTop = 529
    ExplicitWidth = 714
    ExplicitHeight = 157
  end
  object TmrGetMessage: TTimer
    Enabled = False
    OnTimer = TmrGetMessageTimer
    Left = 104
    Top = 16
  end
  object ComPort1: TComPort
    BaudRate = br9600
    Port = 'COM3'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    StoredProps = [spBasic]
    TriggersOnRxChar = True
    SyncMethod = smNone
    OnRxChar = ComPort1RxChar
    Left = 40
    Top = 16
  end
end
