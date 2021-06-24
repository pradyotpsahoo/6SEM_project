#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMath.h"


using namespace Pythia8;
int main()
 {
  Pythia pythia;
  pythia.readString("Beams:idA =  11");  
  pythia.readString("Beams:idB = -11");
  pythia.readString("Beams:eCM = 500.0");  
  pythia.readString(" HiggsSM:ffbar2HZ = on"); // Higgs-Stralung process
  
  pythia.init();
  
  TFile * out_file = new TFile("output_HiggsSt.root","RECREATE");
  
  
  //Angle between mu+ and mu- , e+ and e- in Z decay  
  TH1F * hist1d_angle_mumu = new TH1F("hist1d_Angle_mumu", "Z0 #rightarrow #mu_{+} + #mu_{-}", 100, 0., TMath::Pi());
  TH1F * hist1d_angle_ee = new TH1F("hist1d_Angle_ee", "Z0 #rightarrow e_{+} + e_{-}", 100, 0., TMath::Pi());
  
  
  //Mass invarient in  Z decay 
  TH1F * hist1d_mass_mumu = new TH1F("hist1d_mass_Zmumu", "Z0 #rightarrow #mu_{+} + #mu_{-}", 100, 50., 150.);
  TH1F * hist1d_mass_ee = new TH1F("hist1d_mass_Zee", "Z0 #rightarrow e_{+} + e_{-}", 100, 50., 150.);
  
  
  //Angle between Z and H in e- + e+ -> H + Z process 
  TH1F * hist1d_angle_ZH = new TH1F("hist1d_Angle_ZH", "e_{+} + e_{-} #rightarrow Z0 + H ", 300, 2.6 , 3.4);


  for (int iEvent = 0; iEvent < 20000; ++iEvent) // 20000 event generated
  {
    if (!pythia.next()) continue;
    for (int i = 0; i < pythia.event.size(); ++i)
    {	
	if(pythia.event[i].id() == 23) 
    {
    	int dau1 = pythia.event[i].daughter1();
    	int dau2 = pythia.event[i].daughter2();
    	if (pythia.event[dau1].id() == 13 and pythia.event[dau2].id() == -13 ) 
    	// Sort out the process : Z0--> mu+ + mu-
    	{	
    		int j = i;
    		while(j>0)
    		{	
    			int mot1 = pythia.event[j].mother1();

    			if (pythia.event[mot1].id() != 23)
    			//actual parent 
    			{	

    				//cout << pythia.event[j].name()<<"->" <<pythia.event[dau1].name() << " + " << pythia.event[dau2].name() << endl;		
    				TLorentzVector pmu1;
    				double pt_mu1 = pythia.event[dau1].pT();
    				double eta_mu1 = pythia.event[dau1].eta();
    				double phi_mu1 = pythia.event[dau1].phi();
    				double m_mu1 = pythia.event[dau1].mCalc(); 
    				pmu1.SetPtEtaPhiM(pt_mu1, eta_mu1, phi_mu1, m_mu1);
    				
    				TLorentzVector pmu2;
    				double pt_mu2 = pythia.event[dau2].pT();
    				double eta_mu2 = pythia.event[dau2].eta();
    				double phi_mu2 = pythia.event[dau2].phi();
    				double m_mu2 = pythia.event[dau2].mCalc(); 
    				pmu2.SetPtEtaPhiM(pt_mu2, eta_mu2, phi_mu2, m_mu2);
    				
    				double angle = pmu1.Angle(pmu2.Vect()); //Angle between mu+ and mu- 
				double mass = (pmu1 + pmu2).M(); // Invarient mass calculation 
				
				hist1d_angle_mumu -> Fill(angle); 
				hist1d_mass_mumu -> Fill(mass);
    				break;
    			}
    			else
    			{	 				
 				j = mot1;	
    			}
    		}
    	
    	}
    	
    	else if(pythia.event[dau1].id() == 11) 
    	// Sort out the process : Z0--> e+ + e-
    		{
    		int j = i;
    		while(j>0)
    		{	
    			int mot1 = pythia.event[j].mother1();
    			if (pythia.event[mot1].id() != 23)
    			{	
    				//cout << pythia.event[j].name()<<"->" <<pythia.event[dau1].name() << " + " << pythia.event[dau2].name() << endl;
				TLorentzVector pe1;
    				double pt_e1 = pythia.event[dau1].pT();
    				double eta_e1 = pythia.event[dau1].eta();
    				double phi_e1 = pythia.event[dau1].phi();
    				double m_e1 = pythia.event[dau1].mCalc(); 
    				pe1.SetPtEtaPhiM(pt_e1, eta_e1, phi_e1, m_e1);
    				
    				TLorentzVector pe2;
    				double pt_e2 = pythia.event[dau2].pT();
    				double eta_e2 = pythia.event[dau2].eta();
    				double phi_e2 = pythia.event[dau2].phi();
    				double m_e2 = pythia.event[dau2].mCalc(); 
    				pe2.SetPtEtaPhiM(pt_e2, eta_e2, phi_e2, m_e2);    			
    				
    				double angle = pe1.Angle(pe2.Vect()); //Angle between e+ and e- 
				double mass = (pe1 + pe2).M(); // invarient mass calculation
				
    				hist1d_angle_ee -> Fill(angle);
    				hist1d_mass_ee -> Fill(mass);
    				break;
    			}
    			else
    			{	 				
 				j = mot1;	
    			}
    			
    			}
    		}
    }
    else if(pythia.event[i].id() == 11) 
    {
    	int dau1 = pythia.event[i].daughter1();
    	int dau2 = pythia.event[i].daughter2();
    	if (pythia.event[dau1].id() == 25 and pythia.event[dau2].id() == 23)
    	//Sort out the process:  e- + e+ -> Z + H 
		{
    				//cout <<"->" <<pythia.event[dau1].name() << " + " << pythia.event[dau2].name() << endl;
    				TLorentzVector pH;
    				double pt_pH = pythia.event[dau1].pT();
    				double eta_pH = pythia.event[dau1].eta();
    				double phi_pH = pythia.event[dau1].phi();
    				double m_pH = pythia.event[dau1].mCalc(); 
    				pH.SetPtEtaPhiM(pt_pH, eta_pH, phi_pH, m_pH);
    				
    				TLorentzVector pZ;
    				double pt_pZ = pythia.event[dau2].pT();
    				double eta_pZ = pythia.event[dau2].eta();
    				double phi_pZ = pythia.event[dau2].phi();
    				double m_pZ = pythia.event[dau2].mCalc(); 
    				pZ.SetPtEtaPhiM(pt_pZ, eta_pZ, phi_pZ, m_pZ);    			
    				
    				double angle = pH.Angle(pZ.Vect()); // Angle between H and Zboson
    				hist1d_angle_ZH -> Fill(angle);
		}
	else continue;	
    	}
    
	else continue;
	}
  }
  
  pythia.stat();
  out_file->Write();
  out_file->Close();
  return 0;
  }
