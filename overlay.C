//example of macro illustrating how to superimpose two histograms
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"
   
void overlay()
{
   //example of macro illustrating how to superimpose two histograms
   //with different scales in the "same" pad.
   // To see the output of this macro, click begin_html <a href="gif/twoscales.gif" >here</a> end_html
   //Author: Rene Brun
    
    // TODO: open file output.root into variable f
    // TODO: read histogram from file
      TFile *f = new TFile("output20k-2.root");
      TH1I * daughters_hist = (TH1I*)f.Get("daughters");
      TH1I * finaldaughters_hist = (TH1I*)f.Get("finaldaughters");
      TH1I * nonfinaldaughters_hist = (TH1I*)f.Get("nonfinaldaughters");
    
    
    
   TCanvas *c1 = new TCanvas("c1","hists with different scales",600,400);

   //create/fill draw h1
   gStyle->SetOptStat(kFALSE);
   daughters->SetLineColor(kBlack);
   daughters->SetLineWidth(1);
   daughters_hist->Draw();
   c1->Update();  
    
   //create hint1 filled with the bins integral of h1
   //TH1F *finaldaughters = new TH1I("hint1","h1 bins integral",100,-3,3);
  // instead of hint1 use finaldaughters
    
   //scale hint1 to the pad coordinates
   Float_t rightmax1 = 1.1*daughters->GetMaximum();
   Float_t scale1 = gPad->GetUymax()/rightmax1;
   finaldaughters->SetLineColor(kRed);
   finaldaughters->SetLineWidth(2);
   finaldaughters->Scale(scale1);
   finaldaughters->Draw("same");
   
   Float_t rightmax2 = 1.1*daughters->GetMaximum();
   Float_t scale2 = gPad->GetUymax()/rightmax2;
   nonfinaldaughters->SetLineColor(kBlue);
   nonfinaldaughters->Scale(scale2);
   nonfinaldaughters->Draw("same");
    
    leg = new TLegend(0.1,0.7,0.4,0.9);
    leg->SetHeader("Legend");
    //leg->AddEntry("l", "Daughters","l");
    TLegendEntry* l1 = leg->AddEntry("l", "Daughters","l");
    l1->SetLineColor(kBlack);
    //leg->SetTextColor(kRed);
    //leg->AddEntry("l","Final Daughters","l");
    TLegendEntry* l2 = leg->AddEntry("l","Final Daughters","l");
    l2->SetLineColor(kRed);
    //leg->AddEntry("fl","Non-final Daughters","l");
    TLegendEntry* l3 = leg->AddEntry("fl","Non-final Daughters","l");
    l3->SetLineColor(kBlue);
    
    leg->Draw();
//    
//    {
//        TCanvas *c2 = new TCanvas("c2","c2",500,300);
//        
//        TLegend* leg = new TLegend(0.2, 0.2, .8, .8);
//        TH1* h = new TH1I("", "", 1, 0, 1);
//        
//        leg->AddEntry(h, "Daughters \"h\"", "l");
//        leg->AddEntry((TObject*)0, "", "");
//        leg->AddEntry((TObject*)0, "Final Daughters", "");
//        leg->AddEntry((TObject*)0, "", "");
//        leg->AddEntry(h, "Non-final Daughters", "l");
//        
//        leg->Draw();
//        return c2;
//    }
}
