void MakeHistFromFile(TString fileName)
{
  TH1D* h1 = new TH1D("h1", "", 300 , -0.5, 299.5);


  ifstream myFile(fileName);
  double max = -1;
  double min = 999999999999999;
  if(myFile.is_open())
    {
      double a = -1;
      Int_t low = 1;
      while(myFile >> a)
      //for(int i = low; i < high; i++)
	{
	  h1->Fill(a);
	  //Getting the range
	  if(a > max)
	    max = a;
	  if (a < min)
	    min = a;
	}
      myFile.close();
    }

  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetLogy();
  //c1->SetLogx();
  h1->Draw();

  //TFile* f = new TFile("chi_histo.root","RECREATE ");
  //f->Cd();
  //f->Write();
  //chi1_hist->Write();
  //chi2_hist->Write();
  //chi_sub->Write();

  cout << "max: " << max << "\tmin: " << min << endl;
} 
