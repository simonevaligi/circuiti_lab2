void fit_and_find_max() {
    // Caricamento del file di dati
    ifstream infile("data V(f)/V(f)_R.txt");
    vector<double> f, V_R;
    double x, y;
    while (infile >> x >> y) {
        f.push_back(x);  // Frequenze già in kHz
        V_R.push_back(y);
    }

    // Creazione del grafico
    int n = f.size();
    TGraph *graph = new TGraph(n, &f[0], &V_R[0]);
    graph->SetTitle("Fit della ddp della resistenza in un circuito RLC serie;f (kHz);V_R (V)");
    graph->SetMarkerStyle(7);
    graph->Draw("AP");

    // Definizione della funzione di fit personalizzata
    TF1 *fitFunc = new TF1("fitFunc",
        "[0] * [1] / sqrt([0]*[0] + pow(2*3.141592653589793*x*[2] - 1/(2*3.141592653589793*x*[3]), 2))",
        f.front(), f.back());

    // Impostazione dei parametri iniziali
    fitFunc->SetParameters(997, 5, 4.61E-3, 9.7E-8);  // Parametri iniziali per R, V0, L e C

    // Esegui il fit
    graph->Fit(fitFunc, "R");

    // Disegna il fit
    fitFunc->Draw("same");

    // Trova il massimo della funzione di fit
    double maxX = fitFunc->GetMaximumX();
    double maxY = fitFunc->Eval(maxX);

    // Visualizza il massimo
    cout << "Il massimo della funzione di fit si trova a f = " << maxX << " kHz con V_R = " << maxY << " V" << endl;

    // Disegna una linea verticale nel punto di massimo
    TLine *line = new TLine(maxX, graph->GetYaxis()->GetXmin(), maxX, maxY);
    line->SetLineColor(kRed);
    line->SetLineStyle(2);
    line->Draw("same");

    // Aggiorna il canvas
    gPad->Update();
}
