void MakeGammaVChi2Hist(TString txtFile, TString rootFile, TString chiFile)
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
  
  

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  TH1D* coeffHist80 = new TH1D("coeffHist80", "coeffHist #chi^{2} <= 80",100 ,-0.5,9.5);
  coeffHist80->SetMarkerStyle(2);
  TH1D* coeffHist200 = new TH1D("coeffHist200", "coeffHist 80 < #chi^{2} <= 200",100 ,-0.5,9.5);
  coeffHist200->SetLineColor(kRed);
  coeffHist200->SetMarkerStyle(3);

  TH1D* coeffHistBeyond = new TH1D("coeffHistBeyond", "coeffHist #chi^{2} > 200",100 ,-0.5,9.5);
  coeffHistBeyond->SetLineColor(kGreen);
  coeffHistBeyond->SetMarkerStyle(4);

  ifstream chi2File(chiFile);
  if(chi2File.is_open())
    {
      string line = "";
      std::getline(chi2File,line);
      int index = 0;
      double chi1 = 0.0;
      double chi2 = 0.0;
      
      while(chi2File >> index >> chi1 >> chi2)
	{
	  TH1D* cell = new TH1D();
	  cell = cellVAmplitude->ProjectionY("cell",index,index);
	  
	  Double_t a = -1.0;
	  Double_t cell_integral = cell->Integral(lowCutOffBin,highCutOffBin);
	  
	  if(cell_integral)
	    {
	      //calculating a using a = (I_indiv/norm_I_6000)^(1/gamma)
	      a = TMath::Power(cell_integral/int_norm,1/gamma);
	      cout << index << "\t" << a << endl;
	      if(chi1 <= 80)
		{
		  coeffHist80->Fill(a);
		}//end if < 80
	      else if(chi1 > 80 && chi1 <= 200)
		{
		  coeffHist200->Fill(a);
		}//end else if 80-200
	      else
		{
		  coeffHistBeyond->Fill(a);
		}//end else if >200
	    

	    }//end cell
	}//end while
    }//end if
  chi2File.close();
  //cout << numCells << endl;
  //outPut.close();//*/
  
  gStyle->SetOptStat(0);

  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  coeffHist80->Draw();
  coeffHist200->Draw("same");
  coeffHistBeyond->Draw("same");

  TLegend* leg = new TLegend(0.9,0.9,0.76,0.8);
  leg->AddEntry(coeffHist80, "#chi^{2} <= 80");
  leg->AddEntry(coeffHist200, "80 < #chi^{2} <= 200");
  leg->AddEntry(coeffHistBeyond, "#chi^{2} > 200");
  leg->SetTextSize(0.02);
  leg->Draw();

  //TFile* f = new TFile("blah.root","RECREATE");
  //coeffHist->Write();
  //gdHstsMrgd->Write();


  //return counter;
  
  
}
