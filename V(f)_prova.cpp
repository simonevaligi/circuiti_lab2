#include <iostream>

void plotDataFromFiles() {
    // Creazione di un TCanvas per il plot
    TCanvas *c1 = new TCanvas("c1", "Voltage vs Frequence", 700, 700);

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
        graph[i]->SetMarkerStyle(7);
    }

    // Settaggio del range sull'asse x e y per adattarsi ai dati
    double minX = graph[1]->GetXaxis()->GetXmin();
    double maxX = graph[1]->GetXaxis()->GetXmax();
    double minY = graph[1]->GetYaxis()->GetXmin();
    double maxY = graph[1]->GetYaxis()->GetXmax();

    // Esegui il fit solo per il secondo grafico (graph[1])
    TF1 *fitFunc = new TF1("fitFunc",
        "[0] * [1] / sqrt([0]*[0] + pow(2*3.141592653589793*x*[2] - 1/(2*3.141592653589793*x*[3]), 2))",
        minX, maxX);
    fitFunc->SetParameters(997, 5, 4.61E-3, 9.7E-8);  // Parametri iniziali per R, V0, L e C
    graph[1]->Fit(fitFunc, "R");
    fitFunc->Draw("same");

    // Creazione di un TMultiGraph per plottare tutti i TGraph sullo stesso grafico
    TMultiGraph *mg = new TMultiGraph();
    for (int i = 0; i < 4; ++i) {
        mg->Add(graph[i]);
    }

    // Impostazione dei margini dell'asse x e y
    mg->GetXaxis()->SetLimits(minX, maxX);
    mg->GetYaxis()->SetLimits(minY, maxY);

    // Definizione delle etichette degli assi
    mg->GetXaxis()->SetTitle("Frequenza (kHz)");
    mg->GetYaxis()->SetTitle("Tensione (V)");

    // Disegna il TMultiGraph sul canvas
    mg->Draw("APL");

    // Aggiungi una legenda
    TLegend *leg = new TLegend(0.7,0.7,0.9, 0.9); 
    leg->SetHeader("Legenda", "C");
    leg->AddEntry(graph[0], "V_gen", "p");
    leg->AddEntry(graph[1], "V_R", "p");
    leg->AddEntry(graph[2], "V_L", "p");
    leg->AddEntry(graph[3], "V_C", "p");
    leg->Draw(); 

    // Mostra il canvas
    c1->Draw();
}
