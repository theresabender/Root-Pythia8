// pythia8 basic example
//Author: Andreas Morsch
//
// to run, do
//  root > .x pythia8.C
//
// Note that before executing this script, 
//   -the env variable PYTHIA8 must point to the pythia8100 (or newer) directory
//   -the env variable PYTHIA8DATA must be defined and it must point to $PYTHIA8/xmldoc
//

#include <iostream>
#include <vector>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"
// #include "Pythia8/Event.h"


// ROOT, for histogramming.
#include "TH1.h"
#include "TClonesArray.h"
#include "TParticle.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"
#include "TTree.h" /* this */

using namespace Pythia8;

int main(int argc, char* argv[]) {
    Int_t nev  = 20000;
    Int_t ndeb = 1;

    // Create the ROOT application environment.
    TApplication theApp("pythia8test", &argc, argv);
    
    TFile f("output.root", "recreate");
    TFile *f1 = new TFile("sims.root","READ");
    TTree *T = (TTree*)f1->Get("T");
    
    TBranch *b_event = (TBranch*)T->GetBranch("event");
    Event *event = new Event();
    b_event->SetAddress(&event);
    
    vector<Int_t> daughterList;
    vector<Int_t> granddaughterList;
    Int_t Nfinaldaughters = 0;
    Int_t Nnonfinaldaughters = 0;
    
// Histograms
    TH1F* yH = new TH1F("etaH", "Higgs pseudorapidity", 100, -6.28, 6.28);
    TH1F* ptH  = new TH1F("ptH",  "Higgs transverse momentum", 100, 0., 200.);
    TH1D* m0 = new TH1D("mass", "Mass of Higgs", 100, 0., 200.);
    TH1F* energy_hist = new TH1F("energy", "Energy of Higgs", 100, 0., 500.);
    TH1F* px_hist = new TH1F("px", "Higgs Momentum (X-Direction)", 100, -300., 300.);
    TH1F* py_hist = new TH1F("py", "Higgs Momentum (Y-Direction)", 100, -300., 300.);
    TH1F* pz_hist = new TH1F("pz", "Higgs Momentum (Z-Direction)", 100, -500., 500.);
    TH1I* daughters_hist = new TH1I("daughters", "Higgs Daughters", 61, -30, 30);
    TH1I* finaldaughhters_hist = new TH1I("finaldaughters", "Higgs Final Daughters", 61, -30, 30);
    TH1I* nonfinaldaughters_hist = new TH1I("nonfinaldaughters", "Higgs Non-final Daughters", 61, -30, 30);
    TH1F* yH_daughters = new TH1F("etaH daughters", "Higgs daughters pseudorapidity", 100, -6.28, 6.28);
    TH1F* ptH_daughters  = new TH1F("ptH daughters",  "Higgs daughters transverse momentum", 100, 0., 200.);
    TH1D* m0_daughters = new TH1D("mass daughters", "Mass of Higgs daughters", 100, 0., 200.);
    TH1F* energy_hist_daughters = new TH1F("energy daughters", "Energy of Higgs daughters", 100, 0., 500.);
    TH1F* px_hist_daughters = new TH1F("px daughters", "Higgs Daughters Momentum (X-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters = new TH1F("py daughters", "Higgs Daughters Momentum (Y-Direction)", 100, -300., 300.);
    TH1F* pz_hist_daughters = new TH1F("pz daughters", "Higgs Daughters Momentum (Z-Direction)", 100, -500., 500.);
   
    
    // this is event cycle
    Int_t nEntries = T->GetEntries();
    cout << "nEntries=" << nEntries << endl;
    
    for(Int_t i=0; i<nEntries; ++i) {
        T->GetEvent(i);

        cout << "|event|=" << event->size() << endl;

        // this is event evaluation
        if (event->size()){
            
            // this is particle loop
            for (Int_t iparticle=0; iparticle<event->size(); iparticle++){

                if (event->at(iparticle).id() == 25){
                    
                    Double_t eta = event->at(iparticle).eta();
                    Double_t energy = event->at(iparticle).e();
                    Double_t pt  = event->at(iparticle).pT();
                    Vec4 momentum = event->at(iparticle).p();
                    Double_t mass = event->at(iparticle).m();
                    Double_t px = event->at(iparticle).px();
                    Double_t py = event->at(iparticle).py();
                    Double_t pz = event->at(iparticle).pz();

                    yH->Fill(eta);
                    ptH->Fill(pt, 1./(2. * pt));
                    m0->Fill(mass);
                    energy_hist->Fill(energy);
                    px_hist->Fill(px);
                    py_hist->Fill(py);
                    pz_hist->Fill(pz);
                    
                    
                    cout << "event " << i << " id:" << event->at(iparticle).id()
                        << " isFinal:" << event->at(iparticle).isFinal() << endl;

                    daughterList = event->daughterList(iparticle);

                    cout << " |daughterList|=" << daughterList.size() << endl;
                        // this is daughter loop
                    for (Int_t daughter_index=0; daughter_index<daughterList.size(); daughter_index++ ){
                        Int_t daughter_row_number = daughterList.at(daughter_index);
                        Int_t pdg_daughters = event->at(daughter_row_number).id();
                        cout << "daughter #" << daughter_index << " at row" << daughter_row_number << " has PDG number " << pdg_daughters << endl;
                    
                        if (pdg_daughters != 25){

                            Double_t eta_daughters = event->at(daughter_row_number).eta();
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Vec4 momentum_daughters = event->at(daughter_row_number).p();
                            Double_t mass_daughters = event->at(daughter_row_number).m();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                        
                            daughters_hist->Fill(pdg_daughters);
                            yH_daughters->Fill(eta_daughters);
                            ptH_daughters->Fill(pt_daughters);
                            m0_daughters->Fill(mass_daughters);
                            energy_hist_daughters->Fill(energy_daughters);
                            px_hist_daughters->Fill(px_daughters);
                            py_hist_daughters->Fill(py_daughters);
                            pz_hist_daughters->Fill(pz_daughters);
                            
                            granddaughterList = event->daughterList(daughter_row_number);
                            Int_t Ngrandaughters = granddaughterList.size();
                            

                        if (Ngrandaughters > 1){
                            nonfinaldaughters_hist->Fill(pdg_daughters);
                            Nnonfinaldaughters += 1;

                        } else {
                            
                        if (Ngrandaughters == 1){
                            Int_t granddaughter_row_number = granddaughterList.at(0);
                                Int_t pdg_granddaughter = event->at(granddaughter_row_number).id();

                                if (pdg_daughters == pdg_granddaughter) {
                                    finaldaughhters_hist->Fill(event->at(daughter_row_number).id());
                                    Nfinaldaughters+=1;

                                } else {
                                    nonfinaldaughters_hist->Fill(event->at(daughter_row_number).id());
                                    Nnonfinaldaughters += 1;
                                } // else of: if (pdg_daughters == pdg_granddaughter) {
                              
                            } else {
                                finaldaughhters_hist->Fill(event->at(daughter_row_number).id());
                                Nfinaldaughters+=1;

                                } // else of: if Ngranddaughters==1
                            } // else if/l Ngranddaugtres>1
                        } // if daughter is not Higgs
                    } // end of daughter loop
                } // if (event->at(iparticle).id() == 25) ... parent is Higgs
            } // end of particle loop
        } // end of event evaluation
    } // end of event cycle
    
    
    cout << "nEntries=" << nEntries << endl;
    
    f.cd();

    px_hist->Write();
    py_hist->Write();
    pz_hist->Write();
    m0->Write();
    energy_hist->Write();
    ptH->Write();
    yH->Write();
    daughters_hist->Write();
    finaldaughhters_hist->Write();
    nonfinaldaughters_hist->Write();
    px_hist_daughters->Write();
    py_hist_daughters->Write();
    pz_hist_daughters->Write();
    m0_daughters->Write();
    energy_hist_daughters->Write();
    ptH_daughters->Write();
    yH_daughters->Write();
 
    f.Close();
    
    f1->Close();
    
} // end of main function
