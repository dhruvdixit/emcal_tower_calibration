int GetCoefficient(TString txtFile, TString rootFile)
{
  //Extracting the histogram
  TFile* f = TFile::Open(rootFile);
  TDirectoryFile* dirFile = (TDirectoryFile*)(f->Get("AliAnalysisTaskCalibEmcal"));
  TList* list = (TList*)(dirFile->Get("histogram"));
  TH2D* cellVAmplitude = (TH2D*)(list->FindObject("_histogram_cell_id_amplitude"));
  
  //cout << __FILE__ << __LINE__ << endl;

  //Cell Tower range to analyse
  const Int_t CVALow = 0;
  const Int_t CVAHigh = 17670;
  
  //cout << __FILE__ << __LINE__ << endl;

  //Obtaining a histogram of the Good cells.
  TList* goodHistList = new TList;
  ifstream goodFile(txtFile);
  int numCells = 0;
  if(goodFile.is_open())
    {

      //cout << __FILE__ << __LINE__ << endl;

      string line = "";
      std::getline(goodFile,line);
      int index = 0;
      double chi2 = 0.0;
      
      //cout << __FILE__ << __LINE__ << endl;

      //for(index = 0; index < 3; index++)
      while(goodFile >> index >> chi2)
	{
	  //cout << Form("cell%d",index) << endl;
	  TH1D* cell = cellVAmplitude->ProjectionY(Form("cell%d",index),index+1,index+1);
	  goodHistList->Add(cell);
	  numCells++;
	}
      
    }
  goodFile.close();

  TH1D* gdHstsMrgd = cellVAmplitude->ProjectionY("gdHstsMrgd",1,1);
  gdHstsMrgd->Reset();
  gdHstsMrgd->Merge(goodHistList);
  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetLogy();
  c1->SetLogx();
  gdHstsMrgd->Draw();  
  
  //Creating the power law function
  TF1* pwrLw = new TF1("pwrLw","[0]*TMath::Power(x,[1])",0,10000);
  pwrLw->SetParameter(0,2.64e+07);
  pwrLw->SetParameter(1,-4);
  
  //Cell energy Cut Off
  const Int_t lowCutOffX = 3;
  const Int_t highCutOffX = 23;
  
  //Fitting the Funcion
  gdHstsMrgd->Fit("pwrLw","EM","",3,23); //EM for method consitentcy.
  TF1* myfunc = gdHstsMrgd->GetFunction("pwrLw");

  //Getting the value of the power
  const double gamma = myfunc->GetParameter(1);
  const double gammaErr = myfunc->GetParError(1);
  
  //Finding bins corresponding to the energy cut offs
  const Int_t lowCutOffBin = gdHstsMrgd->GetXaxis()->FindBin(lowCutOffX);
  const Int_t highCutOffBin = gdHstsMrgd->GetXaxis()->FindBin(highCutOffX);
  
  //The integral (counts) of the bins. Bounds are the energy cut offs
  const double gdHstsMrgd_integral = gdHstsMrgd->Integral(lowCutOffBin,highCutOffBin);
  double int_norm = gdHstsMrgd_integral/numCells;
  
  //Output file
  ofstream outPut("newCoeffs.txt");
  outPut << "cell_ID\t" << "par0" << endl; //\t" << "err0\t" << "par1\t" << "err1\t" << "chi2\t" << "integral" << endl;
  
  TH1D* coeffHist = new TH1D("coeffHist", "coeffHist",100 ,-0.5,9.5);
  int counter = 0;
  goodFile.open(txtFile);
  if(goodFile.is_open())
    {
      string line = "";
      std::getline(goodFile,line);
      int i = 0;
      double c = 0.0;
      
      while(goodFile >> i >> c)
	{
	  TH1D* cell = new TH1D();
	  cell = cellVAmplitude->ProjectionY("cell",i+1,i+1);
	  
	  //Double_t chi2, par0, err0, par1, err1, max;
	  //chi2 = par0 = err0 = par1 = err1 = max = -1.0;
	  
	  Double_t a = -1.0;
	  Double_t cell_integral = cell->Integral(lowCutOffBin,highCutOffBin);
	  //cout << "ID: " << i;
	  //cout << "\tContent Check: " << cell_integral << endl;
	  
	  if(cell_integral)
	    {
	      //calculating a using a = (I_indiv/norm_I_6000)^(1/gamma)
	      a = TMath::Power(cell_integral/int_norm,1/gamma);
	      coeffHist->Fill(a);
	      if(a > 1.5 || a < 0.5)
		counter++;
	      //cout << i << "\t" << a << endl;
	      
	      
	    }//
	  outPut << i << "\t" << a << endl;
	}
    }
  goodFile.close();
  cout << numCells << endl;
  outPut.close();//*/
  
  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  coeffHist->Draw();

  TFile* f = new TFile("coeff_histo.root","RECREATE");
  coeffHist->Write();
  gdHstsMrgd->Write();


  return counter;
  
  
}
