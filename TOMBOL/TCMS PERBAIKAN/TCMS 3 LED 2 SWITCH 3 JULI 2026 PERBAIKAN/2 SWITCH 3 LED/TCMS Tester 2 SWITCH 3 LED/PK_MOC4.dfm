object frmPK_MOC4: TfrmPK_MOC4
  Left = 0
  Top = 0
  Caption = 'Tester for MOC4 PK'
  ClientHeight = 493
  ClientWidth = 707
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 707
    Height = 313
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
      Left = 443
      Top = 32
      Width = 103
      Height = 41
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
      Left = 310
      Top = 32
      Width = 108
      Height = 41
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
    object btn01: TGroupBox
      Left = 256
      Top = 93
      Width = 89
      Height = 84
      Caption = 'BTN 01'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      object ShapeButton01: TShape
        Left = 31
        Top = 14
        Width = 49
        Height = 56
        Shape = stCircle
      end
      object shapeLed01: TShape
        Left = 3
        Top = 16
        Width = 24
        Height = 25
        Shape = stCircle
      end
    end
    object btn02: TGroupBox
      Left = 384
      Top = 93
      Width = 90
      Height = 84
      Caption = 'BTN 02'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      object ShapeButton02: TShape
        Left = 38
        Top = 14
        Width = 49
        Height = 56
        Shape = stCircle
      end
      object shapeLed02: TShape
        Left = 3
        Top = 16
        Width = 24
        Height = 25
        Shape = stCircle
      end
    end
    object btn03: TGroupBox
      Left = 512
      Top = 96
      Width = 90
      Height = 81
      Caption = 'BTN 03'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      object ShapeButton03: TShape
        Left = 33
        Top = 11
        Width = 49
        Height = 56
        Shape = stCircle
      end
      object shapeLed03: TShape
        Left = 3
        Top = 15
        Width = 24
        Height = 25
        Shape = stCircle
      end
    end
  end
  object Log: TMemo
    Left = 0
    Top = 313
    Width = 707
    Height = 180
    Align = alClient
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object ComPort1: TComPort
    BaudRate = br115200
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
  object TmrGetMessage: TTimer
    Enabled = False
    OnTimer = TmrGetMessageTimer
    Left = 112
    Top = 16
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 40
    Top = 320
  end
  object Timer2: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 80
    Top = 320
  end
  object Timer3: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 120
    Top = 320
  end
end
