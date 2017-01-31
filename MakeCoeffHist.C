void MakeCoeffHist(TString fileName)
{
  TH1D* emcal = new TH1D("emcal", "EMCA Cell Coefficients",70 ,-0.5,6.5);
  emcal->GetXaxis()->SetTitle("#alpha");
  emcal->SetMarkerStyle(2);

  TH1D* dcal = new TH1D("dcal", "DCAL Cell Coefficients",70 ,-0.5,6.5);
  dcal->GetXaxis()->SetTitle("#alpha");
  dcal->SetMarkerStyle(2);
    
  ifstream myFile(fileName);
  
  if(myFile.is_open())
    {
      string line = "";
      std::getline(myFile,line);
      int id = -1;
      double coeff = 0.0;
      while(myFile >> id >> coeff)
	{
	  if(id < 12288)
	    emcal->Fill(coeff);
	  else
	    dcal->Fill(coeff);
	}
      myFile.close();
    }

  gStyle->SetOptStat(0);

  TCanvas* c1 = new TCanvas("c1","c1",1000,500);
  c1->Divide(2,1);
  c1_1->cd();
  c1_1->SetLogy();
  emcal->Draw("P");

  c1_2->cd();
  c1_2->SetLogy();
  dcal->Draw("P");


   

} 
