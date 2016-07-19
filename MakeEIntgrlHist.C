Double_t MakeEIntgrlHist(TString rootFile)
{
  //Extracting the histogram
  TFile* f = TFile::Open(rootFile);
  TDirectoryFile* dirFile = (TDirectoryFile*)(f->Get("AliAnalysisTaskCalibEmcal"));
  TList* list = (TList*)(dirFile->Get("histogram"));
  TH2D* cellVAmplitude = (TH2D*)(list->FindObject("_histogram_cell_id_amplitude"));
  
  //Creating the power law function
  TF1* pwrLw = new TF1("pwrLw","[0]*TMath::Power(x,[1])",0,10000);
  pwrLw->SetParameter(0,4.6e+06);
  pwrLw->SetParameter(1,-5);
  
  //Cell Tower range to analyse
  const Int_t CVALow = 1;
  const Int_t CVAHigh = 17670;
  
  //Cell energy Cut Off
  const Int_t lowCutOffX = 3;
  const Int_t highCutOffX = 23;

  //Finding bins corresponding to the energy cut offs
  Double_t max = 0.0;
  TH1D* integral_hist = new TH1D("integral_hist", "integral_hist",911000,-0.5,910999.5);
  
  for(int i = CVALow; i < CVAHigh; i++)
    {
      TH1D* cell = new TH1D();
      cell = cellVAmplitude->ProjectionY("cell",i,i);
      Int_t lowCutOffBin = cell->GetXaxis()->FindBin(lowCutOffX);
      Int_t highCutOffBin = cell->GetXaxis()->FindBin(highCutOffX);

      //cout << "ID: " << i <<  endl;
      //cout << "Content Check: " << cell->Integral(lowCutOffBin,highCutOffBin) << endl;
      
      //calculating a using a = (I_indiv/norm_I_6000)^(1/gamma)
      Double_t indiv_integral = cell->Integral(lowCutOffBin,highCutOffBin);
      integral_hist->Fill(indiv_integral);
      //if(max < indiv_integral)
      //max = indiv_integral;

    }
  
  
  TCanvas* c1 = new TCanvas("c1","c1", 500, 500);
  c1->SetLogy();
  integral_hist->Draw();
  
  Double_t median_integral = Median(integral_hist);
  return median_integral;
}

double Median(const TH1D * h1) 
{

   int n = h1->GetXaxis()->GetNbins(); 
   std::vector<double>  x(n);
   h1->GetXaxis()->GetCenter( &x[0] );
   const double * y = h1->GetArray();
   // exclude underflow/overflows from bin content array y
   return TMath::Median(n, &x[0], &y[1]);
}
