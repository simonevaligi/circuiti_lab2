#include <cmath>
#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TLegend.h"
#include "TROOT.h"




 Double_t PotenzialeR(double* x, double* par){
    double omega=par[0];
    double phi=par[1];
    double t0=par[2];
    double A=par[3];
    return A*cos(omega*(x[0]-t0)+phi-TMath::Pi()/2.);

}

 //((R*V0)/TMath::Sqrt(R*R + (omega*L-1/(omega*C))*(omega*L-1/(omega*C))))=A
  
void myfunc(double A=5., double omega= 44000., double phi=0.0,double t0=0.0)
   {
      TF1 *f1 = new TF1("myfunc1",PotenzialeR,0,0.000515,4);
      f1->SetParameter(0,omega);
      f1->SetParameter(1,phi);
      f1->SetParameter(2,t0);
      f1->SetParameter(3,A);
      f1->SetParName(0,"omega");
      f1->SetParName(1,"phi");
      f1->SetParName(2,"t0");
      f1->SetParName(3,"A");
      f1->Draw("same");
   }

void mydata(TString fname="fitC.txt")
{
  	 TGraphErrors *data = new TGraphErrors(fname,"%lg %lg");
	data->Draw("AP");
	data->SetLineColor(4);data->SetMarkerColor(4);
	data->SetTitle("Potenziale");
	data->GetXaxis()->SetTitle("Tempo, s");
	data->GetYaxis()->SetTitle("Potenziale, V");
	data->GetXaxis()->CenterTitle(true);
	data->GetXaxis()->CenterTitle(true);
        data->SetMarkerStyle(8);
}
   
void myfit(TString fname="fitC.txt",double A=5., double omega= 44000., double phi=0.0,double t0=0.0)
   {
   	 TGraphErrors *data = new TGraphErrors(fname,"%lg %lg");
   	 TF1 *f1=(TF1*)gROOT->GetFunction("myfunc1");
      f1->SetParameter(0,omega);
      f1->SetParameter(1,phi);
      f1->SetParameter(2,t0);
      f1->SetParameter(3,A);
    data->SetMarkerStyle(8);

    data->Fit("myfunc1","R");
	data->Draw("AP");
	data->SetLineColor(4);data->SetMarkerColor(4);
	f1->Draw("same");
	data->SetTitle("Potenziale");
	data->GetXaxis()->SetTitle("Tempo, s");
	data->GetYaxis()->SetTitle("Potenziale, V");
	data->GetXaxis()->CenterTitle(true);
	data->GetXaxis()->CenterTitle(true);
    TLegend* leg = new TLegend(.6,.7,.9,.9);  leg->SetTextSize(0.04);   leg->SetBorderSize(0);  //no border for legend 
leg->SetFillColor(0);  //fill color is white
    leg->AddEntry(data,"L= ... m, d=... mm","p");
    leg->AddEntry(f1,"fit","l");
	leg->Draw();
   }
   


