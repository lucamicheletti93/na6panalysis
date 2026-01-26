void SetHistogram(TH1F *, string, Color_t , int );

void vertex(string peakMethod = "KDE", string recoType = "YZ") {
    TFile *fIn = TFile::Open(Form("vtx_%s_%s.root", peakMethod.c_str(), recoType.c_str()));
    TH1F *hnvert = (TH1F*) fIn -> Get("hnvert"); SetHistogram(hnvert, "N vertex", kBlack, 20);
    TH1F *hxgen = (TH1F*) fIn -> Get("hxgen"); SetHistogram(hxgen, "x_{vtx} gen", kBlack, 20);
    TH1F *hygen = (TH1F*) fIn -> Get("hygen"); SetHistogram(hygen, "y_{vtx} gen", kBlack, 20);
    TH1F *hzgen = (TH1F*) fIn -> Get("hzgen"); SetHistogram(hzgen, "z_{vtx} gen", kBlack, 20);
    TH1F *hxrec = (TH1F*) fIn -> Get("hxrec"); SetHistogram(hxrec, "x_{vtx} rec", kBlack, 20);
    TH1F *hyrec = (TH1F*) fIn -> Get("hyrec"); SetHistogram(hyrec, "y_{vtx} rec", kBlack, 20);
    TH1F *hzrec = (TH1F*) fIn -> Get("hzrec"); SetHistogram(hzrec, "z_{vtx} rec", kBlack, 20);

    TCanvas *canvasPosGenRec = new TCanvas("canvasPosGenRec", "", 1800, 1200);
    canvasPosGenRec -> Divide(3, 2);
    canvasPosGenRec -> cd(1); hxgen -> Draw("H");
    canvasPosGenRec -> cd(2); hygen -> Draw("H");
    canvasPosGenRec -> cd(3); hzgen -> Draw("H");
    canvasPosGenRec -> cd(4); hxrec -> Draw("H");
    canvasPosGenRec -> cd(5); hyrec -> Draw("H");
    canvasPosGenRec -> cd(6); hzrec -> Draw("H");

    const int nTargs = 5;
    TH1F *histDxPerTarg = new TH1F("histDxPerTarg" ,";N. target;#Deltax (cm)", nTargs, 0, nTargs);
    SetHistogram(histDxPerTarg, "#Deltax per target", kBlack, 20);
    TH1F *histDyPerTarg = new TH1F("histDyPerTarg" ,";N. target;#Deltay (cm)", nTargs, 0, nTargs);
    SetHistogram(histDyPerTarg, "#Deltay per target", kBlack, 20);
    TH1F *histDzPerTarg = new TH1F("histDzPerTarg" ,";N. target;#Deltay (cm)", nTargs, 0, nTargs);
    SetHistogram(histDzPerTarg, "#Deltaz per target", kBlack, 20);
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
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

    TCanvas *canvasDxPerTarg = new TCanvas("canvasDxPerTarg", "", 800, 600);
    //gStyle -> SetOptStat(false);
    histDxPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDxPerTarg -> Draw("EP");

    TCanvas *canvasDyPerTarg = new TCanvas("canvasDyPerTarg", "", 800, 600);
    //gStyle -> SetOptStat(false);
    histDyPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDyPerTarg -> Draw("EP");

    TCanvas *canvasDzPerTarg = new TCanvas("canvasDzPerTarg", "", 800, 600);
    //gStyle -> SetOptStat(false);
    histDzPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDzPerTarg -> Draw("EP");

    string dirOut = Form("figures/%s_%s", peakMethod.c_str(), recoType.c_str());
    if (gSystem -> AccessPathName(dirOut.c_str()) == true) {
        gSystem -> mkdir(dirOut.c_str(), true);
    }

    canvasPosGenRec -> SaveAs(Form("%s/posGenRec.pdf", dirOut.c_str()));
    canvasDxPerTarg -> SaveAs(Form("%s/dxPerTarg.pdf", dirOut.c_str()));
    canvasDyPerTarg -> SaveAs(Form("%s/dyPerTarg.pdf", dirOut.c_str()));
    canvasDzPerTarg -> SaveAs(Form("%s/dzPerTarg.pdf", dirOut.c_str()));
}
////////////////////////
void SetHistogram(TH1F *hist, string name, Color_t color, int markerStyle) {
    hist -> SetName(name.c_str());
    hist -> SetLineColor(color);
    hist -> SetLineWidth(1);
    hist -> SetMarkerStyle(markerStyle);
    hist -> SetMarkerColor(color);
}