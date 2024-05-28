#include <TMath.h>
#include <TGraph.h>
#include <TF1.h>
#include <TAxis.h>
#include <iostream>

Double_t r_w(Double_t *f, Double_t *par) {
    Double_t omega = f[0] * 2 * TMath::Pi();
    Double_t gamma = par[0];
    Double_t wo = par[1];
    Double_t Risposta = 1 / (TMath::Sqrt(1 + (1 / (gamma * gamma)) * ((omega * omega - wo * wo) * (omega * omega - wo * wo) / (omega * omega))));
    return Risposta;
}

void Fit() {
    TGraph *data = new TGraph("data V(f)/V(f)_R.txt", "%lg %lg");
    TF1 *f1 = new TF1("f1", r_w, 5000, 20000, 2);
    f1->SetParameter(0, 59300); // gamma
    f1->SetParameter(1, 55048); // wo

    data->Fit(f1);
    data->SetLineColor(4);
    data->SetMarkerColor(4);
    data->Draw("AP");
    f1->Draw("SAME");

    data->SetTitle("Funzione di risposta");
    data->GetXaxis()->SetTitle("Frequenza, kHz");
    data->GetYaxis()->SetTitle("Tensione, V");
    data->GetXaxis()->CenterTitle(true);
    data->GetYaxis()->CenterTitle(true);

    std::cout << "gamma = " << f1->GetParameter(0) << std::endl;
    std::cout << "wo = " << f1->GetParameter(1) << std::endl;
    //std::cout << "L = " << f1->GetParameter(2) << std::endl;
    //std::cout << "C = " << f1->GetParameter(3) << std::endl;
    //std::cout << "Massima ampiezza = " << f1->GetMaximum() << std::endl;
    //std::cout << "Frequenza corrispondente al massimo = " << f1->GetMaximumX() << std::endl;
}