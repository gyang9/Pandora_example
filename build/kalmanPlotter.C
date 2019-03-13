{
  #include "TGraph.h"

  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat("");

  gStyle->SetLabelFont(102,"");
  gStyle->SetLabelSize(0.06,"");
  gStyle->SetLabelFont(102,"xyz");
  gStyle->SetLabelSize(0.06,"xyz");
  gStyle->SetLabelOffset(0.001,"x");
  gStyle->SetLabelOffset(0.01,"y");

  gStyle->SetTitleFont(42,"xyz");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleSize(0.06,"xyz");
  gStyle->SetTitleOffset(1.05,"x");
  gStyle->SetTitleOffset(1.25,"y");

  gStyle->SetStripDecimals(kFALSE);

  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);

  gStyle->SetStatW(0.35);
  gStyle->SetStatH(0.25);

  //gStyle->SetTitleW(0.2);
  //gStyle->SetTitleH(0.2);

  gStyle->SetPadTickX(kTRUE);
  gStyle->SetPadTickY(kTRUE);

  gStyle->SetPalette(1);
  gStyle->SetNumberContours(99);

  gStyle->SetHistLineWidth(3);
  gStyle->SetFrameLineWidth(3);
  gStyle->SetFuncWidth(3);

  gStyle->SetStatFont(42);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);

  ifstream in;
  in.open("outputExample.txt");
  int counter = 0;
  double a[200];
  int b;
  int n = 150;
  int aa;
  double cc,dd;
  double c[200];
  double d[200];
  double e,f,g,h;
  while(!in.eof())
  {
      in>>aa>>cc>>dd;
      a[counter] = aa;
      c[counter] = cc;
      d[counter] = dd;
      counter++;
  }

  TCanvas* c1 = new TCanvas();
  TGraph* gr = new TGraph(n , a, c );
  gr->SetMarkerSize(1);
  gr->SetMarkerStyle(4);
  gr->GetXaxis()->SetTitle("Y travel distance (cm)");
  gr->GetYaxis()->SetTitle("Z location (cm)");
  gr->Draw("AP");

  TGraph* g2 = new TGraph("outputExample.txt","%lg %*lg %lg");
  g2->SetLineColor(2);
  g2->SetLineWidth(2);
  g2->Draw("same");

  TLegend* legend = new TLegend(0.1, 0.6, 0.25, 0.9);
  legend->SetHeader("Kalman filter");
  legend->AddEntry(gr,"hit points","p");
  legend->AddEntry(g2,"fitted curve","l");
  legend->Draw();

  c1->SaveAs("kalmanFilterExample.C")

}
