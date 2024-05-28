#include <iostream>

void plotGraphs() {
    // Percorsi dei file di testo
    const char* file1 = "VL_VC_Lissajous/VL_VC_3kHz.txt";
    const char* file2 = "VL_VC_Lissajous/VL_VC_resonance.txt";
    const char* file3 = "VL_VC_Lissajous/VL_VC_12kHz.txt";

    // Funzione per leggere i dati dal file di testo
    auto readData = [](const char* filename) {
        std::vector<double> x, y;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Errore nell'apertura del file: " << filename << std::endl;
            return std::make_pair(x, y);
        }

        double xVal, yVal;
        while (file >> xVal >> yVal) {
            x.push_back(xVal);
            y.push_back(yVal);
        }

        file.close();
        return std::make_pair(x, y);
    };

    // Lettura dei dati dai file
    auto data1 = readData(file1);
    auto data2 = readData(file2);
    auto data3 = readData(file3);

    // Creazione dei grafici
    TGraph* graph1 = new TGraph(data1.first.size(), data1.first.data(), data1.second.data());
    TGraph* graph2 = new TGraph(data2.first.size(), data2.first.data(), data2.second.data());
    TGraph* graph3 = new TGraph(data3.first.size(), data3.first.data(), data3.second.data());

    // Personalizzazione dei grafici (opzionale)
    graph1->SetLineColor(kOrange);
    graph2->SetLineColor(kMagenta);
    graph3->SetLineColor(kCyan);

    graph1->SetLineWidth(1);
    graph2->SetLineWidth(1);
    graph3->SetLineWidth(1);

    // Calcolo del range degli assi
    double xMin = std::min({*std::min_element(data1.first.begin(), data1.first.end()), 
                            *std::min_element(data2.first.begin(), data2.first.end()), 
                            *std::min_element(data3.first.begin(), data3.first.end())});
    
    double xMax = std::max({*std::max_element(data1.first.begin(), data1.first.end()), 
                            *std::max_element(data2.first.begin(), data2.first.end()), 
                            *std::max_element(data3.first.begin(), data3.first.end())});
    
    double yMin = std::min({*std::min_element(data1.second.begin(), data1.second.end()), 
                            *std::min_element(data2.second.begin(), data2.second.end()), 
                            *std::min_element(data3.second.begin(), data3.second.end())});
    
    double yMax = std::max({*std::max_element(data1.second.begin(), data1.second.end()), 
                            *std::max_element(data2.second.begin(), data2.second.end()), 
                            *std::max_element(data3.second.begin(), data3.second.end())});

    // Creazione del canvas
    TCanvas* c1 = new TCanvas("c1", "", 800, 1200);

    // Impostazione del range degli assi
    graph1->GetXaxis()->SetLimits(xMin - 0.45, xMax + 0.45);
    graph1->SetMinimum(yMin - 0.79);
    graph1->SetMaximum(yMax + 0.79);

    // Disegno del primo grafico
    graph1->SetTitle("VL vs VC;VC (V);VL (V)");
    graph1->Draw("AL"); // "A" per l'asse, "L" per linee

    // Disegno dei grafici successivi sullo stesso canvas
    graph2->Draw("L SAME"); // "L" per linee, "SAME" per sovrapporre
    graph3->Draw("L SAME");

    // Creazione della legenda
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(graph1, "3 kHz", "l");
    legend->AddEntry(graph2, "7.341 kHz", "l");
    legend->AddEntry(graph3, "12 kHz", "l");
    legend->Draw();

    // Impostazione della dimensione del testo nella legenda
    legend->SetTextSize(0.035);  // Aumenta il valore per aumentare la dimensione del testo

    // Visualizzazione del canvas
    c1->Update();
}
