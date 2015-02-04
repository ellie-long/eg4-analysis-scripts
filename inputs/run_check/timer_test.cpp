#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <time.h>
#include <math.h>
using namespace std;


void timer_test(){

	TStopwatch time;
	int a;
	for (int i=0; i<1000000; i++)
	{
		a = i+1;
	}

	Double_t someTime  = time.RealTime(); time.Continue();
	cout << "Elapsed some time:              " << someTime  << " seconds" << endl;
	for (int i=0; i<1000000; i++)
	{
		a = i+1;
	}
	Double_t totTime  = time.RealTime();

	int totTimeDays   = floor(totTime/60/60/24);
        int totTimeHours     = fmod((totTime/60/60.0),24);
        int totTimeMinutes   = fmod((totTime/60.0),60);
        double totTimeSeconds   = totTime - 24*60*60*totTimeDays - 60*60*totTimeHours - 60*totTimeMinutes;

	cout << "Elapsed total time:              " << totTimeDays << " Days, " << totTimeHours << " Hours, " << totTimeMinutes << " Min., " << totTimeSeconds << " Sec." << endl;
	return;

}












