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
#include "TLegend.h"
#include "TLegendEntry.h"

// for overlay
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"


using namespace Pythia8;

int main(int argc, char* argv[]) {
    
    Int_t cms = 14;
    if (argc == 2) {
        cms = atoi (argv[1]);
    }

    
    Int_t nEntries;
    Int_t ndeb = 1;


    // Create the ROOT application environment.
    TApplication theApp("pythia8test", &argc, argv);
    
    char filename[100]; // = "sims_%d.root" + en;
    sprintf(filename, "output_%d.root", cms);
    
//    TFile f("output_14.root", "recreate");
    TFile f(filename, "recreate");
    
    sprintf(filename, "sims_%d.root", cms);
    
 //   TFile *f1 = new TFile("sims_14.root","READ");
    TFile *f1 = new TFile(filename,"READ");
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
    TH1F* ptH_daughters  = new TH1F("ptH daughters",  "Higgs Daughters Transverse Momentum", 100, 0., 200.);
    TH1D* m0_daughters = new TH1D("mass daughters", "Mass of Higgs daughters", 100, 0., 200.);
    TH1F* energy_hist_daughters = new TH1F("energy daughters", "Energy of Higgs Daughters", 100, 0., 500.);
    TH1F* px_hist_daughters = new TH1F("px daughters", "Higgs Daughters Momentum (X-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters = new TH1F("py daughters", "Higgs Daughters Momentum (Y-Direction)", 100, -300., 300.);
    TH1F* pz_hist_daughters = new TH1F("pz daughters", "Higgs Daughters Momentum (Z-Direction)", 100, -500., 500.);
   
    TH1F* ptH_daughters_b  = new TH1F("ptH daughters b",  "Higgs daughters b transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_antib  = new TH1F("ptH daughters anti b",  "Higgs daughters anti b transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_w  = new TH1F("ptH daughters w ",  "Higgs daughters w transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_antiw  = new TH1F("ptH daughters anti w",  "Higgs daughters anti w transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_z = new TH1F("ptH daughters z",  "Higgs daughters z transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_t  = new TH1F("ptH daughters t",  "Higgs daughters t transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_antit  = new TH1F("ptH daughters anti t",  "Higgs daughters anti t transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_c  = new TH1F("ptH daughters c ",  "Higgs daughters c transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_antic  = new TH1F("ptH daughters anti c",  "Higgs daughters anti c transverse momentum", 100, 0., 200.);
    TH1F* ptH_daughters_gamma = new TH1F("ptH daughters gamma",  "Higgs daughters gamma transverse momentum", 100, 0., 200.);
    
    TH1F* energy_hist_daughters_b = new TH1F("energy daughters b", "Energy of Higgs daughters b quark", 100, 0., 500.);
    TH1F* energy_hist_daughters_antib = new TH1F("energy daughters anti b", "Energy of Higgs daughters anti b quark", 100, 0., 500.);
    TH1F* energy_hist_daughters_w = new TH1F("energy daughters w", "Energy of Higgs daughters w", 100, 0., 500.);
    TH1F* energy_hist_daughters_antiw = new TH1F("energy daughters anti w", "Energy of Higgs daughters anti w", 100, 0., 500.);
    TH1F* energy_hist_daughters_z = new TH1F("energy daughters z", "Energy of Higgs daughters z", 100, 0., 500.);
    TH1F* energy_hist_daughters_t = new TH1F("energy daughters t", "Energy of Higgs daughters t ", 100, 0., 500.);
    TH1F* energy_hist_daughters_antit = new TH1F("energy daughters anti b", "Energy of Higgs daughters anti t ", 100, 0., 500.);
    TH1F* energy_hist_daughters_c = new TH1F("energy daughters c", "Energy of Higgs daughters c", 100, 0., 500.);
    TH1F* energy_hist_daughters_antic = new TH1F("energy daughters anti c", "Energy of Higgs daughters anti c", 100, 0., 500.);
    TH1F* energy_hist_daughters_gamma = new TH1F("energy daughters gamma", "Energy of Higgs daughters gamma", 100, 0., 500.);
    
    TH1F* px_hist_daughters_b = new TH1F("px daughters b", "Higgs Daughters Momentum b (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_antib = new TH1F("px daughters anti b", "Higgs Daughters Momentum anti b (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_w = new TH1F("px daughters w", "Higgs Daughters Momentum w (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_antiw = new TH1F("px daughters anti w", "Higgs Daughters Momentum anti w (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_z = new TH1F("px daughters z", "Higgs Daughters Momentum z (X-Direction)", 100, -300., 300.);
    
    TH1F* px_hist_daughters_t = new TH1F("px daughters t", "Higgs Daughters Momentum t (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_antit = new TH1F("px daughters anti t", "Higgs Daughters Momentum anti t (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_c = new TH1F("px daughters c", "Higgs Daughters Momentum c (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_antic = new TH1F("px daughters anti c", "Higgs Daughters Momentum anti c (X-Direction)", 100, -300., 300.);
    TH1F* px_hist_daughters_gamma = new TH1F("px daughters gamma", "Higgs Daughters Momentum gamma (X-Direction)", 100, -300., 300.);
    
    TH1F* py_hist_daughters_b = new TH1F("py daughters b", "Higgs Daughters Momentum b (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_antib = new TH1F("py daughters anti b", "Higgs Daughters Momentum anti b (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_w = new TH1F("py daughters w", "Higgs Daughters Momentum w (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_antiw = new TH1F("py daughters anti w", "Higgs Daughters Momentum anti w (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_z = new TH1F("py daughters z", "Higgs Daughters Momentum z (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_t = new TH1F("py daughters t", "Higgs Daughters Momentum t (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_antit = new TH1F("py daughters anti t", "Higgs Daughters Momentum anti t (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_c = new TH1F("py daughters c", "Higgs Daughters Momentum c (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_antic = new TH1F("py daughters anti c", "Higgs Daughters Momentum anti c (Y-Direction)", 100, -300., 300.);
    TH1F* py_hist_daughters_gamma = new TH1F("py daughters gamma", "Higgs Daughters Momentum gamma (Y-Direction)", 100, -300., 300.);

    
    
    TH1F* pz_hist_daughters_b = new TH1F("pz daughters b", "Higgs Daughters Momentum b (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_antib = new TH1F("pz daughters anti b", "Higgs Daughters anti b Momentum (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_w = new TH1F("pz daughters w", "Higgs Daughters Momentum w (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_antiw = new TH1F("pz daughters anti w", "Higgs Daughters anti w Momentum (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_z = new TH1F("pz daughters z", "Higgs Daughters Momentum z (Z-Direction)", 100, -500., 500.);
    
    TH1F* pz_hist_daughters_t = new TH1F("pz daughters t", "Higgs Daughters Momentum t (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_antit = new TH1F("pz daughters anti t", "Higgs Daughters anti t Momentum (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_c = new TH1F("pz daughters c", "Higgs Daughters Momentum c (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_antic = new TH1F("pz daughters anti c", "Higgs Daughters anti c Momentum (Z-Direction)", 100, -500., 500.);
    TH1F* pz_hist_daughters_gamma = new TH1F("pz daughters gamma", "Higgs Daughters Momentum gamma (Z-Direction)", 100, -500., 500.);

    
    
//// Overlay
//    TFile * Overlay = new TFile("output20k-2.root");
//    TH1F * ptH_daughters = (TH1F*)f.Get("daughters");
//    TH1F * hs = (TH1F*)f.Get("stacked daughters");
////    
//    TCanvas *c1 = new TCanvas("c1","Daughter overlay ptH",600,400);
//    
//    //create/fill draw h1
//    gStyle->SetOptStat(kFALSE);
// //   ptH_daughters->SetLineColor(kBlack);
//    ptH_daughters->SetLineWidth(1);
//    ptH_daughters->Draw();
//    c1->Update();
//    
//    //scale hint1 to the pad coordinates
//    Float_t rightmax1 = 1.1*ptH_daughters->GetMaximum();
//    //Float_t scale1 = gPad->GetUymax()/rightmax1;
//  //  hs->SetLineColor(kRed);
////    hs->Scale(scale1);
//    hs->Draw("same");
    
    
    // this is event cycle
    nEntries = T->GetEntries();
//    nEntries = 100;
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
                            
                        if (pdg_daughters == -15){ // tau+
                                
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                                
                            ptH_daughters_t->Fill(pt_daughters);
                            energy_hist_daughters_t->Fill(energy_daughters);
                            px_hist_daughters_t->Fill(px_daughters);
                            py_hist_daughters_t->Fill(py_daughters);
                            pz_hist_daughters_t->Fill(pz_daughters);
                                
                        } // if tau+
                            
                        if (pdg_daughters == 15){ // tau-
                                
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                                
                            ptH_daughters_antit->Fill(pt_daughters);
                            energy_hist_daughters_antit->Fill(energy_daughters);
                            px_hist_daughters_antit->Fill(px_daughters);
                            py_hist_daughters_antit->Fill(py_daughters);
                            pz_hist_daughters_antit->Fill(pz_daughters);
                            
                        } // if tau-
                            
                        if (pdg_daughters == 4){ // c
                                
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                                
                            ptH_daughters_c->Fill(pt_daughters);
                            energy_hist_daughters_c->Fill(energy_daughters);
                            px_hist_daughters_c->Fill(px_daughters);
                            py_hist_daughters_c->Fill(py_daughters);
                            pz_hist_daughters_c->Fill(pz_daughters);
                                
                            } // if c
                            
                        if (pdg_daughters == -4){ // anti c
                                
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                                
                            ptH_daughters_antic->Fill(pt_daughters);
                            energy_hist_daughters_antic->Fill(energy_daughters);
                            px_hist_daughters_antic->Fill(px_daughters);
                            py_hist_daughters_antic->Fill(py_daughters);
                            pz_hist_daughters_antic->Fill(pz_daughters);
                                
                        } // if anti c
                            
                        if (pdg_daughters == 22){ // gamma
                                
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                            
                            ptH_daughters_gamma->Fill(pt_daughters);
                            energy_hist_daughters_gamma->Fill(energy_daughters);
                            px_hist_daughters_gamma->Fill(px_daughters);
                            py_hist_daughters_gamma->Fill(py_daughters);
                            pz_hist_daughters_gamma->Fill(pz_daughters);
                                
                        } // if gamma
                            
                            
                            
                            
                            

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

    Int_t color_b = kRed;
    Int_t color_antib = kBlue;
    Int_t color_w = kGreen;
    Int_t color_antiw = kOrange-3;
    Int_t color_z = kYellow;
    Int_t color_t = kCyan-7;
    Int_t color_antit = kSpring+3;
    Int_t color_c = kViolet;
    Int_t color_antic = kRed+3;
    Int_t color_p = kBlue-10;
    
            THStack *ptH_overlay = new THStack("ptH overlay","ptH of Higgs Daughters");

            ptH_daughters_b->SetFillColor(color_b);
            ptH_daughters_b->SetMarkerStyle(21);
            ptH_daughters_b->SetMarkerColor(color_b);
           // ptH_daughters_b->SetFillStyle(3001);
            ptH_overlay->Add(ptH_daughters_b);

            ptH_daughters_antib->SetFillColor(color_antib);
            ptH_daughters_antib->SetFillStyle(3014);
            ptH_daughters_antib->SetMarkerStyle(21);
         //   ptH_daughters_antib->SetMarkerColor(color_antib);
            ptH_overlay->Add(ptH_daughters_antib);

            ptH_daughters_w->SetFillColor(color_w);
            ptH_daughters_w->SetMarkerStyle(21);
            ptH_daughters_w->SetMarkerColor(color_w);
            ptH_overlay->Add(ptH_daughters_w);

            ptH_daughters_antiw->SetFillColor(color_antiw);
            ptH_daughters_antiw->SetMarkerStyle(21);
            ptH_daughters_antiw->SetMarkerColor(color_antiw);
            ptH_overlay->Add(ptH_daughters_antiw);

            ptH_daughters_z->SetFillColor(color_z);
            ptH_daughters_z->SetMarkerStyle(21);
            ptH_daughters_z->SetMarkerColor(color_z);
            ptH_overlay->Add(ptH_daughters_z);
    
            ptH_daughters_t->SetFillColor(color_t);
            ptH_daughters_t->SetMarkerStyle(21);
            ptH_daughters_t->SetMarkerColor(color_t);
            ptH_overlay->Add(ptH_daughters_t);
    
            ptH_daughters_antit->SetFillColor(color_antit);
            ptH_daughters_antit->SetMarkerStyle(21);
            ptH_daughters_antit->SetMarkerColor(color_antit);
            ptH_overlay->Add(ptH_daughters_antit);
    
            ptH_daughters_c->SetFillColor(color_c);
            ptH_daughters_c->SetMarkerStyle(21);
            ptH_daughters_c->SetMarkerColor(color_c);
            ptH_overlay->Add(ptH_daughters_c);
    
            ptH_daughters_antic->SetFillColor(color_antic);
            ptH_daughters_antic->SetMarkerStyle(21);
            ptH_daughters_antic->SetMarkerColor(color_antic);
            ptH_overlay->Add(ptH_daughters_antic);
    
            ptH_daughters_gamma->SetFillColor(color_p);
            ptH_daughters_gamma->SetMarkerStyle(21);
            ptH_daughters_gamma->SetMarkerColor(color_p);
            ptH_overlay->Add(ptH_daughters_gamma);

    


//            TLegend *leg = new TLegend(0.1,0.7,0.4,0.9);
//            leg->SetHeader("Legend");
//            TLegendEntry* l1 = leg->AddEntry("l", "Bottom Quark","l");
//            l1->SetLineColor(kRed);
//            l1->SetLineWidth(4);
//            TLegendEntry* l2 = leg->AddEntry("l","Anti-Bottom Quark","l");
//            l2->SetLineColor(kBlue);
//            l2->SetLineWidth(4);
//            TLegendEntry* l3 = leg->AddEntry("fl","W Boson","l");
//            l3->SetLineColor(kGreen);
//            l3->SetLineWidth(4);
//            TLegendEntry* l4 = leg->AddEntry("l", "Anti-W Boson","l");
//            l4->SetLineColor(kOrange);
//            l4->SetLineWidth(4);
//            TLegendEntry* l5 = leg->AddEntry("l", "Z","l");
//            l5->SetLineColor(kYellow);
//            l5->SetLineWidth(4);
    
    
    
    
            THStack *energy_overlay = new THStack("energy overlay","Energy of Higgs Daughters");
    
    energy_hist_daughters_b->SetFillColor(color_b);
    energy_hist_daughters_b->SetMarkerStyle(21);
    energy_hist_daughters_b->SetMarkerColor(color_b);
    energy_overlay->Add(energy_hist_daughters_b);
    
    energy_hist_daughters_antib->SetFillColor(color_antib);
    energy_hist_daughters_antib->SetMarkerStyle(21);
    energy_hist_daughters_antib->SetMarkerColor(color_antib);
    energy_overlay->Add(energy_hist_daughters_antib);
    
    energy_hist_daughters_w->SetFillColor(color_w);
    energy_hist_daughters_w->SetMarkerStyle(21);
    energy_hist_daughters_w->SetMarkerColor(color_w);
    energy_overlay->Add(energy_hist_daughters_w);
    
    energy_hist_daughters_antiw->SetFillColor(color_antiw);
    energy_hist_daughters_antiw->SetMarkerStyle(21);
    energy_hist_daughters_antiw->SetMarkerColor(color_antiw);
    energy_overlay->Add(energy_hist_daughters_antiw);
    
    energy_hist_daughters_z->SetFillColor(color_z);
    energy_hist_daughters_z->SetMarkerStyle(21);
    energy_hist_daughters_z->SetMarkerColor(color_z);
    energy_overlay->Add(energy_hist_daughters_z);
    
    energy_hist_daughters_t->SetFillColor(color_t);
    energy_hist_daughters_t->SetMarkerStyle(21);
    energy_hist_daughters_t->SetMarkerColor(color_t);
    energy_overlay->Add(energy_hist_daughters_t);
    
    energy_hist_daughters_antit->SetFillColor(color_antit);
    energy_hist_daughters_antit->SetMarkerStyle(21);
    energy_hist_daughters_antit->SetMarkerColor(color_antit);
    energy_overlay->Add(energy_hist_daughters_antit);
    
    energy_hist_daughters_c->SetFillColor(color_c);
    energy_hist_daughters_c->SetMarkerStyle(21);
    energy_hist_daughters_c->SetMarkerColor(color_c);
    energy_overlay->Add(energy_hist_daughters_c);
    
    energy_hist_daughters_antic->SetFillColor(color_antic);
    energy_hist_daughters_antic->SetMarkerStyle(21);
    energy_hist_daughters_antic->SetMarkerColor(color_antic);
    energy_overlay->Add(energy_hist_daughters_antic);
    
    energy_hist_daughters_gamma->SetFillColor(color_p);
    energy_hist_daughters_gamma->SetMarkerStyle(21);
    energy_hist_daughters_gamma->SetMarkerColor(color_p);
    energy_overlay->Add(energy_hist_daughters_gamma);
    
            THStack *px_overlay = new THStack("px overlay","Higgs Daughters Momentum (X-Direction)");
    
    px_hist_daughters_b->SetFillColor(color_b);
    px_hist_daughters_b->SetMarkerStyle(21);
    px_hist_daughters_b->SetMarkerColor(color_b);
    px_overlay->Add(px_hist_daughters_b);
    
    px_hist_daughters_antib->SetFillColor(color_antib);
    px_hist_daughters_antib->SetMarkerStyle(21);
    px_hist_daughters_antib->SetMarkerColor(color_antib);
    px_overlay->Add(px_hist_daughters_antib);
    
    px_hist_daughters_w->SetFillColor(color_w);
    px_hist_daughters_w->SetMarkerStyle(21);
    px_hist_daughters_w->SetMarkerColor(color_w);
    px_overlay->Add(px_hist_daughters_w);
    
    px_hist_daughters_antiw->SetFillColor(color_antiw);
    px_hist_daughters_antiw->SetMarkerStyle(21);
    px_hist_daughters_antiw->SetMarkerColor(color_antiw);
    px_overlay->Add(px_hist_daughters_antiw);
    
    px_hist_daughters_z->SetFillColor(color_z);
    px_hist_daughters_z->SetMarkerStyle(21);
    px_hist_daughters_z->SetMarkerColor(color_z);
    px_overlay->Add(px_hist_daughters_z);
    
    px_hist_daughters_t->SetFillColor(color_t);
    px_hist_daughters_t->SetMarkerStyle(21);
    px_hist_daughters_t->SetMarkerColor(color_t);
    px_overlay->Add(px_hist_daughters_t);
    
    px_hist_daughters_antit->SetFillColor(color_antit);
    px_hist_daughters_antit->SetMarkerStyle(21);
    px_hist_daughters_antit->SetMarkerColor(color_antit);
    px_overlay->Add(px_hist_daughters_antit);
    
    px_hist_daughters_c->SetFillColor(color_c);
    px_hist_daughters_c->SetMarkerStyle(21);
    px_hist_daughters_c->SetMarkerColor(color_c);
    px_overlay->Add(px_hist_daughters_c);
    
    px_hist_daughters_antic->SetFillColor(color_antic);
    px_hist_daughters_antic->SetMarkerStyle(21);
    px_hist_daughters_antic->SetMarkerColor(color_antic);
    px_overlay->Add(px_hist_daughters_antic);
    
    px_hist_daughters_gamma->SetFillColor(color_p);
    px_hist_daughters_gamma->SetMarkerStyle(21);
    px_hist_daughters_gamma->SetMarkerColor(color_p);
    px_overlay->Add(px_hist_daughters_gamma);


            THStack *py_overlay = new THStack("py overlay","Higgs Daughters Momentum (Y-Direction)");
    
    py_hist_daughters_b->SetFillColor(color_b);
    py_hist_daughters_b->SetMarkerStyle(21);
    py_hist_daughters_b->SetMarkerColor(color_b);
    py_overlay->Add(py_hist_daughters_b);
    
    py_hist_daughters_antib->SetFillColor(color_antib);
    py_hist_daughters_antib->SetMarkerStyle(21);
    py_hist_daughters_antib->SetMarkerColor(color_antib);
    py_overlay->Add(py_hist_daughters_antib);
    
    py_hist_daughters_w->SetFillColor(color_w);
    py_hist_daughters_w->SetMarkerStyle(21);
    py_hist_daughters_w->SetMarkerColor(color_w);
    py_overlay->Add(py_hist_daughters_w);
    
    py_hist_daughters_antiw->SetFillColor(color_antiw);
    py_hist_daughters_antiw->SetMarkerStyle(21);
    py_hist_daughters_antiw->SetMarkerColor(color_antiw);
    py_overlay->Add(py_hist_daughters_antiw);
    
    py_hist_daughters_z->SetFillColor(color_z);
    py_hist_daughters_z->SetMarkerStyle(21);
    py_hist_daughters_z->SetMarkerColor(color_z);
    py_overlay->Add(py_hist_daughters_z);
    
    py_hist_daughters_t->SetFillColor(color_t);
    py_hist_daughters_t->SetMarkerStyle(21);
    py_hist_daughters_t->SetMarkerColor(color_t);
    py_overlay->Add(py_hist_daughters_t);
    
    py_hist_daughters_antit->SetFillColor(color_antit);
    py_hist_daughters_antit->SetMarkerStyle(21);
    py_hist_daughters_antit->SetMarkerColor(color_antit);
    py_overlay->Add(py_hist_daughters_antit);
    
    py_hist_daughters_c->SetFillColor(color_c);
    py_hist_daughters_c->SetMarkerStyle(21);
    py_hist_daughters_c->SetMarkerColor(color_c);
    py_overlay->Add(py_hist_daughters_c);
    
    py_hist_daughters_antic->SetFillColor(color_antic);
    py_hist_daughters_antic->SetMarkerStyle(21);
    py_hist_daughters_antic->SetMarkerColor(color_antic);
    py_overlay->Add(py_hist_daughters_antic);
    
    py_hist_daughters_gamma->SetFillColor(color_p);
    py_hist_daughters_gamma->SetMarkerStyle(21);
    py_hist_daughters_gamma->SetMarkerColor(color_p);
    py_overlay->Add(py_hist_daughters_gamma);

            THStack *pz_overlay = new THStack("pz overlay","Higgs Daughters Momentum (Z-Direction)");
    
    pz_hist_daughters_b->SetFillColor(color_b);
    pz_hist_daughters_b->SetMarkerStyle(21);
    pz_hist_daughters_b->SetMarkerColor(color_b);
    pz_overlay->Add(pz_hist_daughters_b);
    
    pz_hist_daughters_antib->SetFillColor(color_antib);
    pz_hist_daughters_antib->SetMarkerStyle(21);
    pz_hist_daughters_antib->SetMarkerColor(color_antib);
    pz_overlay->Add(pz_hist_daughters_antib);
    
    pz_hist_daughters_w->SetFillColor(color_w);
    pz_hist_daughters_w->SetMarkerStyle(21);
    pz_hist_daughters_w->SetMarkerColor(color_w);
    pz_overlay->Add(pz_hist_daughters_w);
    
    pz_hist_daughters_antiw->SetFillColor(color_antiw);
    pz_hist_daughters_antiw->SetMarkerStyle(21);
    pz_hist_daughters_antiw->SetMarkerColor(color_antiw);
    pz_overlay->Add(pz_hist_daughters_antiw);
    
    pz_hist_daughters_z->SetFillColor(color_z);
    pz_hist_daughters_z->SetMarkerStyle(21);
    pz_hist_daughters_z->SetMarkerColor(color_z);
    pz_overlay->Add(pz_hist_daughters_z);
    
    pz_hist_daughters_t->SetFillColor(color_t);
    pz_hist_daughters_t->SetMarkerStyle(21);
    pz_hist_daughters_t->SetMarkerColor(color_t);
    pz_overlay->Add(pz_hist_daughters_t);
    
    pz_hist_daughters_antit->SetFillColor(color_antit);
    pz_hist_daughters_antit->SetMarkerStyle(21);
    pz_hist_daughters_antit->SetMarkerColor(color_antit);
    pz_overlay->Add(pz_hist_daughters_antit);
    
    pz_hist_daughters_c->SetFillColor(color_c);
    pz_hist_daughters_c->SetMarkerStyle(21);
    pz_hist_daughters_c->SetMarkerColor(color_c);
    pz_overlay->Add(pz_hist_daughters_c);
    
    pz_hist_daughters_antic->SetFillColor(color_antic);
    pz_hist_daughters_antic->SetMarkerStyle(21);
    pz_hist_daughters_antic->SetMarkerColor(color_antic);
    pz_overlay->Add(pz_hist_daughters_antic);
    
    pz_hist_daughters_gamma->SetFillColor(color_p);
    pz_hist_daughters_gamma->SetMarkerStyle(21);
    pz_hist_daughters_gamma->SetMarkerColor(color_p);
    pz_overlay->Add(pz_hist_daughters_gamma);

    

//    void overlay()
//    {
//
//        TFile *f = new TFile("output20k-2.root");
//        TH1I * hs = (TH1I*)f.Get("daughters");
//        TH1I * ptH_daughters = (TH1I*)f.Get("finaldaughters");
//  
//        
//        
//        
//        TCanvas *c1 = new TCanvas("c1","hists with different scales",600,400);
//        
//        //create/fill draw h1
//        gStyle->SetOptStat(kFALSE);
//        daughters->SetLineColor(kBlack);
//        daughters->SetLineWidth(1);
//        daughters_hist->Draw();
//        c1->Update();  

    
    

    
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
    ptH_daughters_t->Write();
    ptH_daughters_antit->Write();
    ptH_daughters_c->Write();
    ptH_daughters_antic->Write();
    ptH_daughters_gamma->Write();
    energy_hist_daughters_b->Write();
    energy_hist_daughters_antib->Write();
    energy_hist_daughters_w->Write();
    energy_hist_daughters_antiw->Write();
    energy_hist_daughters_z->Write();
    energy_hist_daughters_t->Write();
    energy_hist_daughters_antit->Write();
    energy_hist_daughters_c->Write();
    energy_hist_daughters_antic->Write();
    energy_hist_daughters_gamma->Write();
    px_hist_daughters_b->Write();
    px_hist_daughters_antib->Write();
    px_hist_daughters_w->Write();
    px_hist_daughters_antiw->Write();
    px_hist_daughters_z->Write();
    px_hist_daughters_t->Write();
    px_hist_daughters_antit->Write();
    px_hist_daughters_c->Write();
    px_hist_daughters_antic->Write();
    px_hist_daughters_gamma->Write();
    py_hist_daughters_b->Write();
    py_hist_daughters_antib->Write();
    py_hist_daughters_w->Write();
    py_hist_daughters_antiw->Write();
    py_hist_daughters_z->Write();
    py_hist_daughters_t->Write();
    py_hist_daughters_antit->Write();
    py_hist_daughters_c->Write();
    py_hist_daughters_antic->Write();
    py_hist_daughters_gamma->Write();
    pz_hist_daughters_b->Write();
    pz_hist_daughters_antib->Write();
    pz_hist_daughters_w->Write();
    pz_hist_daughters_antiw->Write();
    pz_hist_daughters_z->Write();
    pz_hist_daughters_t->Write();
    pz_hist_daughters_antit->Write();
    pz_hist_daughters_c->Write();
    pz_hist_daughters_antic->Write();
    pz_hist_daughters_gamma->Write();
    
    ptH_overlay->Write();
    energy_overlay->Write();
    px_overlay->Write();
    py_overlay->Write();
    pz_overlay->Write();
 //   Overlay->Write();
    
    f.Close();
    
    f1->Close();
    
        };   // end of main function

