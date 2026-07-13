object Form1: TForm1
  Left = 0
  Top = 0
  ClientHeight = 536
  ClientWidth = 1358
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblThrottle: TLabel
    Left = 128
    Top = 336
    Width = 3
    Height = 13
  end
  object lblStatusRadjiman: TLabel
    Left = 8
    Top = 93
    Width = 75
    Height = 13
    Caption = 'KRI_RADJIMAN'
  end
  object lblStatusGolok: TLabel
    Left = 8
    Top = 126
    Width = 57
    Height = 13
    Caption = 'KRI_GOLOK'
    DragKind = dkDock
  end
  object lblStatusBelati: TLabel
    Left = 8
    Top = 158
    Width = 57
    Height = 13
    Caption = 'KRI_BELATI'
    DragKind = dkDock
  end
  object lblStatusBrawijaya: TLabel
    Left = 8
    Top = 190
    Width = 82
    Height = 13
    Caption = 'KRI_BRAWIJAYA'
    DragKind = dkDock
  end
  object lblStatusFatahillah: TLabel
    Left = 8
    Top = 222
    Width = 84
    Height = 13
    Caption = 'KRI_FATAHILLAH'
    DragKind = dkDock
  end
  object lblStatusAlugoro: TLabel
    Left = 8
    Top = 254
    Width = 72
    Height = 13
    Caption = 'KRI_ALUGORO'
    DragKind = dkDock
  end
  object Label1: TLabel
    Left = 392
    Top = 357
    Width = 20
    Height = 13
    Caption = 'Yaw'
  end
  object Label2: TLabel
    Left = 480
    Top = 357
    Width = 23
    Height = 13
    Caption = 'Pitch'
  end
  object lblStatusReMartadinata: TLabel
    Left = 8
    Top = 286
    Width = 115
    Height = 13
    Caption = 'KRI_RE_MARTADINATA'
    DragKind = dkDock
  end
  object Label3: TLabel
    Left = 392
    Top = 24
    Width = 21
    Height = 13
    Caption = 'SAM'
  end
  object Label4: TLabel
    Left = 696
    Top = 24
    Width = 20
    Height = 13
    Caption = 'SSM'
  end
  object Label5: TLabel
    Left = 824
    Top = 335
    Width = 93
    Height = 13
    Caption = 'Milenium Gun 35mm'
  end
  object Label6: TLabel
    Left = 984
    Top = 24
    Width = 48
    Height = 13
    Caption = 'TORPEDO'
  end
  object Label7: TLabel
    Left = 605
    Top = 357
    Width = 20
    Height = 13
    Caption = 'Yaw'
  end
  object Label8: TLabel
    Left = 693
    Top = 357
    Width = 23
    Height = 13
    Caption = 'Pitch'
  end
  object Label9: TLabel
    Left = 440
    Top = 336
    Width = 28
    Height = 13
    Caption = '76mm'
  end
  object Label10: TLabel
    Left = 648
    Top = 336
    Width = 34
    Height = 13
    Caption = '127mm'
  end
  object Label11: TLabel
    Left = 1054
    Top = 335
    Width = 77
    Height = 13
    Caption = 'Helicopter Mode'
  end
  object Label12: TLabel
    Left = 174
    Top = 30
    Width = 49
    Height = 13
    Caption = 'Ship Mode'
  end
  object btnKanan: TButton
    Left = 215
    Top = 378
    Width = 75
    Height = 25
    Caption = 'RIGHT'
    TabOrder = 0
    OnMouseDown = btnKananMouseDown
    OnMouseUp = btnKananMouseUp
  end
  object btnKiri: TButton
    Left = 8
    Top = 378
    Width = 75
    Height = 25
    Caption = 'LEFT'
    TabOrder = 1
    OnMouseDown = btnKiriMouseDown
    OnMouseUp = btnKiriMouseUp
  end
  object edtAddress: TEdit
    Left = 8
    Top = 49
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '127.0.0.1'
  end
  object tbThrottle: TTrackBar
    Left = 145
    Top = 378
    Width = 45
    Height = 150
    Max = 100
    Min = -100
    Orientation = trVertical
    TabOrder = 3
    OnChange = tbThrottleChange
  end
  object cbPilihKapal: TComboBox
    Left = 135
    Top = 49
    Width = 145
    Height = 21
    TabOrder = 4
    OnChange = cbPilihKapalChange
    Items.Strings = (
      'KRI_RADJIMAN'
      'KRI_GOLOK'
      'KRI_BELATI'
      'KRI_BRAWIJAYA'
      'KRI_FATAHILLAH'
      'KRI_ALUGORO'
      'KRI_RE_MARTADINATA')
  end
  object BtnTerapung: TButton
    Left = 215
    Top = 426
    Width = 75
    Height = 25
    Caption = 'Naik'
    TabOrder = 5
    OnMouseDown = BtnTerapungMouseDown
    OnMouseUp = BtnTerapungMouseUp
  end
  object BtnMenyelam: TButton
    Left = 215
    Top = 466
    Width = 75
    Height = 25
    Caption = 'Menyelam'
    TabOrder = 6
    OnMouseDown = BtnMenyelamMouseDown
    OnMouseUp = BtnMenyelamMouseUp
  end
  object edtSudutBase: TEdit
    Left = 356
    Top = 376
    Width = 75
    Height = 21
    TabOrder = 7
  end
  object edtSudutLauncher: TEdit
    Left = 454
    Top = 376
    Width = 78
    Height = 21
    TabOrder = 8
  end
  object btnSetSudut: TButton
    Left = 356
    Top = 422
    Width = 75
    Height = 25
    Caption = 'Set Sudut'
    TabOrder = 9
    OnClick = btnSetSudutClick
  end
  object btnTembakArtileri: TButton
    Left = 457
    Top = 422
    Width = 75
    Height = 25
    Caption = 'TEMBAK !'
    TabOrder = 10
    OnClick = btnTembakArtileriClick
  end
  object Button1: TButton
    Left = 816
    Top = 497
    Width = 89
    Height = 25
    Caption = 'AUTO LOCK'
    TabOrder = 11
    OnClick = btnAutoTrackOnClick
  end
  object Button2: TButton
    Left = 816
    Top = 435
    Width = 89
    Height = 25
    Caption = 'Manual Control'
    TabOrder = 12
    OnClick = btnAutoTrackOffClick
  end
  object cbNomorTabung: TComboBox
    Left = 632
    Top = 49
    Width = 145
    Height = 21
    TabOrder = 13
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8')
  end
  object btnTembakMisil: TButton
    Left = 808
    Top = 47
    Width = 97
    Height = 25
    Caption = 'TEMBAK !'
    TabOrder = 14
    OnClick = btnTembakMisilClick
  end
  object btnReloadMisil: TButton
    Left = 808
    Top = 88
    Width = 97
    Height = 25
    Caption = 'RELOAD'
    TabOrder = 15
    OnClick = btnReloadMisilClick
  end
  object cbNomorSiloVLS: TComboBox
    Left = 328
    Top = 49
    Width = 145
    Height = 21
    TabOrder = 16
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12')
  end
  object btnTembakVLS: TButton
    Left = 512
    Top = 47
    Width = 89
    Height = 25
    Caption = 'TEMBAK !'
    TabOrder = 17
    OnClick = btnTembakVLSClick
  end
  object btnReloadVLS: TButton
    Left = 512
    Top = 88
    Width = 89
    Height = 25
    Caption = 'RELOAD'
    TabOrder = 18
    OnClick = btnReloadVLSClick
  end
  object cbModeTembak35mm: TComboBox
    Left = 790
    Top = 354
    Width = 145
    Height = 21
    TabOrder = 19
    OnChange = cbModeTembak35mmChange
    Items.Strings = (
      'SINGLE'
      'BURST')
  end
  object btnTembakCIWS35mm: TButton
    Left = 816
    Top = 466
    Width = 89
    Height = 25
    Caption = 'TEMBAK !'
    TabOrder = 20
    OnMouseDown = btnTembakCIWS35mmMouseDown
    OnMouseUp = btnTembakCIWS35mmMouseUp
  end
  object cbNomorTabungTorpedo: TComboBox
    Left = 936
    Top = 49
    Width = 145
    Height = 21
    TabOrder = 21
    Items.Strings = (
      '1'
      '2'
      '3'
      '4')
  end
  object btnTembakTorpedo: TButton
    Left = 1104
    Top = 47
    Width = 91
    Height = 25
    Caption = 'TEMBAK !'
    TabOrder = 22
    OnClick = btnTembakTorpedoClick
  end
  object btnReloadTorpedo: TButton
    Left = 1104
    Top = 88
    Width = 91
    Height = 25
    Caption = 'RELOAD'
    TabOrder = 23
    OnClick = btnReloadTorpedoClick
  end
  object edtSudutBase127: TEdit
    Left = 561
    Top = 376
    Width = 83
    Height = 21
    TabOrder = 24
  end
  object edtSudutLauncher127: TEdit
    Left = 670
    Top = 376
    Width = 83
    Height = 21
    TabOrder = 25
  end
  object btnSetSudut127: TButton
    Left = 561
    Top = 422
    Width = 83
    Height = 25
    Caption = 'Set Sudut'
    TabOrder = 26
    OnClick = btnSetSudut127Click
  end
  object btnTembakMeriam127: TButton
    Left = 670
    Top = 422
    Width = 83
    Height = 25
    Caption = 'TEMBAK !'
    TabOrder = 27
    OnClick = btnTembakMeriam127Click
  end
  object cbPilihHeli: TComboBox
    Left = 1016
    Top = 354
    Width = 145
    Height = 21
    TabOrder = 28
    Items.Strings = (
      'AS365N3'
      'NB412S')
  end
  object btnHeliMundur: TButton
    Left = 1056
    Top = 466
    Width = 75
    Height = 25
    Caption = 'Mundur'
    TabOrder = 29
    OnClick = btnHeliMundurClick
  end
  object btnHeliMaju: TButton
    Left = 1056
    Top = 412
    Width = 75
    Height = 25
    Caption = 'Maju'
    TabOrder = 30
    OnClick = btnHeliMajuClick
  end
  object btnHeliKanan: TButton
    Left = 1137
    Top = 435
    Width = 75
    Height = 25
    Caption = 'Kanan'
    TabOrder = 31
    OnClick = btnHeliKananClick
  end
  object btnHeliTakeOff: TButton
    Left = 975
    Top = 503
    Width = 75
    Height = 25
    Caption = 'TakeOff'
    TabOrder = 32
    OnClick = btnHeliTakeOffClick
  end
  object btnHeliKiri: TButton
    Left = 975
    Top = 435
    Width = 75
    Height = 25
    Caption = 'Kiri'
    TabOrder = 33
    OnClick = btnHeliKiriClick
  end
  object btnHeliAutoLanding: TButton
    Left = 1137
    Top = 503
    Width = 75
    Height = 25
    Caption = 'Auto Land'
    TabOrder = 34
    OnClick = btnHeliAutoLandingClick
  end
  object btnHeliTurun: TButton
    Left = 1232
    Top = 395
    Width = 75
    Height = 25
    Caption = 'Turun'
    TabOrder = 35
    OnClick = btnHeliTurunClick
  end
  object btnHeliNaik: TButton
    Left = 1232
    Top = 352
    Width = 75
    Height = 25
    Caption = 'Naik'
    TabOrder = 36
    OnClick = btnHeliNaikClick
  end
  object IdTCPClient1: TIdTCPClient
    ConnectTimeout = 1000
    Host = '127.0.0.1'
    IPVersion = Id_IPv4
    Port = 12345
    ReadTimeout = 1000
    Top = 504
  end
end
