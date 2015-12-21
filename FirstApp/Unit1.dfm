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
  object buttonStoreDelta: TButton
    Left = 762
    Top = 398
    Width = 75
    Height = 25
    Caption = 'Store delta'
    TabOrder = 2
    OnClick = buttonStoreDeltaClick
  end
  object buttonSaveDeltaToFile: TButton
    Left = 762
    Top = 352
    Width = 75
    Height = 25
    Caption = 'Save to File'
    TabOrder = 3
    OnClick = buttonSaveDeltaToFileClick
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 16
    Width = 596
    Height = 411
    ActivePage = TabSheet2
    TabOrder = 4
    object TabSheet1: TTabSheet
      Caption = 'Manual mode'
      ExplicitLeft = -52
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
        Top = 206
        Width = 18
        Height = 13
        Caption = 'Slot'
      end
      object Label4: TLabel
        Left = 20
        Top = 241
        Width = 31
        Height = 13
        Caption = 'Switch'
      end
      object adressGPIB: TEdit
        Left = 81
        Top = 16
        Width = 32
        Height = 21
        TabOrder = 0
        Text = '0'
      end
      object initGPIBButton: TButton
        Left = 165
        Top = 7
        Width = 89
        Height = 25
        Caption = 'Init GPIB'
        TabOrder = 1
        OnClick = initGPIBButtonClick
      end
      object adressInstrument: TEdit
        Left = 127
        Top = 56
        Width = 32
        Height = 21
        TabOrder = 2
        Text = '10'
      end
      object initInstrumentButton: TButton
        Left = 165
        Top = 50
        Width = 89
        Height = 25
        Caption = 'Init Instrument'
        TabOrder = 3
        OnClick = initInstrumentButtonClick
      end
      object laserAdress: TEdit
        Left = 131
        Top = 90
        Width = 32
        Height = 21
        TabOrder = 4
        Text = '5'
      end
      object buttonInitLaser: TButton
        Left = 169
        Top = 88
        Width = 89
        Height = 25
        Caption = 'Init Instrument'
        TabOrder = 5
        OnClick = buttonInitLaserClick
      end
      object buttonIDNPowerMeter: TButton
        Left = 264
        Top = 50
        Width = 71
        Height = 25
        Caption = 'IDN'
        TabOrder = 6
        OnClick = buttonIDNPowerMeterClick
      end
      object buttonIDNLaser: TButton
        Left = 264
        Top = 86
        Width = 71
        Height = 25
        Caption = 'IDN'
        TabOrder = 7
        OnClick = buttonIDNLaserClick
      end
      object slotNumber: TEdit
        Left = 54
        Top = 203
        Width = 30
        Height = 21
        TabOrder = 8
        Text = '1'
      end
      object buttonDBm: TButton
        Left = 97
        Top = 202
        Width = 45
        Height = 25
        Caption = 'dBm'
        TabOrder = 9
        OnClick = buttonDBmClick
      end
      object buttonWatt: TButton
        Left = 148
        Top = 202
        Width = 45
        Height = 25
        Caption = 'Watt'
        TabOrder = 10
        OnClick = buttonWattClick
      end
      object buttonPower: TButton
        Left = 199
        Top = 202
        Width = 96
        Height = 25
        Caption = 'read Power'
        TabOrder = 11
        OnClick = buttonPowerClick
      end
      object switchEdit: TEdit
        Left = 57
        Top = 238
        Width = 25
        Height = 21
        TabOrder = 12
        Text = '1'
      end
      object buttonSwitch: TButton
        Left = 88
        Top = 233
        Width = 75
        Height = 25
        Caption = 'Switch'
        TabOrder = 13
        OnClick = buttonSwitchClick
      end
      object waveLenghtEdit: TEdit
        Left = 312
        Top = 202
        Width = 42
        Height = 21
        TabOrder = 14
        Text = '1550'
      end
      object waveLenghtButton: TButton
        Left = 383
        Top = 202
        Width = 75
        Height = 25
        Caption = 'Wavelenght'
        TabOrder = 15
        OnClick = waveLenghtButtonClick
      end
      object RadioGroup1: TRadioGroup
        Left = 19
        Top = 270
        Width = 140
        Height = 103
        Caption = 'Wave OPM'
        Columns = 2
        TabOrder = 16
      end
      object buttonSetWaveForAll: TButton
        Left = 169
        Top = 283
        Width = 101
        Height = 25
        Caption = 'Set wave for all'
        TabOrder = 17
        OnClick = buttonSetWaveForAllClick
      end
      object buttonReadTwo: TButton
        Left = 169
        Top = 323
        Width = 101
        Height = 25
        Caption = 'Read two'
        TabOrder = 18
        OnClick = buttonReadTwoClick
      end
      object CheckBox2: TCheckBox
        Left = 169
        Top = 354
        Width = 97
        Height = 17
        Caption = 'Use store delta'
        Checked = True
        State = cbChecked
        TabOrder = 19
      end
      object CheckBox1: TCheckBox
        Left = 341
        Top = 90
        Width = 120
        Height = 17
        Caption = 'Enable/Disable laser'
        TabOrder = 20
        OnClick = CheckBox1Click
      end
      object laserWave: TEdit
        Left = 467
        Top = 88
        Width = 38
        Height = 21
        TabOrder = 21
        Text = '1550'
      end
      object laserWaveButton: TButton
        Left = 510
        Top = 86
        Width = 75
        Height = 25
        Caption = 'Wavelenght'
        TabOrder = 22
        OnClick = laserWaveButtonClick
      end
      object ControlTLS: TCheckBox
        Left = 293
        Top = 287
        Width = 75
        Height = 17
        Caption = 'control  TLS'
        Checked = True
        State = cbChecked
        TabOrder = 23
      end
      object ReadTwoPorts: TCheckBox
        Left = 293
        Top = 327
        Width = 146
        Height = 17
        Caption = 'Read from 2 port Agilent'
        TabOrder = 24
      end
      object GroupBox1: TGroupBox
        Left = 11
        Top = 117
        Width = 571
        Height = 72
        Caption = 'OPM function'
        TabOrder = 25
        object Label9: TLabel
          Left = 166
          Top = 19
          Width = 43
          Height = 13
          Caption = 'ip adress'
        end
        object ButtonSetZero: TButton
          Left = 487
          Top = 40
          Width = 75
          Height = 25
          Caption = 'Set Zero'
          TabOrder = 0
          OnClick = ButtonSetZeroClick
        end
        object buttonSetWavelenght: TButton
          Left = 455
          Top = 11
          Width = 105
          Height = 25
          Caption = 'set Wavelenght'
          TabOrder = 1
          OnClick = buttonSetWavelenghtClick
        end
        object ButtonReadOPM: TButton
          Left = 342
          Top = 11
          Width = 78
          Height = 25
          Caption = 'Read OPM'
          TabOrder = 2
          OnClick = ButtonReadOPMClick
        end
        object buttonInitOPM: TButton
          Left = 6
          Top = 19
          Width = 67
          Height = 25
          Caption = 'init OPM'
          TabOrder = 3
          OnClick = buttonInitOPMClick
        end
        object typeConnection: TRadioGroup
          Left = 79
          Top = 11
          Width = 73
          Height = 52
          Caption = 'conection'
          ItemIndex = 0
          Items.Strings = (
            'USB'
            'TCP')
          TabOrder = 4
          OnClick = typeConnectionClick
        end
        object ipAdressText: TEdit
          Left = 166
          Top = 38
          Width = 99
          Height = 21
          Enabled = False
          TabOrder = 5
          Text = '192.168.100.171'
        end
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
      object ButtonStart: TButton
        Left = 376
        Top = 61
        Width = 75
        Height = 25
        Caption = 'Start'
        TabOrder = 1
        OnClick = ButtonStartClick
      end
      object FileNameEdit: TEdit
        Left = 106
        Top = 29
        Width = 121
        Height = 21
        TabOrder = 2
        Text = 'veex number'
      end
      object buttonSaveResult: TButton
        Left = 376
        Top = 104
        Width = 75
        Height = 25
        Caption = 'Save result'
        TabOrder = 3
        OnClick = buttonSaveResultClick
      end
      object buttonGenerateFake: TButton
        Left = 496
        Top = 344
        Width = 75
        Height = 25
        Caption = 'Generate'
        TabOrder = 4
        OnClick = buttonGenerateFakeClick
      end
      object buttonInitOPMAutoMode: TButton
        Left = 16
        Top = 344
        Width = 75
        Height = 25
        Caption = 'Init OPM'
        TabOrder = 5
        OnClick = buttonInitOPMClick
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
      object buttonChangeCoeff: TButton
        Left = 375
        Top = 212
        Width = 75
        Height = 25
        Caption = 'Change Coeff'
        TabOrder = 13
        OnClick = buttonChangeCoeffClick
      end
      object CheckBoxEnableChange: TCheckBox
        Left = 474
        Top = 216
        Width = 97
        Height = 17
        Caption = 'enable Change'
        TabOrder = 14
      end
      object buttonReleasePort: TButton
        Left = 120
        Top = 344
        Width = 75
        Height = 25
        Caption = 'Release Port'
        TabOrder = 15
        OnClick = buttonReleasePortClick
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'WaveLength'
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
end
