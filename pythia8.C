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
//   }

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
    
    TFile f("output.root", "recreate");

// Histograms
    TH1F* yH = new TH1F("etaH", "Higgs pseudorapidity", 100, -6.28., 6.28.);
    TH1F* ptH  = new TH1F("ptH",  "Higgs transverse momentum", 100, 0., 200.);
    TH1D* m0 = new TH1D("mass", "Mass of Higgs", 100, 0., 200.);
    TH1F* energy_hist = new TH1F("energy", "Energy of Higgs", 100, 0., 500.);
    TH1F* px_hist = new TH1F("px", "Higgs Momentum (X-Direction)", 100, -300., 300.);
    TH1F* py_hist = new TH1F("py", "Higgs Momentum (Y-Direction)", 100, -300., 300.);
    TH1F* pz_hist = new TH1F("pz", "Higgs Momentum (Z-Direction)", 100, -500., 500.);
    TH1I* daughters_hist = new TH1I("daughters", "Higgs Daughters", 61, -30, 30);

    
// Array of particles
   TClonesArray* particles = new TClonesArray("TParticle", 1000);
// Create pythia8 object
   TPythia8* pythia8 = new TPythia8();
    
// Configure    
    pythia8->ReadString("Beams:eCM = 14000.");
    pythia8->ReadString("HiggsSM:gg2H = on");
    
// Initialize 
    
   pythia8->Initialize(2212 /* p */, 2212 /* p */, 14000. /* TeV */);
    
    Int_t Nfinaldaughters = 0;
    Int_t Nnonfinaldaughters = 0;


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
              Double_t px = part->Px();
              Double_t py = part->Py();
              Double_t pz = part->Pz();
              // TODO: get number of daughters: part->GetNDaughters();
              Int_t Ndaughters = part->GetNDaughters();
              cout << "Ndaughters="<< Ndaughters << endl;
              // TODO: loop over daughters
              // TODO:      for each daughter retrieve this daughter particle:
              // TODO:          part->GetDaughter(index_daughter)
              // TODO:              index_daughter goes from 0 to GetNDaughters
              // TODO:          what is the particle ID of the daughter? dump it into a new histogram
              //         if (charge == 0.) continue;
              for (Int_t daughter_index=0; daughter_index<Ndaughters; daughter_index++){
                  Int_t daughter = part->GetDaughter(daughter_index);
                  TParticle* daughterpart = (TParticle*) particles->At(daughter);
                  Int_t daughterpdg = daughterpart->GetPdgCode();
                  Int_t daughterist = daughterpart->GetStatusCode();
                  // TODO: cout daughter
                  // TODO: if daughter is not Higgs (daughterpdg != 25), then fill daughters_hist
                  if (daughterpdg != 25){
                     daughters_hist->Fill(daughterpdg);
                  }
                  
                  if (daughterpdg > 0) {
                      Nfinaldaughters+=1;
                      cout << "Final Daughters: " << Nfinaldaughters << endl;
                  }
                  
                  if (daughterpdg < 0) {
                      Nnonfinaldaughters += 1;
                      
                      cout << "Nonfinal Daughters: " << Nnonfinaldaughters << endl;
                  }
                  
                
//                cout << "Final Daughters: " << Nfinaldaughters << endl;
//                cout << "Nonfinal Daughters: " << Nnonfinaldaughters << endl;
                  
                cout << "Daughter; " << daughter_index << "daughter= " << daughter << "Daughter pdg: " << daughterpdg << endl;
                 
                  
                  
                  
              }
              if (pt > 0.){
                  yH->Fill(eta);
                  ptH->Fill(pt, 1./(2. * pt));
                  m0->Fill(mass);
                  energy_hist->Fill(energy);
                  px_hist->Fill(px);
                  py_hist->Fill(py);
                  pz_hist->Fill(pz);
                  
                  cout << "Energy: " << energy << " Momentum: " << momentum << " Mass: " << mass << endl ;
                  if (iev % 100 == 1)
                      cout << "pdg=" << pdg << " Transverse momentum: "<< pt << " Rapidity: " << eta
                            << " mass=" << mass << endl ;
              } // if pt>0.
        } // if pdg==25

          
      } // for .. particle loop
       
        
   } // for .. event loop

    
    cout << "Final Daughters: " << Nfinaldaughters << endl;
    cout << "Nonfinal Daughters: " << Nnonfinaldaughters << endl;
   pythia8->PrintStatistics();
    
    
//    TCanvas* c1 = new TCanvas("c1","Pythia8 test example",600,600);
//    TCanvas* c2 = new TCanvas("c2","Pythia8 test example II",600,600);
//    TCanvas* c3 = new TCanvas("c3","Pythia8 test example III",600,900);
//    TCanvas* c4 = new TCanvas("c4","Pythia8 test example IV", 600, 300);
//        
//    c1->Divide(1, 2);
//    c1->cd(1);
//    yH->Scale(5./Float_t(nev));
//    yH->Draw();
//    yH->SetXTitle("#eta");
//    yH->SetYTitle("dN/d#eta");
//   
//
//   c1->cd(2);
//   gPad->SetLogy();
//   ptH->Scale(5./Float_t(nev));
//   ptH->Draw();
//   ptH->SetXTitle("p_{t} [GeV/c]");
//   ptH->SetYTitle("dN/dp_{t}^{2} [GeV/c]^{-2}");
//
//    c2->Divide(1, 2);
//    c2->cd(1);
//    m0->Scale(5./Float_t(nev));
//    m0->Draw();
//    m0->SetXTitle("#m0");
//    m0->SetYTitle("dN/d#m0");
//    
//    c2->cd(2);
//    energy_hist->Scale(5./Float_t(nev));
//    energy_hist->Draw();
//    energy_hist->SetXTitle("#energy");
//    energy_hist->SetYTitle("dN/d#energy");
//
//    c3->Divide(1,3);
//    c3->cd(1);
//    px_hist->Scale(5./Float_t(nev));
//    px_hist->Draw();
//    px_hist->SetXTitle("#px");
//    px_hist->SetYTitle("dN/d#px");
//    
//    c3->cd(2);
//    py_hist->Scale(5./Float_t(nev));
//    py_hist->Draw();
//    py_hist->SetXTitle("#py");
//    py_hist->SetYTitle("dN/d#py");
//    
//    c3->cd(3);
//    pz_hist->Scale(5./Float_t(nev));
//    pz_hist->Draw();
//    pz_hist->SetXTitle("#pz");
//    pz_hist->SetYTitle("dN/d#pz");
//        
//    c4->Divide(1,2);
//    c4->cd(1);
//    daughters_hist->Scale(5./Float_t(nev));
//    daughters_hist->Draw();
//    daughters_hist->SetXTitle("#daughters");
//    daughters_hist->SetYTitle("dN/d#daughters");

    /// Saving all th histograms to the file...
    px_hist->Write();
    py_hist->Write();
    pz_hist->Write();
    m0->Write();
    energy_hist->Write();
    ptH->Write();
    yH->Write();
    daughters_hist->Write();

    f.Close();
   
}
