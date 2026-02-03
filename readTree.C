void SetHistogram(TH1F *, string, Color_t, int, double );
void SetLegend(TLegend * );
Color_t colors[] = {kRed, kOrange+7, kGreen+1, kAzure+2, kBlue};

void readTree(string sim = "high_mult", string peakMethod = "KDE", string kdeOption = "Standard", string recoType = "YZ", bool doFit = false) {
    TFile *fIn = TFile::Open(Form("data/real_config/vtx_%s_%s_%s_%s.root", sim.c_str(), peakMethod.c_str(), kdeOption.c_str(), recoType.c_str()));

    int nVtx, targId;
    double genX, genY, genZ;
    int nContrib[20];
    double recsX[20], recsY[20], recsZ[20];
    TTree *tree = (TTree*) fIn -> Get("vertex");
    tree -> SetBranchAddress("nVtx", &nVtx);
    tree -> SetBranchAddress("targId", &targId);
    tree -> SetBranchAddress("genX", &genX);
    tree -> SetBranchAddress("genY", &genY);
    tree -> SetBranchAddress("genZ", &genZ);
    tree -> SetBranchAddress("nContrib", nContrib);
    tree -> SetBranchAddress("recsX", recsX);
    tree -> SetBranchAddress("recsY", recsY);
    tree -> SetBranchAddress("recsZ", recsZ);

    TH1F *hnvert = new TH1F("hnvert", "; N_{vertices}; counts", 11, -0.5, 10.5);
    TH1F *hncontr = new TH1F("hncontr", "; N_{contributors}; counts", 1000, -0.5, 999.5); SetHistogram(hncontr, "hncontr", kBlack, 20, 0.5);
    TH2D *hnvertcontrib = new TH2D("hnvertcontrib", "; N_{vertices}; N_{contributors}", 11, -0.5, 10.5, 1000, -0.5, 999.5);

    const int nTargs = 5;
    TH1F *hxgen = new TH1F("hxgen", "; x_{gen} (cm); counts", 1000, -5, 5); SetHistogram(hxgen, "x_{vtx} gen", kBlack, 20, 1);
    TH1F *hygen = new TH1F("hygen", "; y_{gen} (cm); counts", 1000, -5, 5); SetHistogram(hygen, "y_{vtx} gen", kBlack, 20, 1);
    TH1F *hzgen = new TH1F("hzgen", "; x_{gen} (cm); counts", 1000, -9, 1); SetHistogram(hzgen, "z_{vtx} gen", kBlack, 20, 1);
    TH1F* hxrec = new TH1F("hxrec", "; x_{rec} (cm); counts", 1000, -5, 5); SetHistogram(hxrec, "x_{vtx} rec", kBlack, 20, 1);
    TH1F* hyrec = new TH1F("hyrec", "; y_{rec} (cm); counts", 1000, -5, 5); SetHistogram(hyrec, "y_{vtx} rec", kBlack, 20, 1);
    TH1F* hzrec = new TH1F("hzrec", "; x_{rec} (cm); counts", 1000, -9, 1); SetHistogram(hzrec, "z_{vtx} rec", kBlack, 20, 1);

    TH1F *hncontrs[20];
    for (int i = 0;i < 20;i++) {
        hncontrs[i] = new TH1F(Form("hncontrs_vtx_%i", i), "; N_{contributors}; counts", 1000, -0.5, 999.5); SetHistogram(hncontrs[i], Form("hncontrs_vtx_%i", i), i < 5 ? colors[i] : kBlack, 20, 1);
    }
    TH1F *hxrecs[nTargs], *hyrecs[nTargs], *hzrecs[nTargs];
    TH1F *hxrecsall[nTargs], *hyrecsall[nTargs], *hzrecsall[nTargs];
    TH1F *hdxs[nTargs], *hdys[nTargs], *hdzs[nTargs];
    TH1F *hdxsall[nTargs], *hdysall[nTargs], *hdzsall[nTargs];
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
        hxrecs[iTarg] = new TH1F(Form("hxrec_target_%i", iTarg), "; x_{rec} cm; counts", 1000, -5, 5);
        hyrecs[iTarg] = new TH1F(Form("hyrec_target_%i", iTarg), "; y_{rec} cm; counts", 1000, -5, 5);
        hzrecs[iTarg] = new TH1F(Form("hzrec_target_%i", iTarg), "; z_{rec} cm; counts", 1000, -9, 1);

        hxrecsall[iTarg] = new TH1F(Form("hxrecall_target_%i", iTarg), "; x_{rec} cm; counts", 1000, -5, 5);
        hyrecsall[iTarg] = new TH1F(Form("hyrecall_target_%i", iTarg), "; y_{rec} cm; counts", 1000, -5, 5);
        hzrecsall[iTarg] = new TH1F(Form("hzrecall_target_%i", iTarg), "; z_{rec} cm; counts", 1000, -9, 1);

        hdxs[iTarg] = new TH1F(Form("hdx_target_%i", iTarg), "; x_{rec} - x_{gen} cm; counts", 100, -0.5, 0.5); SetHistogram(hdxs[iTarg], Form("#Deltax Target %i", iTarg), kBlack, 20, 2);
        hdys[iTarg] = new TH1F(Form("hdy_target_%i", iTarg), "; y_{rec} - y_{gen} cm; counts", 100, -0.5, 0.5); SetHistogram(hdys[iTarg], Form("#Deltay Target %i", iTarg), kBlack, 20, 2);
        hdzs[iTarg] = new TH1F(Form("hdz_target_%i", iTarg), "; z_{rec} - z_{gen} cm; counts", 1600, -8, 8); SetHistogram(hdzs[iTarg], Form("#Deltaz Target %i", iTarg), kBlack, 20, 2);

        hdxsall[iTarg] = new TH1F(Form("hdxall_target_%i", iTarg), "; x_{rec} - x_{gen} cm; counts", 100, -0.5, 0.5); SetHistogram(hdxsall[iTarg], Form("#Deltax all Target %i", iTarg), kRed, 20, 2);
        hdysall[iTarg] = new TH1F(Form("hdyall_target_%i", iTarg), "; y_{rec} - y_{gen} cm; counts", 100, -0.5, 0.5); SetHistogram(hdysall[iTarg], Form("#Deltax all Target %i", iTarg), kRed, 20, 2);
        hdzsall[iTarg] = new TH1F(Form("hdzall_target_%i", iTarg), "; z_{rec} - z_{gen} cm; counts", 1600, -8, 8); SetHistogram(hdzsall[iTarg], Form("#Deltax all Target %i", iTarg), kRed, 20, 2);
    }

    // Loop over all the events
    int nEvts = tree -> GetEntries();
    for (int iEvt = 0;iEvt < nEvts;iEvt++) {
        tree -> GetEntry(iEvt);
        
        hnvert -> Fill(nVtx);
        hxgen -> Fill(genX);
        hygen -> Fill(genY);
        hzgen -> Fill(genZ);

        int nVtxs = nVtx;
        for (int iVtx = 0;iVtx < nVtxs;iVtx++) {
            hncontr -> Fill(nContrib[iVtx]);
            hnvertcontrib -> Fill(iVtx, nContrib[iVtx]);
            hncontrs[iVtx] -> Fill(nContrib[iVtx]);

            if (iVtx == 0) {
                hxrec -> Fill(recsX[iVtx]);
                hyrec -> Fill(recsY[iVtx]);
                hzrec -> Fill(recsZ[iVtx]);

                hxrecs[targId] -> Fill(recsX[iVtx]);
                hyrecs[targId] -> Fill(recsY[iVtx]);
                hzrecs[targId] -> Fill(recsZ[iVtx]);

                hdxs[targId] -> Fill(recsX[iVtx] - genX);
                hdys[targId] -> Fill(recsY[iVtx] - genY);
                hdzs[targId] -> Fill(recsZ[iVtx] - genZ);
            }
            hxrecsall[targId] -> Fill(recsX[iVtx]);
            hyrecsall[targId] -> Fill(recsY[iVtx]);
            hzrecsall[targId] -> Fill(recsZ[iVtx]);

            hdxsall[targId] -> Fill(recsX[iVtx] - genX);
            hdysall[targId] -> Fill(recsY[iVtx] - genY);
            hdzsall[targId] -> Fill(recsZ[iVtx] - genZ);
        }
    }

    TH1F *histDxPerTarg = new TH1F("histDxPerTarg" ,";N. target;#Deltax (cm)", nTargs, 0, nTargs);
    SetHistogram(histDxPerTarg, "#Deltax per target", kBlack, 20, 1);
    TH1F *histDyPerTarg = new TH1F("histDyPerTarg" ,";N. target;#Deltay (cm)", nTargs, 0, nTargs);
    SetHistogram(histDyPerTarg, "#Deltay per target", kBlack, 20, 1);
    TH1F *histDzPerTarg = new TH1F("histDzPerTarg" ,";N. target;#Deltaz (cm)", nTargs, 0, nTargs);
    SetHistogram(histDzPerTarg, "#Deltaz per target", kBlack, 20, 1);
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
        histDxPerTarg -> GetXaxis() -> SetBinLabel(iTarg+1, Form("%i", iTarg));
        histDxPerTarg -> SetBinContent(iTarg+1, hdxs[iTarg] -> GetMean());
        histDxPerTarg -> SetBinError(iTarg+1, hdxs[iTarg] -> GetStdDev());

        histDyPerTarg -> GetXaxis() -> SetBinLabel(iTarg+1, Form("%i", iTarg));
        histDyPerTarg -> SetBinContent(iTarg+1, hdys[iTarg] -> GetMean());
        histDyPerTarg -> SetBinError(iTarg+1, hdys[iTarg] -> GetStdDev());

        histDzPerTarg -> GetXaxis() -> SetBinLabel(iTarg+1, Form("%i", iTarg));
        histDzPerTarg -> SetBinContent(iTarg+1, hdzs[iTarg] -> GetMean());
        histDzPerTarg -> SetBinError(iTarg+1, hdzs[iTarg] -> GetStdDev());
    }

    // Plots
    gStyle -> SetOptStat(0);
    TLatex latexTitle;
    latexTitle.SetNDC();
    latexTitle.SetTextSize(0.05);
    latexTitle.SetTextFont(42);

    TCanvas *canvasPosGenRec = new TCanvas("canvasPosGenRec", "", 1800, 1200);
    canvasPosGenRec -> Divide(3, 2);
    canvasPosGenRec -> cd(1); hxgen -> Draw("H");
    canvasPosGenRec -> cd(2); hygen -> Draw("H");
    canvasPosGenRec -> cd(3); hzgen -> Draw("H");
    canvasPosGenRec -> cd(4); hxrec -> Draw("H");
    canvasPosGenRec -> cd(5); hyrec -> Draw("H");
    canvasPosGenRec -> cd(6); hzrec -> Draw("H");

    TCanvas *canvasPosResX = new TCanvas("canvasPosResX", "", 1800, 1200);
    canvasPosResX -> Divide(3, 2);
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
        canvasPosResX -> cd(iTarg+1);
        hdxsall[iTarg] -> SetMinimum(0);
        hdxsall[iTarg] -> Draw("H");
        hdxs[iTarg] -> Draw("H SAME");
        latexTitle.DrawLatex(0.15, 0.80, Form("#color[1]{#Deltax = %5.3f #pm %5.3f}", hdxs[iTarg] -> GetMean(), hdxs[iTarg] -> GetStdDev()));
        latexTitle.DrawLatex(0.15, 0.75, Form("#color[2]{#Deltax = %5.3f #pm %5.3f}", hdxsall[iTarg] -> GetMean(), hdxsall[iTarg] -> GetStdDev()));
    }
    canvasPosResX -> cd(6);
    gPad -> SetGridy(true);
    histDxPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDxPerTarg -> Draw("EP");

    TCanvas *canvasPosResY = new TCanvas("canvasPosResY", "", 1800, 1200);
    canvasPosResY -> Divide(3, 2);
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
        canvasPosResY -> cd(iTarg+1);
        hdysall[iTarg] -> SetMinimum(0);
        hdysall[iTarg] -> Draw("H");
        hdys[iTarg] -> Draw("H SAME");
        latexTitle.DrawLatex(0.15, 0.80, Form("#color[1]{#Deltay = %5.3f #pm %5.3f}", hdys[iTarg] -> GetMean(), hdys[iTarg] -> GetStdDev()));
        latexTitle.DrawLatex(0.15, 0.75, Form("#color[2]{#Deltay = %5.3f #pm %5.3f}", hdysall[iTarg] -> GetMean(), hdysall[iTarg] -> GetStdDev()));
    }
    canvasPosResY -> cd(6);
    gPad -> SetGridy(true);
    histDyPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDyPerTarg -> Draw("EP");

    TCanvas *canvasPosResZ = new TCanvas("canvasPosResZ", "", 1800, 1200);
    canvasPosResZ -> Divide(3, 2);
    for (int iTarg = 0;iTarg < nTargs;iTarg++) {
        canvasPosResZ -> cd(iTarg+1);
        hdzsall[iTarg] -> SetMinimum(0);
        hdzsall[iTarg] -> Draw("H");
        hdzs[iTarg] -> Draw("H SAME");
        latexTitle.DrawLatex(0.15, 0.80, Form("#color[1]{#Deltaz = %5.3f #pm %5.3f}", hdzs[iTarg] -> GetMean(), hdzs[iTarg] -> GetStdDev()));
        latexTitle.DrawLatex(0.15, 0.75, Form("#color[2]{#Deltaz = %5.3f #pm %5.3f}", hdzsall[iTarg] -> GetMean(), hdzsall[iTarg] -> GetStdDev()));
    }
    canvasPosResZ -> cd(6);
    gPad -> SetGridy(true);
    histDzPerTarg -> GetYaxis() -> SetRangeUser(-0.30, 0.30);
    histDzPerTarg -> Draw("EP");

    TCanvas *canvasNcontr = new TCanvas("canvasNcontrib", "", 800, 600);
    gPad -> SetLogy(true);
    hncontr -> Draw("EP");

    TLegend *legendNcontr = new TLegend(0.60, 0.60, 0.80, 0.85);
    SetLegend(legendNcontr);
    legendNcontr -> AddEntry(hncontr, "All", "PL");
    for (int iVtx = 0;iVtx < 5;iVtx++) {
        hncontrs[iVtx] -> Draw("H SAME");
        legendNcontr -> AddEntry(hncontrs[iVtx], Form("vtx array: %d, #mu: %1.0f", iVtx, hncontrs[iVtx] -> GetMean()), "L");
    }
    legendNcontr -> Draw("SAME");

    TCanvas *canvasNcontrVsNverts = new TCanvas("canvasNcontrVsNverts", "", 800, 600);
    hnvertcontrib -> Draw("COLZ");

    string dirOut = Form("outputs/real_config/%s/%s_%s_%s", sim.c_str(), peakMethod.c_str(), kdeOption.c_str(), recoType.c_str());
    if (gSystem -> AccessPathName(dirOut.c_str()) == true) {
        gSystem -> mkdir(dirOut.c_str(), true);
    }

    /*TFile *fOut = new TFile(Form("%s/AnalysisResults.root", dirOut.c_str()), "RECREATE");
    hnvert -> Write("hnvert");
    hncontr -> Write("hncontr");
    histDxPerTarg -> Write("histDxPerTarg");
    histDyPerTarg -> Write("histDyPerTarg");
    histDzPerTarg -> Write("histDzPerTarg");
    histInTargFrac -> Write("histInTargFrac");
    fOut -> Close();*/

    canvasPosGenRec -> SaveAs(Form("%s/posGenRec.pdf", dirOut.c_str()));
    canvasPosResX -> SaveAs(Form("%s/posResX.pdf", dirOut.c_str()));
    canvasPosResY -> SaveAs(Form("%s/posResY.pdf", dirOut.c_str()));
    canvasPosResZ -> SaveAs(Form("%s/posResZ.pdf", dirOut.c_str()));
    canvasNcontr -> SaveAs(Form("%s/nContr.pdf", dirOut.c_str()));
    canvasNcontrVsNverts -> SaveAs(Form("%s/nContrVsNverts.pdf", dirOut.c_str()));
    /*canvasZrecPerTarg -> SaveAs(Form("%s/zRecPerTarg.pdf", dirOut.c_str()));
    canvasInTargFrac -> SaveAs(Form("%s/inTargFrac.pdf", dirOut.c_str()));
    canvasDxPerTarg -> SaveAs(Form("%s/dxPerTarg.pdf", dirOut.c_str()));
    canvasDyPerTarg -> SaveAs(Form("%s/dyPerTarg.pdf", dirOut.c_str()));
    canvasDzPerTarg -> SaveAs(Form("%s/dzPerTarg.pdf", dirOut.c_str()));*/
}
////////////////////////
void SetHistogram(TH1F *hist, string name, Color_t color, int markerStyle, double markerSize = 1) {
    hist -> SetName(name.c_str());
    hist -> SetLineColor(color);
    hist -> SetLineWidth(1);
    hist -> SetMarkerStyle(markerStyle);
    hist -> SetMarkerColor(color);
    hist -> SetMarkerSize(markerSize);
}
////////////////////////
void SetLegend(TLegend *legend){
    legend -> SetBorderSize(0);
    legend -> SetFillColor(10);
    legend -> SetFillStyle(1);
    legend -> SetLineStyle(0);
    legend -> SetLineColor(0);
    legend -> SetTextFont(42);
    legend -> SetTextSize(0.04);
}