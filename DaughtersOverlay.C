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
// ptH
    TFile *f = new TFile("output.root");
    TH1F *ptH_daughters = (TH1F*)f->Get("ptH daughters");
    THStack *ptH_overlay = (THStack*)f->Get("ptH overlay");
    
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
    c1->Update();
    
    c1->SaveAs("Output.png");
    
    
// px
    TFile *f = new TFile("output.root");
    TH1F *px_hist_daughters = (TH1F*)f->Get("px daughters");
    THStack *px_overlay = (THStack*)f->Get("px overlay");
    
    TCanvas *c2 = new TCanvas("c2","Daughter Overlay px",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    px_hist_daughters->SetLineColor(kPink+7);
    px_hist_daughters->SetLineWidth(3);
    //    cout << &ptH_daughters << ptH_daughters << endl;
    //    ptH_daughters->Draw();
    ////    c1->Update();
    
    px_hist_daughters->Draw();
    c2->Update();
    
    
    
    //    TCanvas *c2 = new TCanvas("c2","Daughter Overlay ptH 2",600,400);
    //
    //    //create hint1 filled with the bins integral of h1
    //    TH1I *finaldaughters = new TH1I("hint1","h1 bins integral",100,-3,3);
    //    // instead of hint1 use finaldaughters
    //
    //    //scale hint1 to the pad coordinates
    Float_t rightmax1 = 1.1*px_hist_daughters->GetMaximum();
    Float_t scale1 = gPad->GetUymax()/rightmax1;
    ////    hs->SetLineColor(kRed);
    // //   hs->SetLineWidth(1);
    ////    hs->Scale(scale1);
    //    //hs->Draw("same");
    hs3->Draw("same");
    c2->Update();
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
    c2->Update();
    
    c2->SaveAs("Output2.png");
    
// py
    TFile *f = new TFile("output.root");
    TH1F *py_hist_daughters = (TH1F*)f->Get("py daughters");
    THStack *py_overlay = (THStack*)f->Get("py overlay");
    
    TCanvas *c3 = new TCanvas("c3","py daughters",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    py_hist_daughters->SetLineColor(kPink+7);
    py_hist_daughters->SetLineWidth(3);
    //    cout << &ptH_daughters << ptH_daughters << endl;
    //    ptH_daughters->Draw();
    ////    c1->Update();
    
    py_hist_daughters->Draw();
    c3->Update();
    
    
    
    //    TCanvas *c2 = new TCanvas("c2","Daughter Overlay ptH 2",600,400);
    //
    //    //create hint1 filled with the bins integral of h1
    //    TH1I *finaldaughters = new TH1I("hint1","h1 bins integral",100,-3,3);
    //    // instead of hint1 use finaldaughters
    //
    //    //scale hint1 to the pad coordinates
    Float_t rightmax1 = 1.1*py_hist_daughters->GetMaximum();
    Float_t scale1 = gPad->GetUymax()/rightmax1;
    ////    hs->SetLineColor(kRed);
    // //   hs->SetLineWidth(1);
    ////    hs->Scale(scale1);
    //    //hs->Draw("same");
    hs4->Draw("same");
    c3->Update();
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
    c3->Update();
    
    c3->SaveAs("Output3.png");
    
// pz
    TFile *f = new TFile("output.root");
    TH1F *pz_hist_daughters = (TH1F*)f->Get("pz daughters");
    THStack *pz_overlay = (THStack*)f->Get("pz overlay");
    
    TCanvas *c4 = new TCanvas("c4","pz daughters",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    pz_hist_daughters->SetLineColor(kPink+7);
    pz_hist_daughters->SetLineWidth(3);
    //    cout << &ptH_daughters << ptH_daughters << endl;
    //    ptH_daughters->Draw();
    ////    c1->Update();
    
    pz_hist_daughters->Draw();
    c4->Update();
    
    
    
    //    TCanvas *c2 = new TCanvas("c2","Daughter Overlay ptH 2",600,400);
    //
    //    //create hint1 filled with the bins integral of h1
    //    TH1I *finaldaughters = new TH1I("hint1","h1 bins integral",100,-3,3);
    //    // instead of hint1 use finaldaughters
    //
    //    //scale hint1 to the pad coordinates
    Float_t rightmax1 = 1.1*pz_hist_daughters->GetMaximum();
    Float_t scale1 = gPad->GetUymax()/rightmax1;
    ////    hs->SetLineColor(kRed);
    // //   hs->SetLineWidth(1);
    ////    hs->Scale(scale1);
    //    //hs->Draw("same");
    hs5->Draw("same");
    c4->Update();
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
    c4->Update();
    
    c4->SaveAs("Output4.png");
    
// energy
    TFile *f = new TFile("output.root");
    TH1F *energy_hist_daughters = (TH1F*)f->Get("energy daughters");
    THStack *energy_overlay = (THStack*)f->Get("energy overlay");
    
    TCanvas *c5 = new TCanvas("c5","energy daughters",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    energy_hist_daughters->SetLineColor(kPink+7);
    energy_hist_daughters->SetLineWidth(3);
    //    cout << &ptH_daughters << ptH_daughters << endl;
    //    ptH_daughters->Draw();
    ////    c1->Update();
    
    energy_hist_daughters->Draw();
    c5->Update();
    
    
    
    //    TCanvas *c2 = new TCanvas("c2","Daughter Overlay ptH 2",600,400);
    //
    //    //create hint1 filled with the bins integral of h1
    //    TH1I *finaldaughters = new TH1I("hint1","h1 bins integral",100,-3,3);
    //    // instead of hint1 use finaldaughters
    //
    //    //scale hint1 to the pad coordinates
    Float_t rightmax1 = 1.1*energy_hist_daughters->GetMaximum();
    Float_t scale1 = gPad->GetUymax()/rightmax1;
    ////    hs->SetLineColor(kRed);
    // //   hs->SetLineWidth(1);
    ////    hs->Scale(scale1);
    //    //hs->Draw("same");
    hs2->Draw("same");
    c5->Update();
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
    c5->Update();
    
    c5->SaveAs("Output5.png");
}
