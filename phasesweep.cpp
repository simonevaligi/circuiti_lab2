#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TImage.h>

void plotPhases() {
    // Open the data file
    std::ifstream infile("phasesweepRLC.txt");
    if (!infile.is_open()) {
        std::cerr << "Error opening data file phasesweepRLC.txt" << std::endl;
        return;
    }

    // Vectors to store data
    std::vector<double> frequencies, phase_R, phase_L, phase_C, phase_RLC;

    // Read data from the file
    double freq, phi_R, phi_L, phi_C, phi_RLC;
    while (infile >> freq >> phi_R >> phi_L >> phi_C >> phi_RLC) {
        frequencies.push_back(freq);
        phase_R.push_back(phi_R);
        phase_L.push_back(phi_L);
        phase_C.push_back(phi_C);
        phase_RLC.push_back(phi_RLC);
    }

    infile.close();

    // Print the data for debugging
    std::cout << "Data read from file:" << std::endl;
    for (size_t i = 0; i < frequencies.size(); ++i) {
        std::cout << frequencies[i] << "\t" << phase_R[i] << "\t" << phase_L[i] << "\t" << phase_C[i] << "\t" << phase_RLC[i] << std::endl;
    }

    // Check if any data was read
    if (frequencies.empty()) {
        std::cerr << "No data found in the file" << std::endl;
        return;
    }

    // Create graphs
    TGraph *gr_R = new TGraph(frequencies.size(), &frequencies[0], &phase_R[0]);
    TGraph *gr_L = new TGraph(frequencies.size(), &frequencies[0], &phase_L[0]);
    TGraph *gr_C = new TGraph(frequencies.size(), &frequencies[0], &phase_C[0]);
    TGraph *gr_RLC = new TGraph(frequencies.size(), &frequencies[0], &phase_RLC[0]);

    // Set titles and axes
    gr_R->SetTitle("Phases vs Frequency;Frequency (Hz);Phase (degrees)");
    gr_R->SetLineColor(kRed);
    gr_R->SetMarkerColor(kRed);
    gr_R->SetMarkerStyle(20);

    gr_L->SetLineColor(kBlue);
    gr_L->SetMarkerColor(kBlue);
    gr_L->SetMarkerStyle(21);

    gr_C->SetLineColor(kGreen);
    gr_C->SetMarkerColor(kGreen);
    gr_C->SetMarkerStyle(22);

    gr_RLC->SetLineColor(kMagenta);
    gr_RLC->SetMarkerColor(kMagenta);
    gr_RLC->SetMarkerStyle(23);

    // Create canvas
    TCanvas *c1 = new TCanvas("c1", "Phases vs Frequency", 800, 600);

    // Draw graphs
    gr_R->Draw("ALP");
    gr_L->Draw("LP SAME");
    gr_C->Draw("LP SAME");
    gr_RLC->Draw("LP SAME");

    // Add legend
    TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9);
    legend->AddEntry(gr_R, "Phase R", "lp");
    legend->AddEntry(gr_L, "Phase L", "lp");
    legend->AddEntry(gr_C, "Phase C", "lp");
    legend->AddEntry(gr_RLC, "Phase RLC", "lp");
    legend->Draw();

    // Save the graph as image file
    c1->SaveAs("phases_vs_frequency.png");

    // Print the graph as PDF
    TImage *img = TImage::Create();
    img->FromPad(c1);
    img->WriteImage("phases_vs_frequency.pdf");
    delete img;

    delete c1; // Free the memory allocated for the canvas
}

int main() {
    plotPhases();
    return 0;
}
