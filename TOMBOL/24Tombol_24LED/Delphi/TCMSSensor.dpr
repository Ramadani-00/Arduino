program TCMSSensor;

uses
  Vcl.Forms,
  TCMS_SIGMA in 'TCMS_SIGMA.pas' {frmTCMS_SIGMA},
  UBinaryPacketizer in 'UBinaryPacketizer.pas';

{$R *.res}

begin
  ReportMemoryLeaksOnShutdown:= True;
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TfrmTCMS_SIGMA, frmTCMS_SIGMA);
  Application.Run;
end.
