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
// #include "TH1.h"
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
    
    TFile f("sims.root", "recreate");
    TTree *T = new TTree("T","ev1 Tree");
    // TODO: TTree definition goes here

//// Histograms
//    TH1F* yH = new TH1F("etaH", "Higgs pseudorapidity", 100, -6.28, 6.28);
//    TH1F* ptH  = new TH1F("ptH",  "Higgs transverse momentum", 100, 0., 200.);
//    TH1D* m0 = new TH1D("mass", "Mass of Higgs", 100, 0., 200.);
//    TH1F* energy_hist = new TH1F("energy", "Energy of Higgs", 100, 0., 500.);
//    TH1F* px_hist = new TH1F("px", "Higgs Momentum (X-Direction)", 100, -300., 300.);
//    TH1F* py_hist = new TH1F("py", "Higgs Momentum (Y-Direction)", 100, -300., 300.);
//    TH1F* pz_hist = new TH1F("pz", "Higgs Momentum (Z-Direction)", 100, -500., 500.);
//    TH1I* daughters_hist = new TH1I("daughters", "Higgs Daughters", 61, -30, 30);
//    TH1I* finaldaughhters_hist = new TH1I("finaldaughters", "Higgs Final Daughters", 61, -30, 30);
//    TH1I* nonfinaldaughters_hist = new TH1I("nonfinaldaughters", "Higgs Non-final Daughters", 61, -30, 30);
//    TH1F* yH_daughters = new TH1F("etaH daughters", "Higgs daughters pseudorapidity", 100, -6.28, 6.28);
//    TH1F* ptH_daughters  = new TH1F("ptH daughters",  "Higgs daughters transverse momentum", 100, 0., 200.);
//    TH1D* m0_daughters = new TH1D("mass daughters", "Mass of Higgs daughters", 100, 0., 200.);
//    TH1F* energy_hist_daughters = new TH1F("energy daughters", "Energy of Higgs daughters", 100, 0., 500.);
//    TH1F* px_hist_daughters = new TH1F("px daughters", "Higgs Daughters Momentum (X-Direction)", 100, -300., 300.);
//    TH1F* py_hist_daughters = new TH1F("py daughters", "Higgs Daughters Momentum (Y-Direction)", 100, -300., 300.);
//    TH1F* pz_hist_daughters = new TH1F("pz daughters", "Higgs Daughters Momentum (Z-Direction)", 100, -500., 500.);
    
// Array of particles
   TClonesArray* particles = new TClonesArray("TParticle", 1000);
// Create pythia8 object
//   TPythia8* pythia8 = new TPythia8();
   Pythia pythia8;
//    Pythia pythia8(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
    
// Configure    

    pythia8.readString("Beams:eCM = 14000.");
    pythia8.readString("HiggsSM:gg2H = on");
    
    // TODO: Event *event goes here, instead of pythia. use puthia8.
    // TODO: TBranch thingy goes here
    Event *event = &pythia8.event;
    T->Branch("event",&event);
    
// Initialize
    
//    pythia8->Initialize(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
//    pythia8.initialize(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
    pythia8.init(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
    
    
    
//    Int_t Nfinaldaughters = 0;
//    Int_t Nnonfinaldaughters = 0;
    
//    id(int idIn) {idSave = idIn; setPDEPtr();
//    status(int statusIn) {statusSave = statusIn;

    // Event loop

    // Begin event loop. Generate event; skip if generation aborted.
    for (int iev = 0; iev < nev; ++iev) {
        if (!pythia8.next()) continue;
        
        if (iev % 100 == 0){
            cout << "Event # " << iev << endl;
        }
        
    
        
//        // Find number of all final charged particles.
//        int nCharged = 0;
//        // Begin particle loop.
//        for (int i = 0; i < pythia8.event.size(); ++i){
//            
//            
//            Double_t eta = pythia8.event[i].eta();
//            Double_t energy = pythia8.event[i].e();
//            Double_t pt  = pythia8.event[i].pT();
//            Vec4 momentum = pythia8.event[i].p();
//            Double_t mass = pythia8.event[i].m();
//            Double_t px = pythia8.event[i].px();
//            Double_t py = pythia8.event[i].py();
//            Double_t pz = pythia8.event[i].pz();
//                
//            if (pythia8.event[i].id() == 25) {
//                
//                if (pt > 0.){
//                    yH->Fill(eta);
//                    ptH->Fill(pt, 1./(2. * pt));
//                    m0->Fill(mass);
//                    energy_hist->Fill(energy);
//                    px_hist->Fill(px);
//                    py_hist->Fill(py);
//                    pz_hist->Fill(pz);
//                } // if pt>0.
//                vector<Int_t> daughterList = pythia8.event[i].daughterList();
//                //cout << " Size: " << daughterList.size() << endl;
//                
//                vector<Int_t> daughters = pythia8.event[i].daughterList();
//                
//                
//                for (Int_t daughter_index=0; daughter_index<daughters.size(); daughter_index++){
//                    Int_t daughter_row_number = daughters.at(daughter_index);
//                    Int_t pdg_daughters=pythia8.event[daughter_row_number].id();
//                    
//                    if (pdg_daughters != 25){
//                        Double_t eta_daughters = pythia8.event[daughter_row_number].eta();
//                        Double_t pt_daughters  = pythia8.event[daughter_row_number].pT();
//                        Double_t energy_daughters = pythia8.event[daughter_row_number].e();
//                        Vec4 momentum_daughters = pythia8.event[daughter_row_number].p();
//                        Double_t mass_daughters = pythia8.event[daughter_row_number].m();
//                        Double_t px_daughters = pythia8.event[daughter_row_number].px();
//                        Double_t py_daughters = pythia8.event[daughter_row_number].py();
//                        Double_t pz_daughters = pythia8.event[daughter_row_number].pz();
//                    
//                        daughters_hist->Fill(pdg_daughters);
//                        yH_daughters->Fill(eta_daughters);
//                        ptH_daughters->Fill(pt_daughters);
//                        m0_daughters->Fill(mass_daughters);
//                        energy_hist_daughters->Fill(energy_daughters);
//                        px_hist_daughters->Fill(px_daughters);
//                        py_hist_daughters->Fill(py_daughters);
//                        pz_hist_daughters->Fill(pz_daughters);
//                    
//                    
//                        vector<Int_t> granddaughters = pythia8.event[daughter_index].daughterList();
//                        Int_t Ngrandaughters = granddaughters.size();
//                    
//                    
//                        if (Ngrandaughters > 1){
//                            nonfinaldaughters_hist->Fill(pdg_daughters);
//                            Nnonfinaldaughters += 1;
//
//                        } else {
//                            // Ngranddaughters <= 1
//                            if (Ngrandaughters == 1){
//                                Int_t granddaughter_row_number = granddaughters.at(0);
//                                Int_t pdg_granddaughter = pythia8.event[granddaughter_row_number].id();
//
//                                if (pdg_daughters == pdg_granddaughter) {
//                                    finaldaughhters_hist->Fill(pythia8.event[daughter_row_number].id());
//                                    Nfinaldaughters+=1;
//                              
//                                } else {
//                                    nonfinaldaughters_hist->Fill(pythia8.event[daughter_row_number].id());
//                                    Nnonfinaldaughters += 1;
//                                } // else of: if (pdg_daughters == pdg_granddaughter) {
//                              
//                            } else {
//                                finaldaughhters_hist->Fill(pythia8.event[daughter_row_number].id());
//                                Nfinaldaughters+=1;
//
//                            } // else of: if Ngranddaughters==1
//                        } // else if/l Ngranddaugtres>1
//                    } //if daughter is not Higgs
//                }//for (Int_t daughter_index=0; daughter_index<Ndaughters
//            }//if (pythia8.event[i].id() == 25)
//        } // end of: particle loop
        
        //TODO: fill T->Fill(); here
        T->Fill();
    } // end of: event loop

    
//    pythia8.PrintStatistics();
    pythia8.stat();
    

//    px_hist->Write();
//    py_hist->Write();
//    pz_hist->Write();
//    m0->Write();
//    energy_hist->Write();
//    ptH->Write();
//    yH->Write();
//    daughters_hist->Write();
//    finaldaughhters_hist->Write();
//    nonfinaldaughters_hist->Write();
//    px_hist_daughters->Write();
//    py_hist_daughters->Write();
//    pz_hist_daughters->Write();
//    m0_daughters->Write();
//    energy_hist_daughters->Write();
//    ptH_daughters->Write();
//    yH_daughters->Write();
    T->Write();
    // TODO: T->Write(); here
    
    
    f.Close();
  
    exit(0);
    
}
