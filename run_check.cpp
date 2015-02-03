


void run_check(){


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
	int sector;
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
	else {e_beam=1.1; target="nh3"; checkAll="y"; maxSector = 2;}

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


	if (!debug && e_beam==1.1 && target=="nh3" && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 52080; endRunNumber = 52289;}
	else if (debug && e_beam==1.1 && target=="nh3" && ((checkAll == "yes") || (checkAll == "Yes") || (checkAll == "y") || (checkAll =="Y"))) {cout << "Rad" << endl; runNumber = 52080; endRunNumber = 52080;}
	else
	{
		cout << "Enter beginning run number: ";
		cin >> runNumber;
		cout << "Enter ending run number: ";
		cin >> endRunNumber;
	}

	cout << "Beginning run number: " << runNumber << endl;	
	cout << "Endding run number:   " << endRunNumber << endl;	

	for (int i=runNumber; i<(endRunNumber+1); i++)
	{
		for (int sector=1; sector<maxSector; sector++)
		{
			check_run(i, e_beam, targetStr, target, filePrefix, sector, debug);
		}
	}	

	cout << "All done!" << endl;
	return;
}


void check_run(int runNumber, double e_beam, TString targetStr, TString target, TString filePrefix, int sector, bool debug)
{
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
	cout << "Running check_run for Run # " << runNumber << "..." << endl;
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
	else {aMax = 1000; cout << "Normal Mode On" << endl;}

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
		pad5a =  new  TPad("pad5a","pad5a",0.3333,0.4549,0.6666,0.6333,0,0,0);
		pad5b =  new  TPad("pad5b","pad5b",0.3333,0.3166,0.6666,0.4549,0,0,0);
		pad6  =  new  TPad("pad6","pad6",0.6666,0.3166,1.0000,0.6333,0,0,0);
		pad7  =  new  TPad("pad7","pad7",0.0000,0.0000,0.3333,0.3166,0,0,0);
		pad8  =  new  TPad("pad8","pad8",0.3333,0.0000,0.6666,0.3166,0,0,0);
		pad9  =  new  TPad("pad9","pad9",0.6666,0.0000,1.0000,0.3166,0,0,0);
		pad1->Draw();pad2->Draw();pad3->Draw();pad4->Draw();pad5a->Draw();pad5b->Draw();
		pad6->Draw();pad7->Draw();pad8->Draw();pad9->Draw();pad0->Draw();


	
		pad0->cd();
		TPaveLabel *titleBox = new TPaveLabel(0,0,1,1,title);
		titleBox->Draw();
		pad0->Update();

		pad1->cd();
		TString titleTarget = "Vertex z for Run # ";
		titleTarget += runNumber;
		cout << "Drawing Vertex z..." << endl;
		chain->Draw("dc_vz>>vertZ(400,-800,800)", cuts, "");
		vertZ->SetTitle(titleTarget);
		vertZ->Draw();
		pad1->Update();

		pad2->cd();
		TString titleQ2 = "Q2 for Run # ";
		titleQ2 += runNumber;
		cout << "Drawing " << titleQ2 << "..." << endl;
		TString drawQ2 = "4*";
		drawQ2 += e_beam;
		drawQ2 += "*p*(sin(dc_ccth*3.14159/180/2)^2)>>histQ2(400,0,6)";
		chain->Draw(drawQ2, cuts, "");
		histQ2->SetTitle(titleQ2);
	//	histQ2->SetStats(kFALSE);
		histQ2->Draw();
		pad2->Update(); 

		pad3->cd();
		TString titleNu = "Nu for Run # ";
		titleNu += runNumber;
		cout << "Drawing " << titleNu << "..." << endl;
		TString drawNu = "";
		drawNu += e_beam;
		drawNu += "-p>>histNu(100,-1,4)";
		chain->Draw(drawNu, cuts, "");
		histNu->SetTitle(titleNu);
	//	histNu->SetStats(kFALSE);
		histNu->Draw();
		pad3->Update();

		pad4->cd();
		TString titledp = "dE/dx for Run # ";
		titledp += runNumber;
		cout << "Drawing " << titledp << "..." << endl;
		chain->Draw("edep>>dEdx(400,0,100)", cuts, "");
		dEdx->SetTitle(titledp);
		dEdx->Draw();
		pad4->Update();

		pad5a->cd();
		TString titleThetaPhi = "Theta and Phi for Run # ";
		titleThetaPhi += runNumber;
		cout << "Drawing " << titleThetaPhi << "..."  << endl;
		chain->Draw("dc_ccth:dc_ccph>>thPh(100,-60,60,100,0,60)", cuts, "");
		thPh->SetTitle(titleThetaPhi);
		thPh->SetStats(kFALSE);
		thPh->Draw("COLZ");
		pad5a->Update();

		pad7->cd();
		pad7->SetLogy();
		TString titlex = "Bjorken x ";
		titlex += " (x=Q^2/[2m*nu]) for Run # ";
		titlex += runNumber;
		cout << "Drawing " << titlex << "..." << endl;
		TString drawx = "4*";
		drawx += e_beam;
		drawx += "*p*(sin(dc_ccth*3.14159/180/2)^2)/(2*0.938*(";
		drawx += e_beam;
		drawx += "-p))>>histx(400,0,6)";
	//	TH1F *histx = new TH1F("histx",titlex,bins,xmin,xmax);
	//	histx->Sumw2();
		chain->Draw(drawx, cuts, "");
		histx->SetTitle(titlex);
		histx->Draw();
		pad7->Update();
		
		TString imagename = "./Run_Checks/Run_Check_for_Sector_";
		imagename += sector;
		imagename += "_Run_";
		imagename += runNumber;
		imagename += ".png";
		c1->Print(imagename);
	}
	else {cout << "There is no file for Run # " << runNumber << endl;}
	
	cout << "Finished check_run for Run # " << runNumber << "!" << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

	return;

}












