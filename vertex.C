void SetHistogram(TH1F *, string, Color_t, int, int );

void vertex(string sim = "high_mult", string peakMethod = "KDE", string kdeOption = "Standard", string recoType = "YZ", bool doFit = false) {
    TFile *fIn = TFile::Open(Form("data/real_config/vtx_%s_%s_%s_%s.root", sim.c_str(), peakMethod.c_str(), kdeOption.c_str(), recoType.c_str()));
    TH1F *hnvert  = (TH1F*) fIn -> Get("hnvert"); SetHistogram(hnvert, "N vertex", kBlack, 20, 1);
    TH1F *hxgen   = (TH1F*) fIn -> Get("hxgen"); SetHistogram(hxgen, "x_{vtx} gen", kBlack, 20, 1);
    TH1F *hygen   = (TH1F*) fIn -> Get("hygen"); SetHistogram(hygen, "y_{vtx} gen", kBlack, 20, 1);
    TH1F *hzgen   = (TH1F*) fIn -> Get("hzgen"); SetHistogram(hzgen, "z_{vtx} gen", kBlack, 20, 1);
    TH1F *hxrec   = (TH1F*) fIn -> Get("hxrec"); SetHistogram(hxrec, "x_{vtx} rec", kBlack, 20, 1);
    TH1F *hyrec   = (TH1F*) fIn -> Get("hyrec"); SetHistogram(hyrec, "y_{vtx} rec", kBlack, 20, 1);
    TH1F *hzrec   = (TH1F*) fIn -> Get("hzrec"); SetHistogram(hzrec, "z_{vtx} rec", kBlack, 20, 1);
    TH1F *hncontr = (TH1F*) fIn -> Get("hncontr"); SetHistogram(hncontr, "N contributors", kBlack, 20, 1);
    TH2F *hnvertcontrib = (TH2F*) fIn -> Get("hnvertcontrib");

    TCanvas *canvasPosGenRec = new TCanvas("canvasPosGenRec", "", 1800, 1200);
    canvasPosGenRec -> Divide(3, 2);
    canvasPosGenRec -> cd(1); hxgen -> Draw("H");
    canvasPosGenRec -> cd(2); hygen -> Draw("H");
    canvasPosGenRec -> cd(3); hzgen -> Draw("H");
    canvasPosGenRec -> cd(4); hxrec -> Draw("H");
    canvasPosGenRec -> cd(5); hyrec -> Draw("H");
    canvasPosGenRec -> cd(6); hzrec -> Draw("H");

    const int nTargs = 5;
    TH1F *histXrecPerTarg[nTargs], *histYrecPerTarg[nTargs], *histZrecPerTarg[nTargs];
    TH1F *histDxPerTarg = new TH1F("histDxPerTarg" ,";N. target;#Deltax (cm)", nTargs, 0, nTargs);
    SetHistogram(histDxPerTarg, "#Deltax per target", kBlack, 20, 1);
    TH1F *histDyPerTarg = new TH1F("histDyPerTarg" ,";N. target;#Deltay (cm)", nTargs, 0, nTargs);
    SetHistogram(histDyPerTarg, "#Deltay per target", kBlack, 20, 1);
    TH1F *histDzPerTarg = new TH1F("histDzPerTarg" ,";N. target;#Deltaz (cm)", nTargs, 0, nTargs);
    SetHistogram(histDzPerTarg, "#Deltaz per target", kBlack, 20, 1);
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
        histXrecPerTarg[iTarg] = (TH1F*) fIn -> Get(Form("hxrec_target_%i", iTarg)); SetHistogram(histXrecPerTarg[iTarg], "x_{rec} per target", kBlack, 20, 1);
        histYrecPerTarg[iTarg] = (TH1F*) fIn -> Get(Form("hyrec_target_%i", iTarg)); SetHistogram(histYrecPerTarg[iTarg], "y_{rec} per target", kBlack, 20, 1);
        histZrecPerTarg[iTarg] = (TH1F*) fIn -> Get(Form("hzrec_target_%i", iTarg)); SetHistogram(histZrecPerTarg[iTarg], "z_{rec} per target", kBlack, 20, 1);

        TH1F *hdx = (TH1F*) fIn -> Get(Form("hdx_target_%i", iTarg));
        TH1F *hdy = (TH1F*) fIn -> Get(Form("hdy_target_%i", iTarg));
        TH1F *hdz = (TH1F*) fIn -> Get(Form("hdz_target_%i", iTarg));

        histDxPerTarg -> SetBinContent(iTarg+1, hdx -> GetMean());
        histDxPerTarg -> SetBinError(iTarg+1, hdx -> GetStdDev());

        histDyPerTarg -> SetBinContent(iTarg+1, hdy -> GetMean());
        histDyPerTarg -> SetBinError(iTarg+1, hdy -> GetStdDev());

        histDzPerTarg -> SetBinContent(iTarg+1, hdz -> GetMean());
        histDzPerTarg -> SetBinError(iTarg+1, hdz -> GetStdDev());
    }

    ////////////////////////////
    // Plots
    ////////////////////////////
    Color_t colors[] = {kRed+1, kOrange+7, kGreen+1, kAzure+2, kBlue+1};
    gStyle -> SetOptFit(1111);
    gStyle -> SetStatFontSize(0.03);

    TCanvas *canvasNvert = new TCanvas("canvasNvert", "", 800, 600);
    hnvert -> Draw("EP");

    TCanvas *canvasNcontr = new TCanvas("canvasNcontrib", "", 800, 600);
    hncontr -> Draw("EP");

    //double zPosTargs[] = {-2, -1, 0, 1, 2}; // default config
    double zPosTargs[] = {-5.3, -4.1, -2.9, -1.7, -0.5}; // real config
    double zWidthTargs = 0.075;
    TCanvas *canvasZrecPerTarg = new TCanvas("canvasZrecPerTarg", "", 800, 600);
    //gPad -> SetLogy(true);
    gStyle -> SetOptStat(false);
    TH1F *histInTargFrac = new TH1F("histInTargFrac", ";N. target;Fraction in target", 5, 0, 5); SetHistogram(histInTargFrac, "vtx. Z fraction in target", kBlack, 20, 1);

    TH2D *histGridZrecPerTarg = new TH2D("histGridZrecPerTarg", ";z_{rec} (cm);Counts", 100, -7, 1, 100, 0, 600);
    histGridZrecPerTarg -> Draw();
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
        histZrecPerTarg[iTarg] -> SetLineColor(colors[iTarg]);
        histZrecPerTarg[iTarg] -> SetFillColorAlpha(colors[iTarg], 0.5);
        histZrecPerTarg[iTarg] -> Rebin(2);
        histZrecPerTarg[iTarg] -> Draw("H SAME");
        TLine *lineMinTargs = new TLine(zPosTargs[iTarg]-zWidthTargs, 0.1, zPosTargs[iTarg]-zWidthTargs, 600); lineMinTargs -> SetLineStyle(kDotted); lineMinTargs -> SetLineWidth(2); lineMinTargs -> SetLineColor(kGray+1);
        TLine *lineMaxTargs = new TLine(zPosTargs[iTarg]+zWidthTargs, 0.1, zPosTargs[iTarg]+zWidthTargs, 600); lineMaxTargs -> SetLineStyle(kDotted); lineMaxTargs -> SetLineWidth(2); lineMaxTargs -> SetLineColor(kGray+1);
        lineMinTargs -> Draw("SAME");
        lineMaxTargs -> Draw("SAME");

        int minTarg = histZrecPerTarg[iTarg] -> FindBin(zPosTargs[iTarg]-zWidthTargs);
        int maxTarg = histZrecPerTarg[iTarg] -> FindBin(zPosTargs[iTarg]+zWidthTargs);
        double allVertZ = histZrecPerTarg[iTarg] -> Integral();
        double inTargVertZ = histZrecPerTarg[iTarg] -> Integral(minTarg, maxTarg);

        for (int jTarg = 0;jTarg < nTargs;jTarg++) {
            if (jTarg != iTarg) {
                double contInTargVertZ = histZrecPerTarg[jTarg] -> Integral(minTarg, maxTarg);
                std::cout << "N. vertices in target for other targets = " << contInTargVertZ << std::endl;
            }
        }
        double inTargFrac = inTargVertZ / allVertZ;
        std::cout << "fraction of vertices in target = " << inTargFrac << " +/- " << TMath::Sqrt(allVertZ * inTargFrac * (1 - inTargFrac)) / allVertZ << std::endl;
        histInTargFrac -> SetBinContent(iTarg+1, inTargFrac);
        histInTargFrac -> SetBinError(iTarg+1, (TMath::Sqrt(allVertZ * inTargFrac * (1 - inTargFrac))) / allVertZ);
    }

    TCanvas *canvasInTargFrac = new TCanvas("canvasInTargFrac", "", 800, 600);
    histInTargFrac -> GetYaxis() -> SetRangeUser(0, 1.2);
    histInTargFrac -> Draw("EP");
    TLine *lineUnity = new TLine(0, 1, 5, 1);
    lineUnity -> SetLineStyle(kDashed);
    lineUnity -> SetLineWidth(2);
    lineUnity -> SetLineColor(kGray+1);
    lineUnity -> Draw("SAME");

    TCanvas *canvasDxPerTarg = new TCanvas("canvasDxPerTarg", "", 800, 600);
    histDxPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDxPerTarg -> Draw("EP");

    if (doFit) {
        TF1 *funcPol0DxPerTarg = new TF1("funcPol0DxPerTarg", "pol0", 0, 5); funcPol0DxPerTarg -> SetLineColor(kRed);
        histDxPerTarg -> Fit(funcPol0DxPerTarg, "R0Q");
        funcPol0DxPerTarg -> Draw("SAME");
    }

    TCanvas *canvasDyPerTarg = new TCanvas("canvasDyPerTarg", "", 800, 600);
    histDyPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDyPerTarg -> Draw("EP");

    if (doFit) {
        TF1 *funcPol0DyPerTarg = new TF1("funcDyPerTarg", "pol0", 0, 5); funcPol0DyPerTarg -> SetLineColor(kRed);
        histDyPerTarg -> Fit(funcPol0DyPerTarg, "R0Q");
        funcPol0DyPerTarg -> Draw("SAME");
    }

    TCanvas *canvasDzPerTarg = new TCanvas("canvasDzPerTarg", "", 800, 600);
    histDzPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDzPerTarg -> Draw("EP");

    if (doFit) {
        TF1 *funcPol0DzPerTarg = new TF1("funcDzPerTarg", "pol0", 0, 5); funcPol0DzPerTarg -> SetLineColor(kRed);
        histDzPerTarg -> Fit(funcPol0DzPerTarg, "R0Q");
        funcPol0DzPerTarg -> Draw("SAME");
    }

    string dirOut = Form("outputs/real_config/%s/%s_%s_%s", sim.c_str(), peakMethod.c_str(), kdeOption.c_str(), recoType.c_str());
    if (gSystem -> AccessPathName(dirOut.c_str()) == true) {
        gSystem -> mkdir(dirOut.c_str(), true);
    }

    TFile *fOut = new TFile(Form("%s/AnalysisResults.root", dirOut.c_str()), "RECREATE");
    hnvert -> Write("hnvert");
    hncontr -> Write("hncontr");
    histDxPerTarg -> Write("histDxPerTarg");
    histDyPerTarg -> Write("histDyPerTarg");
    histDzPerTarg -> Write("histDzPerTarg");
    histInTargFrac -> Write("histInTargFrac");
    fOut -> Close();

    canvasPosGenRec -> SaveAs(Form("%s/posGenRec.pdf", dirOut.c_str()));
    canvasZrecPerTarg -> SaveAs(Form("%s/zRecPerTarg.pdf", dirOut.c_str()));
    canvasInTargFrac -> SaveAs(Form("%s/inTargFrac.pdf", dirOut.c_str()));
    canvasDxPerTarg -> SaveAs(Form("%s/dxPerTarg.pdf", dirOut.c_str()));
    canvasDyPerTarg -> SaveAs(Form("%s/dyPerTarg.pdf", dirOut.c_str()));
    canvasDzPerTarg -> SaveAs(Form("%s/dzPerTarg.pdf", dirOut.c_str()));
}