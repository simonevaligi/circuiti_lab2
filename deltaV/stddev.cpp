#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

double CalculateMean(const std::vector<double>& data) {
    double sum = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    return sum / data.size();
}

double CalculateStandardDeviation(const std::vector<double>& data) {
    double mean = CalculateMean(data);
    double variance = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        variance += (data[i] - mean) * (data[i] - mean);
    }
    return sqrt(variance / data.size());
}

void ReadData(const std::string& filename, std::vector<double>& data) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double value;
        if (!(iss >> value)) { break; } // error
        data.push_back(value);
    }
}

void CalculateAndPrintStandardDeviation(const std::vector<double>& data) {
    double stdDev = CalculateStandardDeviation(data);
    std::cout << "Deviazione standard dei dati: " << stdDev << std::endl;
}

void MyMacro() {
    // Nome del file da leggere fornito dall'utente
    std::string filename;
    std::cout << "Inserisci il nome del file di dati (formato: una colonna di dati): ";
    std::cin >> filename;

    // Vettore per contenere i dati
    std::vector<double> data;

    // Leggi i dati dal file
    ReadData(filename, data);

    // Calcola e stampa la deviazione standard dei dati
    CalculateAndPrintStandardDeviation(data);
}
