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
    graph->SetTitle("V(t), freq. = 12 kHz");
    graph->GetXaxis()->SetTitle("Time (s)");
    graph->GetYaxis()->SetTitle("Voltage (V)");

    return graph;

}

void PlotData() {
    TCanvas* canvas = new TCanvas("canvas", "Graphs", 800, 600);
    canvas->Divide(2, 2);

    TGraph* graph1 = nullptr;
    TGraph* graph2 = nullptr;
    //TGraph* graph3 = nullptr;
    //TGraph* graph4 = nullptr;

try{
    graph1=CreateGraph("V(t)_gen.txt", graph1); 
    graph2=CreateGraph("V(t+1.00127E-6 s)_R.txt", graph2);
    //graph3=CreateGraph("f_12kHz/V(t)_L.txt", graph3);
    //graph4=CreateGraph("f_12kHz/V(t)_C.txt", graph4);
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

// if (graph3) {
//     graph3->SetMarkerStyle(7);
//     graph3->SetMarkerColor(kGreen); 
//     graph3->SetLineColor(kGreen);
//     graph3->Draw("same, PL");
// }


// if (graph4) {
//     graph4->SetMarkerStyle(7);
//     graph4->SetMarkerColor(kBlue);
//     graph4->SetLineColor(kBlue);  
//     graph4->Draw("same, PL");
// }

TLegend *leg = new TLegend(0.7,0.7,0.9, 0.9); 
leg->SetHeader("Legenda", "C");
leg->AddEntry(graph1, "V_gen", "p");
leg->AddEntry(graph2, "V_R", "p");
// leg->AddEntry(graph3, "V_L", "p");
// leg->AddEntry(graph4, "V_C", "p");
leg->Draw(); 
    canvas->Update();
    canvas->Draw();
}

void VoltageGraphs() {
    PlotData();
}
