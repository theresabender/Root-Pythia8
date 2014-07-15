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

void pythia8(Int_t nev  = 100, Int_t ndeb = 1){
   char *p8dataenv = gSystem->Getenv("PYTHIA8DATA");
   if (!p8dataenv) {
      char *p8env = gSystem->Getenv("PYTHIA8"); 
      if (!p8env) {
         Error("pythia8.C", 
               "Environment variable PYTHIA8 must contain path to pythia directory!");
         return;
      }
      TString p8d = p8env;
      p8d += "/xmldoc";
      gSystem->Setenv("PYTHIA8DATA", p8d);
   }
      
   char* path = gSystem->ExpandPathName("$PYTHIA8DATA");
   if (gSystem->AccessPathName(path)) {
         Error("pythia8.C", 
               "Environment variable PYTHIA8DATA must contain path to $PYTHIA8/xmldoc directory !");
      return;
   }
    
// Load libraries
#ifndef G__WIN32 // Pythia8 is a static library on Windows
   gSystem->Load("$PYTHIA8/lib/libpythia8");
#endif
   gSystem->Load("libEG");
   gSystem->Load("libEGPythia8");
// Histograms
    TH1F* yH = new TH1F("etaH", "Higgs pseudorapidity", 100, -5., 5.);
    TH1F* ptH  = new TH1F("ptH",  "Higgs transverse momentum", 100, 0., 200.);
    TH1F* m0 = new TH1F("mass", "Mass of Higgs", 100, 0., 200.);
    
    
    
// Array of particles
   TClonesArray* particles = new TClonesArray("TParticle", 1000);
// Create pythia8 object
   TPythia8* pythia8 = new TPythia8();
    
// Configure    
    pythia8->ReadString("Beams:eCM = 14000.");
    pythia8->ReadString("HiggsSM:gg2H = on");
    
// Initialize 
    
   pythia8->Initialize(2212 /* p */, 2212 /* p */, 14000. /* TeV */);


// Event loop

    for (Int_t iev = 0; iev < nev; iev++) {
      pythia8->GenerateEvent();
      if (iev < ndeb) pythia8->EventListing();
      pythia8->ImportParticles(particles,"All");
      Int_t np = particles->GetEntriesFast();
        
// Particle loop
      for (Int_t ip = 0; ip < np; ip++) {
         TParticle* part = (TParticle*) particles->At(ip);
         Int_t ist = part->GetStatusCode();
         // Positive codes are final particles.
//         if (ist <= 0) continue;
         Int_t pdg = part->GetPdgCode();
          if (pdg == 25){
              Float_t eta = part->Eta();
              Float_t pt  = part->Pt();
              Double_t energy = part->Energy();
              Double_t momentum = part->P();
              Double_t mass = sqrt(energy**2 - momentum**2);
              //         if (charge == 0.) continue;
              
              Float_t charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge();
          }

          
          if (pdg == 25){
              if (pt > 0.){
                  yH->Fill(eta);
                  ptH->Fill(pt, 1./(2. * pt));
                  m0->Fill(mass);
                  
                  // Float_t mymass= TODO;
                  // print energy, momentum, mass
                  // cout << TODO ;
                  
                  cout << "Energy: " << energy << " Momentum: " << momentum << " Mass: " << mass << endl ;
                  
                  
                  if (iev % 100 == 1)
                      cout << "pdg=" << pdg << " Transverse momentum: "<< pt << " Rapidity: " << eta << " mass=" << mass << endl ;
              }
        }

          
      } // for .. particle loop
       
        
   } // for .. event loop

    
   //  delete pdg_vector;
    
   pythia8->PrintStatistics();
    
    TCanvas* c1 = new TCanvas("c1","Pythia8 test example",800,800);
    TCanvas* c2 = new TCanvas("c2","Pythia8 test example II",800,800);
    c1->Divide(1, 2);
    c1->cd(1);
    yH->Scale(5./Float_t(nev));
    yH->Draw();
    yH->SetXTitle("#eta");
    yH->SetYTitle("dN/d#eta");
   

   c1->cd(2);
   gPad->SetLogy();
   ptH->Scale(5./Float_t(nev));
   ptH->Draw();
   ptH->SetXTitle("p_{t} [GeV/c]");
   ptH->SetYTitle("dN/dp_{t}^{2} [GeV/c]^{-2}");

    c2->Divide(1, 2);
    c2->cd(1);
    m0->Scale(5./Float_t(nev));
    m0->Draw();
    m0->SetXTitle("#m0");
    m0->SetYTitle("dN/d#m0");


}
