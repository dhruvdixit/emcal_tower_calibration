void SeperateGoodBadTowers(TString fileName)
{

  ifstream myFile(fileName);
  ofstream goodFile("goodTowers.txt");
  ofstream badFile("badTowers.txt");
  goodFile << "cell_ID\t" << "Chi2" <<  endl;
  badFile << "cell_ID\t" << "Chi2" <<  endl;
  int good, bad;
  good = bad = 0;
  if(myFile.is_open())
    {
      string line = "";
      std::getline(myFile,line);
      double a,b,c;
      a = b = c = 0.5;
      const Int_t cutoff = 300;
      while(myFile >> a >> b >> c)
	{
	  Double_t index, chi1, chi2;
	  index = a;
	  chi1 = b; 
	  chi2 = c;
	  
	  if(chi1 < 0)
	    {
	      cout << "Throwing away: " << index << "\t" << chi1 << endl;
	      continue;
	    }
	  
	  if(chi1 < cutoff)
	    {
	      cout << "Good Tower: " << index << "\t" << chi1 << endl;
	      goodFile << index << "\t" << chi1 << endl;
	      good++;
	      continue;
	    }

	  if(chi1 > cutoff)
	    {
	      cout << "Bad Tower: " << index << "\t" << chi1 << endl;
	      badFile << index << "\t" << chi1 << endl;
	      bad++;
	      continue;
	    }

	}
      myFile.close();
      badFile.close();
      goodFile.close();
    }
  cout << "Num Good: " << good << "\tNum Bad: " << bad << endl;

} 
