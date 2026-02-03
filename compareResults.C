void SetHistogram(TH1F *, string, Color_t, int, int );

void compareResults() {
    const int nDirs = 8;
    string histNames[] = {
        "high mult. KDE+YZ", "high mult. Pairs+YZ", "high mult. KDE+3D", "high mult. Pairs+3D",
        "low mult. KDE+YZ", "low mult. Pairs+YZ", "low mult. KDE+3D", "low mult. Pairs+3D"
    };
    string dirNames[] = {
        "high_mult/KDE_YZ", "high_mult/Pairs_YZ", "high_mult/KDE_3D", "high_mult/Pairs_3D",
        "low_mult/KDE_YZ", "low_mult/Pairs_YZ", "low_mult/KDE_3D", "low_mult/Pairs_3D"
    };
    Color_t colors[] = {
        kRed, kBlue, kRed+2, kBlue+2,
        kOrange+7, kAzure+2, kOrange+8, kAzure+3
    };
    int markerStyle[] = {
        20, 20, 24, 24,
        20, 20, 24, 24
    };
    TH1F *hnverts[nDirs], *hncontrs[nDirs], *histDxPerTargs[nDirs], *histDyPerTargs[nDirs], *histDzPerTargs[nDirs];

    for (int iDir = 0;iDir < nDirs;iDir++) {
        TFile *fIn = TFile::Open(Form("outputs/%s/AnalysisResults.root", dirNames[iDir].c_str()));
        hnverts[iDir] = (TH1F*) fIn -> Get("hnvert"); hnverts[iDir] -> SetDirectory(0); SetHistogram(hnverts[iDir], histNames[iDir], colors[iDir], markerStyle[iDir], 2);
        hncontrs[iDir] = (TH1F*) fIn -> Get("hncontr"); hncontrs[iDir] -> SetDirectory(0); SetHistogram(hncontrs[iDir], histNames[iDir], colors[iDir], markerStyle[iDir], 2);
        histDxPerTargs[iDir] = (TH1F*) fIn -> Get("histDxPerTarg"); histDxPerTargs[iDir] -> SetDirectory(0); SetHistogram(histDxPerTargs[iDir], histNames[iDir], colors[iDir], markerStyle[iDir], 2);
        histDyPerTargs[iDir] = (TH1F*) fIn -> Get("histDyPerTarg"); histDyPerTargs[iDir] -> SetDirectory(0); SetHistogram(histDyPerTargs[iDir], histNames[iDir], colors[iDir], markerStyle[iDir], 2);
        histDzPerTargs[iDir] = (TH1F*) fIn -> Get("histDzPerTarg"); histDzPerTargs[iDir] -> SetDirectory(0); SetHistogram(histDzPerTargs[iDir], histNames[iDir], colors[iDir], markerStyle[iDir], 2);
        fIn -> Close();
    }

    gStyle -> SetOptStat(0);

    TCanvas *canvasNvert = new TCanvas("canvasNvert", "", 1600, 600);
    canvasNvert -> Divide(2, 1);
    canvasNvert -> cd(1);
    gPad -> SetLogy(true);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("low_mult") != std::string::npos) {
            string tmpHistName = hnverts[iDir] -> GetName();
            string stringToSubtract = "low mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            hnverts[iDir] -> SetName(tmpHistName.c_str());
            hnverts[iDir] -> GetXaxis() -> SetRangeUser(0, 8);
            hnverts[iDir] -> GetYaxis() -> SetRangeUser(1e-1, 1e5);
            hnverts[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();
    canvasNvert -> cd(2);
    gPad -> SetLogy(true);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("high_mult") != std::string::npos) {
            string tmpHistName = hnverts[iDir] -> GetName();
            string stringToSubtract = "high mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1   ));
            hnverts[iDir] -> SetName(tmpHistName.c_str());
            hnverts[iDir] -> GetXaxis() -> SetRangeUser(0, 8);
            hnverts[iDir] -> GetYaxis() -> SetRangeUser(1e-1, 1e5);
            hnverts[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();



    TCanvas *canvasNcontr = new TCanvas("canvasNcontr", "", 1600, 600);
    canvasNcontr -> Divide(2, 1);
    canvasNcontr -> cd(1);
    gPad -> SetLogy(true);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("low_mult") != std::string::npos) {
            string tmpHistName = hncontrs[iDir] -> GetName();
            string stringToSubtract = "low mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            hncontrs[iDir] -> SetName(tmpHistName.c_str());
            hncontrs[iDir] -> GetXaxis() -> SetRangeUser(0, 100);
            hncontrs[iDir] -> GetYaxis() -> SetRangeUser(1e-1, 1e5);
            hncontrs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();
    canvasNcontr -> cd(2);
    gPad -> SetLogy(true);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("high_mult") != std::string::npos) {
            string tmpHistName = hncontrs[iDir] -> GetName();
            string stringToSubtract = "high mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            hncontrs[iDir] -> SetName(tmpHistName.c_str());
            hncontrs[iDir] -> GetYaxis() -> SetRangeUser(1e-1, 1e5);
            hncontrs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();

    // Deltax
    TCanvas *canvasDxPerTargs = new TCanvas("canvasDxPerTargs", "", 1600, 600);
    canvasDxPerTargs -> Divide(2, 1);
    canvasDxPerTargs -> cd(1);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("low_mult") != std::string::npos) {
            string tmpHistName = histDxPerTargs[iDir] -> GetName();
            string stringToSubtract = "low mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            histDxPerTargs[iDir] -> SetName(tmpHistName.c_str());
            histDxPerTargs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();
    canvasDxPerTargs -> cd(2);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("high_mult") != std::string::npos) {
            string tmpHistName = histDxPerTargs[iDir] -> GetName();
            string stringToSubtract = "high mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            histDxPerTargs[iDir] -> SetName(tmpHistName.c_str());
            histDxPerTargs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();

    // Deltay
    TCanvas *canvasDyPerTargs = new TCanvas("canvasDyPerTargs", "", 1600, 600);
    canvasDyPerTargs -> Divide(2, 1);
    canvasDyPerTargs -> cd(1);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("low_mult") != std::string::npos) {
            string tmpHistName = histDyPerTargs[iDir] -> GetName();
            string stringToSubtract = "low mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            histDyPerTargs[iDir] -> SetName(tmpHistName.c_str());
            histDyPerTargs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();
    canvasDyPerTargs -> cd(2);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("high_mult") != std::string::npos) {
            string tmpHistName = histDyPerTargs[iDir] -> GetName();
            string stringToSubtract = "high mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            histDyPerTargs[iDir] -> SetName(tmpHistName.c_str());
            histDyPerTargs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();



    // Deltaz
    TCanvas *canvasDzPerTargs = new TCanvas("canvasDzPerTargs", "", 1600, 600);
    canvasDzPerTargs -> Divide(2, 1);
    canvasDzPerTargs -> cd(1);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("low_mult") != std::string::npos) {
            string tmpHistName = histDzPerTargs[iDir] -> GetName();
            string stringToSubtract = "low mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            histDzPerTargs[iDir] -> SetName(tmpHistName.c_str());
            histDzPerTargs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();
    canvasDzPerTargs -> cd(2);
    for (int iDir = 0;iDir < nDirs;iDir++) {
        if (dirNames[iDir].find("high_mult") != std::string::npos) {
            string tmpHistName = histDzPerTargs[iDir] -> GetName();
            string stringToSubtract = "high mult. ";
            std::string::size_type pos = tmpHistName.find(stringToSubtract);
            if (pos != std::string::npos) {
                tmpHistName.erase(pos, stringToSubtract.length());
            }
            tmpHistName = Form("%s, counts = %3.0f", tmpHistName.c_str(), hnverts[iDir] -> Integral(2, -1));
            histDzPerTargs[iDir] -> SetName(tmpHistName.c_str());
            histDzPerTargs[iDir] -> Draw(iDir == 0 ? "EP" : "EP SAME");
        }
    }
    gPad -> Update();
    gStyle -> SetStatFontSize(0.03);
    gPad -> BuildLegend();



    canvasNvert -> SaveAs("outputs/summaryNvert.pdf");
    canvasNcontr -> SaveAs("outputs/summaryNcontr.pdf");
    canvasDxPerTargs -> SaveAs("outputs/summaryDxPerTargs.pdf");
    canvasDyPerTargs -> SaveAs("outputs/summaryDyPerTargs.pdf");
    canvasDzPerTargs -> SaveAs("outputs/summaryDzPerTargs.pdf");
}
////////////////////////
void SetHistogram(TH1F *hist, string name, Color_t color, int markerStyle, int markerSize = 1) {
    hist -> SetName(name.c_str());
    hist -> SetLineColor(color);
    hist -> SetLineWidth(1);
    hist -> SetMarkerStyle(markerStyle);
    hist -> SetMarkerColor(color);
    hist -> SetMarkerSize(markerSize);
} 