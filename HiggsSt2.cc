#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {

  Pythia pythia;
  ofstream file1; file1.open("zdecaylepton.txt");
  ofstream file2; file2.open("zdecaye+e-.txt");
  pythia.readString("PDF:lepton = on");
  pythia.readString("Beams:idA =  11");  
  pythia.readString("Beams:idB = -11");
  pythia.readString("Beams:eCM = 10000.0");
  pythia.readString(" HiggsSM:ffbar2HZ = on");
  //pythia.readString(" HiggsSM:all = on");
  //pythia.readString("Next:numberShowEvent = 5");
  pythia.init();
  
 
  Hist pTZ1("pTZ1", 100, 0, 5000);
  int counter = 0;
  int counter2 = 0;
  for (int iEvent = 0; iEvent < 20000; ++iEvent) //20000 event 
  {
    if (!pythia.next()) continue;
    //int iZ = 0;

    for (int i = 0; i < pythia.event.size(); ++i)
    {	
	if(pythia.event[i].id() == 23) 
    {
    	int dau1 = pythia.event[i].daughter1();
    	int dau2 = pythia.event[i].daughter2();
    	if (pythia.event[dau1].isLepton() and pythia.event[dau2].isLepton())
    	{	
    		file1<<pythia.event[i].name()<<"-->"<<pythia.event[dau1].name()<< "+"<< pythia.event[dau2].name()
    		<<"==="<<pythia.event[dau1].id()<< "+"<< pythia.event[dau2].id()<<endl;
    		counter += 1;
    		
    		if (pythia.event[dau1].id() == 11)
    		{
    			//file2<<"Z0--->"<<pythia.event[dau1].name()<< "+"<< pythia.event[dau2].name()<<endl;
    			/*file2<<pythia.event[i].pT()<<endl;
    			pTZ1.fill( pythia.event[i].pT() );
    			counter2 += 1;*/
    			
    			int j = i;
    			while(j>0)
    			{	
    			int mot1 = pythia.event[j].mother1();
    			if (pythia.event[mot1].id() != 23)
    			{
 				file2 << pythia.event[i].pT() <<endl;
 				//file << pythia.event[i].name() <<endl;
    				pTZ1.fill( pythia.event[i].pT() );
    				counter2 += 1;
    				break;
    			}
    			else
    			{	 				
 				j = mot1;	
    			}
    			
    			}
    		}
    		
    	}
    }
	else continue;
	}
	
  }

  file1.close();
  file2.close();
  pythia.stat();
  cout<<counter<<"\n"<< counter2<<endl;
  cout<<pTZ1;
  return 0;
}
