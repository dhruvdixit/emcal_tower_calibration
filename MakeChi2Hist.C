void set_log_axis(TAxis *axis)
{
  const double axis_range[2] = 
    {log10(axis->GetXmin()), 
     log10(axis->GetXmax())};
  
  const size_t nbin = axis->GetNbins();
  const double bin_width = (axis_range[1] - axis_range[0]) / nbin;
  double *bin = new double[nbin + 1];
  
  for (size_t i = 0; i <= nbin; i++) 
    {
      bin[i] = pow(10, axis_range[0] + i * bin_width);
    }
  axis->Set(nbin, bin);
}


void MakeChi2Hist(TString fileName)//, TString rootFile)//TString histName, Int_t nBins, Int_t xLow, Int_t xHigh)
{
  //TH1D* chi1_hist = new TH1D("chi1_hist", "chi1_hist", 24516, 0, 24516);
  //TH1D* chi2_hist = new TH1D("chi2_hist", "chi2_hist", 300, 0, 300);

  //set_log_axis(chi1_hist->GetXaxis());
  //set_log_axis(chi2_hist->GetXaxis());

  //TH1D* chi3_hist = new TH1D("chi3_hist", "chi3_hist", 910532, -1.5, 910530.5);
  TH2D* h1 = new TH2D("h1", "#chi^{2}_{2par} vs #chi^{2}_{1par}", 70, 0.5 , 700.5, 1000, 0.5, 10000.5);
  h1->GetXaxis()->SetTitle("#chi^{2}-variable #gamma");
  h1->GetYaxis()->SetTitle("#chi^{2}-fixed #gamma");
  set_log_axis(h1->GetXaxis());
  set_log_axis(h1->GetYaxis());
  //printf("%p", h1);
  
  //chi1_hist->SetLineColor(kRed);
  //chi3_hist->SetLineColor(kCyan);
  
  //TH1D* chi_sub = new TH1D("chi_sub", "chi_sub", 24500, -0.5, 24499.5);
  //chi_sub->SetLineColor(kGreen);
  //Int_t chi1Counter = 0;
  //Int_t chi2Counter = 0;
  //Double_t max1 , max2;//////////////////remove the comment marker
  //max1 = max2 = -1.0;
  //Double_t min = 999999999999;

  ifstream myFile(fileName);
  if(myFile.is_open())
    {
      string line = "";
      std::getline(myFile,line);
      Int_t index = 0;
      Double_t chi1 , chi2, chi3;
      chi1 = chi2 = chi3 = -1.0;
      //Int_t low = 1;
      //Int_t high = 17670;
      //cout << __FILE__ << __LINE__ << endl; 
      
      
      while(myFile >> index >> chi1 >> chi2)// >> chi3) 
	{
	  if(index < 12288)
	    {
	      if(chi1 > -1 && chi2 > -1)
		{
		  cout << index << "\t" << chi1 << "\t" << chi2 << endl;//"\t" << chi3 << endl;
		  
		  //chi1_hist->Fill(chi1);
		  //chi2_hist->Fill(chi2);
		  //chi3_hist->Fill(chi3);
		  
		  //printf("%p", h1);
		  h1->Fill(chi1,chi2);
		  //chi_sub->Fill(chi1-chi2);
		  
		  //if(chi1 > chi2)
		  //chi1Counter++;
		  //if(chi1 < chi2)
		  //chi2Counter++;
		  
		  //if(max1 < chi1)
		  //max1 = chi1;
		  //if(max2 < chi1-chi2 )
		  //max2 = chi1-chi2;
		  //if(min > chi1-chi2)
		  //min = chi1-chi2;
		}
	      //chi1 = chi2 = -1.0;
	      //index = 0
	    }
	}
      myFile.close();
    }

  //cout << __FILE__ << __LINE__ << endl;


  /*TFile* f = new TFile(rootFile,"RECREATE");
  chi1_hist->Write();
  chi2_hist->Write();
  chi_sub->Write();
  h1->Write();
  f->Close();//*/
  
  gStyle->SetOptStat(0);
  
  /*TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetLogy();
  c1->SetLogx();
  chi1_hist->Draw();
  chi2_hist->Draw("same");
  //chi3_hist->Draw("same");
  chi_sub->Draw("same");//*/
  
  //TLegend* leg = new TLegend(0.9,0.9,0.76,0.8);
  //leg->AddEntry(chi1_hist, "#chi^{2}_{2par}");
  //leg->AddEntry(chi2_hist, "#chi^{2}_{1par}");
  //leg->AddEntry(chi_sub, "#chi^{2}_{sub}");
  //leg->SetTextSize(0.02);
  //leg->Draw(); 


  TCanvas* c3 = new TCanvas("c3","c3",500,500);
  c3->SetLogz();
  c3->SetLogy();
  c3->SetLogx();
  h1->Draw("colz");//*/

  
  //cout << "chi1Counter: " <<  chi1Counter << "\tchi2Counter: " <<  chi2Counter << endl;
  //cout << "min: " << min << "\tmax2: " << max2 << endl;
} 

