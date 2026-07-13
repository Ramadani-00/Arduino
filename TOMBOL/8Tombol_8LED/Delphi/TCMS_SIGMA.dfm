object frmTCMS_SIGMA: TfrmTCMS_SIGMA
  Left = 0
  Top = 0
  Caption = '`'
  ClientHeight = 541
  ClientWidth = 704
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
    Width = 704
    Height = 377
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
      Left = 335
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
      Left = 462
      Top = 143
      Width = 90
      Height = 81
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
      Left = 583
      Top = 143
      Width = 89
      Height = 81
      Caption = 'LED 04'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      object shapeLed04: TShape
        Left = 24
        Top = 13
        Width = 41
        Height = 62
        Shape = stCircle
      end
    end
    object LED05: TGroupBox
      Left = 216
      Top = 241
      Width = 89
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
      Left = 335
      Top = 241
      Width = 90
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
        Left = 19
        Top = 19
        Width = 48
        Height = 49
        Shape = stCircle
      end
    end
    object LED07: TGroupBox
      Left = 462
      Top = 241
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
      Left = 583
      Top = 241
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
        Left = 24
        Top = 21
        Width = 44
        Height = 44
        Shape = stCircle
      end
    end
  end
  object Log: TMemo
    Left = 0
    Top = 377
    Width = 704
    Height = 164
    Align = alClient
    ScrollBars = ssVertical
    TabOrder = 0
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
