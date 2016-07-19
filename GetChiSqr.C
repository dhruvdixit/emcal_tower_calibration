void GetChiSqr()
{
  //Extracting the histogram
  TFile* f = TFile::Open("/home/dhruv/alice_calib_emcal/alice_calib_emcal/AnalysisResults.root");
  TDirectoryFile* dirFile = (TDirectoryFile*)(f->Get("AliAnalysisTaskCalibEmcal"));
  TList* list = (TList*)(dirFile->Get("histogram"));
  TH2D* cellVAmplitude = (TH2D*)(list->FindObject("_histogram_cell_id_amplitude"));
  
  //Creating the power law function
  TF1* pwrLw = new TF1("pwrLw","[0]*TMath::Power(x,[1])",0,10000);
  pwrLw->SetParameter(0,4.6e+06);
  pwrLw->SetParameter(1,-5);
  
  //Cell Tower range to analyse
  const Int_t CVALow = 0;
  const Int_t CVAHigh = 17670;

  //Cell energy Cut Off
  const Int_t lowCutOffX = 3;
  const Int_t highCutOffX = 23;

  TList* goodHistList = new TList;
  ifstream goodFile("goodTowers.txt");
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

  TH1D* sixKCells = cellVAmplitude->ProjectionY("sixKCells",1,1);
  sixKCells->Reset();
  sixKCells->Merge(goodHistList);
  sixKCells->Fit("pwrLw", "EM","",lowCutOffX, highCutOffX);
  
  //Extracting the function
  TF1* myfunc = sixKCells->GetFunction("pwrLw");
  
  //Getting the value of the power
  const double gamma = myfunc->GetParameter(1);
 
  //Output file
  ofstream outPut("chiSqrRebin5_2.txt");
  outPut << "cell_ID\t" << "Chi_2parF\t" << "Chi_1parF" << endl;

  Double_t max = -1.0;

  for(int i = CVALow; i < CVAHigh; i++)
    {
      TH1D* cell = new TH1D();
      cell = cellVAmplitude->ProjectionY("cell",i+1,i+1);
      cell->Rebin(5);
      
      Double_t chi2, par0, err0, par1, err1;
      chi2 = par0 = err0 = par1 = err1 = -1.0;
      
      Double_t chi = -1.0;
 
      //Finding bins corresponding to the energy cut offs
      Int_t lowCutOffBin = cell->GetXaxis()->FindBin(lowCutOffX);
      Int_t highCutOffBin = cell->GetXaxis()->FindBin(highCutOffX);
  
      cout << "ID: " << i <<  endl;
      cout << "Content Check: " << cell->Integral(lowCutOffBin,highCutOffBin) << endl;
      
      if(cell->Integral(lowCutOffBin,highCutOffBin))
	{
	  //Fitting the original function
	  cell->Fit("pwrLw", "EM","",lowCutOffX,highCutOffX);
	  myfunc = cell->GetFunction("pwrLw");
	  chi = myfunc->GetChisquare();
	  //integral_hist->Fill(chi);
	  cout << "chi: " << chi << "\t";
	  if(max < chi)
	    max = chi;
	  
	  //Fitting the 1 parameter function
	  //cout << __FILE__ << __LINE__ << "\t" << gamma << endl;
	  TF1* pwrLw2 = new TF1("pwrLw2",Form("[0]*TMath::Power(x,%d)",gamma),0,10000);
	  pwrLw2->SetParameter(0,4.6e+06);
	  cell->Fit("pwrLw2", "EM","",lowCutOffX,highCutOffX);
	  //cout << __FILE__ << __LINE__ << "\t" << gamma << endl;
      	  TF1* myfunc2 = cell->GetFunction("pwrLw2");
	  chi2 = myfunc2->GetChisquare();
	  //integral_hist->Fill(chi2);
	  cout << "chi2: " << chi2 << endl;
	  if (max < chi2)
	    max = chi2;
	}//*/
      outPut << i << "\t" << chi << "\t" << chi2 << endl;
      }
  
  outPut.close();
  
  /*TCanvas* c1 = new TCanvas("c1","c1", 500, 500);
  c1->SetLogx();
  c1->SetLogy();
  integral_hist->Draw();*/

}

