//
//  Daughters Overlay.c
//  
//
//  Created by test on 7/28/14.
//
//
//
//#include <stdio.h>
//#include "TCanvas.h"
//#include "TStyle.h"
//#include "TH1.h"
//#include "TGaxis.h"
//#include "TRandom.h"
//
//#include "TFile.h"
//#include "THStack.h"
//#include "TLegend.h"
//#include "TLegendEntry.h"
//
//// for overlay
//#include "TCanvas.h"
//#include "TStyle.h"
//
//#include "TGaxis.h"


void gauss()
{
    TH1F *h1= new TH1F("h1", "histo from a gaussian", 100, -3, 3);
    h1->FillRandom("gaus", 500000);
    TCanvas *c1 = new TCanvas("c1","Gauss",800,600);
    
    h1->Draw();
    c1->Update();
}
