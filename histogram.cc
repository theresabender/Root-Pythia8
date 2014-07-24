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
    
    //TFile f("output.root", "recreate");
    // TTree *T = new TTree("T","ev1 Tree");
    TFile f("output.root", "recreate");
    TFile *f1 = new TFile("sims.root","READ");
    TTree *T = (TTree*)f1->Get("T");
    
    TBranch *b_event = (TBranch*)T->GetBranch("event");
    Event *event = new Event();
//    Event& eventCopy = *event; // we do not need eventCopy
    b_event->SetAddress(&event);
    
    vector<Int_t> daughterList;
    vector<Int_t> granddaughterList;
    Int_t Nfinaldaughters = 0;
    Int_t Nnonfinaldaughters = 0;
    
    // TODO: define parent kinematics histograms:
    //    yH, ptH, m0, energy_hist, px_hist, py_hist, pz_hist
    // TODO: define the daughters kinematics histograms, too... all the histograms from below
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
//    for(Int_t i=0; i<10; ++i) {
        T->GetEvent(i);

        //        event->list(); // list particles of this event
        cout << "|event|=" << event->size() << endl;

        // this is event evaluation
        if (event->size()){
//           Particle First = event->at(0);
//            cout << "event " << i << "First particle's type: " << First.eta() << endl;
            
            // this is particle loop
            for (Int_t iparticle=0; iparticle<event->size(); iparticle++){
//                cout << "event " << i << " id:" << event->at(iparticle).id() << endl;
                if (event->at(iparticle).id() == 25){
                    
                    // TODO: define kinematics variables for parent, e.g. eta, mass, energy, px, py, pz, pT
                    Double_t eta = event->at(iparticle).eta();
                    Double_t energy = event->at(iparticle).e();
                    Double_t pt  = event->at(iparticle).pT();
                    Vec4 momentum = event->at(iparticle).p();
                    Double_t mass = event->at(iparticle).m();
                    Double_t px = event->at(iparticle).px();
                    Double_t py = event->at(iparticle).py();
                    Double_t pz = event->at(iparticle).pz();
                    
                    // TODO: fill parent kinematics histograms:
                    //    yH, ptH, m0, energy_hist, px_hist, py_hist, pz_hist

                    yH->Fill(eta);
                    ptH->Fill(pt, 1./(2. * pt));
                    m0->Fill(mass);
                    energy_hist->Fill(energy);
                    px_hist->Fill(px);
                    py_hist->Fill(py);
                    pz_hist->Fill(pz);
                    
                    
                    cout << "event " << i << " id:" << event->at(iparticle).id()
                        << " isFinal:" << event->at(iparticle).isFinal() << endl;
//                    vector<Int_t> daughterList = event->at(iparticle).daughterList();
//                    daughterList = event->at(iparticle).daughterList(iparticle);
                    daughterList = event->daughterList(iparticle);
                        // daughterList contains iparticle idexes of daughters, the daughter_row_number.
                        // you can access daughters by those indexes like: event->at(daughter_row_number)
                    
                    // if (daughterList.size() != 0){
                        // cout << "|daughterList|:" << daughterList.at(0) << endl;
                    cout << " |daughterList|=" << daughterList.size() << endl;
                        // this is daughter loop
                    for (Int_t daughter_index=0; daughter_index<daughterList.size(); daughter_index++ ){
                        // here fill in the histogramming logic for daughters
                        Int_t daughter_row_number = daughterList.at(daughter_index);
                        Int_t pdg_daughters = event->at(daughter_row_number).id();
                        cout << "daughter #" << daughter_index << " at row" << daughter_row_number << " has PDG number " << pdg_daughters << endl;
                    
                        if (pdg_daughters != 25){
                            
    // TODO: define daughters kinematics variables: e.g. eta_daughters, mass_daughters, energy_daughters, px_daughters, py_daughters, pz_daughters, pT_daughters
                            Double_t eta_daughters = event->at(daughter_row_number).eta();
                            Double_t pt_daughters  = event->at(daughter_row_number).pT();
                            Double_t energy_daughters = event->at(daughter_row_number).e();
                            Vec4 momentum_daughters = event->at(daughter_row_number).p();
                            Double_t mass_daughters = event->at(daughter_row_number).m();
                            Double_t px_daughters = event->at(daughter_row_number).px();
                            Double_t py_daughters = event->at(daughter_row_number).py();
                            Double_t pz_daughters = event->at(daughter_row_number).pz();
                            
                        // TODO: fill daughters kinematics histograms
                            daughters_hist->Fill(pdg_daughters);
                            yH_daughters->Fill(eta_daughters);
                            ptH_daughters->Fill(pt_daughters);
                            m0_daughters->Fill(mass_daughters);
                            energy_hist_daughters->Fill(energy_daughters);
                            px_hist_daughters->Fill(px_daughters);
                            py_hist_daughters->Fill(py_daughters);
                            pz_hist_daughters->Fill(pz_daughters);
                            
                            // TODO: get list of granddaughters from daughter daughter_row_number
                            granddaughterList = event->daughterList(daughter_row_number);
                            
                            Int_t Ngrandaughters = granddaughterList.size();
                            

                        if (Ngrandaughters > 1){
                            nonfinaldaughters_hist->Fill(pdg_daughters);
                            Nnonfinaldaughters += 1;

                        } else {
                                                        // Ngranddaughters <= 1
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


//    t1.Branch("eta",&eta,"eta/F");
//    t1.Branch("energy",&e,"energy/F");
//    t1.Branch("pt",&pT,"pt/F");
//    t1.Branch("momentum",&p,"momentum/F");
//    t1.Branch("mass",&m,"mass/F");
//    t1.Branch("px",&px,"px/F");
//    t1.Branch("py",&py,"py/F");
//    t1.Branch("pz",&pz,"pz/F");


//void treelr()
//{
//  
//    TFile *f = new TFile("tree1.root");
//    TTree *t1 = (TTree*)f->Get("t1");
//    Double_t eta = pythia8.event[i].eta();
//    Double_t energy = pythia8.event[i].e();
//    Double_t pt  = pythia8.event[i].pT();
//    Vec4 momentum = pythia8.event[i].p();
//    Double_t mass = pythia8.event[i].m();
//    Double_t px = pythia8.event[i].px();
//    Double_t py = pythia8.event[i].py();
//    Double_t pz = pythia8.event[i].pz();
//    Int_t ev;
//    t1->SetBranchAddress("px",&px);
//    t1->SetBranchAddress("py",&py);
//    t1->SetBranchAddress("pz",&pz);
//    t1->SetBranchAddress("eta",&eta);
//    t1->SetBranchAddress("energy",&e);
//    t1->SetBranchAddress("pt",&pT);
//    t1->SetBranchAddress("momentum",&p);
//    t1>SetBranchAddress("mass", &m);
//
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
//    
//    yH->Fill(eta);
//    ptH->Fill(pt, 1./(2. * pt));
//    m0->Fill(mass);
//    energy_hist->Fill(energy);
//    px_hist->Fill(px);
//    py_hist->Fill(py);
//    pz_hist->Fill(pz);
//    
//    //}
//
//
//
//    
//    
//    
//// Array of particles
//   TClonesArray* particles = new TClonesArray("TParticle", 1000);
//// Create pythia8 object
////   TPythia8* pythia8 = new TPythia8();
//   Pythia pythia8;
////    Pythia pythia8(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
//    
//// Configure    
//
//    pythia8.readString("Beams:eCM = 14000.");
//    pythia8.readString("HiggsSM:gg2H = on");
//    
//    // TODO: Event *event goes here, instead of pythia. use puthia8.
//    // TODO: TBranch thingy goes here
//    Event *event = &pythia8.event;
//    T->Branch("event",&event);
//    
//// Initialize
//    
////    pythia8->Initialize(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
////    pythia8.initialize(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
//    pythia8.init(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
//    
//    
//    
//    Int_t Nfinaldaughters = 0;
//    Int_t Nnonfinaldaughters = 0;
//    
////    id(int idIn) {idSave = idIn; setPDEPtr();
////    status(int statusIn) {statusSave = statusIn;
//
//    // Event loop
//
//    // Begin event loop. Generate event; skip if generation aborted.
//    for (int iev = 0; iev < nev; ++iev) {
//        if (!pythia8.next()) continue;
//        
//        if (iev % 100 == 0){
//            cout << "Event # " << iev << endl;
//        }
//        
//    
//        
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
//        
//        //TODO: fill T->Fill(); here
//        T->Fill();
//    } // end of: event loop
//
//    
////    pythia8.PrintStatistics();
//    pythia8.stat();
//    
//
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
//    T->Write();
//    // TODO: T->Write(); here
//    
//    
//    f.Close();
//  
//    exit(0);
//    
//}

