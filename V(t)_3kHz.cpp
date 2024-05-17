#include <iostream>
#include <fstream>
#include <string>

void plotGraph() {
    // Definizione dei percorsi dei file
    const char* file1 = "f_3kHz (corretto)/V(t)_gen.txt";
    const char* file2 = "f_3kHz (corretto)/V(t)_R.txt";
    const char* file3 = "f_3kHz (corretto)/V(t)_L.txt";
    const char* file4 = "f_3kHz (corretto)/V(t)_C.txt";

    // Include delle librerie di ROOT
    #include "TCanvas.h"
    #include "TGraphErrors.h"
    #include "TAxis.h"

    // Definizione del numero di punti dei grafici
    const int numPoints = 300;

    // Apertura dei file
    std::ifstream inFile1(file1);
    std::ifstream inFile2(file2);
    std::ifstream inFile3(file3);
    std::ifstream inFile4(file4);

    // Controllo se i file sono stati aperti correttamente
    if (!inFile1.is_open() || !inFile2.is_open() || !inFile3.is_open() || !inFile4.is_open()) {
        std::cerr << "Errore nell'apertura dei file." << std::endl;
        return;
    }

    // Definizione degli array per i dati
    double time[numPoints];
    double voltage1[numPoints];
    double voltage2[numPoints];
    double voltage3[numPoints];
    double voltage4[numPoints];
    double error[numPoints];

    // Lettura dei dati dai file e conversione del tempo in millisecondi
    for (int i = 0; i < numPoints; ++i) {
        double rawTime;
        inFile1 >> rawTime >> voltage1[i];
        time[i] = rawTime * 1000.0; // Converti il tempo da secondi a millisecondi
        inFile2 >> rawTime >> voltage2[i];
        inFile3 >> rawTime >> voltage3[i];
        inFile4 >> rawTime >> voltage4[i];
        error[i] = 0.007019; // Definizione dell'errore per ogni punto
    }

    // Creazione di un nuovo canvas
    TCanvas *c1 = new TCanvas("c1","Graph with errors",200,10,700,700);

    // Rimozione del titolo standard del canvas
    c1->SetTitle("");

    // Creazione del grafico con barre di errore
    TGraphErrors *gr1 = new TGraphErrors(numPoints, time, voltage1, 0, error);
    TGraphErrors *gr2 = new TGraphErrors(numPoints, time, voltage2, 0, error);
    TGraphErrors *gr3 = new TGraphErrors(numPoints, time, voltage3, 0, error);
    TGraphErrors *gr4 = new TGraphErrors(numPoints, time, voltage4, 0, error);

    // Impostazione dei titoli degli assi
    gr1->GetXaxis()->SetTitle("Tempo (ms)");
    gr1->GetYaxis()->SetTitle("Tensione (V)");

    // Impostazione dei colori e dello stile dei grafici
    gr1->SetLineColor(kBlack);
    gr1->SetMarkerColor(kBlack);
    gr1->SetMarkerStyle(1);

    gr2->SetLineColor(kRed);
    gr2->SetMarkerColor(kRed);
    gr2->SetMarkerStyle(1);

    gr3->SetLineColor(kGreen);
    gr3->SetMarkerColor(kGreen);
    gr3->SetMarkerStyle(1);

    gr4->SetLineColor(kBlue);
    gr4->SetMarkerColor(kBlue);
    gr4->SetMarkerStyle(1);

    // Disegno dei grafici sul canvas
    gr1->Draw("APL");
    gr2->Draw("PL SAME");
    gr3->Draw("PL SAME");
    gr4->Draw("PL SAME");

    // Creazione della legenda
    TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->SetHeader("Legenda", "C");
    legend->AddEntry(gr1,"V(t)_gen","lep");
    legend->AddEntry(gr2,"V(t)_R","lep");
    legend->AddEntry(gr3,"V(t)_L","lep");
    legend->AddEntry(gr4,"V(t)_C","lep");
    legend->Draw();

    // Mostra il canvas
    c1->Draw();
}
