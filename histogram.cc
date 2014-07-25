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
#include "THStack.h"


using namespace Pythia8;

int main(int argc, char* argv[]) {
    Int_t nEntries;
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
   
    TH1F* ptH_daughters_b  = new TH1F("ptH daughters b",  "Higgs daughters b transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_antib  = new TH1F("ptH daughters anti b",  "Higgs daughters anti b transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_w  = new TH1F("ptH daughters w ",  "Higgs daughters w transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_antiw  = new TH1F("ptH daughters anti w",  "Higgs daughters anti w transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_z = new TH1F("ptH daughters z",  "Higgs daughters z transverse momentum", 100, 0., 200.);
    
    TH1F* energy_hist_daughters_b = new TH1F("energy daughters b", "Energy of Higgs daughters b quark", 100, 0., 500.);
    TH1F* energy_hist_daughters_antib = new TH1F("energy daughters anti b", "Energy of Higgs daughters anti b quark", 100, 0., 500.);
    TH1F* energy_hist_daughters_w = new TH1F("energy daughters w", "Energy of Higgs daughters w", 100, 0., 500.);
    TH1F* energy_hist_daughters_antiw = new TH1F("energy daughters anti w", "Energy of Higgs daughters anti w", 100, 0., 500.);
    TH1F* energy_hist_daughters_z = new TH1F("energy daughters z", "Energy of Higgs daughters z", 100, 0., 500.);
    
    TH1F* px_hist_daughters_b = new TH1F("px daughters b", "Higgs Daughters Momentum b (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_antib = new TH1F("px daughters anti b", "Higgs Daughters Momentum anti b (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_w = new TH1F("px daughters w", "Higgs Daughters Momentum w (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_antiw = new TH1F("px daughters anti w", "Higgs Daughters Momentum anti w (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_z = new TH1F("px daughters z", "Higgs Daughters Momentum z (X-Direction)", 100, -300., 300.);
    
    TH1F* py_hist_daughters_b = new TH1F("py daughters b", "Higgs Daughters Momentum b (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_antib = new TH1F("py daughters anti b", "Higgs Daughters Momentum anti b (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_w = new TH1F("py daughters w", "Higgs Daughters Momentum w (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_antiw = new TH1F("py daughters anti w", "Higgs Daughters Momentum anti w (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_z = new TH1F("py daughters z", "Higgs Daughters Momentum z (Y-Direction)", 100, -300., 300.);
    
    TH1F* pz_hist_daughters_b = new TH1F("pz daughters b", "Higgs Daughters Momentum b (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_antib = new TH1F("pz daughters anti b", "Higgs Daughters anti b Momentum (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_w = new TH1F("pz daughters w", "Higgs Daughters Momentum w (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_antiw = new TH1F("pz daughters anti w", "Higgs Daughters anti w Momentum (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_z = new TH1F("pz daughters z", "Higgs Daughters Momentum z (Z-Direction)", 100, -500., 500.);
    

    // this is event cycle
    nEntries = T->GetEntries();
    //nEntries = 100;
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
                    
                        if (pdg_daughters != 25){ //not higgs

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
                            

                        if (pdg_daughters == 5){ // b quark
                                
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                                
                            ptH_daughters_b->Fill(pt_daughters);
                            energy_hist_daughters_b->Fill(energy_daughters);
                            px_hist_daughters_b->Fill(px_daughters);
                            py_hist_daughters_b->Fill(py_daughters);
                            pz_hist_daughters_b->Fill(pz_daughters);
                            
                        } // if b
                            
                        if (pdg_daughters == -5){ // anti b quark
                            
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                            
                            ptH_daughters_antib->Fill(pt_daughters);
                            energy_hist_daughters_antib->Fill(energy_daughters);
                            px_hist_daughters_antib->Fill(px_daughters);
                            py_hist_daughters_antib->Fill(py_daughters);
                            pz_hist_daughters_antib->Fill(pz_daughters);
                            
                        } // if anti b
                            
                        if (pdg_daughters == 24){ // w
                            
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                            
                            ptH_daughters_w->Fill(pt_daughters);
                            energy_hist_daughters_w->Fill(energy_daughters);
                            px_hist_daughters_w->Fill(px_daughters);
                            py_hist_daughters_w->Fill(py_daughters);
                            pz_hist_daughters_w->Fill(pz_daughters);
                            
                        } // if w
                            
                        if (pdg_daughters == -24){ // anti w
                            
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                            
                            ptH_daughters_antiw->Fill(pt_daughters);
                            energy_hist_daughters_antiw->Fill(energy_daughters);
                            px_hist_daughters_antiw->Fill(px_daughters);
                            py_hist_daughters_antiw->Fill(py_daughters);
                            pz_hist_daughters_antiw->Fill(pz_daughters);
                            
                        } // if anti w
                            
                        if (pdg_daughters == 23){ // z
                            
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                            
                            ptH_daughters_z->Fill(pt_daughters);
                            energy_hist_daughters_z->Fill(energy_daughters);
                            px_hist_daughters_z->Fill(px_daughters);
                            py_hist_daughters_z->Fill(py_daughters);
                            pz_hist_daughters_z->Fill(pz_daughters);
                            
                        } // if z

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


    
            THStack *hs = new THStack("hs","pT");
            //create three 1-d histograms
//            TH1F* ptH_daughters_stackedhisto  = new TH1F("ptH daughters stacked histogram",  "Higgs daughters transverse momentum", 100, 0., 200.);
//            ptH_daughters_b->FillRandom("gaus",20000);
            ptH_daughters_b->SetFillColor(kRed);
            ptH_daughters_b->SetMarkerStyle(21);
            ptH_daughters_b->SetMarkerColor(kRed);
            hs->Add(ptH_daughters_b);
    
//            TH1F* ptH_daughters_antib  = new TH1F("ptH daughters anti b",  "Higgs daughters anti b transverse momentum", 100, 0., 200.);
//            ptH_daughters_antib->FillRandom("gaus",15000);
            ptH_daughters_antib->SetFillColor(kBlue);
            ptH_daughters_antib->SetMarkerStyle(21);
            ptH_daughters_antib->SetMarkerColor(kBlue);
            hs->Add(ptH_daughters_antib);
//            TH1F* ptH_daughters_w  = new TH1F("ptH daughters w ",  "Higgs daughters w transverse momentum", 100, 0., 200.);
//            ptH_daughters_w->FillRandom("gaus",10000);
            ptH_daughters_w->SetFillColor(kGreen);
            ptH_daughters_w->SetMarkerStyle(21);
            ptH_daughters_w->SetMarkerColor(kGreen);
            hs->Add(ptH_daughters_w);
//            TH1F* ptH_daughters_antiw  = new TH1F("ptH daughters anti w",  "Higgs daughters anti w transverse momentum", 100, 0., 200.);
//            ptH_daughters_antiw->FillRandom("gaus",10000);
            ptH_daughters_antiw->SetFillColor(kOrange);
            ptH_daughters_antiw->SetMarkerStyle(21);
            ptH_daughters_antiw->SetMarkerColor(kOrange);
            hs->Add(ptH_daughters_antiw);
//            TH1F* ptH_daughters_z = new TH1F("ptH daughters z",  "Higgs daughters z transverse momentum", 100, 0., 200.);
//            ptH_daughters_z->FillRandom("gaus",10000);
            ptH_daughters_z->SetFillColor(kYellow);
            ptH_daughters_z->SetMarkerStyle(21);
            ptH_daughters_z->SetMarkerColor(kYellow);
            hs->Add(ptH_daughters_z);
    
//            TCanvas *cst = new TCanvas("cst","stacked hists",10,10,700,700);
//            cst->SetFillColor(41);
//            cst->Divide(2,2);
//            // in top left pad, draw the stack with defaults
//            cst->cd(1);
//            hs->Draw();
    
        
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
    
    ptH_daughters_b->Write();
    ptH_daughters_antib->Write();
    ptH_daughters_w->Write();
    ptH_daughters_antiw->Write();
    ptH_daughters_z->Write();
    energy_hist_daughters_b->Write();
    energy_hist_daughters_antib->Write();
    energy_hist_daughters_w->Write();
    energy_hist_daughters_antiw->Write();
    energy_hist_daughters_z->Write();
    px_hist_daughters_b->Write();
    px_hist_daughters_antib->Write();
    px_hist_daughters_w->Write();
    px_hist_daughters_antiw->Write();
    px_hist_daughters_z->Write();
    py_hist_daughters_b->Write();
    py_hist_daughters_antib->Write();
    py_hist_daughters_w->Write();
    py_hist_daughters_antiw->Write();
    py_hist_daughters_z->Write();
    pz_hist_daughters_b->Write();
    pz_hist_daughters_antib->Write();
    pz_hist_daughters_w->Write();
    pz_hist_daughters_antiw->Write();
    pz_hist_daughters_z->Write();
    
    hs->Write();
    
    f.Close();
    
    f1->Close();
    
        };   // end of main function

