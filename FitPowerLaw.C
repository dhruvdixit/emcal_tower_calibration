// #include "AliAnalysisTaskCalibEmcal.h"
//#include <ofstream>

/*int FitPowerLaw(TString txtFile, TString rootFile)
{
  ifstream inPut(txtFile);
  int works = 0;
  if(inPut.is_open())
    cout << txtFile << " exists" << endl;
  else
    {
      cout << txtFile << " does not exist" << endl;
      cout << "Do you want to generate one?[y/n]" << endl;
      bool exitCondition = false;
      while(!exitCondition)
	{
	  TString reply;
	  cin >> reply;
	  if(reply.CompareTo("y") == 0 || reply.CompareTo("Y") == 0)
	    {
	      cout << "Generating File" << endl;
	      exitCondition = true;
	      works = MakeParameterFile(txtFile,rootFile);
	    }//end if
	  
	  else if(reply.CompareTo("n") == 0 || reply.CompareTo("N") == 0)
	    {
	      cout << "Not generating File" << endl;
	      exitCondition = true;
	    }//end else if
	  
	  else
	    cout << "Please reply with y or n. It's not that hard" << endl;
	  
	}//end while
    }//end else
  
  return works;
}*/

/*/////////////////////////////////////////////////////////////////////////////////
The function below takes the root file with the 2D hist of towers vs energy and applies the power law function: ax^g (where g should be around -4) to the first 6000 towers to obtain the value of g.Then, with the g calculated, let's write the known g as G, the new function: ax^G is applied to each individual tower to obtain values of a. Since true A is a^(1/G), it is calculated that way.  
*///////////////////////////////////////////////////////////////////////////////////
Double_t FitPowerLaw(TString txtFile, TString rootFile)
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
  const Int_t CVAHigh = 10;//6000;//17670;
  
  //Cell energy Cut Off
  const Int_t lowCutOffX = 3;
  const Int_t highCutOffX = 23;

  TH1D* sixKCells = cellVAmplitude->ProjectionY("6KCells", CVALow,CVAHigh);
  sixKCells->Fit("pwrLw", "","",lowCutOffX, highCutOffX);
  TF1* myfunc = sixKCells->GetFunction("pwrLw");
  
  //Getting the value of the power
  const double gamma = myfunc->GetParameter(1);
  const double gammaErr = myfunc->GetParError(1);

  //Finding bins corresponding to the energy cut offs
  Int_t lowCutOffBin = sixKCells->GetXaxis()->FindBin(lowCutOffX);
  Int_t highCutOffBin = sixKCells->GetXaxis()->FindBin(highCutOffX);

  //The integral (counts) of the bins. Bounds are the energy cut offs
  const double integral_sixK = sixKCells->Integral(lowCutOffBin,highCutOffBin);
  const double normalized_Integral_sixK = 488;//integral_sixK/(highCutOffX-lowCutOffX+1);
  
  //Output file
  //ofstream outPut(txtFile);
  //outPut << "cell_ID\t" << "par0\t" << "err0\t" << "par1\t" << "err1\t" << "chi2\t" << "integral" << endl;
  //outPut << "1st6K" << "\t" << myfunc->GetParameter(0) << "\t"<< myfunc->GetParError(0) << "\t"<< myfunc->GetParameter(1) << "\t"<< myfunc->GetParError(1) << "\t"<< myfunc->GetChisquare() << "\t" << normalized_Integral_sixK << endl;

  //TH1D* integral_hist = new TH1D("chi_hist", "chi_hist",911000,-1.5,910998.5);
  
  for(int i = CVALow; i < CVAHigh; i++)
    {
      TH1D* cell = new TH1D();
      cell = cellVAmplitude->ProjectionY("cell",i,i);

      //TCanvas* c1 = new TCanvas("c1","c1", 500, 500);
      //c1->SetLogx();
      //c1->SetLogy();
      //cell->Draw();

      
      //calculating a using a = (I_indiv/norm_I_6000)^(1/gamma)
      //Double_t indiv_integral = cell->Integral(lowCutOffBin,highCutOffBin);
      //Double_t integral_ratio = indiv_integral/normalized_Integral_sixK;
      //Double_t a = TMath::Power(integral_ratio,1/gamma);

      //outPut << i << "\t" << a << "\t"<< "NA" << "\t"<< "NA" << "\t"<< "NA" << "\t"<< "NA" << "\t" << indiv_integral << endl;
      Double_t chi2, par0, err0, par1, err1, max;
      chi2 = par0 = err0 = par1 = err1 = max = -1.0;
      
      Double_t chi = -1.0;
      
      cout << "ID: " << i <<  endl;
      cout << "Content Check: " << cell->Integral(lowCutOffBin,highCutOffBin) << endl;
      
      if(cell->Integral(lowCutOffBin,highCutOffBin))
	{
	  cell->Fit("pwrLw", "","",lowCutOffX,highCutOffX);
	  myfunc = cell->GetFunction("pwrLw");
	  chi = myfunc->GetChiSquare();
	  if(max < chi)
	    max = chi;
	  
	  TF1* pwrLw2 = new TF1("pwrLw2","[0]*TMath::Power(x,gamma)",0,10000);
	  pwrLw2->SetParameter(0,4.6e+06);
	  cell->Fit("pwrLw2", "","",lowCutOffX,highCutOffX);
      	  myfunc2 = cell->GetFunction("pwrLw2");
	  chi2 = myfunc2->GetChisquare();
	  if (max < chi2)
	    max = chi2;


	  //par0 = myfunc2->GetParameter(0);
	  //err0 = myfunc2->GetParError(0);
	  //par1 = myfunc2->GetParameter(1);
	  //err1 = myfunc2->GetParError(1);
	}//*/
      //outPut << i << "\t" << par0 << "\t"<< err0 << "\t"<< par1 << "\t"<< err1 << "\t"<< chi2 << endl;
      }
  
  //outPut.close();

  return max;
}
