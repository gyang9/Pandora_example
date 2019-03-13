#include <iostream>
#include <fstream>

{
  ifstream in;
  in.open("output.txt");
  //out<<o_id<<" "<<m_muonSign2<<" "<<depositEnergy<<" "<<kf.state().transpose()(1)<<" "<<kf.state().transpose()(2)<<" "<<meanFirstOrder<<" "<<meanSecondOrder<<" "<<trueEnergy<<std::endl;

  TH1I* h1 = new TH1I("","charge ID",5,-2,2);
  TH2D* h2 = new TH2D("","true E vs. mean second",10,0,4000,20,-100,100);
  TH2D* h3 = new TH2D("","true E vs. mean third",10,0,4000,20,-10,10);

  TH2D* hh2 = new TH2D("","true E vs. last second",10,0,4000,20,-100,100);
  TH2D* hh3 = new TH2D("","true E vs. last third",10,0,4000,20,-10,10);
  TH2D* h5 = new TH2D("","true vs. deposit",10,0,3000,10,0,300);

  int counter = 0;
  int a,b;
  double c,d,e,f,g,h;
  while(!in.eof())
  {
      in>>a>>b>>c>>d>>e>>f>>g>>h;
      cout<<counter<<" "<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<h<<endl;
      if(e<0)h1->Fill(-1);
      else h1->Fill(1);
      h2->Fill(h,d);
      h3->Fill(h,e);
      hh2->Fill(h,f);
      hh3->Fill(h,g);
      h5->Fill(h,c);
      if(counter > 900) break;
      counter++;
  }


  TCanvas* c1 = new TCanvas();
  c1->Divide(3,2);
  c1->cd(1);
  h1->Draw();
  c1->cd(2);
  h2->Draw("colz");
  c1->cd(3);
  h3->GetXaxis()->SetTitle("True energy (GeV)");
  h3->GetYaxis()->SetTitle("bending term");
  h3->Draw("colz");
  c1->cd(4);
  hh2->Draw("colz");
  c1->cd(5);
  hh3->Draw("colz");
  c1->cd(6);
  h5->Draw("colz");

}
