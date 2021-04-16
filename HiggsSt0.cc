#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {

  Pythia pythia;
  ofstream file1; file1.open("data23decay.txt");
  ofstream file2; file2.open("data25decay.txt");

  pythia.readString("Beams:idA =  11");  
  pythia.readString("Beams:idB = -11");
  pythia.readString("Beams:eCM = 10000.0");
  pythia.readString(" HiggsSM:ffbar2HZ = on");
  //pythia.readString("Next:numberShowEvent = 5");
  pythia.init();
  
 
  Hist pTZ1("pTZ1", 100, 0, 5000);
  Hist pTZ2("pTZ2", 100, 0, 5000);
  //int counter = 0;
  for (int iEvent = 0; iEvent < 20000; ++iEvent) //20000 event 
  {
    if (!pythia.next()) continue;
    int iZ = 0;

    for (int i = 0; i < pythia.event.size(); ++i)
    {	
	if(pythia.event[i].id() == 23 and pythia.event[i].status() == -62 )//decay of zboson 
    	{
    	iZ = i;
    	pTZ1.fill( pythia.event[iZ].pT() );
    	file1<<pythia.event[iZ].pT()<<endl;
	}
	else if(pythia.event[i].id() == 25 and pythia.event[i].status() == -62)//decay of Higgs
    	{
    	iZ = i;
    	pTZ2.fill( pythia.event[iZ].pT() );
    	file2<<pythia.event[iZ].pT()<<endl;
	}
	else
	{
	continue;
	}
  }}
  file1.close();
  file2.close();
  
  pythia.stat();
  cout << pTZ1<<pTZ2;
  return 0;
}
