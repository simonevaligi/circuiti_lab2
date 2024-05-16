#include <iostream>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

void plotDataFromFiles() {
    // Creazione di un TCanvas per il plot
    TCanvas *c1 = new TCanvas("c1", "Differenze di Potenziali", 800, 600);

    // Creazione di un TGraph per ogni set di dati
    TGraph *graph[4];

    // Array per memorizzare i nomi dei file .txt
    std::string fileNames[4] = {"data V(f)/V(f)_gen.txt", "data V(f)/V(f)_R.txt", "data V(f)/V(f)_L.txt", "data V(f)/V(f)_C.txt"};

    // Leggere i dati dai file .txt e riempire i TGraph
    for (int i = 0; i < 4; ++i) {
        std::ifstream file(fileNames[i]);
        if (!file.is_open()) {
            std::cerr << "Errore nell'apertura del file " << fileNames[i] << std::endl;
            return;
        }

        std::vector<double> freq, potDiff;
        double f, d;
        while (file >> f >> d) {
            freq.push_back(f);
            potDiff.push_back(d);
        }

        graph[i] = new TGraph(freq.size(), &freq[0], &potDiff[0]);
        graph[i]->SetTitle(("Set " + std::to_string(i + 1)).c_str());
        graph[i]->SetLineColor(i + 1);
        graph[i]->SetMarkerColor(i + 1);
        graph[i]->SetMarkerStyle(20 + i);
    }

    // Settaggio del range sull'asse x e y per adattarsi ai dati
    double minX = graph[0]->GetXaxis()->GetXmin();
    double maxX = graph[0]->GetXaxis()->GetXmax();
    double minY = graph[0]->GetYaxis()->GetXmin();
    double maxY = graph[0]->GetYaxis()->GetXmax();
    for (int i = 1; i < 4; ++i) {
        minX = std::min(minX, graph[i]->GetXaxis()->GetXmin());
        maxX = std::max(maxX, graph[i]->GetXaxis()->GetXmax());
        minY = std::min(minY, graph[i]->GetYaxis()->GetXmin());
        maxY = std::max(maxY, graph[i]->GetYaxis()->GetXmax());
    }

    // Creazione di un TMultiGraph per plottare tutti i TGraph sullo stesso grafico
    TMultiGraph *mg = new TMultiGraph();
    for (int i = 0; i < 4; ++i) {
        mg->Add(graph[i]);
    }
    mg->SetTitle("Differenze di Potenziali");

    // Impostazione dei margini dell'asse x e y
    mg->GetXaxis()->SetLimits(minX, maxX);
    mg->GetYaxis()->SetLimits(minY, maxY);

    // Disegna il TMultiGraph sul canvas
    mg->Draw("APL");

    // Aggiungi una legenda
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    for (int i = 0; i < 4; ++i) {
        legend->AddEntry(graph[i], ("Set " + std::to_string(i + 1)).c_str(), "l");
    }
    legend->Draw();

    // Mostra il canvas
    c1->Draw();
}
