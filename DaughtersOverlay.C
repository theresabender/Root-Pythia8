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

int DaughtersOverlay(int cms=14)
{
    cout << "cms=" << cms << endl;
    char filename[100];
    sprintf(filename, "output_%d.root", cms);
    
    // TODO: Define color constants for legend
//    Int_t color_b = kRed;
    Int_t color_b = 1;
    Int_t color_antib = 1;
    Int_t color_w = 1;
    Int_t color_antiw = 1;
    Int_t color_z = 2;
    Int_t color_t = 4;
    Int_t color_antit = 8;
    Int_t color_c = 6;
    Int_t color_antic = 7;
    Int_t color_p = 41;
    Int_t color_ptHd = kBlack;
    
    Int_t fillstyle_b = 3025;
    Int_t fillstyle_antib = 3004;
    Int_t fillstyle_w = 3023;
    Int_t fillstyle_antiw = 3012;
    
    
//    Int_t color_b = 1756;
//    TColor *color = new TColor(color_b, 1.0, 0.12, 0.12);
//    
//    Int_t color_antib = 3825;
//    TColor *color2 = new TColor(color_b, 0.68, 0.24, 0.32);
    
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
    Int_t linewidth_patterns = 9;
    Int_t linewidth_fit = 2;
    Int_t linestyle_ptHd = 2;

    // ...

// ptH
    TFile *f = new TFile(filename);
    TH1F *ptH_daughters = (TH1F*)f->Get("ptH daughters");
//    THStack *ptH_overlay = (THStack*)f->Get("ptH overlay");
    

// this is new
    TH1F *ptH_daughters_b = (TH1F*)f->Get("ptH daughters b");
    TH1F *ptH_daughters_antib = (TH1F*)f->Get("ptH daughters anti b");
    TH1F *ptH_daughters_w = (TH1F*)f->Get("ptH daughters w");
    TH1F *ptH_daughters_antiw = (TH1F*)f->Get("ptH daughters anti w");
    TH1F *ptH_daughters_z = (TH1F*)f->Get("ptH daughters z");
    TH1F *ptH_daughters_t = (TH1F*)f->Get("ptH daughters anti t");
    TH1F *ptH_daughters_antit = (TH1F*)f->Get("ptH daughters anti t");
    TH1F *ptH_daughters_c = (TH1F*)f->Get("ptH daughters anti c");
    TH1F *ptH_daughters_antic = (TH1F*)f->Get("ptH daughters anti c");
    TH1F *ptH_daughters_gamma = (TH1F*)f->Get("ptH daughters gamma");
    
    
    THStack *ptH_overlay = new THStack("ptH overlay","ptH of Higgs Daughters");
    
    ptH_daughters_b->SetFillColor(color_b);
    ptH_daughters_b->SetMarkerStyle(21);
    ptH_daughters_b->SetMarkerColor(color_b);
    ptH_daughters_b->SetFillStyle(fillstyle_b);
    ptH_overlay->Add(ptH_daughters_b);
    
    ptH_daughters_antib->SetFillColor(color_antib);
    ptH_daughters_antib->SetMarkerStyle(21);
    ptH_daughters_antib->SetMarkerColor(color_antib);
    ptH_daughters_antib->SetFillStyle(fillstyle_antib);
    ptH_overlay->Add(ptH_daughters_antib);
    
    ptH_daughters_w->SetFillColor(color_w);
    ptH_daughters_w->SetMarkerStyle(21);
    ptH_daughters_w->SetMarkerColor(color_w);
    ptH_daughters_w->SetFillStyle(fillstyle_w);
    ptH_overlay->Add(ptH_daughters_w);
    
    ptH_daughters_antiw->SetFillColor(color_antiw);
    ptH_daughters_antiw->SetMarkerStyle(21);
    ptH_daughters_antiw->SetMarkerColor(color_antiw);
    ptH_daughters_antiw->SetFillStyle(fillstyle_antiw);
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
    
    
    
    
    TCanvas *testc1 = new TCanvas("testc1","Daughter Overlay ptH 1",600,400);
    
    
    TLegend *lleg = new TLegend(.7,0.4,0.9,0.9);
    lleg->SetHeader("Legend");
    
    TLegendEntry* ll1 = lleg->AddEntry(ptH_daughters_b, name_b,"f");
    ll1->SetLineColor(color_b);
    ll1->SetLineWidth(1);
    ll1->SetFillStyle(fillstyle_b);
    
    TLegendEntry* ll2 = lleg->AddEntry(ptH_daughters_antib, name_antib, "f");
    ll2->SetLineColor(color_antib);
    ll2->SetLineWidth(linewidth_patterns);
    ll2->SetFillStyle(fillstyle_antib);
    
    TLegendEntry* ll3 = lleg->AddEntry(ptH_daughters_w, name_w,"f");
    ll3->SetLineColor(color_w);
    ll3->SetLineWidth(linewidth_patterns);
    ll3->SetFillStyle(fillstyle_w);
    
    TLegendEntry* ll4 = lleg->AddEntry(ptH_daughters_antiw, name_antiw,"f");
    ll4->SetLineColor(color_antiw);
    ll4->SetLineWidth(linewidth_patterns);
    ll4->SetFillStyle(fillstyle_antiw);
    
    TLegendEntry* ll5 = lleg->AddEntry("l", name_z,"l");
    ll5->SetLineColor(color_z);
    ll5->SetLineWidth(linewidth_legend);
    
    TLegendEntry* ll6 = lleg->AddEntry("l", name_t, "l");
    ll6->SetLineColor(color_t);
    ll6->SetLineWidth(linewidth_legend);
    
    TLegendEntry* ll7 = lleg->AddEntry("l", name_antit, "l");
    ll7->SetLineColor(color_antit);
    ll7->SetLineWidth(linewidth_legend);
    
    TLegendEntry* ll8 = lleg->AddEntry("l", name_c, "l");
    ll8->SetLineColor(color_c);
    ll8->SetLineWidth(linewidth_legend);
    
    TLegendEntry* ll9 = lleg->AddEntry("l", name_antic, "l");
    ll9->SetLineColor(color_antic);
    ll9->SetLineWidth(linewidth_legend);
    
    TLegendEntry* ll10 = lleg->AddEntry("l", name_p, "l");
    ll10->SetLineColor(color_p);
    ll10->SetLineWidth(linewidth_legend);

    
    
    lleg->Draw();
    testc1->Update();

    
// end of this is new
    
    
    
    
    TCanvas *c1 = new TCanvas("c1","Daughter Overlay ptH 1",600,400);
    
    gStyle->SetOptStat(kFALSE);
    ptH_daughters->SetLineColor(color_ptHd);
    ptH_daughters->SetLineWidth(3);
    ptH_daughters->SetLineStyle(2);
      
    
    Double_t max_ptH_daughters = ptH_daughters->GetMaximum();
    Double_t max_ptH_overlay = ptH_overlay->GetMaximum();
    Double_t M = 1.1*max(max_ptH_daughters,max_ptH_overlay);
    Double_t scale1=1.0;
    Double_t scale2 = 1.0;
    
    if (fabs(max_ptH_daughters)>1.0e-15){
        scale1 = M/max_ptH_daughters;
    }
    ptH_daughters->Scale(scale1);
    
    
    ptH_overlay->SetMaximum(M);
    ptH_overlay->Draw();
  //  c2->Update();
    ptH_daughters->Draw("same");
 //   c2->Update();

    
    
    
    //create/fill draw h1

    ptH_overlay->Draw();
    c1->Update();
    
    ptH_daughters->Draw("same");
    c1->Update();
  
//    TLegend *leg = new TLegend(.7,0.4,0.9,0.9);
//    leg->SetHeader("Legend");
//
//    TLegendEntry* l1 = leg->AddEntry("l1", name_b,"f");
//    l1->SetLineColor(color_b);
//    l1->SetLineWidth(1);
//    l1->SetFillStyle(fillstyle_b);
//    TLegendEntry* l2 = leg->AddEntry("l2", name_antib,"l");
//    l2->SetLineColor(color_antib);
//    l2->SetLineWidth(linewidth_patterns);
//    l2->SetFillStyle(fillstyle_antib);
//    TLegendEntry* l3 = leg->AddEntry("l3", name_w,"l");
//    l3->SetLineColor(color_w);
//    l3->SetLineWidth(linewidth_patterns);
//    l3->SetFillStyle(fillstyle_w);
//    TLegendEntry* l4 = leg->AddEntry("l4", name_antiw,"l");
//    l4->SetLineColor(color_antiw);
//    l4->SetLineWidth(linewidth_patterns);
//    l4->SetFillStyle(fillstyle_antiw);
//    TLegendEntry* l5 = leg->AddEntry("l5", name_z,"l");
//    l5->SetLineColor(color_z);
//    l5->SetLineWidth(linewidth_legend);
//    TLegendEntry* l6 = leg->AddEntry("l6", name_t, "l");
//    l6->SetLineColor(color_t);
//    l6->SetLineWidth(linewidth_legend);
//    TLegendEntry* l7 = leg->AddEntry("l7", name_antit, "l");
//    l7->SetLineColor(color_antit);
//    l7->SetLineWidth(linewidth_legend);
//    TLegendEntry* l8 = leg->AddEntry("l8", name_c, "l");
//    l8->SetLineColor(color_c);
//    l8->SetLineWidth(linewidth_legend);
//    TLegendEntry* l9 = leg->AddEntry("l9", name_antic, "l");
//    l9->SetLineColor(color_antic);
//    l9->SetLineWidth(linewidth_legend);
//    TLegendEntry* l10 = leg->AddEntry("l10", name_p, "l");
//    l10->SetLineColor(color_p);
//    l10->SetLineWidth(linewidth_legend);
//    
//    TLegendEntry* l11 = leg->AddEntry("l11", name_ptHd, "l");
//    l11->SetLineColor(color_ptHd);
//    l11->SetLineWidth(linewidth_legend);
//    l11->SetLineStyle(linestyle_ptHd);
    lleg->Draw();
    c1->Update();
    
    sprintf(filename, "Output_%d.png", cms);

    c1->SaveAs(filename);

// px
    TH1F *px_hist_daughters = (TH1F*)f->Get("px daughters");
    THStack *px_overlay = (THStack*)f->Get("px overlay");
    
    TCanvas *c2 = new TCanvas("c2","Daughter Overlay px",600,400);
    
    gStyle->SetOptStat(kFALSE);
    px_hist_daughters->SetLineColor(color_ptHd);
    px_hist_daughters->SetLineWidth(3);
    px_hist_daughters->SetLineStyle(linestyle_ptHd);
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
    
    lleg->Draw();
    c2->Update();
    sprintf(filename, "Output2_%d.png", cms);

    c2->SaveAs(filename);

// py
    TH1F *py_hist_daughters = (TH1F*)f->Get("py daughters");
    THStack *py_overlay = (THStack*)f->Get("py overlay");
    
    TCanvas *c3 = new TCanvas("c3","py daughters",600,400);
    gStyle->SetOptStat(kFALSE);
    py_hist_daughters->SetLineColor(color_ptHd);
    py_hist_daughters->SetLineWidth(3);
    py_hist_daughters->SetLineStyle(linestyle_ptHd);
    
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
    
    lleg->Draw();
    c3->Update();
    
    sprintf(filename, "Output3_%d.png", cms);
    
    c3->SaveAs(filename);
    
// pz
    TH1F *pz_hist_daughters = (TH1F*)f->Get("pz daughters");
    THStack *pz_overlay = (THStack*)f->Get("pz overlay");
    
    TCanvas *c4 = new TCanvas("c4","pz daughters",600,400);
    gStyle->SetOptStat(kFALSE);
    pz_hist_daughters->SetLineColor(color_ptHd);
    pz_hist_daughters->SetLineWidth(3);
    pz_hist_daughters->SetLineStyle(linestyle_ptHd);
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


    lleg->Draw();
    c4->Update();
  
    sprintf(filename, "Output4_%d.png", cms);
    c4->SaveAs(filename);
    TH1F *energy_hist_daughters = (TH1F*)f->Get("energy daughters");
    THStack *energy_overlay = (THStack*)f->Get("energy overlay");
    TCanvas *c5 = new TCanvas("c5","energy daughters",600,400);

    gStyle->SetOptStat(kFALSE);
    energy_hist_daughters->SetLineColor(color_ptHd);
    energy_hist_daughters->SetLineStyle(linestyle_ptHd);
    energy_hist_daughters->SetLineWidth(3);
    energy_overlay->Draw();
    c5->Update();
    energy_hist_daughters->Draw("same");
    c5->Update();


    lleg->Draw();
    c5->Update();
    
    sprintf(filename, "Output5_%d.png", cms);
    
    c5->SaveAs(filename);
    
    return 0;
}
