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

Double_t max(Double_t a, Double_t b){
    return (a<b) ? b : a;
}

int DaughtersOverlay(int cms=6)
{
    cout << "cms=" << cms << endl;
    char filename[100];
    sprintf(filename, "output_%d.root", cms);
    
    // TODO: Define color constants for legend
    Int_t color_b = kRed;
    Int_t color_antib = kBlue;
    Int_t color_w = kGreen;
    Int_t color_antiw = kOrange;
    Int_t color_z = kYellow;
    Int_t color_t = kCyan;
    Int_t color_antit = kSpring+10;
    Int_t color_c = kViolet;
    Int_t color_antic = kAzure-9;
    Int_t color_p = kOrange-5;
    Int_t color_ptHd = kPink+7;
    // ...
    char * name_b = "Bottom Quark";
    char * name_antib = "Bottom Anti-Quark";
    char * name_w = "W Boson";
    char * name_antiw = "W Anti-Boson";
    char * name_z = "Z Boson";
    char * name_t = "Tau+";
    char * name_antit = "Tau-";
    char * name_c = "Charm Quark";
    char * name_antic = "Charm Anti-Quark";
    char * name_p = "Photon";
    char * name_ptHd = "ptH Daughters";
    // ...
    Int_t linewidth_legend = 5;
    Int_t linewidth_fit = 2;
    // ...

// ptH
    TFile *f = new TFile(filename);
    TH1F *ptH_daughters = (TH1F*)f->Get("ptH daughters");
    THStack *ptH_overlay = (THStack*)f->Get("ptH overlay");
    
   TCanvas *c1 = new TCanvas("c1","Daughter Overlay ptH 1",600,400);
    
    //create/fill draw h1
    gStyle->SetOptStat(kFALSE);
    ptH_daughters->SetLineColor(kPink+7);
    ptH_daughters->SetLineWidth(5);
    
    ptH_daughters->Draw();
    c1->Update();
    
    ptH_overlay->Draw("same");
    c1->Update();
  
    TLegend *leg = new TLegend(.7,0.4,0.9,0.9);
    leg->SetHeader("Legend");
//    TLegendEntry* l1 = leg->AddEntry("l", "Bottom Quark","l");
//    l1->SetLineColor(kRed);
//    l1->SetLineWidth(5);
    TLegendEntry* l1 = leg->AddEntry("l", name_b,"l");
    l1->SetLineColor(color_b);
    l1->SetLineWidth(linewidth_legend);
    TLegendEntry* l2 = leg->AddEntry("l", name_antib,"l");
    l2->SetLineColor(color_antib);
    l2->SetLineWidth(linewidth_legend);
    TLegendEntry* l3 = leg->AddEntry("fl", name_w,"l");
    l3->SetLineColor(color_w);
    l3->SetLineWidth(linewidth_legend);
    TLegendEntry* l4 = leg->AddEntry("l", name_antiw,"l");
    l4->SetLineColor(color_antiw);
    l4->SetLineWidth(linewidth_legend);
    TLegendEntry* l5 = leg->AddEntry("l", name_z,"l");
    l5->SetLineColor(color_z);
    l5->SetLineWidth(linewidth_legend);
    TLegendEntry* l6 = leg->AddEntry("l", name_t, "l");
    l6->SetLineColor(color_t);
    l6->SetLineWidth(linewidth_legend);
    TLegendEntry* l7 = leg->AddEntry("l", name_antit, "l");
    l7->SetLineColor(color_antit);
    l7->SetLineWidth(linewidth_legend);
    TLegendEntry* l8 = leg->AddEntry("l", name_c, "l");
    l8->SetLineColor(color_c);
    l8->SetLineWidth(linewidth_legend);
    TLegendEntry* l9 = leg->AddEntry("l", name_antic, "l");
    l9->SetLineColor(color_antic);
    l9->SetLineWidth(linewidth_legend);
    TLegendEntry* l10 = leg->AddEntry("l", name_p, "l");
    l10->SetLineColor(color_p);
    l10->SetLineWidth(linewidth_legend);
    
    TLegendEntry* l11 = leg->AddEntry("l", name_ptHd, "l");
    l11->SetLineColor(color_ptHd);
    l11->SetLineWidth(linewidth_legend);
    leg->Draw();
    c1->Update();
    
    sprintf(filename, "Output_%d.png", cms);

    c1->SaveAs(filename);

// px
    TH1F *px_hist_daughters = (TH1F*)f->Get("px daughters");
    THStack *px_overlay = (THStack*)f->Get("px overlay");
    
    TCanvas *c2 = new TCanvas("c2","Daughter Overlay px",600,400);
    
    gStyle->SetOptStat(kFALSE);
    px_hist_daughters->SetLineColor(kPink+7);
    px_hist_daughters->SetLineWidth(5);
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
    func->SetLineWidth(linewidth_fit);
    cout << "### px daughters with energy " << cms << " TeV " << endl;
    px_hist_daughters->Fit("fit");
    
    cout << "max"<< max(1,2) << endl;
    
    Double_t max_px_hist_daughters = px_hist_daughters->GetMaximum();
    Double_t max_px_overlay = px_overlay->GetMaximum();
    Double_t M = 1.1*max(max_px_hist_daughters,max_px_overlay);
    Double_t scale1=1.0;
    Double_t scale2 = 1.0;
    
    if (fabs(max_px_hist_daughters)>1.0e-15){
        scale1 = M/max_px_hist_daughters;
    }
    px_hist_daughters->Scale(scale1);
    

    px_overlay->SetMaximum(M);
    cout << "scale= " << scale1 << endl;
    px_overlay->Draw();
    c2->Update();
    px_hist_daughters->Draw("same");
    c2->Update();
    
    
// Legend
//    TLegendEntry* l1 = leg->AddEntry("l", name_b,"l");
//    l1->SetLineColor(color_b);
//    l1->SetLineWidth(linewidth_legend);
//    TLegendEntry* l2 = leg->AddEntry("l", name_antib,"l");
//    l2->SetLineColor(color_antib);
//    l2->SetLineWidth(linewidth_legend);
//    TLegendEntry* l3 = leg->AddEntry("fl", name_w,"l");
//    l3->SetLineColor(color_w);
//    l3->SetLineWidth(linewidth_legend);
//    TLegendEntry* l4 = leg->AddEntry("l", name_antiw,"l");
//    l4->SetLineColor(color_antiw);
//    l4->SetLineWidth(linewidth_legend);
//    TLegendEntry* l5 = leg->AddEntry("l", name_z,"l");
//    l5->SetLineColor(color_z);
//    l5->SetLineWidth(linewidth_legend);
//    TLegendEntry* l6 = leg->AddEntry("l", name_t, "l");
//    l6->SetLineColor(color_t);
//    l6->SetLineWidth(linewidth_legend);
//    TLegendEntry* l7 = leg->AddEntry("l", name_antit, "l");
//    l7->SetLineColor(color_antit);
//    l7->SetLineWidth(linewidth_legend);
//    TLegendEntry* l8 = leg->AddEntry("l", name_c, "l");
//    l8->SetLineColor(color_c);
//    l8->SetLineWidth(linewidth_legend);
//    TLegendEntry* l9 = leg->AddEntry("l", name_antic, "l");
//    l9->SetLineColor(color_antic);
//    l9->SetLineWidth(linewidth_legend);
//    TLegendEntry* l10 = leg->AddEntry("l", name_p, "l");
//    l10->SetLineColor(color_p);
//    l10->SetLineWidth(linewidth_legend);
//    
//    TLegendEntry* l11 = leg->AddEntry("l", name_ptHd, "l");
//    l11->SetLineColor(color_ptHd);
//    l11->SetLineWidth(linewidth_legend);
    leg->Draw();
    c2->Update();
    sprintf(filename, "Output2_%d.png", cms);

    c2->SaveAs(filename);

// py
    TH1F *py_hist_daughters = (TH1F*)f->Get("py daughters");
    THStack *py_overlay = (THStack*)f->Get("py overlay");
    
    TCanvas *c3 = new TCanvas("c3","py daughters",600,400);
    gStyle->SetOptStat(kFALSE);
    py_hist_daughters->SetLineColor(kPink+7);
    py_hist_daughters->SetLineWidth(5);
    
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
    func->SetLineWidth(2);
    cout << "### py daughters with energy " << cms << " TeV " << endl;

    py_hist_daughters->Fit("fit");
    
    Double_t max_py_hist_daughters = py_hist_daughters->GetMaximum();
    Double_t max_py_overlay = py_overlay->GetMaximum();
    Double_t M = 1.1*max(max_py_hist_daughters,max_py_overlay);
    Double_t scale1=1.0;
    Double_t scale2 = 1.0;
    
    if (fabs(max_py_hist_daughters)>1.0e-15){
        scale1 = M/max_px_hist_daughters;
    }
    py_hist_daughters->Scale(scale1);
    
    
    py_overlay->SetMaximum(M);
    

    
    py_overlay->Draw();
    c3->Update();
    py_hist_daughters->Draw("same");
    c3->Update();
    
// Legend
//    TLegendEntry* l1 = leg->AddEntry("l", name_b,"l");
//    l1->SetLineColor(color_b);
//    l1->SetLineWidth(linewidth_legend);
//    TLegendEntry* l2 = leg->AddEntry("l", name_antib,"l");
//    l2->SetLineColor(color_antib);
//    l2->SetLineWidth(linewidth_legend);
//    TLegendEntry* l3 = leg->AddEntry("fl", name_w,"l");
//    l3->SetLineColor(color_w);
//    l3->SetLineWidth(linewidth_legend);
//    TLegendEntry* l4 = leg->AddEntry("l", name_antiw,"l");
//    l4->SetLineColor(color_antiw);
//    l4->SetLineWidth(linewidth_legend);
//    TLegendEntry* l5 = leg->AddEntry("l", name_z,"l");
//    l5->SetLineColor(color_z);
//    l5->SetLineWidth(linewidth_legend);
//    TLegendEntry* l6 = leg->AddEntry("l", name_t, "l");
//    l6->SetLineColor(color_t);
//    l6->SetLineWidth(linewidth_legend);
//    TLegendEntry* l7 = leg->AddEntry("l", name_antit, "l");
//    l7->SetLineColor(color_antit);
//    l7->SetLineWidth(linewidth_legend);
//    TLegendEntry* l8 = leg->AddEntry("l", name_c, "l");
//    l8->SetLineColor(color_c);
//    l8->SetLineWidth(linewidth_legend);
//    TLegendEntry* l9 = leg->AddEntry("l", name_antic, "l");
//    l9->SetLineColor(color_antic);
//    l9->SetLineWidth(linewidth_legend);
//    TLegendEntry* l10 = leg->AddEntry("l", name_p, "l");
//    l10->SetLineColor(color_p);
//    l10->SetLineWidth(linewidth_legend);
//    
//    TLegendEntry* l11 = leg->AddEntry("l", name_ptHd, "l");
//    l11->SetLineColor(color_ptHd);
//    l11->SetLineWidth(linewidth_legend);
    
    leg->Draw();
    c3->Update();
    
    sprintf(filename, "Output3_%d.png", cms);
    
    c3->SaveAs(filename);
    
// pz
    TH1F *pz_hist_daughters = (TH1F*)f->Get("pz daughters");
    THStack *pz_overlay = (THStack*)f->Get("pz overlay");
    
    TCanvas *c4 = new TCanvas("c4","pz daughters",600,400);
    gStyle->SetOptStat(kFALSE);
    pz_hist_daughters->SetLineColor(kPink+7);
    pz_hist_daughters->SetLineWidth(5);
    Double_t fitf(Double_t *v, Double_t *par)
    {
        Double_t arg = 0;
        if (par[2] != 0) arg = (v[0] - par[1])/par[2];
        
        Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
        return fitval;
    }
    
    TF1 *func = new TF1("fit",fitf,-30,30,5);
    func->SetParameters(2000,pz_hist_daughters->GetMean(),20);
    func->SetParNames("Constant","Mean_value","Sigma");
    func->SetLineColor(kBlack);
    func->SetLineWidth(2);
    cout << "### pz daughters with energy " << cms << " TeV " << endl;

    pz_hist_daughters->Fit("fit");
    
    Double_t max_pz_hist_daughters = pz_hist_daughters->GetMaximum();
    Double_t max_pz_overlay = pz_overlay->GetMaximum();
    Double_t M = 1.1*max(max_pz_hist_daughters,max_pz_overlay);
    Double_t scale1=1.0;
    Double_t scale2 = 1.0;
    
    if (fabs(max_pz_hist_daughters)>1.0e-15){
        scale1 = M/max_pz_hist_daughters;
    }
    pz_hist_daughters->Scale(scale1);
    pz_overlay->SetMaximum(M);
    pz_overlay->Draw();
    c4->Update();
    pz_hist_daughters->Draw("same");
    c4->Update();

// Legend
//    TLegendEntry* l1 = leg->AddEntry("l", name_b,"l");
//    l1->SetLineColor(color_b);
//    l1->SetLineWidth(linewidth_legend);
//    TLegendEntry* l2 = leg->AddEntry("l", name_antib,"l");
//    l2->SetLineColor(color_antib);
//    l2->SetLineWidth(linewidth_legend);
//    TLegendEntry* l3 = leg->AddEntry("fl", name_w,"l");
//    l3->SetLineColor(color_w);
//    l3->SetLineWidth(linewidth_legend);
//    TLegendEntry* l4 = leg->AddEntry("l", name_antiw,"l");
//    l4->SetLineColor(color_antiw);
//    l4->SetLineWidth(linewidth_legend);
//    TLegendEntry* l5 = leg->AddEntry("l", name_z,"l");
//    l5->SetLineColor(color_z);
//    l5->SetLineWidth(linewidth_legend);
//    TLegendEntry* l6 = leg->AddEntry("l", name_t, "l");
//    l6->SetLineColor(color_t);
//    l6->SetLineWidth(linewidth_legend);
//    TLegendEntry* l7 = leg->AddEntry("l", name_antit, "l");
//    l7->SetLineColor(color_antit);
//    l7->SetLineWidth(linewidth_legend);
//    TLegendEntry* l8 = leg->AddEntry("l", name_c, "l");
//    l8->SetLineColor(color_c);
//    l8->SetLineWidth(linewidth_legend);
//    TLegendEntry* l9 = leg->AddEntry("l", name_antic, "l");
//    l9->SetLineColor(color_antic);
//    l9->SetLineWidth(linewidth_legend);
//    TLegendEntry* l10 = leg->AddEntry("l", name_p, "l");
//    l10->SetLineColor(color_p);
//    l10->SetLineWidth(linewidth_legend);
//    
//    TLegendEntry* l11 = leg->AddEntry("l", name_ptHd, "l");
//    l11->SetLineColor(color_ptHd);
//    l11->SetLineWidth(linewidth_legend);
    leg->Draw();
    c4->Update();
  
    sprintf(filename, "Output4_%d.png", cms);
    c4->SaveAs(filename);
    TH1F *energy_hist_daughters = (TH1F*)f->Get("energy daughters");
    THStack *energy_overlay = (THStack*)f->Get("energy overlay");
    TCanvas *c5 = new TCanvas("c5","energy daughters",600,400);

    gStyle->SetOptStat(kFALSE);
    energy_hist_daughters->SetLineColor(kPink+7);
    energy_hist_daughters->SetLineWidth(5);
    energy_hist_daughters->Draw();
    c5->Update();
    energy_overlay->Draw("same");
    c5->Update();

// Legend
//    TLegendEntry* l1 = leg->AddEntry("l", name_b,"l");
//    l1->SetLineColor(color_b);
//    l1->SetLineWidth(linewidth_legend);
//    TLegendEntry* l2 = leg->AddEntry("l", name_antib,"l");
//    l2->SetLineColor(color_antib);
//    l2->SetLineWidth(linewidth_legend);
//    TLegendEntry* l3 = leg->AddEntry("fl", name_w,"l");
//    l3->SetLineColor(color_w);
//    l3->SetLineWidth(linewidth_legend);
//    TLegendEntry* l4 = leg->AddEntry("l", name_antiw,"l");
//    l4->SetLineColor(color_antiw);
//    l4->SetLineWidth(linewidth_legend);
//    TLegendEntry* l5 = leg->AddEntry("l", name_z,"l");
//    l5->SetLineColor(color_z);
//    l5->SetLineWidth(linewidth_legend);
//    TLegendEntry* l6 = leg->AddEntry("l", name_t, "l");
//    l6->SetLineColor(color_t);
//    l6->SetLineWidth(linewidth_legend);
//    TLegendEntry* l7 = leg->AddEntry("l", name_antit, "l");
//    l7->SetLineColor(color_antit);
//    l7->SetLineWidth(linewidth_legend);
//    TLegendEntry* l8 = leg->AddEntry("l", name_c, "l");
//    l8->SetLineColor(color_c);
//    l8->SetLineWidth(linewidth_legend);
//    TLegendEntry* l9 = leg->AddEntry("l", name_antic, "l");
//    l9->SetLineColor(color_antic);
//    l9->SetLineWidth(linewidth_legend);
//    TLegendEntry* l10 = leg->AddEntry("l", name_p, "l");
//    l10->SetLineColor(color_p);
//    l10->SetLineWidth(linewidth_legend);
//    
//    TLegendEntry* l11 = leg->AddEntry("l", name_ptHd, "l");
//    l11->SetLineColor(color_ptHd);
//    l11->SetLineWidth(linewidth_legend);
    leg->Draw();
    c5->Update();
    
    sprintf(filename, "Output5_%d.png", cms);
    
    c5->SaveAs(filename);
    
    return 0;
}
