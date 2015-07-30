#ifndef LOOPER_H
#define LOOPER_H

#include "TFile.h"
#include "TChain.h"
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

#include "Math/Vector4D.h" 
#include "Math/LorentzVector.h"

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

  bool checkMuonTag (unsigned int i);
  bool checkElectronTag (unsigned int i);
  void fillMuonTriggerBranches(LorentzVector &p4, int idx);
  void fillElectronTriggerBranches(LorentzVector &p4, int idx);



protected:

  TFile* BabyFile;
  TTree* BabyTree;

private:

  bool usedMu = false;
  bool usedEl = false;
  float rndm = 0;

  std::string path = "./";

  //for tree
  //---event stuff---//
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

  //---both e and mu---//
  LorentzVector p4;
  LorentzVector tag_p4;
  LorentzVector dilep_p4;
  LorentzVector mc_p4;
  LorentzVector mc_motherp4;
  int mc_motherid;
  int id; 
  bool isPF; 
  int idx;
  float dxyPV;
  float dZ;
  float dxyPV_err;
  int motherID;
  int mc_id;
  float RelIso03; //RelIso03 (not corrected)
  float RelIso03EA; //RelIso03 (EffectiveArea corrected)
  float RelIso03DB; //RelIso03 (DeltaBeta corrected)
  float pfChargedHadronIso;
  float pfPhotonIso;
  float pfNeutralHadronIso;
  float tkIso;
  float sumPUPt;
  bool passes_SS_tight_v3;
  bool passes_SS_tight_noiso_v3;
  bool passes_SS_fo_v3;
  bool passes_SS_fo_noiso_v3;
  bool passes_SS_fo_looseMVA_v3;
  bool passes_SS_fo_looseMVA_noiso_v3;
  bool passes_WW_medium_v1;
  bool passes_WW_medium_noiso_v1;
  bool passes_WW_fo_v1;
  bool passes_WW_fo_noiso_v1;
  bool passes_WW_fo_looseMVA_v1;
  bool passes_WW_fo_looseMVA_noiso_v1;
  bool passes_WW_veto_v1;
  bool passes_WW_veto_noiso_v1;
  bool passes_HAD_veto_v3;
  bool passes_HAD_veto_noiso_v3;
  bool passes_HAD_loose_v3;
  bool passes_HAD_loose_noiso_v3;
  bool passes_POG_vetoID;
  bool passes_POG_looseID;
  bool passes_POG_mediumID;
  bool passes_POG_tightID;
  float ip3d;
  float ip3derr;
  int type;
  float mt;
  float ptrelv0;
  float ptrelv1;
  float miniiso;
  float miniisoDB;
  float reliso04;
  float annulus04;
  LorentzVector jet_close_lep;
  float ptratio;
  int tag_charge;
  float tag_eSeed;
  float tag_eSCraw;
  bool tag_HLTLeadingLeg;
  float dilep_mass;
  bool isRandom;
  float iso03sumPt;
  float iso03emEt;
  float iso03hadEt;

  // -- tag HLT match -- // 
  int tag_HLT_Ele25WP60_Ele8_Mass55_LeadingLeg;
  int tag_HLT_Ele25WP60_SC4_Mass55_LeadingLeg;
  int tag_HLT_Ele33_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg;
  int tag_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg;
  int tag_HLT_Ele18_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg;
  int tag_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg;
  int tag_HLT_Ele33_CaloIdM_TrackIdM_PFJet30_ElectronLeg;
  int tag_HLT_Ele23_CaloIdM_TrackIdM_PFJet30_ElectronLeg;
  int tag_HLT_Ele18_CaloIdM_TrackIdM_PFJet30_ElectronLeg;
  int tag_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_ElectronLeg;
  int tag_HLT_Ele8_CaloIdM_TrackIdM_PFJet30_ElectronLeg;

  int tag_HLT_Ele27_eta2p1_WP75_Gsf;
  int tag_HLT_Ele27_WP85_Gsf;
  int tag_HLT_Ele27_eta2p1_WPLoose_Gsf;
  int tag_HLT_Ele27_eta2p1_WPTight_Gsf;
  int tag_HLT_Ele32_eta2p1_WP75_Gsf;
  int tag_HLT_Ele32_eta2p1_WPLoose_Gsf;
  int tag_HLT_Ele32_eta2p1_WPTight_Gsf;
  int tag_HLT_Ele22_eta2p1_WPLoose_Gsf;
  int tag_HLT_Ele22_eta2p1_WPTight_Gsf;
  int tag_HLT_Ele23_WPLoose_Gsf;
  int tag_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg;
  int tag_HLT_Ele23_CaloIdL_TrackIdL_IsoVL;
  int tag_HLT_Ele12_CaloIdL_TrackIdL_IsoVL;
	
  int tag_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg;
  int tag_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg;
  int tag_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_TrailingLeg;
  int tag_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_LeadingLeg;
  int tag_HLT_IsoMu20;
  int tag_HLT_IsoTkMu20;
  int tag_HLT_IsoMu24_eta2p1;
  int tag_HLT_IsoTkMu24_eta2p1;
  int tag_HLT_IsoMu27;
  int tag_HLT_IsoTkMu27;

  // -- probe HLT match -- // 

  int probe_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg;
  int probe_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg;

  int probe_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg;
  int probe_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg;
  int probe_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_TrailingLeg;
  int probe_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_LeadingLeg;

  //---els---//
  float sigmaIEtaIEta_full5x5;
  float sigmaIEtaIEta;
  float etaSC;
  float dEtaIn;
  float dPhiIn;
  float hOverE;
  float eSeed;
  float ecalEnergy;
  float eOverPIn;
  bool  conv_vtx_flag;
  int   exp_innerlayers;
  int   charge;
  int   sccharge;
  int   ckf_charge;
  int   trk_charge;
  bool  threeChargeAgree_branch;
  float mva;
  float ecalIso;
  float hcalIso;
  float ecalPFClusterIso;
  float hcalPFClusterIso;
  int ckf_laywithmeas       ;
  float sigmaIPhiIPhi_full5x5 ;
  float e1x5_full5x5          ;
  float e5x5_full5x5          ;
  float r9_full5x5            ;
  float etaSCwidth            ;
  float phiSCwidth            ;
  float eSCRaw                ;
  float eSCPresh              ;
  float ckf_chi2              ;
  int ckf_ndof              ;
  float chi2                  ;
  int ndof                  ;
  float fbrem                 ;
  float eOverPOut             ;
  float dEtaOut               ;
  float dPhiOut               ;


  //---mus---//
  int   pid_PFMuon;
  float gfit_chi2;
  float gfit_ndof;
  int   gfit_validSTAHits;
  int   numberOfMatchedStations;
  int   validPixelHits;
  int   nlayers;
  float chi2LocalPosition;
  float trkKink;
  int   validHits;
  int   lostHits;
  int   exp_outerlayers;
  float segmCompatibility;

  //---single mu trigger---//
  // for trigger branches the following conventions hold:
  // 0,1,N mean respectively not passes, passed unprescaled, passed with prescale N 
  // the sign tells if the object matched one of the trigger legs (positive match, negative no match)

  //---single mu trigger---//
  int HLT_Mu8_TrkIsoVVL;
  int HLT_Mu17_TrkIsoVVL;
  int HLT_Mu24_TrkIsoVVL;
  int HLT_Mu34_TrkIsoVVL;
  int HLT_Mu8;
  int HLT_Mu17;
  int HLT_Mu24;
  int HLT_Mu34;
  int HLT_Mu10_CentralPFJet30_BTagCSV0p5PF;
  int HLT_Mu10_CentralPFJet30_BTagCSV0p54PF;
  int HLT_IsoMu20;
  int HLT_IsoTkMu20;
  int HLT_IsoMu24_eta2p1;
  int HLT_IsoTkMu24_eta2p1;
  int HLT_IsoMu27;
  int HLT_IsoTkMu27;
  int HLT_Mu45_eta2p1;
  int HLT_Mu50;
  
  //---single el trigger---//
  int HLT_Ele8_CaloIdM_TrackIdM_PFJet30;
  int HLT_Ele12_CaloIdM_TrackIdM_PFJet30;
  int HLT_Ele18_CaloIdM_TrackIdM_PFJet30;
  int HLT_Ele23_CaloIdM_TrackIdM_PFJet30;
  int HLT_Ele33_CaloIdM_TrackIdM_PFJet30;
  int HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;
  int HLT_Ele18_CaloIdL_TrackIdL_IsoVL_PFJet30;
  int HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
  int HLT_Ele33_CaloIdL_TrackIdL_IsoVL_PFJet30;
  int HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p5PF;
  int HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p54PF;
  int HLT_Ele27_eta2p1_WP75_Gsf;//used in MC xxx
  int HLT_Ele27_WP85_Gsf;//used in MC
  int HLT_Ele27_eta2p1_WPLoose_Gsf;//used in data
  int HLT_Ele27_eta2p1_WPTight_Gsf;//used in data
  int HLT_Ele32_eta2p1_WP75_Gsf;//used in MC
  int HLT_Ele32_eta2p1_WPLoose_Gsf;//used in data
  int HLT_Ele32_eta2p1_WPTight_Gsf;//used in data
  int HLT_Ele22_eta2p1_WPLoose_Gsf;//used in data
  int HLT_Ele22_eta2p1_WPTight_Gsf;//used in data
  int HLT_Ele23_WPLoose_Gsf;//used in data
  int HLT_Ele23_CaloIdL_TrackIdL_IsoVL;
  int HLT_Ele12_CaloIdL_TrackIdL_IsoVL;

  //--- mu-el trigger---//
  int HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300;
  int HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
  int HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;

  //--- double mu trigger---//
  int HLT_DoubleMu8_Mass8_PFHT300;
  int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
  int HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
  int HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;//xxx
  int HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;//xxx

  //--- double el trigger---//
  int HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300;
  int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
  int HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
    
};


#endif
