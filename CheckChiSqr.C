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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double CalcChiSqr(TH1D* hist, Double_t coeff, Double_t expo, Int_t xMin, Int_t xMax)
{
  {
    TH1D* myHist = hist->Clone();
    int bins = myHist->GetSize()-2;
    double chiSqr = 0;
    for(int i = xMin+1; i < xMax+1; i++)
      {
	double x = myHist->GetBinCenter(i);
	double o = myHist->GetBinContent(i);
	double e = coeff*(TMath::Power(x,expo));
	//cout << x << "\t" << o << "\t" << e;
	if(o != 0)
	  chiSqr += ((o-e)*(o-e))/o;
	//cout << "\tchiSqr: " << chiSqr << endl;
      }
    return chiSqr/2;
    
  }
  
  
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Chi(int num, double* arr)
{
  //double chi[3] = arr;
  //double* pointer = &chi;
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

      TF1* pwrLw = new TF1("pwrLw", "[0]*TMath::Power(x,[1])",1,1000);//changed to 0 parameter
      pwrLw->SetParameter(0,5);
      pwrLw->SetParameter(1,-4);
      //cout << pwrLw->GetParameter(0) << "\t" << pwrLw->GetParameter(1) << endl;

      //cout << __FILE__ << __LINE__<< endl;
      
      h1->Fit("pwrLw","0","",2,25);
      TF1* func = h1->GetFunction("pwrLw");
      double chi = func->GetChisquare();
      double dof = func->GetNDF();
      arr[0] = chi/dof;
      double par0 = func->GetParameter(0);
      double par1 = func->GetParameter(1);
      //cout << par0 << "\t" << par1 << endl;
      arr[1] = CalcChiSqr(h1,par0,par1,2,25);
      //chi[2] = CalcChiSqr(h1,5,-4,2,25);
      //cout << "Outputing values from Chi()" << endl;
      //cout << arr[0] << "\t" << arr[1] << endl;//"\t" << chi[2] << endl;
      //DoCleanUp(h1, f, pwrLw);
    }
    //arr = chi;
    //return chi;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckChiSqr()
{
  //TCanvas* c1 = new TCanvas("c1","c1",500,500);
  TH1D* chiHist = new TH1D("chiHist","chiHist",200,-0.5,199.5);
  TH1D* myChiHist = new TH1D("myChiHist","myChiHist",100,-0.5,99.5);
  myChiHist->SetLineColor(kRed);

  ofstream chis("checkings_chiCompare_1000.txt");
  for(int i = 0; i < 1000; i++)
    {    
      double chi[3] = {-1, -1 ,1};
      Chi(i, chi);
      //cout << chi[0] << "\t" << chi[1] << "\t" << chi[2] << endl;
      //chis << chi << "/t" endl;
      //if(!(i % 100))
	{
	  cout << "From CheckChiSqr" << endl;
	  cout << chi[0] << "\t" << chi[1] << endl;
	  //cout << i << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\t" << __FILE__ << __LINE__ << endl;
	}
      chiHist->Fill(chi[0]);
      myChiHist->Fill(chi[1]);
    }//
  
  
  chiHist->Draw();
  myChiHist->Draw("same");//*/

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
  
  //if(h1->Integral())
  //{
  h1->Fit("pwrLw","EM","",2,20);
  TF1* myFunc = h1->GetFunction("pwrLw");
  //cout <<  myFunc->GetChisquare() << endl;
  //  }
  //else
  //cout << -1;//
    
  h1->Draw();
  
  double chi2 = -1;
  double chi_calc1 = -1;
  double chi_calc2 = -1;
  
  double par0 = myFunc->GetParameter(0);
  double par1 = myFunc->GetParameter(1);
  
  cout << "Parmaters" << endl;
  cout << par0 << "\t" << par1 << endl;
  
  chi2 = myFunc->GetChisquare();
  chi_calc1 = CalcChiSqr(h1,par0,par1, 2,20);
  //chi_calc2 = CalcChiSqr(h1,5,-4, 2, 20);
  
  cout << "Chi Sqrs" << endl;
  cout << chi2 << "\t" << chi_calc1 << "\t" << chi_calc2 << endl;

  cout << "DOF: " << myFunc->GetNDF() << endl;
  
  /*for(int i = 1; i < h2->GetSize()-1; i++)
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



