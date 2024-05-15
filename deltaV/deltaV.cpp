#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>

void ReadData(const std::string& filename, std::vector<double>& times, std::vector<double>& ddp_values) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double time, ddp;
        if (!(iss >> time >> ddp)) { break; } // error
        times.push_back(time);
        ddp_values.push_back(ddp);
    }
}

void FitGaussian(const std::vector<double>& times, const std::vector<double>& ddp_values) {
    // Creazione di un istogramma per i dati
    TH1F *histogram = new TH1F("histogram", "Dati", 100, -5, 5);

    // Riempimento dell'istogramma con i valori di ddp
    for (size_t i = 0; i < ddp_values.size(); ++i) {
        histogram->Fill(ddp_values[i]);
    }

    // Fitting della gaussiana ai dati
    TF1 *fitFunc = new TF1("fitFunc", "gaus", -5, 5);
    histogram->Fit(fitFunc, "Q");

    // Ottenere il valore medio e la deviazione standard dei dati
    double mean = histogram->GetMean();
    double stdDev = histogram->GetStdDev();

    // Calcolare il valore medio delle ddp e l'incertezza
    double sum = 0.0;
    for (size_t i = 0; i < ddp_values.size(); ++i) {
        sum += ddp_values[i];
    }
    double ddp_mean = sum / ddp_values.size();
    
    double ddp_error = 0.0;
    for (size_t i = 0; i < ddp_values.size(); ++i) {
        ddp_error += (ddp_values[i] - ddp_mean) * (ddp_values[i] - ddp_mean);
    }
    ddp_error = sqrt(ddp_error / (ddp_values.size() - 1));

    // Creazione di un canvas per visualizzare il grafico
    TCanvas *canvas = new TCanvas("canvas", "Grafico della Gaussiana", 800, 600);
    histogram->Draw();
    fitFunc->Draw("same");

    // Output del valore medio e dell'incertezza della ddp
    std::cout << "Valore medio delle ddp: " << ddp_mean << std::endl;
    std::cout << "Incertezza delle ddp: " << ddp_error << std::endl;

    // Mostra il canvas
    canvas->Draw();
}

void MyMacro() {
    // Nome del file da leggere fornito dall'utente
    std::string filename;
    std::cout << "Inserisci il nome del file di dati (formato: tempi ddp): ";
    std::cin >> filename;

    // Vettori per contenere tempi e valori di ddp
    std::vector<double> times;
    std::vector<double> ddp_values;

    // Leggi i dati dal file
    ReadData(filename, times, ddp_values);

    // Fai il fitting della gaussiana e calcola il valore medio delle ddp e l'incertezza
    FitGaussian(times, ddp_values);
}
