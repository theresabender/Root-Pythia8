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
   //TH1F* etaH = new TH1F("etaH", "Pseudorapidity", 120, -12., 12.);
   //TH1F* ptH  = new TH1F("ptH",  "pt",              50,   0., 10.);
    TH1F* yH = new TH1F("etaH", "Higgs pseudorapidity", 100, -5., 5.);
    TH1F* ptH  = new TH1F("ptH",  "Higgs transverse momentum", 100, 0., 200.);
    
    
    
// Array of particles
   TClonesArray* particles = new TClonesArray("TParticle", 1000);
// Create pythia8 object
   TPythia8* pythia8 = new TPythia8();
    
// Configure    
    // pythia8->ReadString("SoftQCD:minBias = on");
   //   pythia8->ReadString("SoftQCD:singleDiffractive = on");
   //   pythia8->ReadString("SoftQCD:doubleDiffractive = on");
    pythia8->ReadString("Beams:eCM = 14000.");
    pythia8->ReadString("HiggsSM:gg2H = on");
    
// Initialize 
    
   pythia8->Initialize(2212 /* p */, 2212 /* p */, 14000. /* TeV */);

    //Hist pTH("Higgs transverse momentum", 100, 0., 200.);
    //Hist etaH("Higgs pseudorapidity", 100, -5., 5.);

// Event loop
    //cout << "nev=" << nev << endl;
    /// here: declare the array
//    Int_t pdg_array[20000];
//    Int_t pdg_array_idx=-1;

// Write out histograms
//    cout << ptH << yH;

//    vector<Int_t> pdg_vector;

cout << nev << endl;
    for (Int_t iev = 0; iev < nev; iev++) {
      pythia8->GenerateEvent();
      if (iev < ndeb) pythia8->EventListing();
      pythia8->ImportParticles(particles,"All");
      Int_t np = particles->GetEntriesFast();
          
//    int iH = 0;
        
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
              //         if (charge == 0.) continue;
              Float_t charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge();
          }

//         if (pdg == 211){
//              yH->Fill(eta);
//              if (pt > 0.) ptH->Fill(pt, 1./(2. * pt));
//         }
         
//         for (int iEvent = 0; iEvent < 10; ++iEvent){
//                pythia8->next();
//         } // for iEvent < 10
          
          if (pdg == 25){
              if (pt > 0.){
                  yH->Fill(eta);
                  ptH->Fill(pt, 1./(2. * pt));
                  if (iev % 100 == 1)
                      cout << "pdg=" << pdg << " Transverse momentum: "<< pt << " Rapidity: " << eta << endl ;
              }
              /// print values of final Higgs
          }

          
          
//         for (int i = 0; i < pythia8->event.size(); ++i){
//            cout << "i = " << i
//                << ", id = " << pythia8->event[i].id() << endl;
//            pythia8->stat();
//         } // for i <pythia8->event.size
//        
//          cout << "i=" << ip << " id=" << pdg << endl;
          
//          /// print values of final Higgs
//         cout << "Transverse momentum: "<< pythia8->event[i].pT() << "Rapidity: " << pythia.event[i].y() ;
          
//          if (ist>0){
//              cout << "pdg="<< pdg << " status:"<< ist << endl;
//          
//              if (pdg != 211 && pdg != -211){
//                  cout << "............ pdg=" << pdg << endl;
//                  //// here: fill the array
//                  pdg_array_idx += 1;
//                  pdg_array[pdg_array_idx]= pdg;
//                  pdg_vector.push_back(pdg);
//              }
//              
//          }
          
      } // for .. particle loop
       
//       /// here: print the array
//       //// do for-loop to print every element of the array
//        cout << "We stored "<< pdg_array_idx << " values of pdg." << endl;
//        for(Int_t li=0; li < pdg_array_idx; li++){
//            cout << "["<< li <<"]: pdg=" << pdg_array[li] << endl;
//            cout << "["<< li <<"]: pdg=" << pdg_vector[li] << endl;
//        }
//        
//        for (vector<Int_t>::iterator iter = pdg_vector.begin() ; iter != pdg_vector.end(); ++iter){
//        
//            cout << "pdg=" << pdg_vector[*iter] << endl;
//        }
        
   } // for .. event loop

    
   //  delete pdg_vector;
    
   pythia8->PrintStatistics();
    
   TCanvas* c1 = new TCanvas("c1","Pythia8 test example",800,800);
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
 }
