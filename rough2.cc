#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {

  Pythia pythia;
  ofstream file1; file1.open("roughot.txt");
  pythia.readString("Beams:idA =  11");  
  pythia.readString("Beams:idB = -11");
  pythia.readString("Beams:eCM = 10000.0");
  pythia.readString(" HiggsSM:ffbar2HZ = on");
  //pythia.readString("Next:numberShowEvent = 5");
  pythia.init();
  
 
  Hist pTZ1("pTZ1", 100, 0, 5000);
  Hist pTZ2("pTZ2", 100, 0, 5000);
  int counter = 0;
  for (int iEvent = 0; iEvent < 10000; ++iEvent) //10000 event 
  {
    if (!pythia.next()) continue;
    //int iZ = 0;

    for (int i = 0; i < pythia.event.size(); ++i)
    {	
	if(pythia.event[i].id() == 23) 
    {
    	int dau1 = pythia.event[i].daughter1();
    	int dau2 = pythia.event[i].daughter2();
    	if (pythia.event[dau1].id() == 13 and pythia.event[dau2].id() == -13)
    	{	
		
    		int j = i;
    		while(j>0)
    		{	
    			int mot1 = pythia.event[j].mother1();
    			if (pythia.event[mot1].id() != 23)
    			{
 				file1 << pythia.event[i].name() <<endl;
    				pTZ1.fill( pythia.event[i].pT() );
    				counter += 1;
    				break;
    			}
    			else
    			{	 				
 				j = mot1;	
    			}
    		}
    		
    		/*file1 << pythia.event[i].name()<< "->"<< pythia.evenht[dau1].name() << "+"<< pythia.event[dau2].name() <<endl;
    		pTZ1.fill( pythia.event[i].pT() );
    		counter += 1;*/

    		
    	}
    }
	else continue;
	}
	
  }

  file1.close();
  pythia.stat();
  cout<<counter<<endl;
  cout<<pTZ1;
  return 0;
}
