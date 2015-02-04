#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <time.h>
#include <math.h>
using namespace std;


void run_check(){

	TStopwatch allTime;
	TString filePrefix = "/volatile/clas/claseg4/pass2/";
	double e_beam;
	TString e_beamStr;
	TString target;
	TString targetStr;
	int runNumber;
	int endRunNumber;
	TString checkAll;
	TString debugStr;
	bool debug = false;
	int sector = 1;
	int maxSector = 7;

	cout << "Are you debugging code? ";
	cin >> debugStr;
	if ((debugStr == "yes") || (debugStr == "Yes") || (debugStr == "y") || (debugStr =="Y")) {cout << "Entering Debug Mode..." << endl; debug = true;}
	else {cout << "Entering Normal Mode..." << endl; debug = false;}

	if (!debug)
	{
		cout << "Enter beam energy (1.1, 1.3, 1.5, 2.0, 2.2, 3.0): ";
		cin >> e_beam;
//		cout << "Beam energy: " << e_beam << endl;

		cout << "Enter target type (c12, nh3, nd3, empty): ";
		cin >> target;

		cout << "Check all runs for " << e_beam << " GeV, " << target << "? ";
		cin >> checkAll;

	}
	else 
	{
		e_beam=1.1; 
		target="nh3"; 
		checkAll="y"; 
//		maxSector = 2;
		sector = 6;
	}

	if (e_beam==1.1) {e_beamStr = "1p1gev/";}
	else if (e_beam==1.3) {e_beamStr = "1p3gev/";}
	else if (e_beam==1.5) {e_beamStr = "1p5gev/";}
	else if (e_beam==2.0) {e_beamStr = "2gev/";}
	else if (e_beam==2.2) {e_beamStr = "2p2gev/";}
	else if (e_beam==3.0) {e_beamStr = "3gev/";}
	else {cout << "ERR: Incorrect input." << endl; return;}
	filePrefix += e_beamStr;

//	cout << "Target: " << target << endl;
	if (target=="c12") {targetStr="carb/";}
	else if (target=="nh3") {targetStr="nh3/";}
	else if (target=="nd3") {targetStr="nd3/";}
	else if (target=="empty") {targetStr="emp/";}
	else {cout << "ERR: Incorrect input." << endl; return;}
	filePrefix += targetStr;
	filePrefix += "root/root_";


	if (!debug && e_beam==1.1 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 52054; endRunNumber = 52295;}
	else if (!debug && e_beam==1.3 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 51181; endRunNumber = 52040;}
	else if (!debug && e_beam==1.5 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 50626; endRunNumber = 50671;}
	else if (!debug && e_beam==2.0 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 51507; endRunNumber = 51867;}
	else if (!debug && e_beam==2.2 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 50998; endRunNumber = 51154;}
	else if (!debug && e_beam==3.0 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 50770; endRunNumber = 50982;}
	else if (debug) {cout << "Rad" << endl; runNumber = 52080; endRunNumber = 52080;}
	else
	{
		cout << "Enter beginning run number: ";
		cin >> runNumber;
		cout << "Enter ending run number: ";
		cin >> endRunNumber;
	}

	cout << "Beginning run number: " << runNumber << endl;	
	cout << "Ending run number:    " << endRunNumber << endl;	

	for (int i=runNumber; i<(endRunNumber+1); i++)
	{
		for (int j=sector; j<maxSector; j++)
		{
			check_run(i, e_beam, targetStr, target, filePrefix, j, debug, allTime);
		}
	}	

	cout << "All done!" << endl;
	return;
}


void get_run_info(int runNumber){

	TStopwatch allTime;
	TString filePrefix = "/volatile/clas/claseg4/pass2/";
	double e_beam;
	TString e_beamStr;
	TString target;
	TString targetStr;
	TString checkAll;
	TString debugStr;
	bool debug = false;
	int sector = 1;
	int maxSector = 7;

	cout << "Are you debugging code? ";
	cin >> debugStr;
	if ((debugStr == "yes") || (debugStr == "Yes") || (debugStr == "y") || (debugStr =="Y")) {cout << "Entering Debug Mode..." << endl; debug = true;}
	else {cout << "Entering Normal Mode..." << endl; debug = false;}

	if (!debug)
	{
		cout << "Enter beam energy (1.1, 1.3, 1.5, 2.0, 2.2, 3.0): ";
		cin >> e_beam;
//		cout << "Beam energy: " << e_beam << endl;

		cout << "Enter target type (c12, nh3, nd3, empty): ";
		cin >> target;

		cout << "Check all runs for " << e_beam << " GeV, " << target << "? ";
		cin >> checkAll;

	}
	else 
	{
		e_beam=1.1; 
		target="nh3"; 
		checkAll="y"; 
//		maxSector = 2;
		sector = 6;
	}

	if (e_beam==1.1) {e_beamStr = "1p1gev/";}
	else if (e_beam==1.3) {e_beamStr = "1p3gev/";}
	else if (e_beam==1.5) {e_beamStr = "1p5gev/";}
	else if (e_beam==2.0) {e_beamStr = "2gev/";}
	else if (e_beam==2.2) {e_beamStr = "2p2gev/";}
	else if (e_beam==3.0) {e_beamStr = "3gev/";}
	else {cout << "ERR: Incorrect input." << endl; return;}
	filePrefix += e_beamStr;

//	cout << "Target: " << target << endl;
	if (target=="c12") {targetStr="carb/";}
	else if (target=="nh3") {targetStr="nh3/";}
	else if (target=="nd3") {targetStr="nd3/";}
	else if (target=="empty") {targetStr="emp/";}
	else {cout << "ERR: Incorrect input." << endl; return;}
	filePrefix += targetStr;
	filePrefix += "root/root_";


	if (!debug && e_beam==1.1 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 52054; endRunNumber = 52295;}
	else if (!debug && e_beam==1.3 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 51181; endRunNumber = 52040;}
	else if (!debug && e_beam==1.5 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 50626; endRunNumber = 50671;}
	else if (!debug && e_beam==2.0 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 51507; endRunNumber = 51867;}
	else if (!debug && e_beam==2.2 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 50998; endRunNumber = 51154;}
	else if (!debug && e_beam==3.0 && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 50770; endRunNumber = 50982;}
	else if (debug) {cout << "Rad" << endl; runNumber = 52080; endRunNumber = 52080;}
	else
	{
		cout << "Enter beginning run number: ";
		cin >> runNumber;
		cout << "Enter ending run number: ";
		cin >> endRunNumber;
	}

	cout << "Beginning run number: " << runNumber << endl;	
	cout << "Ending run number:    " << endRunNumber << endl;	

	for (int i=runNumber; i<(endRunNumber+1); i++)
	{
		for (int j=sector; j<maxSector; j++)
		{
			check_run(i, e_beam, targetStr, target, filePrefix, j, debug, allTime);
		}
	}	

	cout << "All done!" << endl;
	return;
}


void check_run(int runNumber, double e_beam, TString targetStr, TString target, TString filePrefix, int sector, bool debug, TStopwatch allTime)
{
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
	cout << "Running check_run for Run # " << runNumber << ", Sector " << sector << "..." << endl;

	TStopwatch thisRunTime;
	TString fileName;
	TChain* chain = new TChain("h10");
	bool fileExists = false;
	int aMax;	
	char e_beamStr[3];
	
	sprintf(e_beamStr,"%.1f",e_beam);

	TString title = "Beam Energy = ";
	title += e_beamStr;
	title += " GeV, Target = ";
	title += target;
	title += ", Run # ";
	title += runNumber;
	title += ", Sector ";
	title += sector;
	
	TString cuts = "id==11 && dc_sect==";
	cuts += sector;

	if (debug) {aMax = 2; cout << "Debug Mode On" << endl;}
	else {aMax = 1000; cout << "Debug Mode Off" << endl;}

	// Beam energies below are taken from Xiaochao Zheng's EG4 analysis note:
	// "Double- and Target Spin Asymmetries in
	//  Pion Electro-production from Polarized NH3 Targets"
	if (runNumber < 50724) {e_beam = 1.5190;}
	else if (runNumber > 50723 && runNumber < 50989) {e_beam = 2.9990;}
	else if (runNumber > 50988 && runNumber < 51155) {e_beam = 2.2596;}
	else if (runNumber > 51154 && runNumber < 51407) {e_beam = 1.3390;}
	else if (runNumber > 51406 && runNumber < 51487) {e_beam = 1.3376;}
	else if (runNumber > 51486 && runNumber < 51791) {e_beam = 1.9889;}
	else if (runNumber > 51790 && runNumber < 51871) {e_beam = 1.9932;}
	else if (runNumber > 51874 && runNumber < 52041) {e_beam = 1.3369;}
	else if (runNumber > 52050 && runNumber < 52296) {e_beam = 1.0539;}
	else {cout << "ERR: Run number has no known beam energy. Skipping run." << endl; return;}



	for (int a=0; a<aMax; a++)
	{
		fileName = filePrefix;
		fileName += runNumber;
		fileName += "_pass2.a";
		if (a < 10) {fileName += "0";}
		fileName += a;
		fileName += ".root";
		ifstream ifile(fileName);
		if (ifile)
		{
			cout << "Adding file to chain: " << fileName << endl;
			chain->Add(fileName);
			TFile file(fileName);
			fileExists = true;
		}
		else
		{
			cout << "File " << fileName << " does not exist. Ending here." << endl;
			a=999999999;
		}
	}
//	}

	if (fileExists)
	{
		gStyle->SetPalette(1);

		TCanvas *c1 = new TCanvas("c1","Run Check",1100,1100); //x,y
		pad0  =  new  TPad("pad0","pad0",0.0000,0.9500,1.0000,1.0000,0,0,0);
		pad1  =  new  TPad("pad1","pad1",0.0000,0.6333,0.3333,0.9500,0,0,0);
		pad2  =  new  TPad("pad2","pad2",0.3333,0.6333,0.6666,0.9500,0,0,0);
		pad3  =  new  TPad("pad3","pad3",0.6666,0.6333,1.0000,0.9500,0,0,0);
		pad4  =  new  TPad("pad4","pad4",0.0000,0.3166,0.3333,0.6333,0,0,0);
		pad5a =  new  TPad("pad5a","pad5a",0.3333,0.4749,0.6666,0.6333,0,0,0);
		pad5b =  new  TPad("pad5b","pad5b",0.3333,0.3166,0.6666,0.4749,0,0,0);
		pad6  =  new  TPad("pad6","pad6",0.6666,0.3166,1.0000,0.6333,0,0,0);
		pad7  =  new  TPad("pad7","pad7",0.0000,0.0000,0.3333,0.3166,0,0,0);
		pad8  =  new  TPad("pad8","pad8",0.3333,0.0000,0.6666,0.3166,0,0,0);
		pad9  =  new  TPad("pad9","pad9",0.6666,0.0000,1.0000,0.3166,0,0,0);
		pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5a->Draw();pad5b->Draw();
		pad6->Draw();pad7->Draw();pad8->Draw();pad9->Draw();pad0->Draw();


	
		pad0->cd();
		TPaveLabel *titleBox = new TPaveLabel(0.1,0.1,0.9,0.9,title);
		titleBox->Draw();
		titleBox->SetFillColor(kWhite);
		pad0->Update();

		pad1->cd();
		TString titleRaster = "Raster x:y for Run # ";
		titleRaster += runNumber;
		cout << "Drawing " << titleRaster << "..."  << endl;
		chain->Draw("raster_x:raster_y>>raster(100,2000,6000,100,2000,6000)", cuts, "");
		raster->SetTitle(titleRaster);
		raster->SetStats(kFALSE);
		raster->Draw("COLZ");
		pad1->Update();

		pad2->cd();
		TString titleTarget = "Vertex z for Run # ";
		titleTarget += runNumber;
		cout << "Drawing Vertex z..." << endl;
		chain->Draw("dc_vz>>vertZ(400,-800,800)", cuts, "");
		vertZ->SetTitle(titleTarget);
		vertZ->Draw();
		pad2->Update();

		pad3->cd();
		TString titleVThPh = "Vertex th:ph for Run # ";
		titleVThPh += runNumber;
		cout << "Drawing " << titleVThPh << "..." << endl;
		chain->Draw("atan(dc_vx/dc_vy)*180/3.14159:acos(dc_vz/sqrt(dc_vx*dc_vx+dc_vy*dc_vy+dc_vz*dc_vz))*180/3.14159>>vThPh(300,0,180,300,-90,90)", cuts, "");
		vThPh->SetTitle(titleVThPh);
		vThPh->SetStats(kFALSE);
		vThPh->Draw("COLZ");
		pad3->Update();

		pad4->cd();
		TString titlebeamE = "Beam Energy for Run # ";
		titlebeamE += runNumber;
		cout << "Drawing " << titlebeamE << "..." << endl;
		TString drawbeamE = "";
		drawbeamE += e_beam;
		drawbeamE += ">>beamE(100,0,4)";
		chain->Draw(drawbeamE, cuts, "");
		beamE->SetTitle(titlebeamE);
	//	beamE->SetStats(kFALSE);
		beamE->Draw();
		pad4->Update();

		pad5a->cd();
		TString titleRThNphe = "Reconstructed Theta:nphe for Run # ";
		titleRThNphe += runNumber;
		cout << "Drawing " << titleRThNphe << "..."  << endl;
		chain->Draw("dc_ccth:nphe>>rThNphe(100,0,500,100,0,60)", cuts, "");
		rThNphe->SetTitle(titleRThNphe);
		rThNphe->SetStats(kFALSE);
		rThNphe->Draw("COLZ");
		pad5a->Update();

		pad5b->cd();
		TString titleRPhNphe = "Reconstructed Phi:nphe for Run # ";
		titleRPhNphe += runNumber;
		cout << "Drawing " << titleRPhNphe << "..."  << endl;
		chain->Draw("dc_ccph:nphe>>rPhNphe(100,0,500,100,-30,30)", cuts, "");
		rPhNphe->SetTitle(titleRPhNphe);
		rPhNphe->SetStats(kFALSE);
		rPhNphe->Draw("COLZ");
		pad5b->Update();

		pad6->cd();
		TString titleNu = "Nu for Run # ";
		titleNu += runNumber;
		cout << "Drawing " << titleNu << "..." << endl;
		TString drawNu = "";
		drawNu += e_beam;
		drawNu += "-p>>histNu(100,-0.2,1.1)";
		chain->Draw(drawNu, cuts, "");
		histNu->SetTitle(titleNu);
	//	histNu->SetStats(kFALSE);
		histNu->Draw();
		pad6->Update();

		pad7->cd();
		TString titleW2 = "W^2 for Run # ";
		titleW2 += runNumber;
		cout << "Drawing " << titleW2 << "..." << endl;
		TString drawW2 = "0.938*0.938+2*0.938*(";
		drawW2 += e_beam;
		drawW2 += "-p)-4*";
		drawW2 += e_beam;
		drawW2 += "*p*(sin(dc_ccth*3.14159/180/2)^2)>>histW2(100,0,4)";
		chain->Draw(drawW2, cuts, "");
		histW2->SetTitle(titleW2);
	//	histW2->SetStats(kFALSE);
		histW2->Draw();
		pad7->Update();

		pad8->cd();
		TString titleQ2 = "Q^2 for Run # ";
		titleQ2 += runNumber;
		cout << "Drawing " << titleQ2 << "..." << endl;
		TString drawQ2 = "4*";
		drawQ2 += e_beam;
		drawQ2 += "*p*(sin(dc_ccth*3.14159/180/2)^2)>>histQ2(400,0,0.5)";
		chain->Draw(drawQ2, cuts, "");
		histQ2->SetTitle(titleQ2);
		histQ2->Draw();
		pad8->Update(); 

		pad9->cd();
//		pad9->SetLogy();
		TString titlex = "Bjorken x ";
		titlex += " (x=Q^2/[2m*nu]) for Run # ";
		titlex += runNumber;
		cout << "Drawing " << titlex << "..." << endl;
		TString drawx = "4*";
		drawx += e_beam;
		drawx += "*p*(sin(dc_ccth*3.14159/180/2)^2)/(2*0.938*(";
		drawx += e_beam;
		drawx += "-p))>>histx(400,0,3)";
		chain->Draw(drawx, cuts, "");
		histx->SetTitle(titlex);
		histx->Draw();
		pad9->Update();

	
		TString imagename = "./Run_Checks/Run_Check_for_Sector_";
		imagename += sector;
		imagename += "_Run_";
		imagename += runNumber;
		imagename += ".png";
		c1->Print(imagename);
	}
	else {cout << "There is no file for Run # " << runNumber << endl;}

	if (debug)
	{
		TString exits;
		cout << "Are you ready to finish?" << endl;
		cin >> exits;
	}

	Double_t thisTime = thisRunTime.RealTime(); thisRunTime.Reset();
	Double_t totTime  = allTime.RealTime(); allTime.Continue();
	
	int thisTimeDays		= floor(thisTime/60/60/24);
	int thisTimeHours	= fmod((thisTime/60/60.0),24);
	int thisTimeMinutes	= fmod((thisTime/60.0),60);
	double thisTimeSeconds	= thisTime - 24*60*60*thisTimeDays - 60*60*thisTimeHours - 60*thisTimeMinutes;

	int totTimeDays		= floor(totTime/60/60/24);
	int totTimeHours	= fmod((totTime/60/60.0),24);
	int totTimeMinutes	= fmod((totTime/60.0),60);
	double totTimeSeconds	= totTime - 24*60*60*totTimeDays - 60*60*totTimeHours - 60*totTimeMinutes;


	cout << "Elapsed time for current sector: " << thisTimeDays << " Days, " << thisTimeHours << " Hours, " << thisTimeMinutes << " Min., " << thisTimeSeconds << " Sec." << endl;
	cout << "Elapsed total time:              " << totTimeDays << " Days, " << totTimeHours << " Hours, " << totTimeMinutes << " Min., " << totTimeSeconds << " Sec." << endl;
	cout << "Finished check_run for Run # " << runNumber << "!" << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

	return;

}












