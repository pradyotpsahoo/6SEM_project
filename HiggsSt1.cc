#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLorentzVector.h"


using namespace Pythia8;
int main()
 {
  Pythia pythia;
  pythia.readString("Beams:idA =  11");  
  pythia.readString("Beams:idB = -11");
  pythia.readString("Beams:eCM = 500.0");
  pythia.readString(" HiggsSM:ffbar2HZ = on");
  //pythia.readString("Next:numberShowEvent = 4");
  
  pythia.init();
  TFile * out_file = new TFile("output_file.root","RECREATE");
  TH1F * hist1d_pTZ_ee = new TH1F("hist1dpTZee", "eepT", 100, 0, 500.);
  TH1F * hist1d_pTZ_mumu = new TH1F("hist1dpTZmumu", "mumupT", 100, 0, 500.);
  TH2F * hist2d_pTZ_ee_mumu = new TH2F("hist2dpTZeemumu","mumu vs ee", 100, 0.,500.,100,0., 500. );
  
  TH1F * hist1d_thetaZ_ee = new TH1F("hist1dthetaZee", "eetheta", 100, -4, 4);
  TH1F * hist1d_thetaZ_mumu = new TH1F("hist1dthetaZmumu", "mumutheta", 100, -4, 4);
  
  TH1F * hist1d_phiZ_ee = new TH1F("hist1dphiZee", "eephi", 100, -8, 8);
  TH1F * hist1d_phiZ_mumu = new TH1F("hist1dphiZmumu", "mumuphi", 100, -8, 8); 
   
  TH1F * hist1d_yZ_ee = new TH1F("hist1dyZee", "eey", 100, -6, 6);
  TH1F * hist1d_yZ_mumu = new TH1F("hist1dyZmumu", "mumuy", 100, -6, 6);
   
  TH1F * hist1d_etaZ_ee = new TH1F("hist1detaZee", "eeeta", 100, -6, 6);
  TH1F * hist1d_etaZ_mumu = new TH1F("hist1detaZmumu", "mumueta", 100, -6, 6);
   
   
  TH1F * hist1d_pTH_bbar = new TH1F("hist1dpTHbbar", "bbarpT", 100, 0 , 500.);
  TH1F * hist1d_thetaH_bbar = new TH1F("hist1dthetaHbbar", "bbartheta", 100, -4, 4);
  TH1F * hist1d_phiH_bbar = new TH1F("hist1dphiHbbar", "bbarphi", 100, -8, 8);
  TH1F * hist1d_etaH_bbar = new TH1F("hist1detaHbbar", "bbareta", 100, -6, 6);
  TH1F * hist1d_yH_bbar = new TH1F("hist1dyHbbar", "bbary", 100, -6, 6);
  
  TLorentzVector v1;
  
   
  int counter = 0;
  for (int iEvent = 0; iEvent < 20000; ++iEvent)
  {
    if (!pythia.next()) continue;
    for (int i = 0; i < pythia.event.size(); ++i)
    {	
	if(pythia.event[i].id() == 23) 
    {
    	int dau1 = pythia.event[i].daughter1();
    	int dau2 = pythia.event[i].daughter2();
    	if (pythia.event[dau1].id() == 13 and pythia.event[dau2].id() == -13) // Z0--> mu+ + mu-
    	{	
    		int j = i;
    		while(j>0)
    		{	
    			int mot1 = pythia.event[j].mother1();
    			if (pythia.event[mot1].id() != 23)//actual parent 
    			{	
				hist1d_pTZ_mumu->Fill(pythia.event[j].pT());
				hist1d_thetaZ_mumu->Fill(pythia.event[j].theta());
				hist1d_phiZ_mumu->Fill(pythia.event[j].phi());
				hist1d_etaZ_mumu->Fill(pythia.event[j].eta());
				hist1d_yZ_mumu->Fill(pythia.event[j].y());
				
				hist2d_pTZ_ee_mumu->Fill(pythia.event[j].pT(),pythia.event[j].pT());
    				counter += 1;
    				break;
    			}
    			else
    			{	 				
 				j = mot1;	
    			}
    		}
    	
    	}
    	
    	else if(pythia.event[dau1].id() == 11) // z0--> e+e- 
    		{
    		int j = i;
    		while(j>0)
    		{	
    			int mot1 = pythia.event[j].mother1();
    			if (pythia.event[mot1].id() != 23)
    			{	
    				hist1d_pTZ_ee->Fill(pythia.event[j].pT());
    				hist1d_thetaZ_ee->Fill(pythia.event[j].theta());
				hist1d_phiZ_ee->Fill(pythia.event[j].phi());
				hist1d_etaZ_ee->Fill(pythia.event[j].eta());
				hist1d_yZ_ee->Fill(pythia.event[j].y());
    				break;
    			}
    			else
    			{	 				
 				j = mot1;	
    			}
    			
    			}
    		}
    }
    else if(pythia.event[i].id() == 25) 
    {
    	int dau1 = pythia.event[i].daughter1();
    	int dau2 = pythia.event[i].daughter2();
    	if (pythia.event[dau1].id() == 5 and pythia.event[dau2].id() == -5) // H->b+bbar
    	{	
    		int j = i;
    		while(j>0)
    		{	
    			int mot1 = pythia.event[j].mother1();
    			if (pythia.event[mot1].id() != 25)//actual parent 
    			{	
				hist1d_pTH_bbar->Fill(pythia.event[j].pT());
				hist1d_thetaH_bbar->Fill(pythia.event[j].theta());
				hist1d_phiH_bbar->Fill(pythia.event[j].phi());
				hist1d_etaH_bbar->Fill(pythia.event[j].eta());
				hist1d_yH_bbar->Fill(pythia.event[j].y());
				
				//hist2d_pTZ_ee_mumu->Fill(pythia.event[j].pT(),pythia.event[j].pT());
    				counter += 1;
    				break;
    			}
    			else
    			{	 				
 				j = mot1;	
    			}
    		}
    	
    	}}
    
	else continue;
	}
  }
  
  
  
  
  pythia.stat();
  out_file->Write();
  out_file->Close();
  return 0;
  }
