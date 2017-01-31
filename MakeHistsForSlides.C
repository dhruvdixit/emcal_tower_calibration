Double_t MakeHistsForSlides(TString goodFile, TString badFile, TString rootFile)
{
  //Extracting the histogram
  TFile* f = TFile::Open(rootFile);
  TDirectoryFile* dirFile = (TDirectoryFile*)(f->Get("AliAnalysisTaskCalibEmcal"));
  TList* list = (TList*)(dirFile->Get("histogram"));
  TH2D* cellVAmplitude = (TH2D*)(list->FindObject("_histogram_cell_id_amplitude"));

    
  //Getting a Good Cell
  TH1D* goodC = new TH1D();
  ifstream myFile(goodFile);
  TString title = "";

  const int num = 500;

  if(myFile.is_open())
    {
      string line = "";
      std::getline(myFile,line);

      int index = 0;
      double chi2 = 0.0;
      
      while(myFile >> index >> chi2 && index < num)
	{
	  //cout << index << "\t" << chi2 << endl;
	  title = Form("Energy distribution of Cell %d",index);
	  TH1D* goodCell = cellVAmplitude->ProjectionY("goodCell", index+1,index+1);
	  goodC = (TH1D*)goodCell->Clone();
	}
    }
  myFile.close();

  Int_t bins = goodC->GetSize()-2;//minus for the over and underflow ins
  for(int i = 1; i < bins+1; i++)
    {
      double dE = goodC->GetBinWidth(i);
      double dN = goodC->GetBinContent(i);
      double newContent = dN/dE;
      goodC->SetBinContent(i,newContent);
    }

  TCanvas* c3 = new TCanvas("c3","c3",500,500);
  c3->SetLogx();
  c3->SetLogy();
  goodC->SetTitle(title);
  goodC->GetXaxis()->SetTitle("E (GeV)");
  goodC->GetYaxis()->SetTitle("dN/dE");
  gStyle->SetOptStat(0);
  goodC->Draw();//*/





  //Getting a Bad Cell
  TH1D* badC = new TH1D();
  ifstream badList(badFile);
  TString title2 = "";

  if(badList.is_open())
    {
      string line = "";
      std::getline(badList,line);
      
      int index = 0;
      double chi1, chi2;
      
      while(badList >> index >> chi2 && index < num)
	{
	  title2 = Form("Energy distribution of Cell %d",index);
	  TH1D* badCell = cellVAmplitude->ProjectionY("badCell", index+1,index+1);
	  badC = (TH1D*)badCell->Clone();
	}
    }
  badList.close();

  Int_t bins2 = badC->GetSize()-2;//minus for the over and underflow ins
  for(int i = 1; i < bins2+1; i++)
    {
      double dE = badC->GetBinWidth(i);
      double dN = badC->GetBinContent(i);
      double newContent = dN/dE;
      badC->SetBinContent(i,newContent);
    }

  TCanvas* c4 = new TCanvas("c4","c4",500,500);
  c4->SetLogx();
  c4->SetLogy();
  badC->SetTitle(title2);
  badC->GetXaxis()->SetTitle("E (GeV)");
  badC->GetYaxis()->SetTitle("dN/dE");
  gStyle->SetOptStat(0);
  badC->Draw();//*/

}
