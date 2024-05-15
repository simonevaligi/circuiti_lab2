#include <iostream>

TGraph* CreateGraph(const char* filename, TGraph* graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;

        throw std::runtime_error("Could not open file");

    }

    std::vector<double> time, voltage;
    double t, v;
    while (file >> t >> v) {
        time.push_back(t);
        voltage.push_back(v);
    }

    graph = new TGraph(time.size(), &time[0], &voltage[0]);
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);
    graph->SetTitle("V(t), gen");
    graph->GetXaxis()->SetTitle("Time");
    graph->GetYaxis()->SetTitle("Voltage");

    return graph;

}

void PlotData() {
    TCanvas* canvas = new TCanvas("canvas", "Graphs", 800, 600);
    canvas->Divide(2, 2);

    TGraph* graph1 = nullptr;
    TGraph* graph2 = nullptr;
    TGraph* graph3 = nullptr;

try{
    graph1=CreateGraph("f_resonance/V(t)_gen.txt", graph1); 

  
    graph2=CreateGraph("f_3kHz/V(t)_gen.txt", graph2);
    graph3=CreateGraph("f_12kHz/V(t)_gen.txt", graph3);
    }
    catch(const std::runtime_error& e){
    std::cerr << "Error: " << e.what() << std::endl;
    return;
}

if (graph1) {
    graph1->SetMarkerStyle(7);
    graph1->SetMarkerColor(kBlack);
    graph1->SetLineColor(kBlack);
    graph1->Draw("APL");
}

if (graph2) {
    graph2->SetMarkerStyle(7);
    graph2->SetMarkerColor(kRed);
    graph2->SetLineColor(kRed); 
    graph2->Draw("same, PL");  
}

if (graph3) {
    graph3->SetMarkerStyle(7);
    graph3->SetMarkerColor(kGreen); 
    graph3->SetLineColor(kGreen);
    graph3->Draw("same, PL");
}

TLegend *leg = new TLegend(0.7,0.7,0.9, 0.9); 
leg->SetHeader("Legenda", "C");
leg->AddEntry(graph1, "V_gen (f_0)", "p");
leg->AddEntry(graph2, "V_gen (3kHz)", "p");
leg->AddEntry(graph3, "V_gen (12kHz)", "p");
leg->Draw(); 
    canvas->Update();
    canvas->Draw();
}

void VoltageGraphs() {
    PlotData();
}
