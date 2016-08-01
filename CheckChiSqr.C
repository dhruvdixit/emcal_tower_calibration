#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <fstream>
//using namespace std;

void DoCleanUp(TH1D* hist, TF1* func1,TF1* fitFunc)
{
  hist->Delete();
  func1->Delete();
  fitFunc->Delete();
  cout << "pointers delete" << endl;
  return;
}

double Chi(int num)
{
  double chi2 = -1; 
  //if(num > -1)
    {
      TF1* f = new TF1("f", "5*(TMath::Power(x,-4))",1,100);
      TH1D* h1 = new TH1D("h1","h1", 100, -0.5, 99.5);

      for(int i = 0; i < 1000000; i++)
	{
	  h1->Fill(f->GetRandom(1,100));
	  //cout << f.GetRandom(1,100) << endl;
	}
      
      //cout << __FILE__ << __LINE__<< endl;

      TF1* pwrLw = new TF1("pwrLw", "[0]*TMath::Power(x,[1])",1,1000);
      pwrLw->SetParameter(0,5);
      pwrLw->SetParameter(1,-4.0);
      
      //cout << __FILE__ << __LINE__<< endl;
      
      h1->Fit("pwrLw","0","",2,50);
      TF1* func = h1->GetFunction("pwrLw");
      chi2 = func->GetChisquare();

      //DoCleanUp(h1, f, pwrLw);
    }
  return chi2;
}


void CheckChiSqr()
{
 
  TH1D* chiHist = new TH1D("chiHist","chiHist",400,-0.5,399.5);
  
  ofstream chis("checkings_100000.txt");
  for(int i = 0; i < 100000; i++)
    {    
      double chi = -1.0;
      chi = Chi(i);
      chis << chi << endl;
      if(!(i % 1000))
	{
	  cout << "CHI = " << chi << endl;
	  cout << i << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\t" << __FILE__ << __LINE__ << endl;
	}
      chiHist->Fill(chi);
    }

  
  chiHist->Draw();//*/
  

  /*TF1* f = new TF1("f", "5*(TMath::Power(x,-4))",1,100);
  TH1D* h1 = new TH1D("h1","h1", 100, -0.5, 99.5);
  
  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetLogy();
  //cout << h1 << endl;
  for(int i = 0; i < 1000000; i++)
    {
      h1->Fill(f->GetRandom(1,100));
      //cout << f.GetRandom(1,100) << endl;
    }
  
  TH1D* h2 = h1->Clone();  
  
  TF1* pwrLw = new TF1("pwrLw", "[0]*TMath::Power(x,[1])",0,1000);
  pwrLw->SetParameter(0,50);
  pwrLw->SetParameter(1,-2.0);
  
  if(h1->Integral())
    {
      h1->Fit("pwrLw","EM","",2,50);
      TF1* myFunc = h1->GetFunction("pwrLw");
      cout <<  myFunc->GetChisquare() << endl;
    }
  else
    cout << -1;//
  
  h1->Draw();

  for(int i = 1; i < h2->GetSize()-1; i++)
    {
      double bc = 0;
      bc = h2->GetBinContent(i);
      bc = bc/1000;
      h2->SetBinContent(i,bc);
    }

  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  c2->SetLogy();
  
  if(h2->Integral())
    {
      h2->Fit("pwrLw","EM","",2,50);
      TF1* myFunc2 = h2->GetFunction("pwrLw");
      cout <<  myFunc2->GetChisquare() << endl;
    }
  else
    cout << -1;//*/
  

}



