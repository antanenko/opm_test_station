object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'GPIB Test application'
  ClientHeight = 435
  ClientWidth = 1002
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label7: TLabel
    Left = 616
    Top = 278
    Width = 119
    Height = 13
    Caption = 'Version of OPM software'
  end
  object Label8: TLabel
    Left = 741
    Top = 278
    Width = 31
    Height = 13
    Caption = 'Label8'
  end
  object answerInsrtumentMemo: TMemo
    Left = 610
    Top = 8
    Width = 384
    Height = 256
    Lines.Strings = (
      'IDN Answer')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object StringGrid1: TStringGrid
    Left = 862
    Top = 270
    Width = 132
    Height = 157
    ColCount = 2
    DefaultColWidth = 60
    DefaultRowHeight = 20
    DrawingStyle = gdsGradient
    RowCount = 4
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    ScrollBars = ssNone
    TabOrder = 1
    OnSetEditText = StringGrid1SetEditText
    RowHeights = (
      20
      20
      20
      20)
  end
  object Button11: TButton
    Left = 762
    Top = 398
    Width = 75
    Height = 25
    Caption = 'Store delta'
    TabOrder = 2
    OnClick = Button11Click
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 16
    Width = 596
    Height = 411
    ActivePage = TabSheet2
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'Manual mode'
      object Label1: TLabel
        Left = 11
        Top = 19
        Width = 59
        Height = 13
        Caption = 'Adress GPIB'
      end
      object Label2: TLabel
        Left = 19
        Top = 55
        Width = 94
        Height = 13
        Caption = 'Adress PowerMeter'
      end
      object Label5: TLabel
        Left = 15
        Top = 91
        Width = 98
        Height = 13
        Caption = 'Adress Laser Source'
      end
      object Label3: TLabel
        Left = 20
        Top = 199
        Width = 18
        Height = 13
        Caption = 'Slot'
      end
      object Label4: TLabel
        Left = 20
        Top = 234
        Width = 31
        Height = 13
        Caption = 'Switch'
      end
      object Label9: TLabel
        Left = 214
        Top = 132
        Width = 43
        Height = 13
        Caption = 'ip adress'
      end
      object Button6: TButton
        Left = 20
        Top = 139
        Width = 88
        Height = 25
        Caption = 'init OPM'
        TabOrder = 0
        OnClick = Button6Click
      end
      object Button7: TButton
        Left = 353
        Top = 139
        Width = 105
        Height = 25
        Caption = 'Read OPM'
        TabOrder = 1
        OnClick = Button7Click
      end
      object Button8: TButton
        Left = 467
        Top = 139
        Width = 105
        Height = 25
        Caption = 'set Wavelenght'
        TabOrder = 2
        OnClick = Button8Click
      end
      object adressGPIB: TEdit
        Left = 81
        Top = 16
        Width = 32
        Height = 21
        TabOrder = 3
        Text = '0'
      end
      object initGPIBButton: TButton
        Left = 165
        Top = 7
        Width = 89
        Height = 25
        Caption = 'Init GPIB'
        TabOrder = 4
        OnClick = initGPIBButtonClick
      end
      object adressInstrument: TEdit
        Left = 127
        Top = 56
        Width = 32
        Height = 21
        TabOrder = 5
        Text = '10'
      end
      object initInstrumentButton: TButton
        Left = 165
        Top = 50
        Width = 89
        Height = 25
        Caption = 'Init Instrument'
        TabOrder = 6
        OnClick = initInstrumentButtonClick
      end
      object laserAdress: TEdit
        Left = 131
        Top = 90
        Width = 32
        Height = 21
        TabOrder = 7
        Text = '5'
      end
      object buttonInitLaser: TButton
        Left = 169
        Top = 88
        Width = 89
        Height = 25
        Caption = 'Init Instrument'
        TabOrder = 8
        OnClick = buttonInitLaserClick
      end
      object Button3: TButton
        Left = 264
        Top = 50
        Width = 71
        Height = 25
        Caption = 'IDN'
        TabOrder = 9
        OnClick = Button3Click
      end
      object buttonIDNLaser: TButton
        Left = 264
        Top = 86
        Width = 71
        Height = 25
        Caption = 'IDN'
        TabOrder = 10
        OnClick = buttonIDNLaserClick
      end
      object slotNumber: TEdit
        Left = 54
        Top = 196
        Width = 30
        Height = 21
        TabOrder = 11
        Text = '1'
      end
      object Button1: TButton
        Left = 97
        Top = 195
        Width = 45
        Height = 25
        Caption = 'dBm'
        TabOrder = 12
        OnClick = Button1Click
      end
      object Button4: TButton
        Left = 148
        Top = 195
        Width = 45
        Height = 25
        Caption = 'Watt'
        TabOrder = 13
        OnClick = Button4Click
      end
      object Button2: TButton
        Left = 199
        Top = 195
        Width = 96
        Height = 25
        Caption = 'Power'
        TabOrder = 14
        OnClick = Button2Click
      end
      object switchEdit: TEdit
        Left = 57
        Top = 231
        Width = 25
        Height = 21
        TabOrder = 15
        Text = '1'
      end
      object Button5: TButton
        Left = 88
        Top = 226
        Width = 75
        Height = 25
        Caption = 'Switch'
        TabOrder = 16
        OnClick = Button5Click
      end
      object waveLenghtEdit: TEdit
        Left = 312
        Top = 195
        Width = 42
        Height = 21
        TabOrder = 17
        Text = '1550'
      end
      object waveLenghtButton: TButton
        Left = 383
        Top = 195
        Width = 75
        Height = 25
        Caption = 'Wavelenght'
        TabOrder = 18
        OnClick = waveLenghtButtonClick
      end
      object RadioGroup1: TRadioGroup
        Left = 19
        Top = 258
        Width = 140
        Height = 103
        Caption = 'Wave OPM'
        Columns = 2
        TabOrder = 19
      end
      object Button10: TButton
        Left = 169
        Top = 271
        Width = 101
        Height = 25
        Caption = 'Set wave for all'
        TabOrder = 20
        OnClick = Button10Click
      end
      object Button9: TButton
        Left = 169
        Top = 311
        Width = 101
        Height = 25
        Caption = 'Read two'
        TabOrder = 21
        OnClick = Button9Click
      end
      object CheckBox2: TCheckBox
        Left = 169
        Top = 342
        Width = 97
        Height = 17
        Caption = 'Use store delta'
        Checked = True
        State = cbChecked
        TabOrder = 22
      end
      object CheckBox1: TCheckBox
        Left = 341
        Top = 90
        Width = 120
        Height = 17
        Caption = 'Enable/Disable laser'
        TabOrder = 23
        OnClick = CheckBox1Click
      end
      object laserWave: TEdit
        Left = 467
        Top = 88
        Width = 38
        Height = 21
        TabOrder = 24
        Text = '1550'
      end
      object laserWaveButton: TButton
        Left = 510
        Top = 86
        Width = 75
        Height = 25
        Caption = 'Wavelenght'
        TabOrder = 25
        OnClick = laserWaveButtonClick
      end
      object ControlTLS: TCheckBox
        Left = 293
        Top = 275
        Width = 75
        Height = 17
        Caption = 'control  TLS'
        Checked = True
        State = cbChecked
        TabOrder = 26
      end
      object ReadTwoPorts: TCheckBox
        Left = 293
        Top = 315
        Width = 146
        Height = 17
        Caption = 'Read from 2 port Agilent'
        TabOrder = 27
      end
      object typeConnection: TRadioGroup
        Left = 114
        Top = 119
        Width = 79
        Height = 53
        Caption = 'conection'
        ItemIndex = 0
        Items.Strings = (
          'USB'
          'TCP')
        TabOrder = 28
        OnClick = typeConnectionClick
      end
      object ipAdressText: TEdit
        Left = 214
        Top = 151
        Width = 99
        Height = 21
        Enabled = False
        TabOrder = 29
        Text = '192.168.100.171'
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Auto mode'
      ImageIndex = 1
      object Label6: TLabel
        Left = 16
        Top = 32
        Width = 84
        Height = 13
        Caption = 'Number of device'
      end
      object StringGrid2: TStringGrid
        Left = 16
        Top = 61
        Width = 314
        Height = 172
        DefaultColWidth = 60
        DefaultRowHeight = 20
        DrawingStyle = gdsGradient
        RowCount = 8
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        ScrollBars = ssNone
        TabOrder = 0
        OnSetEditText = StringGrid2SetEditText
        RowHeights = (
          20
          20
          20
          20
          20
          20
          20
          20)
      end
      object Button12: TButton
        Left = 376
        Top = 61
        Width = 75
        Height = 25
        Caption = 'Start'
        TabOrder = 1
        OnClick = Button12Click
      end
      object FileNameEdit: TEdit
        Left = 106
        Top = 29
        Width = 121
        Height = 21
        TabOrder = 2
        Text = 'veex number'
      end
      object Button13: TButton
        Left = 376
        Top = 104
        Width = 75
        Height = 25
        Caption = 'Save result'
        TabOrder = 3
        OnClick = Button13Click
      end
      object Button15: TButton
        Left = 496
        Top = 344
        Width = 75
        Height = 25
        Caption = 'Generate'
        TabOrder = 4
        OnClick = Button15Click
      end
      object Button16: TButton
        Left = 16
        Top = 344
        Width = 75
        Height = 25
        Caption = 'Init OPM'
        TabOrder = 5
        OnClick = Button6Click
      end
      object CheckBoxCh850: TCheckBox
        Left = 336
        Top = 83
        Width = 25
        Height = 17
        TabOrder = 6
      end
      object CheckBoxCh1300: TCheckBox
        Left = 336
        Top = 106
        Width = 25
        Height = 17
        TabOrder = 7
      end
      object CheckBoxCh1310: TCheckBox
        Left = 336
        Top = 128
        Width = 25
        Height = 17
        TabOrder = 8
      end
      object CheckBoxCh1490: TCheckBox
        Left = 336
        Top = 150
        Width = 25
        Height = 17
        TabOrder = 9
      end
      object CheckBoxCh1550: TCheckBox
        Left = 336
        Top = 170
        Width = 25
        Height = 17
        TabOrder = 10
      end
      object CheckBoxCh1625: TCheckBox
        Left = 336
        Top = 194
        Width = 25
        Height = 17
        TabOrder = 11
      end
      object CheckBoxCh1650: TCheckBox
        Left = 336
        Top = 216
        Width = 25
        Height = 17
        TabOrder = 12
      end
      object Button19: TButton
        Left = 367
        Top = 212
        Width = 75
        Height = 25
        Caption = 'Change Coeff'
        TabOrder = 13
        OnClick = Button19Click
      end
      object CheckBoxEnableChange: TCheckBox
        Left = 474
        Top = 216
        Width = 97
        Height = 17
        Caption = 'enable Change'
        TabOrder = 14
      end
      object Button20: TButton
        Left = 120
        Top = 344
        Width = 75
        Height = 25
        Caption = 'Release Port'
        TabOrder = 15
        OnClick = Button20Click
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'TabSheet3'
      ImageIndex = 2
      object Button17: TButton
        Left = 72
        Top = 112
        Width = 75
        Height = 25
        Caption = 'ReadPower'
        TabOrder = 0
        OnClick = Button17Click
      end
      object Button18: TButton
        Left = 72
        Top = 48
        Width = 75
        Height = 25
        Caption = 'init'
        TabOrder = 1
        OnClick = Button18Click
      end
    end
  end
  object Button14: TButton
    Left = 762
    Top = 352
    Width = 75
    Height = 25
    Caption = 'Save to File'
    TabOrder = 4
    OnClick = Button14Click
  end
end
