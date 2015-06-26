#ifndef LOOPER_H
#define LOOPER_H

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TF1.h"
#include "Math/VectorUtil.h"
#include <vector>

#include "CORE/CMS3.h"
#include "CORE/SSSelections.h"  //remove this one eventually!!!
#include "CORE/ElectronSelections.h"
#include "CORE/MuonSelections.h"
#include "CORE/MetSelections.h"
#include "CORE/JetSelections.h"
#include "CORE/VertexSelections.h"
#include "CORE/TriggerSelections.h"
#include "CORE/MCSelections.h"
#include "CORE/IsolationTools.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

struct val_err_t { float value; float error; };

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef vector<pair<const LorentzVector *, double> > jets_with_corr_t;

using namespace std; 


//Classes
class babyMaker {

public:
  void MakeBabyNtuple(const char* output_name);
  void InitBabyNtuple();
  void InitLeptonBranches(); //init. Lepton variables only.
  int looper(TChain* chain, char* output_name, int nEvents = -1);
  void SetOutputPath( std::string outputpath ); //init. Electron variables only

protected:

  TFile* BabyFile;
  TTree* BabyTree;

private:

  std::string path = "./";

  //for tree
  float evt_pfmet;
  float evt_pfmetPhi;
  float evt_trackmet;  //not CMS3
  float evt_trackmetPhi; //not CMS3
  float evt_pfsumet;
  float evt_pfmetSig;
  int evt_event;
  int evt_lumiBlock;
  int evt_run;
  bool filt_csc;
  bool filt_hbhe;
  bool filt_hcallaser;
  bool filt_ecaltp;
  bool filt_trkfail;
  bool filt_eebadsc;
  bool evt_isRealData;
  float scale1fb;     
  float evt_xsec_incl;         
  float evt_kfactor;      
  float gen_met;      
  float gen_metPhi;  
  float njets;  
  float ht;  
  vector <LorentzVector> jets;
  vector <float> jets_disc; 
  TString sample;
  int nFOs_SS;
  int nvtx;
  //-------------------//
  //------MINE---------//

  //---both--//
  LorentzVector p4;
  LorentzVector tag_p4;
  LorentzVector dilep_p4;
  LorentzVector mc_p4;
  LorentzVector mc_motherp4;
  int id; 
  int idx;
  float dxyPV;
  float dZ;
  float dxyPV_err;
  int motherID;
  int mc_id;
  float RelIso03; //RelIso03 (EA?)
  float RelIso03EA; //RelIso03 (EA?)
  float RelIso03DB; //RelIso03 (EA?)
  bool passes_SS_tight_v3;
  bool passes_SS_tight_noiso_v3;
  bool passes_SS_fo_v3;
  bool passes_SS_fo_noiso_v3;
  bool passes_SS_fo_looseMVA_v3;
  bool passes_SS_fo_looseMVA_noiso_v3;
  float ip3d;
  float ip3derr;
  int type;
  float mt;
  float ptrelv0;
  float ptrelv1;
  float miniiso;
  LorentzVector jet_close_lep;
  float ptratio;
  int tag_charge;
  float dilep_mass;
  bool isRandom;
  //---els---//
  float sigmaIEtaIEta_full5x5;
  float etaSC;
  float dEtaIn;
  float dPhiIn;
  float hOverE;
  float ecalEnergy;
  float eOverPIn;
  bool  conv_vtx_flag;
  int   exp_innerlayers;
  int   charge;
  int   sccharge;
  int   ckf_charge;
  int   trk_charge;
  bool  threeChargeAgree_branch;

  //---mus---//
  int   pid_PFMuon;
  float gfit_chi2;
  float gfit_ndof;
  int   gfit_validSTAHits;
  int   numberOfMatchedStations;
  int   validPixelHits;
  int   nlayers;
  //---------------------
    
};

#endif
