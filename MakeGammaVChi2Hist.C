void MakeGammaVChi2Hist()
{
  //Extracting the histogram
  TFile* f = TFile::Open("/home/dhruv/alice_calib_emcal/alice_calib_emcal/AnalysisResults.root");
  TDirectoryFile* dirFile = (TDirectoryFile*)(f->Get("AliAnalysisTaskCalibEmcal"));
  TList* list = (TList*)(dirFile->Get("histogram"));
  TH2D* cellVAmplitude = (TH2D*)(list->FindObject("_histogram_cell_id_amplitude"));
  
  //cout << __FILE__ << __LINE__ << endl;

  //Cell Tower range to analyse
  const Int_t CVALow = 0;
  const Int_t CVAHigh = 17670;
  
  //cout << __FILE__ << __LINE__ << endl;
  
  //Creating the power law function
  TF1* pwrLw = new TF1("pwrLw","[0]*TMath::Power(x,[1])",0,10000);
  pwrLw->SetParameter(0,2.64e+07);
  pwrLw->SetParameter(1,-4);
  
  //Cell energy Cut Off
  const Int_t lowCutOffX = 3;
  const Int_t highCutOffX = 23;

  //Obtaining a histogram of the cells and their gamma.
  int numCells = 0;
  
  TH1D* gammaHist80EMC = new TH1D("gammaHist80EMC", "gammaHistEMC #chi^{2} <= 80",100 ,-0.5,9.5);
  
  TH1D* gammaHist200EMC = new TH1D("gammaHist200EMC", "gammaHistEMC 80 < #chi^{2} <= 200",100 ,-0.5,9.5);
  gammaHist200EMC->SetLineColor(kRed);
  
  TH1D* gammaHistBeyondEMC = new TH1D("gammaHistBeyondEMC", "gammaHistEMC #chi^{2} > 200",100 ,-0.5,9.5);
  gammaHistBeyondEMC->SetLineColor(kGreen);

  TH1D* gammaHist80DC = new TH1D("gammaHist80DC", "gammaHistDC #chi^{2} <= 80",100 ,-0.5,9.5);
  gammaHist80DC->SetMarkerStyle(2);
  
  TH1D* gammaHist200DC = new TH1D("gammaHist200DC", "gammaHistDC 80 < #chi^{2} <= 200",100 ,-0.5,9.5);
  gammaHist200DC->SetMarkerStyle(3);
  
  TH1D* gammaHistBeyondDC = new TH1D("gammaHistBeyondDC", "gammaHistDC #chi^{2} > 200",100 ,-0.5,9.5);
  gammaHistBeyondDC->SetMarkerStyle(4);

  ifstream chi2File("chiSqrRebin5.txt");
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
	  cell = cellVAmplitude->ProjectionY("cell",index+1,index+1);
	  
	  //Finding bins corresponding to the energy cut offs
	  Int_t lowCutOffBin = cell->GetXaxis()->FindBin(lowCutOffX);
	  Int_t highCutOffBin = cell->GetXaxis()->FindBin(highCutOffX);
  
	  Double_t cell_integral = cell->Integral(lowCutOffBin,highCutOffBin);
	  
	  if(cell_integral)
	    {
	      //Fitting the Funcion
	      cell->Fit("pwrLw","EM","",3,23); //EM for method consitentcy.
	      TF1* myfunc = cell->GetFunction("pwrLw");

	      //Getting the value of the power
	      Double_t gamma = myfunc->GetParameter(1);
	      Double_t gammaErr = myfunc->GetParError(1);
	      Double_t abs_gamma = TMath::Abs(gamma);
	      
	      cout << index << endl;
	      if(gamma > 0)
		cout << gamma << "\t" << __FILE__ << __LINE__ << endl;
	      if(index < 12288)
		{
		  if(chi1 <= 80)
		    {
		      gammaHist80EMC->Fill(abs_gamma);
		    }
		  else if(chi1 > 80 && chi1 <= 200)
		    {
		      gammaHist200EMC->Fill(abs_gamma);
		    }//end else if 80-200
		  else
		    {
		      gammaHistBeyondEMC->Fill(abs_gamma);
		    }//end else if >200
		}// end index
	      else
		{	
		  if(chi1 <= 80)
		    {
		      gammaHist80DC->Fill(abs_gamma);
		    }
		  else if(chi1 > 80 && chi1 <= 200)
		    {
		      gammaHist200DC->Fill(abs_gamma);
		    }//end else if 80-200
		  else
		    {
		      gammaHistBeyondDC->Fill(abs_gamma);
		    }//end else if >200
		}
	    }//end cell
	}//end while
    }//end if

  chi2File.close();
  
  gStyle->SetOptStat(0);

  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  gammaHist80EMC->Draw();
  gammaHist200EMC->Draw("same");
  gammaHistBeyondEMC->Draw("same");

  TLegend* leg = new TLegend(0.9,0.9,0.76,0.8);
  leg->AddEntry(gammaHist80EMC, "#chi^{2} <= 80");
  leg->AddEntry(gammaHist200EMC, "80 < #chi^{2} <= 200");
  leg->AddEntry(gammaHistBeyondEMC, "#chi^{2} > 200");
  leg->SetTextSize(0.02);
  leg->Draw(); 

  TCanvas* c3 = new TCanvas("c3","c3",500,500);
  gammaHist80DC->Draw("p");
  gammaHist200DC->Draw("psame");
  gammaHistBeyondDC->Draw("psame");
  
  TLegend* leg2 = new TLegend(0.9,0.9,0.76,0.8);
  leg2->AddEntry(gammaHist80DC, "#chi^{2} <= 80");
  leg2->AddEntry(gammaHist200DC, "80 < #chi^{2} <= 200");
  leg2->AddEntry(gammaHistBeyondDC, "#chi^{2} > 200");
  leg2->SetTextSize(0.02);
  leg2->Draw(); 

  /*TFile* f = new TFile("gammaVchi2.root","RECREATE");
  
  gammaHist80EMC->Write();;
  gammaHist200EMC->Write();;
  gammaHistBeyondEMC->Write();
  
  gammaHist80DC->Write();;
  gammaHist200DC->Write();;
  gammaHistBeyondDC->Write();
  f->Close();*/
  
}
