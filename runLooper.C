#ifndef __CINT__
#include "TChain.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"

#include "fakeratelooper.C"

#include <iostream>
#endif

enum sample_t { QCD_Test, QCD_Mu_Enriched, QCD_EM_Enriched, QCD_non_Enriched, QCD_HT, TTBAR, DY, WJets };

char* getTitle(sample_t sample); 
TChain* getChain(sample_t sample); 

void runLooper(){
  cout<<__LINE__<<endl;
  //User-controlled options here (only)
  sample_t sample = QCD_Test;
  //int nEvents = 100;
  int nEvents = -1;
  cout<<__LINE__<<endl;

  gSystem->Load("CORE/CMS3_CORE.so");
  gSystem->Load("fakeratelooper.so"); 
  cout<<__LINE__<<endl;

  babyMaker *mylooper = new babyMaker();
  cout<<__LINE__<<endl;

  TChain *chain = (TChain*)getChain(sample);
  char* title = getTitle(sample);
  cout<<__LINE__<<endl;

  mylooper->looper(chain, title, nEvents); 
  cout<<__LINE__<<endl;

  return;
}

char* getTitle(sample_t sample){
  if (sample == QCD_Test) return "qcd_test";
  if (sample == QCD_Mu_Enriched) return "QCD_Mu_Enriched";
  if (sample == QCD_EM_Enriched) return "QCD_EM_Enriched";
  if (sample == QCD_non_Enriched) return "QCD_non_Enriched";
  if (sample == QCD_HT) return "QCD_HT";
  if (sample == TTBAR) return "TTBAR";
  if (sample == DY) return "DY";
  if (sample == WJets) return "WJets";
}

TChain*getChain(sample_t sample){
  TChain *result = new TChain("Events");  
  
  //QCD_test (test with just one file)
  if (sample == QCD_Test){
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-20toInf_MuEnrichedPt15_PionKaonDecay_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v3/V07-02-08/merged_ntuple_1.root");
  }

  //QCD_MuEnriched
  if (sample == QCD_Mu_Enriched){
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-20toInf_MuEnrichedPt15_PionKaonDecay_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v3/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-30to50_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8_Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8_Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-80to120_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8_Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/V07-02-08/merged_ntuple_*.root");
  }

  //QCD_EM_Enriched
  if (sample == QCD_EM_Enriched){
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt_20to30_bcToE_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    //result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt_30to80_bcToE_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");  //bad sample. Doesn't exist
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt_80to170_bcToE_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt_170toInf_bcToE_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-5to10_EMEnriched_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-10to20_EMEnriched_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-20to30_EMEnriched_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-30to80_EMEnriched_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-80to170_EMEnriched_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
  }

  //QCD non-Enriched
  if (sample == QCD_non_Enriched){
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-15to30_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-30to50_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-50to80_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-80to120_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-120to170_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-170to300_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-06/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-300to470_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-470to600_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-600to800_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-800to1000_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-1800_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-1800to2400_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_PHYS14_25_V1-v2/V07-02-06/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-2400to3200_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-3200_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-15to3000_Tune4C_Flat_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
  }

  //QCD HT
  if (sample == QCD_HT){
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_HT-100To250_13TeV-madgraph_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_HT-500To1000_13TeV-madgraph_Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_HT_1000ToInf_13TeV-madgraph_Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v1/V07-02-08/merged_ntuple_*.root");
    result->Add("/hadoop/cms/store/group/snt/phys14/QCD_HT_250To500_13TeV-madgraph_Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v2/V07-02-08/merged_ntuple_*.root");
  }

  //ttbar
  if (sample == TTBAR){
    result->Add("/hadoop/cms/store/group/snt/phys14/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
  }

  //DY
  if (sample == DY){
    result->Add("/hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_13TeV-madgraph-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
  }
  //WJets
  if (sample == WJets){
    result->Add("/hadoop/cms/store/group/snt/phys14/WJetsToLNu_13TeV-madgraph-pythia8-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_*.root");
  }

  return result;
}
