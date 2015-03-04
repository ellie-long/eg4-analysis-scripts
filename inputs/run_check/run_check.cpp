#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <time.h>
#include <math.h>
using namespace std;

void run_check()
{
	TStopwatch runAllTime;
	cout << "Running run_check()..." << endl;

	// Set debug mode
	bool debug = true;
//	bool debug = false;

	// Set verbose mode
//	bool verbose = true;
	bool verbose = false;

	TString outputStr = "";
	bool outputFiles = true;

	if (debug) 
	{
		cout << "Debug Mode On" << endl;
		cout << "Make output files? ";
		cin >> outputStr;
		if (outputStr=="y" || outputStr=="yes" || outputStr=="Y" || outputStr=="Yes" || outputStr=="YES") {outputFiles = true;}
		else {cout << "Not writing output files" << endl; outputFiles = false;}
		cout << "outputFiles = " << outputFiles << endl;
	}
	else {cout << "Debug Mode Off" << endl;}
	if (verbose) {cout << "Verbose Mode On" << endl;}
	else {cout << "Verbose Mode Off" << endl;}

	// Get runNumber from input.file
	string line = "";
	ifstream runNumberInputFile ("./input.file");
	getline(runNumberInputFile, line);
	int inRunNumber = atoi(line.c_str());
	int runNumber = inRunNumber;
	cout << "runNumber: " << runNumber << endl;

	// Make output folder structure
	if (outputFiles) {make_folders();}

	// Gets run information and passes it to the main
	// workhorse script check_run
	get_run_info(runNumber, runAllTime, debug, verbose, outputFiles);

	// Get script run time
	Double_t totTime  = runAllTime.RealTime(); runAllTime.Continue();
	int totTimeDays		= floor(totTime/60/60/24);
	int totTimeHours	= fmod((totTime/60/60.0),24);
	int totTimeMinutes	= fmod((totTime/60.0),60);
	double totTimeSeconds	= totTime - 24*60*60*totTimeDays - 60*60*totTimeHours - 60*totTimeMinutes;
	cout << "Elapsed total time:              " << totTimeDays << " Days, " << totTimeHours << " Hours, " << totTimeMinutes << " Min., " << totTimeSeconds << " Sec." << endl;

	cout << "Finished with run_check()!" << endl;
	gROOT->ProcessLine(".q");
	return;
	cout << "Uh-oh? I shouldn't be here..." << endl;
}


// Gets run information and passes it to the workhorse script check_run
void get_run_info(int runNumber, TStopwatch runInfoTime, bool debug, bool verbose, bool outputFiles)
{
	cout << "============================================================" << endl;
	cout << "Running get_run_info(" << runNumber << ",runInfoTime)..." << endl;

	// Gets file prefix for current runNumber
	TString findCmd = "find /volatile/clas/claseg4/pass2 -name 'root_";
	findCmd += runNumber;
	findCmd += "_pass2.a*root' -print -quit";
//	findCmd += "_pass2.a00.root'";
	TString fullFile = gSystem->GetFromPipe(findCmd);
	TString filePrefix = fullFile.Remove(fullFile.Length()-25,fullFile.Length());

	double e_beam;
//	TString e_beamStr;
	TString target;
	TString targetStr;
	TString checkAll;
	int sector = 0;
	int maxSector = 7;

	// Makes debug mode take far less time
	if (debug) {sector = 0; maxSector = 1;}

	// Get information based on file placement
	if      (fullFile.Contains("1p1gev")) {e_beam = 1.1;}
	else if (fullFile.Contains("1p3gev")) {e_beam = 1.3;}
	else if (fullFile.Contains("1p5gev")) {e_beam = 1.5;}
	else if (fullFile.Contains("2gev"))   
	{
		e_beam = 2.0;
		if (fullFile.Contains("2p2gev")) {e_beam = 2.2;}
	}
	else if (fullFile.Contains("3gev"))   {e_beam = 3.0;}
	else {cout << "ERR: Incorrect input." << endl; return;}

	if (fullFile.Contains("carb"))     {target = "carb";}
	else if (fullFile.Contains("nh3")) {target = "nh3";}
	else if (fullFile.Contains("nd3")) {target = "nd3";}
	else if (fullFile.Contains("emp")) {target = "emp";}
	else {cout << "ERR: Incorrect input." << endl; return;}

	char e_beamStr[3];
	// Stops e_beamStr from being more than 1 decimal place long
	sprintf(e_beamStr,"%.1f",e_beam);

	TString outputRootStr = "plots_";
	outputRootStr += e_beamStr;
	outputRootStr += "_GeV_";
	outputRootStr += target;
	outputRootStr += "_run_";
	outputRootStr += runNumber;
	outputRootStr += ".root";

	cout << "Output Root File: " << outputRootStr << endl;

	TFile *outputRoot = new TFile(outputRootStr, "RECREATE");
	outputRoot->Close();


	// Run main workhorse script for each sector
	for (int j=sector; j<maxSector; j++)
	{
		check_run(runNumber, e_beam, target, filePrefix, outputRootStr, j, debug, verbose, outputFiles, runInfoTime);
	}

	cout << "Finished with get_run_info(" << runNumber << ",runInfoTime," << debug << "," << verbose << ")!" << endl;
	cout << "============================================================" << endl;
	return;
}

// Main workhorse script
void check_run(int runNumber, double e_beam, TString target, TString filePrefix, TString outputRootStr, int sector, bool debug, bool verbose, bool outputFiles, TStopwatch allTime)
{
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
	cout << "Running check_run for Run # " << runNumber << ", Sector " << sector << "..." << endl;

	TStopwatch thisRunTime;
	TString fileName;
	TChain* chain = new TChain("h10");
	bool fileExists = false;
	int aMax;	
	char e_beamStr[3];
	double eBeamChk = e_beam;
	char actualEBeam[6];	
	// Stops e_beamStr from being more than 1 decimal place long
	sprintf(e_beamStr,"%.1f",e_beam);

	
	// Define cuts
	TString basicCuts = "id==11";
	TString sectorCuts = "&& dc_sect==";
	sectorCuts += sector;
	if (sector == 0) {sectorCuts="";}
	TString cuts = basicCuts;
	cuts += sectorCuts;
	

	cout << "Cuts used: \"" << cuts << "\"" << endl;


	if (debug) 
	{
		cout << "Debug Mode On" << endl;
		cout << "Enter aMax: ";
		cin >> aMax;
//		aMax = 2; 
		cout << "aMax = " << aMax << endl;
	}
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
	sprintf(actualEBeam,"%.4f",e_beam);

	TString title10  = "Gen. Beam Energy = ";
	title10 	+= e_beamStr;
	title10 	+= " GeV, Target = ";
	title10 	+= target;
	TString title11  = "Run # ";
	title11 	+= runNumber;
	title11 	+= ", Sector ";
	title11 	+= sector;
	title11		+= ", Ebeam = ";
	title11 	+= actualEBeam; 
	title11 	+= " GeV";

	TString title20  = "Cuts: ";
	title20		+= cuts;
	TString title21  = "";


	// Adds root files to chain
	for (int a=0; a<aMax; a++)
	{
		fileName = filePrefix;
		fileName += "root_";
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
			if (verbose) {cout << "File " << fileName << " does not exist. Ending here." << endl;}
//			a=999999999;
		}
	}
	file.Close();

	TFile *outputRoot = new TFile(outputRootStr, "UPDATE");
//	outputRoot.Open();
	// Makes and displays kinematic variables
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
		pad9b =  new  TPad("pad9b","pad9b",0.6666,0.0000,1.0000,0.1583,0,0,0);
		pad9a =  new  TPad("pad9a","pad9a",0.6666,0.1583,1.0000,0.3166,0,0,0);
		pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5a->Draw();pad5b->Draw();
		pad6->Draw();pad7->Draw();pad8->Draw();pad9a->Draw();pad9b->Draw();pad0->Draw();


	
		pad0->cd();
//		TPaveLabel *titleBox = new TPaveLabel(0.1,0.1,0.9,0.9,title1);
		TPaveText *titleBox1 = new TPaveText(0.01,0.05,0.5,1.0);
		TPaveText *titleBox2 = new TPaveText(0.51,0.05,0.99,1.0);
		titleBox1->AddText(title10);
		titleBox1->AddText(title11);
		titleBox2->AddText(title20);
		titleBox2->AddText(title21);
		titleBox1->Draw();
		titleBox2->Draw();
		titleBox1->SetFillColor(kWhite);
		titleBox2->SetFillColor(kWhite);	
		TString titleBox1Write = "titleBox_sec_";
		titleBox1Write += sector;
		TString titleBox2Write = "cutBox_sec_";
		titleBox2Write += sector;
		titleBox1->SetName(titleBox1Write); titleBox1->Write(titleBox1Write,TObject::kWriteDelete);
		titleBox2->SetName(titleBox2Write); titleBox2->Write(titleBox2Write,TObject::kWriteDelete);
		pad0->Update();

		pad1->cd();
		TString titleRaster = "Raster x:y for Run # ";
		titleRaster += runNumber;
		cout << "Drawing " << titleRaster << "..."  << endl;
		TString rasterCmd = "raster_x:raster_y>>raster";
		if (eBeamChk==1.5) 	{rasterCmd += "(100,1500,6500,100,1500,6500)";}
		else if (eBeamChk==2.0)	{rasterCmd += "(100,1000,7000,100,1000,7000)";}
		else if (eBeamChk==2.2)	{rasterCmd += "(100,1000,7000,100,1000,7000)";}
		else if (eBeamChk==3.0)	{rasterCmd += "(100,0,8500,100,0,8500)";}
		else 		   	{rasterCmd += "(100,2000,6000,100,2000,6000)";}
		chain->Draw(rasterCmd, cuts, "");
		raster->SetTitle(titleRaster);
		raster->SetStats(kFALSE);
		raster->Draw("COLZ");
		TString rasterWrite = "raster_sec_"; rasterWrite += sector;
		raster->SetName(rasterWrite); raster->Write(rasterWrite,TObject::kWriteDelete);
		pad1->Update();

		pad2->cd();
		TString titleTarget = "Vertex z for Run # ";
		titleTarget += runNumber;
		cout << "Drawing Vertex z..." << endl;
		chain->Draw("dc_vz>>vertZ(400,-800,800)", cuts, "");
		vertZ->SetTitle(titleTarget);
		vertZ->Draw();
		TString vertZWrite = "vertZ_sec_"; vertZWrite += sector;
		vertZ->SetName(vertZWrite); vertZ->Write(vertZWrite,TObject::kWriteDelete);
		pad2->Update();

		pad3->cd();
		TString titleVThPh = "Vertex th:ph for Run # ";
		titleVThPh += runNumber;
		cout << "Drawing " << titleVThPh << "..." << endl;
		chain->Draw("atan2(cy,cx)*180/3.14159:acos(cz/sqrt(cx*cx+cy*cy+cz*cz))*180/3.14159>>vThPh(300,0,50,300,-180,180)", cuts, "");
		vThPh->SetTitle(titleVThPh);
		vThPh->SetStats(kFALSE);
		vThPh->Draw("COLZ");
		TString vThPhWrite = "vThPh_sec_"; vThPhWrite += sector;
		vThPh->SetName(vThPhWrite); vThPh->Write(vThPhWrite,TObject::kWriteDelete);
		pad3->Update();

		pad4->cd();
/*		TString titlebeamE = "Beam Energy for Run # ";
		titlebeamE += runNumber;
		cout << "Drawing " << titlebeamE << "..." << endl;
		TString drawbeamE = "";
		drawbeamE += e_beam;
		drawbeamE += ">>beamE(100,0,4)";
		chain->Draw(drawbeamE, cuts, "");
		beamE->SetTitle(titlebeamE);
	//	beamE->SetStats(kFALSE);
		beamE->Draw();
*/
		TString titleRThPh = "Reconstructed (dc_cc) th:ph for Run # ";
		titleRThPh += runNumber;
		cout << "Drawing " << titleRThPh << "..." << endl;
		chain->Draw("dc_ccth:dc_ccph>>rThPh(100,-60,60,100,0,60)", cuts, "");
		rThPh->SetTitle(titleRThPh);
		rThPh->SetStats(kFALSE);
		rThPh->Draw("COLZ");
		TString rThPhWrite = "rThPh_sec_"; rThPhWrite += sector;
		rThPh->SetName(rThPhWrite); rThPh->Write(rThPhWrite,TObject::kWriteDelete);
		pad4->Update();

		pad5a->cd();
		TString titleRThNphe = "Reconstructed Theta:nphe for Run # ";
		titleRThNphe += runNumber;
		cout << "Drawing " << titleRThNphe << "..."  << endl;
		chain->Draw("dc_ccth:nphe>>rThNphe(100,0,500,100,0,60)", cuts, "");
		rThNphe->SetTitle(titleRThNphe);
		rThNphe->SetStats(kFALSE);
		rThNphe->Draw("COLZ");
		TString rThNpheWrite = "rThNphe_sec_"; rThNpheWrite += sector;
		rThNphe->SetName(rThNpheWrite); rThNphe->Write(rThNpheWrite,TObject::kWriteDelete);
		pad5a->Update();

		pad5b->cd();
		TString titleRPhNphe = "Reconstructed Phi:nphe for Run # ";
		titleRPhNphe += runNumber;
		cout << "Drawing " << titleRPhNphe << "..."  << endl;
		chain->Draw("dc_ccph:nphe>>rPhNphe(100,0,500,100,-30,30)", cuts, "");
		rPhNphe->SetTitle(titleRPhNphe);
		rPhNphe->SetStats(kFALSE);
		rPhNphe->Draw("COLZ");
		TString rPhNpheWrite = "rPhNphe_sec_"; rPhNpheWrite += sector;
		rPhNphe->SetName(rPhNpheWrite); rPhNphe->Write(rPhNpheWrite,TObject::kWriteDelete);
		pad5b->Update();

		pad6->cd();
		TString titleNu = "Nu for Run # ";
		titleNu += runNumber;
		cout << "Drawing " << titleNu << "..." << endl;
		TString drawNu = "";
		drawNu += e_beam;
		drawNu += "-p>>histNu(100,-0.2,";
		drawNu += e_beamStr;
		drawNu += ")";
		chain->Draw(drawNu, cuts, "");
		histNu->SetTitle(titleNu);
		histNu->SetStats(kFALSE);
		histNu->Draw();
		TString histNuWrite = "histNu_sec_"; histNuWrite += sector;
		histNu->SetName(histNuWrite); histNu->Write(histNuWrite,TObject::kWriteDelete);
		pad6->Update();

		pad7->cd();
		TString titleW2 = "W^2 for Run # ";
		titleW2 += runNumber;
		cout << "Drawing " << titleW2 << "..." << endl;
		TString drawW2 = "0.938*0.938+2*0.938*(";
		drawW2 += e_beam;
		drawW2 += "-p)-4*";
		drawW2 += e_beam;
		drawW2 += "*p*(sin(dc_ccth*3.14159/180/2)^2)>>histW2";
		if (eBeamChk==2.2) 	{drawW2 += "(100,0,5)";}
		else if (eBeamChk==3.0) {drawW2 += "(100,0,7)";}
		else 		   	{drawW2 += "(100,0,4)";}
		chain->Draw(drawW2, cuts, "");
		histW2->SetTitle(titleW2);
		histW2->SetStats(kFALSE);
		histW2->Draw();
		TString histW2Write = "histW2_sec_"; histW2Write += sector;
		histW2->SetName(histW2Write); histW2->Write(histW2Write,TObject::kWriteDelete);
		pad7->Update();

		pad8->cd();
		TString titleQ2 = "Q^2 for Run # ";
		titleQ2 += runNumber;
		cout << "Drawing " << titleQ2 << "..." << endl;
		TString drawQ2 = "4*";
		drawQ2 += e_beam;
		drawQ2 += "*p*(sin(dc_ccth*3.14159/180/2)^2)>>histQ2";
		if (eBeamChk==2.0) 	{drawQ2 += "(400,0.0001,1.0)";}
		else if (eBeamChk==2.2) {drawQ2 += "(400,0.0001,1.5)";}
		else if (eBeamChk==3.0) {drawQ2 += "(400,0.0001,3.0)";}
		else 		   	{drawQ2 += "(400,0.0001,0.5)";}
		chain->Draw(drawQ2, cuts, "");
		histQ2->SetTitle(titleQ2);
		histQ2->Draw();
		TString histQ2Write = "histQ2_sec_"; histQ2Write += sector;
		histQ2->SetName(histQ2Write); histQ2->Write(histQ2Write,TObject::kWriteDelete);
		pad8->Update(); 

		pad9a->cd();
//		pad9->SetLogy();
		TString titlex = "Bjorken x (1-3) for Run # ";
		titlex += runNumber;
		cout << "Drawing " << titlex << "..." << endl;
		TString drawx = "4*";
		drawx += e_beam;
		drawx += "*p*(sin(dc_ccth*3.14159/180/2)^2)/(2*0.938*(";
		drawx += e_beam;
		drawx += "-p))";
		TString drawx1 = drawx;
		drawx1 += ">>histx1(400,0,3)";
		chain->Draw(drawx1, cuts, "");
		histx1->SetTitle(titlex);
		histx1->Draw();
		TString histx1Write = "histx1_sec_"; histx1Write += sector;
		histx1->SetName(histx1Write); histx1->Write(histx1Write,TObject::kWriteDelete);
		pad9a->Update();

		pad9b->cd();
//		pad9->SetLogy();
		titlex = "Bjorken x (1-20) for Run # ";
		titlex += runNumber;
		TString drawx2 = drawx;
		drawx2 += ">>histx2(400,0,20)";
		chain->Draw(drawx2, cuts, "");
		histx2->SetTitle(titlex);
		histx2->Draw();
		TString histx2Write = "histx2_sec_"; histx2Write += sector;
		histx2->SetName(histx2Write); histx2->Write(histx2Write,TObject::kWriteDelete);
		pad9b->Update();



		if (outputFiles)
		{
			// Outputs file image
			TString imagename = "./Run_Check_for_";
			imagename += target;
			imagename += "_Ebeam_";
			imagename += e_beamStr;
			imagename += "GeV_Sector_";
			imagename += sector;
			imagename += "_Run_";
			imagename += runNumber;
			imagename += ".png";
			c1->Print(imagename);

			TString toFolder = "mv *.png ./Run_Checks/";
			toFolder += e_beamStr;
			toFolder += "\\ GeV/";
			toFolder += target;
			toFolder += "/Sector\\ ";
			toFolder += sector;
			toFolder +="/.";

			gSystem->Exec(toFolder);
		}
	}
	else {cout << "There is no file for Run # " << runNumber << endl;}

	// Stops code from automatically exiting to check that plots
	// look good
//	if (false)
	if (debug)
	{
		TString exits;
		cout << "Are you ready to finish?" << endl;
		cin >> exits;
	}

	outputRoot->Close();

	// Output elapsed time
	Double_t thisTime = thisRunTime.RealTime(); thisRunTime.Reset();
	Double_t totTime  = allTime.RealTime(); allTime.Continue();
	int thisTimeDays	= floor(thisTime/60/60/24);
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


void make_folders()
{
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
	cout << "Starting make_folders()..." << endl;
	TString folderName;
	// Prepares folders for output files
	gSystem->Exec("mkdir Run_Checks");
	gSystem->Exec("mkdir Run_Checks/1.1\\ GeV");
	gSystem->Exec("mkdir Run_Checks/1.1\\ GeV/emp");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.1\\ GeV/emp/Sector\\ "; 
		folderName += i;
		folderName += "";
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/1.1\\ GeV/nh3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.1\\ GeV/nh3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/1.3\\ GeV");
	gSystem->Exec("mkdir Run_Checks/1.3\\ GeV/carb");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.3\\ GeV/carb/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/1.3\\ GeV/emp");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.3\\ GeV/emp/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/1.3\\ GeV/nd3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.3\\ GeV/nd3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}

	gSystem->Exec("mkdir Run_Checks/1.3\\ GeV/nh3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.3\\ GeV/nh3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/1.5\\ GeV");
	gSystem->Exec("mkdir Run_Checks/1.5\\ GeV/emp");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.5\\ GeV/emp/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/1.5\\ GeV/nh3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/1.5\\ GeV/nh3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/2.0\\ GeV");
	gSystem->Exec("mkdir Run_Checks/2.0\\ GeV/carb");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/2.0\\ GeV/carb/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/2.0\\ GeV/emp");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/2.0\\ GeV/emp/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/2.0\\ GeV/nd3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/2.0\\ GeV/nd3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/2.0\\ GeV/nh3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/2.0\\ GeV/nh3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/2.2\\ GeV");
	gSystem->Exec("mkdir Run_Checks/2.2\\ GeV/emp");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/2.2\\ GeV/emp/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/2.2\\ GeV/nh3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/2.2\\ GeV/nh3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/3.0\\ GeV");
	gSystem->Exec("mkdir Run_Checks/3.0\\ GeV/carb");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/3.0\\ GeV/carb/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/3.0\\ GeV/emp");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/3.0\\ GeV/emp/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}
	gSystem->Exec("mkdir Run_Checks/3.0\\ GeV/nh3");
	for (int i=0; i<7; i++)
	{
		folderName = "mkdir Run_Checks/3.0\\ GeV/nh3/Sector\\ "; 
		folderName += i; 
		gSystem->Exec(folderName);
	}

	cout << "Finished make_folders()!" << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
	return;
}









