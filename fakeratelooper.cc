

#include "fakeratelooper.h" 

//Switches
bool verbose = 0;
unsigned int evt_cut = 74994186;

//Main functions
void babyMaker::MakeBabyNtuple(const char* output_name){
  cout<<__LINE__<<endl;
  //Create Baby
//  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");cout<<__LINE__<<endl;
//  rootdir->cd();cout<<__LINE__<<endl;
  BabyFile = new TFile(Form("%s/%s", path.c_str(), output_name), "RECREATE");cout<<__LINE__<<endl;
  BabyFile->cd();cout<<__LINE__<<endl;
  BabyTree = new TTree("t", "Lepton Baby Ntuple");cout<<__LINE__<<endl;
cout<<__LINE__<<endl;
  //Define Branches
  BabyTree->Branch("evt_pfmet", &evt_pfmet);
  BabyTree->Branch("evt_pfmetPhi", &evt_pfmetPhi);
  BabyTree->Branch("evt_trackmet", &evt_trackmet);
  BabyTree->Branch("evt_trackmetPhi", &evt_trackmetPhi);
  BabyTree->Branch("evt_pfsumet", &evt_pfsumet);
  BabyTree->Branch("evt_pfmetSig", &evt_pfmetSig);
  BabyTree->Branch("evt_event", &evt_event);
  BabyTree->Branch("evt_lumiBlock", &evt_lumiBlock);
  BabyTree->Branch("evt_run", &evt_run);
  BabyTree->Branch("filt_csc", &filt_csc);
  BabyTree->Branch("filt_hbhe", &filt_hbhe);
  BabyTree->Branch("filt_hcallaser", &filt_hcallaser);
  BabyTree->Branch("filt_ecaltp", &filt_ecaltp);
  BabyTree->Branch("filt_trkfail", &filt_trkfail);
  BabyTree->Branch("filt_eebadsc", &filt_eebadsc);
  BabyTree->Branch("evt_isRealData", &evt_isRealData);
  BabyTree->Branch("scale1fb", &scale1fb);
  BabyTree->Branch("evt_xsec_incl", &evt_xsec_incl);
  BabyTree->Branch("evt_kfactor", &evt_kfactor);
  BabyTree->Branch("gen_met", &gen_met);
  BabyTree->Branch("gen_metPhi", &gen_metPhi);
  BabyTree->Branch("njets", &njets);
  BabyTree->Branch("ht", &ht);
  BabyTree->Branch("jets", &jets);
  BabyTree->Branch("jets_disc", &jets_disc);
  BabyTree->Branch("sample", &sample);
  BabyTree->Branch("nFOs_SS", &nFOs_SS);
  BabyTree->Branch("nvtx", &nvtx);
cout<<__LINE__<<endl;
  //--------------------MINE----------------------------
  //---both--//
  BabyTree->Branch("p4", &p4);
  BabyTree->Branch("tag_p4", &tag_p4);
  BabyTree->Branch("dilep_p4", &dilep_p4);
  BabyTree->Branch("mc_p4", &mc_p4);
  BabyTree->Branch("mc_motherp4", &mc_motherp4);
  BabyTree->Branch("id", &id);
  BabyTree->Branch("idx", &idx);
  BabyTree->Branch("dxyPV", &dxyPV);
  BabyTree->Branch("dZ", &dZ);
  BabyTree->Branch("dxyPV_err", &dxyPV_err);
  BabyTree->Branch("motherID", &motherID);
  BabyTree->Branch("mc_id", &mc_id);
  BabyTree->Branch("RelIso03", &RelIso03);
  BabyTree->Branch("RelIso03EA", &RelIso03EA);
  BabyTree->Branch("RelIso03DB", &RelIso03DB);
  BabyTree->Branch("passes_SS_tight_v3", &passes_SS_tight_v3);
  BabyTree->Branch("passes_SS_tight_noiso_v3", &passes_SS_tight_noiso_v3);
  BabyTree->Branch("passes_SS_fo_v3", &passes_SS_fo_v3);
  BabyTree->Branch("passes_SS_fo_noiso_v3", &passes_SS_fo_noiso_v3);
  BabyTree->Branch("passes_SS_fo_looseMVA_v3", &passes_SS_fo_looseMVA_v3);
  BabyTree->Branch("passes_SS_fo_looseMVA_noiso_v3", &passes_SS_fo_looseMVA_noiso_v3);
  BabyTree->Branch("ip3d", &ip3d);
  BabyTree->Branch("ip3derr", &ip3derr);
  BabyTree->Branch("type", &type);
  BabyTree->Branch("mt", &mt);
  BabyTree->Branch("ptrelv0", &ptrelv0);
  BabyTree->Branch("ptrelv1", &ptrelv1);
  BabyTree->Branch("miniiso", &miniiso);
  BabyTree->Branch("jet_close_lep", &jet_close_lep);
  BabyTree->Branch("ptratio", &ptratio);
  BabyTree->Branch("tag_charge", &tag_charge);
  BabyTree->Branch("dilep_mass", &dilep_mass);
cout<<__LINE__<<endl;
  //---els---//
  BabyTree->Branch("sigmaIEtaIEta_full5x5", &sigmaIEtaIEta_full5x5);
  BabyTree->Branch("etaSC"                , &etaSC);
  BabyTree->Branch("dEtaIn"               , &dEtaIn);
  BabyTree->Branch("dPhiIn"               , &dPhiIn);
  BabyTree->Branch("hOverE"               , &hOverE);
  BabyTree->Branch("ecalEnergy"           , &ecalEnergy);
  BabyTree->Branch("eOverPIn"             , &eOverPIn);
  BabyTree->Branch("conv_vtx_flag"        , &conv_vtx_flag);
  BabyTree->Branch("exp_innerlayers"      , &exp_innerlayers);
  BabyTree->Branch("charge"               , &charge);
  BabyTree->Branch("sccharge"             , &sccharge);
  BabyTree->Branch("ckf_charge"           , &ckf_charge);
  BabyTree->Branch("threeChargeAgree"     , &threeChargeAgree_branch);
cout<<__LINE__<<endl;
  //---mus---//
  BabyTree->Branch("pid_PFMuon"             , &pid_PFMuon);
  BabyTree->Branch("gfit_chi2"              , &gfit_chi2);
  BabyTree->Branch("gfit_ndof"              , &gfit_ndof);
  BabyTree->Branch("gfit_validSTAHits"      , &gfit_validSTAHits);
  BabyTree->Branch("numberOfMatchedStations", &numberOfMatchedStations);
  BabyTree->Branch("validPixelHits"         , &validPixelHits);
  BabyTree->Branch("nlayers"                , &nlayers);cout<<__LINE__<<endl;
}

void babyMaker::InitBabyNtuple(){

  //Gen variables
  evt_pfmet = -1;
  evt_pfmetPhi = -99.;
  evt_trackmet = -1;
  evt_trackmetPhi = -99;
  evt_pfsumet = -1;
  evt_pfmetSig = -1;
  evt_event = -1;
  evt_lumiBlock = -1;
  evt_run = -1;
  filt_csc = 0;
  filt_hbhe = 0;
  filt_hcallaser = 0;
  filt_ecaltp = 0;
  filt_trkfail = 0;
  filt_eebadsc = 0;
  evt_isRealData = 0;
  scale1fb = -1;
  evt_xsec_incl = -1;
  evt_kfactor = -1;
  gen_met = -1;
  gen_metPhi = -99;
  njets = -1;
  ht = -1;
  jets.clear();
  jets_disc.clear();
  sample = "";
  nFOs_SS = -1;
  nvtx = -1;

  //--------MINE------------
  //---both--//
  p4 = LorentzVector(0,0,0,0); 
  tag_p4 = LorentzVector(0,0,0,0); 
  dilep_p4 = LorentzVector(0,0,0,0);
  mc_p4 = LorentzVector(0,0,0,0);
  mc_motherp4 = LorentzVector(0,0,0,0);
  id = -1; 
  idx = -1;
  dxyPV = -1;
  dZ = -1;
  dxyPV_err = -1;
  motherID = -1;
  mc_id = -1;
  RelIso03 = -1;
  RelIso03EA = -1;
  RelIso03DB = -1;
  passes_SS_tight_v3 = 0;
  passes_SS_tight_noiso_v3 = 0;
  passes_SS_fo_v3 = 0;
  passes_SS_fo_noiso_v3 = 0;
  passes_SS_fo_looseMVA_v3 = 0;
  passes_SS_fo_looseMVA_noiso_v3 = 0;
  ip3d = -1;
  ip3derr = -1;
  type = -1;
  mt = -1;
  ptrelv0 = -1;
  ptrelv1 = -1;
  miniiso = -1;
  jet_close_lep = LorentzVector(0,0,0,0);
  ptratio = -1;
  tag_charge = 0;
  dilep_mass = -1;
  isRandom = false;

  //---els---//
  sigmaIEtaIEta_full5x5 = -1;//below
  etaSC = -1;
  dEtaIn = -1;
  dPhiIn = -99;
  hOverE = -1;
  ecalEnergy = -1;
  eOverPIn = -1;
  conv_vtx_flag = 0;
  exp_innerlayers = -1;
  charge = -1;
  sccharge = -1;
  ckf_charge = -1;
  trk_charge = -1;
  threeChargeAgree_branch = 0;

  //---mus---//
  pid_PFMuon = -1;
  gfit_chi2 = -1;
  gfit_ndof = -1;
  gfit_validSTAHits = -1;
  numberOfMatchedStations = -1;
  validPixelHits = -1;
  nlayers = -1;
  //------------------------
} 

void babyMaker::InitLeptonBranches(){

  //---both---//
  p4 = LorentzVector(0,0,0,0); 
  tag_p4 = LorentzVector(0,0,0,0); 
  dilep_p4 = LorentzVector(0,0,0,0); 
  mc_p4 = LorentzVector(0,0,0,0);
  mc_motherp4 = LorentzVector(0,0,0,0);
  id = -1; 
  idx = -1;
  dxyPV = -1;
  dZ = -1;
  dxyPV_err = -1;
  motherID = -1;
  mc_id = -1;
  RelIso03 = -1;
  RelIso03EA = -1;
  RelIso03DB = -1;
  passes_SS_tight_v3 = 0;
  passes_SS_tight_noiso_v3 = 0;
  passes_SS_fo_v3 = 0;
  passes_SS_fo_noiso_v3 = 0;
  passes_SS_fo_looseMVA_v3 = 0;
  passes_SS_fo_looseMVA_noiso_v3 = 0;
  type = -1;
  ip3d = -1;
  ip3derr = -1;
  mt = -1;
  ptrelv0 = -1;
  ptrelv1 = -1;
  miniiso = -1;
  jet_close_lep = LorentzVector(0,0,0,0);
  ptratio = -1;
  tag_charge = 0.;
  dilep_mass = -1.;
  isRandom = false;

  //---mus---//
  pid_PFMuon = -1;
  gfit_chi2 = -1;
  gfit_ndof = -1;
  gfit_validSTAHits = -1;
  numberOfMatchedStations = -1;
  validPixelHits = -1;
  nlayers = -1;

  //---els---//
  sigmaIEtaIEta_full5x5 = -1;
  etaSC = -1;
  dEtaIn = -1;
  dPhiIn = -99;
  hOverE = -1;
  ecalEnergy = -1;
  eOverPIn = -1;
  conv_vtx_flag = 0;
  exp_innerlayers = -1;
  charge = -1;
  sccharge = -1;
  ckf_charge = -1;
  trk_charge = -1;
  threeChargeAgree_branch = 0;
  //------------------------
}


double calculateMt(const LorentzVector p4, double met, double met_phi){  //<--MT, MET, MET_PHI ARE ALL FLOATS!!!
  float phi1 = p4.Phi();
  float phi2 = met_phi;
  float Et1  = p4.Et();
  float Et2  = met;
  return sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
}

// int lepMotherID(Lep lep){
//   if (tas::evt_isRealData()) return 1;
//   else if (isFromZ(lep.pdgId(),lep.idx()) || isFromW(lep.pdgId(),lep.idx())){
//     if (sgn(lep.pdgId()) == sgn(lep.mc_id())) return 1;
//     else return 2;
//   }
//   else if (isFromB(lep.pdgId(),lep.idx())) return -1;
//   else if (isFromC(lep.pdgId(),lep.idx())) return -2;
//   return 0;
// }

int sign(int num){
  if(num > 0) return 1;
  else if(num < 0) return -1;
  return 0;
}

int lepMotherID(int id, int mc_id, int idx){
  if (tas::evt_isRealData()) return 1;
  else if (isFromZ(id, idx) || isFromW(id, idx)){
    if (sign(id) == sign(mc_id)) return 1;
    else return 2;
  }
  else if (isFromB(id, idx)) return -1;
  else if (isFromC(id, idx)) return -2;
  return 0;
}

float leptonD0(const int id, const int idx){
  if (abs(id)==13) return tas::mus_dxyPV().at(idx); 
  else if (abs(id)==11) return tas::els_dxyPV().at(idx);   
  return -999999.0;
}

float leptonD0err(const int id, const int idx){
  if (abs(id)==13) return tas::mus_d0Err().at(idx); 
  else if (abs(id)==11) return tas::els_d0Err().at(idx);   
  return -999999.0;
}

float leptonDZ(const int id, const int idx){
  if (abs(id) == 11) return tas::els_dzPV().at(idx);
  if (abs(id) == 13) return tas::mus_dzPV().at(idx);
  return -999999.0;
}

//Main function
int babyMaker::looper(TChain* chain, char* output_name, int nEvents){

  //Print warning!
  cout << "Careful!! Path is " << path << endl;

  createAndInitMVA("CORE");cout<<__LINE__<<endl;
  createAndInitMVA("CORE");cout<<__LINE__<<endl;

  //Make Baby Ntuple  
  MakeBabyNtuple( Form("%s.root", output_name) );cout<<__LINE__<<endl;
  
  //Initialize Baby Ntuple
  InitBabyNtuple();cout<<__LINE__<<endl;

  //Set up loop over chain
  unsigned int nEventsDone = 0;
  unsigned int nEventsToDo = chain->GetEntries();
  if( nEvents >= 0 ) nEventsToDo = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
 cout<<__LINE__<<endl;
  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) { 
cout<<__LINE__<<endl;
    // Get File Content
    if(nEventsDone >= nEventsToDo) continue;
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("Events");
    cms3.Init(tree);
  cout<<__LINE__<<endl;
    // Loop over Events in current file
    unsigned int nEventsTree = tree->GetEntriesFast();
    for(unsigned int evt = 0; evt < nEventsTree; evt++){
	  
	  //cout<<"\nEvent loop again"<<endl;	  

      // Get Event Content
      if(nEventsDone >= nEventsToDo) continue;   
      cms3.GetEntry(evt);
      nEventsDone++;
cout<<__LINE__<<endl;
      //Initialize variables
      InitBabyNtuple();
     cout<<__LINE__<<endl;
      // Progress
      CMS3::progress(nEventsDone, nEventsToDo);
cout<<__LINE__<<endl;
      //Debug mode
      if (verbose && tas::evt_event() != evt_cut) continue;
      if (verbose) cout << "file name is " << file->GetName() << endl;
cout<<__LINE__<<endl;
      // //Preliminary stuff
	  if (tas::mus_dxyPV().size() != tas::mus_dzPV().size()) continue;  

	  metStruct myMetStruct =  trackerMET(0.2);

      //Fill Easy Variables
      evt_pfmet      = cms3.evt_pfmet();
      evt_pfmetPhi   = cms3.evt_pfmetPhi();
	  evt_trackmet   = myMetStruct.met;
	  evt_trackmetPhi= myMetStruct.metphi;
      evt_pfsumet    = cms3.evt_pfsumet();
      evt_pfmetSig   = cms3.evt_pfmetSig();
      evt_event      = tas::evt_event();
      evt_lumiBlock  = tas::evt_lumiBlock();
      evt_run        = tas::evt_run();
      evt_isRealData = tas::evt_isRealData();
      evt_xsec_incl  = tas::evt_xsec_incl();
      evt_kfactor    = tas::evt_kfactor();
      gen_met        = tas::gen_met();
      gen_metPhi     = tas::gen_metPhi();
      sample         = Form("%s", file->GetName());

      // Vertex selection:
      int nVert = 0;
      for(unsigned int ivtx=0; ivtx < tas::evt_nvtxs(); ivtx++){
	
	if(tas::vtxs_isFake().at(ivtx)) continue;
	if(tas::vtxs_ndof().at(ivtx) <= 4) continue;
	if(fabs(tas::vtxs_position().at(ivtx).z()) > 24) continue;
	if(tas::vtxs_position().at(ivtx).Rho() > 2) continue;
	
	nVert++;
	
      }
      nvtx = nVert;
      
      
      //Fill data vs. mc variables
      filt_hbhe = evt_isRealData ? (tas::evt_hbheFilter() &&
									tas::hcalnoise_isolatedNoiseSumE() < 50.0 &&
									tas::hcalnoise_isolatedNoiseSumEt() < 25.0 &&
									tas::hcalnoise_numIsolatedNoiseChannels() < 10) : 1;
      filt_csc       = evt_isRealData ? tas::evt_cscTightHaloId()   : 1;
      filt_hcallaser = evt_isRealData ? tas::filt_hcalLaser()       : 1;
      filt_ecaltp    = evt_isRealData ? tas::filt_ecalTP()          : 1;
      filt_trkfail   = evt_isRealData ? tas::filt_trackingFailure() : 1;
      filt_eebadsc   = evt_isRealData ? tas::filt_eeBadSc()         : 1;
      scale1fb       = evt_isRealData ? 1                           : tas::evt_scale1fb();
	  
	  //-------------------------------------------------------------------------------------------------------------
	  //Determine and save jet variables
      ht = 0;
      for (unsigned int i = 0; i < tas::pfjets_p4().size(); i++)
	  	{
	  	  LorentzVector jet = tas::pfjets_p4().at(i);

	  	  //Require loose jet ID
	  	  if (!isLoosePFJet(i)) continue;

	  	  //Kinematic jet cuts
	  	  if (jet.pt() < 25) continue;   //<------WHAT CUTS DO WE WANT???
	  	  //if (fabs(jet.eta()) > 2.4) continue; //want jets of all eta's for fake rate

	  	  //Verbose
	  	  if (verbose) cout << "Possible jet with pT: " << jet.pt() << endl;
            
	  	  // //Jet cleaning -- electrons
	  	  // bool jetIsLep = false;
	  	  // for (unsigned int eidx = 0; eidx < tas::els_p4().size(); eidx++){
	  	  // 	LorentzVector electron = tas::els_p4().at(eidx);
	  	  // 	if (electron.pt() < 7) continue;
	  	  // 	//if (!isVetoLepton(11,eidx,Standard)) continue;                      //Relying on SSSelections here!
	  	  // 	if ( electronID(eidx, SS_veto_noiso_v3)==0 ) continue;                //Other analyses can add their veto w/ &&
	  	  // 	if (ROOT::Math::VectorUtil::DeltaR(jet, electron) > 0.4) continue;
	  	  // 	jetIsLep = true;
	  	  // }
	  	  // if (jetIsLep == true) continue;

	  	  // //Jet cleaning -- muons
	  	  // for (unsigned int muidx = 0; muidx < tas::mus_p4().size(); muidx++){
	  	  // 	LorentzVector muon = tas::mus_p4().at(muidx);
	  	  // 	if (muon.pt() < 5) continue;
	  	  // 	//if (!isVetoLepton(13,muidx,Standard)) continue;                       //Relying on SSSelections here!
	  	  // 	if ( muonID(muidx, SS_veto_noiso_v3)==0 ) continue;                     //Other analyses can add their veto w/ &&
	  	  // 	if (ROOT::Math::VectorUtil::DeltaR(jet, muon) > 0.4) continue;
	  	  // 	jetIsLep = true;
	  	  // }
	  	  // if (jetIsLep == true) continue;

	  	  //Save jets that make it this far
	  	  jets.push_back(jet);
	  	  //ht += jet.pt();  //want to only use jets w/ pt>40, not 25
	  	  if(jet.pt() > 40.) ht += jet.pt();  //not implemented for V00-00-05
		  float disc = tas::pfjets_combinedInclusiveSecondaryVertexV2BJetTag().at(i);  //BRANCH DOESNT EXIST in old samples.
		  jets_disc.push_back(disc);
	
		}
      njets = jets.size();

      //Verbose for jets
      if (verbose){
        cout << "njets: " << njets << endl;
        for (unsigned int i = 0; i < jets.size(); i++) cout << i << " " << jets[i].pt() << " " << jets[i].eta() << endl;
      } 
	  //-----------------------------------------------------------------------------------------------------------------------

	  int count_SS = 0;

	  for(size_t j = 0; j < tas::mus_p4().size(); j++)
	  	{
	  	  //if(isDenominatorLepton(13,j,Standard))     //relying on SSSelections
		  if( muonID(j, SS_fo_v3) && tas::mus_p4().at(j).pt()>10.)                    //Is this the right one?
	  		{count_SS++;}
	  	}
	  for(size_t j = 0; j < tas::els_p4().size(); j++)
	  	{
	  	  //if(isDenominatorLepton(11,j,Standard))     //relying on SSSelections
		  if( electronID(j, SS_fo_v3) && tas::els_p4().at(j).pt()>10.)                //Is this the right one?
	  		{count_SS++;}
	  	}
	  nFOs_SS = count_SS;

	  bool used = false;
	  TRandom r;
	  float rndm = r.Rndm();
	  //Muon Loop
	  //cout<<"\nBegin Muon looping"<<endl;	  
	  for(unsigned int i=0; i<tas::mus_p4().size(); i++)  //What RECO and GEN variables are needed?
		{	

		  // Require tag
		  bool foundTag = false;
		  for(unsigned int j=0; j<tas::mus_p4().size(); j++) {
		    if (i==j) continue;
		    if ( tas::mus_p4().at(j).pt()           <  20.0 ) continue;
		    if ( fabs(tas::mus_p4().at(j).eta())    >  2.4  ) continue;
		    if ( muonID(j,SS_tight_v3) ) { // OK, we have a tag
		      tag_p4 = tas::mus_p4().at(j);
		      tag_charge = tas::mus_charge().at(j);
		      // Randomize if needed
		      if (used == false && ((rndm < 0.5 && tag_charge < 0) || (rndm >= 0.5 && tag_charge > 0))) {
			isRandom = true;
			used = true;
		      }
		      else isRandom = false;
		      foundTag = true; // The probe we are about to save has a corresponding tag
		    }
		  } // End of tag selection
		  
		  //if (!isVetoLeptonNoIso(13,i) && foundTag==false) continue;           //Relying on SSSelections here!
		  if( (muonID(i, SS_veto_noiso_v3)==0 && foundTag==false) || tas::mus_p4().at(i).pt()<=10. ) continue;    //other analyses can add vetoes w/ &&

		  p4 = tas::mus_p4().at(i); 
		  if (foundTag) {
		    dilep_p4 = p4 + tag_p4;
		    dilep_mass = dilep_p4.M();
		  }
		  //		  mc_p4 = tas::mus_mc_p4().at(i);
		  id = -13.0*tas::mus_charge().at(i);
		  idx = i;  
		  //		  mc_id = tas::mus_mc_id().at(i);
		  dxyPV = leptonD0(id, i);
		  dxyPV_err = leptonD0err(id, i);
		  dZ = leptonDZ(id, i);
		  RelIso03 = muRelIso03(i,SS);
		  RelIso03EA = muRelIso03EA(i);
		  RelIso03DB = muRelIso03DB(i);
		  pid_PFMuon = tas::mus_pid_PFMuon().at(i);
		  gfit_chi2 = tas::mus_gfit_chi2().at(i);
		  gfit_ndof = tas::mus_gfit_ndof().at(i);
		  gfit_validSTAHits = tas::mus_gfit_validSTAHits().at(i);
		  numberOfMatchedStations = tas::mus_numberOfMatchedStations().at(i);
		  validPixelHits = tas::mus_validPixelHits().at(i);
		  nlayers = tas::mus_nlayers().at(i);
		  ip3d = tas::mus_ip3d().at(i);
		  ip3derr = tas::mus_ip3derr().at(i);
		  type = tas::mus_type().at(i);
		  mt = calculateMt(p4, evt_pfmet, evt_pfmetPhi); 

		  ///////////////////////////////////////////////////////////////////////////////////////////////////////
		  ///////////////////////////////////// Tight and Loose Bools////////////////////////////////////////////
		  ///////////////////////////////////////////////////////////////////////////////////////////////////////

		  ////////////
		  ///  SS  ///
		  ////////////	
		  if(muonID(i, SS_tight_v3))              passes_SS_tight_v3 = true;
		  if(muonID(i, SS_tight_noiso_v3))        passes_SS_tight_noiso_v3 = true;
		  if(muonID(i, SS_fo_v3))                 passes_SS_fo_v3 = true;
		  if(muonID(i, SS_fo_noiso_v3))           passes_SS_fo_noiso_v3 = true;
		  //if(muonID(i, SS_fo_looseMVA_v3))        passes_SS_fo_looseMVA_v3 = true;        //Doesn't make sense for muons
		  //if(muonID(i, SS_fo_looseMVA_noiso_v3))  passes_SS_fo_looseMVA_noiso_v3 = true;  //Doesn't make sense for muons

		  ////////////
		  ///  OS  ///
		  ////////////

		  ///////////////////////////////////////////////////////////////////////////////////////////////////////
		  //////////////////////////////////////////////End Bools////////////////////////////////////////////////
		  ///////////////////////////////////////////////////////////////////////////////////////////////////////
		  
		  ptrelv0 = getPtRel(id, idx, false);
		  ptrelv1 = getPtRel(id, idx, true);
		  miniiso = muMiniRelIso(idx, 0.1, true);
		  jet_close_lep = closestJet(p4,0.4,2.4);
		  ptratio = ( jet_close_lep.pt()>0. ? p4.pt()/jet_close_lep.pt() : 1. ); 
		  
		  //Lep mu_temp = Lep(id, i);
		  //motherID = lepMotherID(mu_temp);
		  //		  motherID = lepMotherID(id, mc_id, idx);
		  //		  mc_motherp4 = tas::mus_mc_motherp4().at(i);
		  
		  BabyTree->Fill(); 
		  InitLeptonBranches(); 

		  // cout<<"\nEnd Muon loop"<<endl;
		} //close muon loop
	  
      //Electron Loop
	  //cout<<"\nBegin electron looping"<<endl;	  
	  for(unsigned int i=0; i<tas::els_p4().size(); i++)
	  	{
		  
		  // Require tag
		  bool foundTag = false;
		  for(unsigned int j=0; j<tas::els_p4().size(); j++) {
		    if (i==j) continue;
		    if ( tas::els_p4().at(j).pt()  <  20.0 ) continue;
		    if ( fabs(tas::els_etaSC().at(j))    >  2.5  ) continue;
		    if ( electronID(j,SS_medium_v3) ) { // OK, we have a tag   
		      tag_p4 = tas::els_p4().at(j);
		      tag_charge = tas::els_charge().at(j);
		      // Randomize if needed
		      if (used == false && ((rndm < 0.5 && tag_charge < 0) || (rndm >= 0.5 && tag_charge > 0))) {
			isRandom = true;
			used = true;
		      }
		      else isRandom = false;
		      foundTag = true; // The probe we are about to save has a corresponding tag
		    }
		  } // End of tag selection
		  
		  //if (!isVetoLeptonNoIso(11,i) && !foundTag) continue;          //Relying on SSSelections here!
		  if( (electronID(i, SS_veto_noiso_v3)==0 && !foundTag) || tas::els_p4().at(i).pt()<=10. ) continue;  //other analyses can add vetoes w/ &&   

		  p4 = tas::els_p4().at(i);    
		  if (foundTag) {
		    dilep_p4 = p4 + tag_p4;
		    dilep_mass = dilep_p4.M();
		  }
		  //		  mc_p4 = tas::els_mc_p4().at(i);  
		  id = -11.0*tas::els_charge().at(i); 
		  idx = i;
		  //		  mc_id = tas::els_mc_id().at(i);  
		  dxyPV = leptonD0(id, i);
		  dxyPV_err = leptonD0err(id, i);
		  dZ = leptonDZ(id, i);
		  RelIso03 = eleRelIso03(i,SS);
		  RelIso03EA = eleRelIso03EA(i);
		  RelIso03EA = eleRelIso03DB(i);
		  sigmaIEtaIEta_full5x5 = tas::els_sigmaIEtaIEta_full5x5().at(i);//new below
		  etaSC = tas::els_etaSC().at(i);
		  dEtaIn = tas::els_dEtaIn().at(i);
		  dPhiIn = tas::els_dPhiIn().at(i);
		  hOverE = tas::els_hOverE().at(i);
		  ip3d = tas::els_ip3d().at(i);
		  ip3derr = tas::els_ip3derr().at(i);
		  ecalEnergy = tas::els_ecalEnergy().at(i);
		  eOverPIn = tas::els_eOverPIn().at(i);
		  conv_vtx_flag = tas::els_conv_vtx_flag().at(i);
		  exp_innerlayers = tas::els_exp_innerlayers().at(i);
		  charge = tas::els_charge().at(i);    //check on this
		  sccharge = tas::els_sccharge().at(i);    //check on this
		  ckf_charge = tas::els_ckf_charge().at(i);    //check on this
		  trk_charge = tas::els_trk_charge().at(i);
		  threeChargeAgree_branch = threeChargeAgree(i);
		  type = tas::els_type().at(i);
		  mt = calculateMt(p4, evt_pfmet, evt_pfmetPhi); 

		  ///////////////////////////////////////////////////////////////////////////////////////////////////////
		  ///////////////////////////////////// Tight and Loose Bools////////////////////////////////////////////
		  ///////////////////////////////////////////////////////////////////////////////////////////////////////

		  ////////////
		  ///  SS  ///
		  ////////////
		  if(electronID(i, SS_medium_v3))             passes_SS_tight_v3 = true;
		  if(electronID(i, SS_medium_noiso_v3))       passes_SS_tight_noiso_v3 = true;
		  if(electronID(i, SS_fo_v3))                 passes_SS_fo_v3 = true;
		  if(electronID(i, SS_fo_noiso_v3))           passes_SS_fo_noiso_v3 = true;
		  if(electronID(i, SS_fo_looseMVA_v3))        passes_SS_fo_looseMVA_v3 = true;
		  if(electronID(i, SS_fo_looseMVA_noiso_v3))  passes_SS_fo_looseMVA_noiso_v3 = true;

		  ////////////
		  ///  OS  ///
		  ////////////

		  ///////////////////////////////////////////////////////////////////////////////////////////////////////
		  //////////////////////////////////////////////End Bools////////////////////////////////////////////////
		  ///////////////////////////////////////////////////////////////////////////////////////////////////////
		  
		  ptrelv0 = getPtRel(id, idx, false);
		  ptrelv1 = getPtRel(id, idx, true);
		  miniiso = elMiniRelIso(idx, 0.1, true);
		  jet_close_lep = closestJet(p4,0.4,2.4);
		  ptratio = ( jet_close_lep.pt()>0. ? p4.pt()/jet_close_lep.pt() : 1. ); 

		  //Lep el_temp = Lep(id, i);
		  //motherID = lepMotherID(el_temp);
		  //		  motherID = lepMotherID(id, mc_id, idx);
		  //		  mc_motherp4 = tas::els_mc_motherp4().at(i); 

		  BabyTree->Fill(); 
		  InitLeptonBranches();
	  
	  	  //cout<<"\nEnd electron loop"<<endl;
	  	} //close electron loop
	  	  
    }//close event loop
    
    file->Close();
    delete file;
	
	cout<<"\nFile done"<<endl;
  }//close file loop
  
  cout<<"\nWriting file"<<endl;

  BabyFile->cd();
  BabyTree->Write();
  BabyFile->Close();


  return 0;  

}

void babyMaker::SetOutputPath( std::string outputpath )
{
  path = outputpath;
}
