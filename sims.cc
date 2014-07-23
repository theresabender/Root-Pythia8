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
    
// Event loop

    // Begin event loop. Generate event; skip if generation aborted.
    for (int iev = 0; iev < nev; ++iev) {
        if (!pythia8.next()) continue;
        
        if (iev % 100 == 0){
            cout << "Event # " << iev << endl;
        }
        //TODO: fill T->Fill(); here
        T->Fill();
    } // end of: event loop

    
//    pythia8.PrintStatistics();
    pythia8.stat();
    
    T->Write();
    // TODO: T->Write(); here
    
    
    f.Close();
  
    exit(0);
    
}
