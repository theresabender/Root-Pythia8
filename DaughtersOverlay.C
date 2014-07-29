//
//  Daughters Overlay.c
//  
//
//  Created by test on 7/28/14.
//
//

#include <stdio.h>
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"

#include "TFile.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLegendEntry.h"

// for overlay
#include "TCanvas.h"
#include "TStyle.h"

#include "TGaxis.h"


void DaughtersOverlay()
{
      TFile *f = new TFile("output.root");
    TH1F *ptH_daughters = (TH1F*)f->Get("ptH daughters");
    THStack *hs = (THStack*)f->Get("hs");
    
   TCanvas *c1 = new TCanvas("c1","Daughter Overlay ptH 1",600,400);
    
////    TH1I * hs = (TH1I*)f.Get("daughters");
////    c1->cd();
//    //create/fill draw h1
     gStyle->SetOptStat(kFALSE);
    ptH_daughters->SetLineColor(kPink+7);
    ptH_daughters->SetLineWidth(3);
//    cout << &ptH_daughters << ptH_daughters << endl;
//    ptH_daughters->Draw();
////    c1->Update();
    
    ptH_daughters->Draw();
    c1->Update();
    
    
    
//    TCanvas *c2 = new TCanvas("c2","Daughter Overlay ptH 2",600,400);
//    
//    //create hint1 filled with the bins integral of h1
//    TH1I *finaldaughters = new TH1I("hint1","h1 bins integral",100,-3,3);
//    // instead of hint1 use finaldaughters
//    
//    //scale hint1 to the pad coordinates
    Float_t rightmax1 = 1.1*ptH_daughters->GetMaximum();
    Float_t scale1 = gPad->GetUymax()/rightmax1;
////    hs->SetLineColor(kRed);
// //   hs->SetLineWidth(1);
////    hs->Scale(scale1);
//    //hs->Draw("same");
    hs->Draw("same");
   c1->Update();
//    c2->Update();
    
    
    TLegend *leg = new TLegend(.57,0.64,0.9,0.9);
    leg->SetHeader("Legend");
    TLegendEntry* l1 = leg->AddEntry("l", "Bottom Quark","l");
    l1->SetLineColor(kRed);
    l1->SetLineWidth(5);
    TLegendEntry* l2 = leg->AddEntry("l","Anti-Bottom Quark","l");
    l2->SetLineColor(kBlue);
    l2->SetLineWidth(5);
    TLegendEntry* l3 = leg->AddEntry("fl","W Boson","l");
    l3->SetLineColor(kGreen);
    l3->SetLineWidth(5);
    TLegendEntry* l4 = leg->AddEntry("l", "Anti-W Boson","l");
    l4->SetLineColor(kOrange);
    l4->SetLineWidth(5);
    TLegendEntry* l5 = leg->AddEntry("l", "Z Boson","l");
    l5->SetLineColor(kYellow);
    l5->SetLineWidth(5);
    TLegendEntry* l6 = leg->AddEntry("l", "ptH Daughters", "l");
    l6->SetLineColor(kPink+7);
    l6->SetLineWidth(3);
    
    leg->Draw();

    
}
