void GetChiSqr()
{
  //Extracting the histogram
  TFile* f = TFile::Open("/home/dhruv/alice_calib_emcal/alice_calib_emcal/AnalysisResults.root");
  TDirectoryFile* dirFile = (TDirectoryFile*)(f->Get("AliAnalysisTaskCalibEmcal"));
  TList* list = (TList*)(dirFile->Get("histogram"));
  TH2D* cellVAmplitude = (TH2D*)(list->FindObject("_histogram_cell_id_amplitude"));
  
  //Creating the power law function
  TF1* pwrLw2 = new TF1("pwrLw2","[0]*TMath::Power(x,[1])",0,10000);
  pwrLw2->SetParameter(0,4.6e+06);
  pwrLw2->SetParameter(1,500);

  //Cell Tower range to analyse
  const Int_t CVALow = 0;
  const Int_t CVAHigh = 12288; //17670;

  //Cell energy Cut Off
  const Int_t lowCutOffX = 3;
  const Int_t highCutOffX = 23;

  /*TList* goodHistList = new TList;
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
  goodFile.close();//

  TH1D* sixKCells = cellVAmplitude->ProjectionY("sixKCells",1,1);
  sixKCells->Reset();
  sixKCells->Merge(goodHistList);
  sixKCells->Fit("pwrLw2", "EM","",lowCutOffX, highCutOffX);
  
  //Extracting the function
  TF1* func = sixKCells->GetFunction("pwrLw2");*/
  
  //Getting the value of the power
  const double gamma = -4.0;//func->GetParameter(1);

  //Output file
  ofstream outPut("run2_chiSqr_rebin5_intcut200.txt");
  outPut << "cell_ID\t" << "Chi1\t" << "Chi2\t" << endl; //"Chi3" << endl;

  Double_t max = -1.0;
  TCanvas* c1 = new TCanvas("c1","c1", 500, 500);
  c1->SetLogx();
  c1->SetLogy();
  TH1D* cell = new TH1D();
  for(int i = CVALow; i < CVAHigh; i++)
    {
      cell = cellVAmplitude->ProjectionY("cell",i+1,i+1);
      cell->Rebin(5);
      
      Double_t chi1, chi2, chi3, par0, err0, par1, err1;
      chi1 = chi2 = chi3 = par0 = err0 = par1 = err1 = -1.0;
      
      //Finding bins corresponding to the energy cut offs
      Int_t lowCutOffBin = cell->GetXaxis()->FindBin(lowCutOffX);
      Int_t highCutOffBin = cell->GetXaxis()->FindBin(highCutOffX);
  
      cout << "ID: " << i <<  endl;
      cout << "Content Check: " << cell->Integral(lowCutOffBin,highCutOffBin) << endl;
      
      if(cell->Integral(lowCutOffBin,highCutOffBin) > 200)
	{	  
	  //Fitting the 1 parameter function
	  TF1* pwrLw1 = new TF1("pwrLw1",Form("[0]*TMath::Power(x,%d)",gamma),0,10000);
	  pwrLw1->SetParameter(0,4.6e+06);
	  cell->Fit("pwrLw1", "EM","",lowCutOffX,highCutOffX);
      	  TF1* myfunc1 = cell->GetFunction("pwrLw1");
	  chi1 = myfunc1->GetChisquare();
	  cout << "chi1: " << chi1 << endl;//

	  //Fitting the 2 parameter function
	  pwrLw2->SetParameter(0,4.6e+06);
	  pwrLw2->SetParameter(1,-4);
	  cell->Fit("pwrLw2", "EM","",lowCutOffX,highCutOffX);
	  TF1* myfunc2 = cell->GetFunction("pwrLw2");
	  chi2 = myfunc2->GetChisquare();
	  cout << "chi2: " << chi2 << endl;//*/

	  //Fitting the 3 paramter function
	  /*TF1* pwrLw3 = new TF1("pwrLw3","[0]*TMath::Power(x,[1]+[2]*x)",0,10000);
	  pwrLw3->SetParameter(0,200);
	  pwrLw3->SetParameter(1,-4);
	  pwrLw3->SetParameter(2,0);
	  pwrLw3->SetParLimits(2,-100,0);
	  cell->Fit("pwrLw3", "EM","",lowCutOffX,highCutOffX);
      	  TF1* myfunc3 = cell->GetFunction("pwrLw3");
	  chi3 = myfunc3->GetChisquare();
	  cout << "chi3: " << chi3 << endl;//*/
	}//*/
      outPut << i << "\t" << chi1 << "\t" << chi2 << endl; //"\t" << chi3 << endl; endl;
    }
  
  outPut.close();

  //cell->Draw();

}

