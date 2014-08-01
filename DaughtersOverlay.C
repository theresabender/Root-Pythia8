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


//void DaughtersOverlay(int argc, char* argv[])
//Int_t plotter(Int_t cms)
int DaughtersOverlay(int cms=6)
{
    cout << "cms=" << cms << endl;
//Int_t cms = 6;
//    if (argc == 2) {
//        cms = atoi (argv[1]);
//    }

//    Int_t cms = 2;
    char filename[100]; // = "sims_%d.root" + en;
    sprintf(filename, "output_%d.root", cms);

// ptH
    //TFile *f = new TFile("output.root");
    TFile *f = new TFile(filename);
    TH1F *ptH_daughters = (TH1F*)f->Get("ptH daughters");
    THStack *ptH_overlay = (THStack*)f->Get("ptH overlay");
    
   TCanvas *c1 = new TCanvas("c1","Daughter Overlay ptH 1",600,400);
    
////    TH1I * hs = (TH1I*)f.Get("daughters");
////    c1->cd();
//    //create/fill draw h1
     gStyle->SetOptStat(kFALSE);
    ptH_daughters->SetLineColor(kPink+7);
    ptH_daughters->SetLineWidth(5);
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
    ptH_overlay->Draw("same");
    c1->Update();
//    c2->Update();
    
    
    TLegend *leg = new TLegend(.7,0.4,0.9,0.9);
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
    TLegendEntry* l6 = leg->AddEntry("l", "Tau+", "l");
    l6->SetLineColor(kCyan);
    l6->SetLineWidth(5);
    TLegendEntry* l7 = leg->AddEntry("l", "Tau-", "l");
    l7->SetLineColor(kSpring+10);
    l7->SetLineWidth(5);
    TLegendEntry* l8 = leg->AddEntry("l", "C Quark", "l");
    l8->SetLineColor(kViolet);
    l8->SetLineWidth(5);
    TLegendEntry* l9 = leg->AddEntry("l", "Anti-C Quark", "l");
    l9->SetLineColor(kAzure-9);
    l9->SetLineWidth(5);
    TLegendEntry* l10 = leg->AddEntry("l", "Photon", "l");
    l10->SetLineColor(kOrange-5);
    l10->SetLineWidth(5);
    
    TLegendEntry* l11 = leg->AddEntry("l", "ptH Daughters", "l");
    l11->SetLineColor(kPink+7);
    l11->SetLineWidth(5);
    leg->Draw();
    c1->Update();
    

    
    sprintf(filename, "Output_%d.png", cms);
    
    
    
    
  //  c1->SaveAs("Output.png");
    c1->SaveAs(filename);
   // exit(0);
    
    
// px
//    TFile *f = new TFile("output.root");
    TH1F *px_hist_daughters = (TH1F*)f->Get("px daughters");
    THStack *px_overlay = (THStack*)f->Get("px overlay");
    
    TCanvas *c2 = new TCanvas("c2","Daughter Overlay px",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    px_hist_daughters->SetLineColor(kPink+7);
    px_hist_daughters->SetLineWidth(5);
    //    cout << &ptH_daughters << ptH_daughters << endl;
    //    ptH_daughters->Draw();
    ////    c1->Update();
    
    px_hist_daughters->Draw();
    c2->Update();
    
    Double_t fitf(Double_t *v, Double_t *par)
    {
        Double_t arg = 0;
        if (par[2] != 0) arg = (v[0] - par[1])/par[2];
        
        Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
        return fitval;
    }

    TF1 *func = new TF1("fit",fitf,-3,3,3);
    func->SetParameters(500,px_hist_daughters->GetMean(),px_hist_daughters->GetRMS());
    func->SetParNames("Constant","Mean_value","Sigma");
    func->SetLineColor(kBlack);
    func->SetLineWidth(5);
    px_hist_daughters->Fit("fit");
    
    
       
        //    TFile *f = new TFile("hsimple.root");
        
//        TH1F *h1= new TH1F("h1", "histo from a gaussian", 100, -3, 3);
//        h1->FillRandom("gaus", 500000);
        
        //create a function with 3 parameters in the range [-3,3]

    
    
    
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
    px_overlay->Draw("same");
    c2->Update();
    //    c2->Update();
    
    
    TLegend *leg = new TLegend(.7,0.4,0.9,0.9);
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
    TLegendEntry* l6 = leg->AddEntry("l", "Tau+", "l");
    l6->SetLineColor(kCyan);
    l6->SetLineWidth(5);
    TLegendEntry* l7 = leg->AddEntry("l", "Tau-", "l");
    l7->SetLineColor(kSpring+10);
    l7->SetLineWidth(5);
    TLegendEntry* l8 = leg->AddEntry("l", "C Quark", "l");
    l8->SetLineColor(kViolet);
    l8->SetLineWidth(5);
    TLegendEntry* l9 = leg->AddEntry("l", "Anti-C Quark", "l");
    l9->SetLineColor(kAzure-9);
    l9->SetLineWidth(5);
    TLegendEntry* l10 = leg->AddEntry("l", "Photon", "l");
    l10->SetLineColor(kOrange-5);
    l10->SetLineWidth(5);
    
    TLegendEntry* l11 = leg->AddEntry("l", "px Daughters", "l");
    l11->SetLineColor(kPink+7);
    l11->SetLineWidth(5);
    leg->Draw();
    c2->Update();
    sprintf(filename, "Output2_%d.png", cms);

//    c2->SaveAs("Output2.png");
    c2->SaveAs(filename);

    

// py
//   TFile *f = new TFile("output.root");
    TH1F *py_hist_daughters = (TH1F*)f->Get("py daughters");
    THStack *py_overlay = (THStack*)f->Get("py overlay");
    
    TCanvas *c3 = new TCanvas("c3","py daughters",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    py_hist_daughters->SetLineColor(kPink+7);
    py_hist_daughters->SetLineWidth(5);
    //    cout << &ptH_daughters << ptH_daughters << endl;
    //    ptH_daughters->Draw();
    ////    c1->Update();
    
    py_hist_daughters->Draw();
    c3->Update();
    
    Double_t fitf(Double_t *v, Double_t *par)
    {
        Double_t arg = 0;
        if (par[2] != 0) arg = (v[0] - par[1])/par[2];
        
        Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
        return fitval;
    }
    
    TF1 *func = new TF1("fit",fitf,-3,3,3);
    func->SetParameters(500,py_hist_daughters->GetMean(),py_hist_daughters->GetRMS());
    func->SetParNames("Constant","Mean_value","Sigma");
    func->SetLineColor(kBlack);
    func->SetLineWidth(5);
    py_hist_daughters->Fit("fit");
    
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
    py_overlay->Draw("same");
    c3->Update();
    //    c2->Update();
    
    
    TLegend *leg = new TLegend(.7,0.4,0.9,0.9);
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
   
    TLegendEntry* l6 = leg->AddEntry("l", "Tau+", "l");
    l6->SetLineColor(kCyan);
    l6->SetLineWidth(5);
    TLegendEntry* l7 = leg->AddEntry("l", "Tau-", "l");
    l7->SetLineColor(kSpring+10);
    l7->SetLineWidth(5);
    TLegendEntry* l8 = leg->AddEntry("l", "C Quark", "l");
    l8->SetLineColor(kViolet);
    l8->SetLineWidth(5);
    TLegendEntry* l9 = leg->AddEntry("l", "Anti-C Quark", "l");
    l9->SetLineColor(kAzure-9);
    l9->SetLineWidth(5);
    TLegendEntry* l10 = leg->AddEntry("l", "Photon", "l");
    l10->SetLineColor(kOrange-5);
    l10->SetLineWidth(5);
   
    TLegendEntry* l11 = leg->AddEntry("l", "py Daughters", "l");
    l11->SetLineColor(kPink+7);
    l11->SetLineWidth(5);
    
    leg->Draw();
    c3->Update();
    
    sprintf(filename, "Output3_%d.png", cms);
    
  //  c3->SaveAs("Output3.png");
    c3->SaveAs(filename);
    
// pz
 //   TFile *f = new TFile("output.root");
    TH1F *pz_hist_daughters = (TH1F*)f->Get("pz daughters");
    THStack *pz_overlay = (THStack*)f->Get("pz overlay");
    
    TCanvas *c4 = new TCanvas("c4","pz daughters",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    pz_hist_daughters->SetLineColor(kPink+7);
    pz_hist_daughters->SetLineWidth(5);
    //    cout << &ptH_daughters << ptH_daughters << endl;
    //    ptH_daughters->Draw();
    ////    c1->Update();
    
    pz_hist_daughters->Draw();
    c4->Update();
    
    Double_t fitf(Double_t *v, Double_t *par)
    {
        Double_t arg = 0;
        if (par[2] != 0) arg = (v[0] - par[1])/par[2];
        
        Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
        return fitval;
    }
    
    TF1 *func = new TF1("fit",fitf,-30,30,5);
    //func->SetParameters(2000,pz_hist_daughters->GetMean(),pz_hist_daughters->GetRMS());
    func->SetParameters(2000,pz_hist_daughters->GetMean(),20);
    func->SetParNames("Constant","Mean_value","Sigma");
    func->SetLineColor(kBlack);
    func->SetLineWidth(5);
    pz_hist_daughters->Fit("fit");
    
    
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
    pz_overlay->Draw("same");
    c4->Update();
    //    c2->Update();
    
    
    TLegend *leg = new TLegend(.7,0.4,0.9,0.9);
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
    TLegendEntry* l6 = leg->AddEntry("l", "Tau+", "l");
    l6->SetLineColor(kCyan);
    l6->SetLineWidth(5);
    TLegendEntry* l7 = leg->AddEntry("l", "Tau-", "l");
    l7->SetLineColor(kSpring+10);
    l7->SetLineWidth(5);
    TLegendEntry* l8 = leg->AddEntry("l", "C Quark", "l");
    l8->SetLineColor(kViolet);
    l8->SetLineWidth(5);
    TLegendEntry* l9 = leg->AddEntry("l", "Anti-C Quark", "l");
    l9->SetLineColor(kAzure-9);
    l9->SetLineWidth(5);
    TLegendEntry* l10 = leg->AddEntry("l", "Photon", "l");
    l10->SetLineColor(kOrange-5);
    l10->SetLineWidth(5);
    
    TLegendEntry* l11 = leg->AddEntry("l", "pz Daughters", "l");
    l11->SetLineColor(kPink+7);
    l11->SetLineWidth(5);
    leg->Draw();
    c4->Update();
  
    sprintf(filename, "Output4_%d.png", cms);
    
 //   c4->SaveAs("Output4.png");
    c4->SaveAs(filename);
    
    
// energy
//    TFile *f = new TFile("output.root");
    TH1F *energy_hist_daughters = (TH1F*)f->Get("energy daughters");
    THStack *energy_overlay = (THStack*)f->Get("energy overlay");
    
    TCanvas *c5 = new TCanvas("c5","energy daughters",600,400);
    
    ////    TH1I * hs = (TH1I*)f.Get("daughters");
    ////    c1->cd();
    //    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    energy_hist_daughters->SetLineColor(kPink+7);
    energy_hist_daughters->SetLineWidth(5);
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
    energy_overlay->Draw("same");
    c5->Update();
    //    c2->Update();
    
    
    TLegend *leg = new TLegend(.7,0.4,0.9,0.9);
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
    TLegendEntry* l6 = leg->AddEntry("l", "Tau+", "l");
    l6->SetLineColor(kCyan);
    l6->SetLineWidth(5);
    TLegendEntry* l7 = leg->AddEntry("l", "Tau-", "l");
    l7->SetLineColor(kSpring+10);
    l7->SetLineWidth(5);
    TLegendEntry* l8 = leg->AddEntry("l", "C Quark", "l");
    l8->SetLineColor(kViolet);
    l8->SetLineWidth(5);
    TLegendEntry* l9 = leg->AddEntry("l", "Anti-C Quark", "l");
    l9->SetLineColor(kAzure-9);
    l9->SetLineWidth(5);
    TLegendEntry* l10 = leg->AddEntry("l", "Photon", "l");
    l10->SetLineColor(kOrange-5);
    l10->SetLineWidth(5);
    
    TLegendEntry* l11 = leg->AddEntry("l", "Energy Daughters", "l");
    l11->SetLineColor(kPink+7);
    l11->SetLineWidth(5);
    leg->Draw();
    c5->Update();
    
    sprintf(filename, "Output5_%d.png", cms);
    
 //   c5->SaveAs("Output5.png");
    c5->SaveAs(filename);
    
    return 0;
}

//
//void DaughtersOverlay()
//{
//    for (Int_t loop=2; loop<4 ; loop+=2){
//        cout << "loop="<< loop << endl;
//        plotter(loop);
//    }
//}
