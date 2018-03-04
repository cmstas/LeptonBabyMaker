#include "fakeratelooper.h"
#include "CORE/Tools/goodrun.h"
#include "CORE/Tools/jetcorr/Utilities.icc"
#include "CORE/Tools/jetcorr/SimpleJetCorrectionUncertainty.h"
#include "CORE/Tools/jetcorr/JetCorrectionUncertainty.h"

//Switches
bool verbose = 0;
unsigned int evt_cut = 0;
bool addPFCandidates = false; // Default is false
bool checkIsPFTrueFalse = false; // Default is false (requires double loop on recocandidates and pfcandidates)
bool addAnnulus = false; // Default is false
bool recoLeptonsDownTo5GeV = false; // Default is false (meaning 10 GeV)
bool recoLeptonsDownTo20GeV = false; // Default is false (meaning 10 GeV)
bool onlySaveTagProbePairs = false; // Default is false
bool applyJson = true;

bool isDataFromFileName = false; // set automatically later on


//Main function
//___________________________________________________________________________________________________________________________________________
int babyMaker::looper(TChain* chain, char* output_name, int nEvents)
{
    //Print warning!
    cout << "Careful!! Path is " << path << endl;

    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // Make baby root file. This is our main output.
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    MakeBabyNtuple(Form("%s", output_name));
    InitBabyNtuple();

    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    // Set up all the tools needed for looping over CMS3/4.
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    //Add good run list
    set_goodrun_file("goodRunList/goldenJson_2016rereco_36p46ifb.txt");
    //Create and init MVA
    createAndInitMVA("./CORE", true, false, 80); // Moriond
    readMVA* v25nsMVAreader = new readMVA();
    v25nsMVAreader->InitMVA("CORE", true);
    //JEC files -- 50 ns MC
    std::vector<std::string> jetcorr_filenames_50ns_MC_pfL1;
    std::vector<std::string> jetcorr_filenames_50ns_MC_pfL1L2L3;
    std::vector<std::string> jetcorr_filenames_50ns_MC_pfL2L3;
    jetcorr_filenames_50ns_MC_pfL1.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_50ns_MC_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_50ns_MC_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_50ns_MC_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_50ns_MC_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_50ns_MC_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_50ns_MC_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_L2L3Residual_AK4PFchs.txt");
    std::string jetcorrunc_filename_50ns_MC = "CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_MC_Uncertainty_AK4PFchs.txt";
    //JEC files -- 50 ns DATA
    std::vector<std::string> jetcorr_filenames_50ns_DATA_pfL1;
    std::vector<std::string> jetcorr_filenames_50ns_DATA_pfL1L2L3;
    jetcorr_filenames_50ns_DATA_pfL1.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_DATA_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_50ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_DATA_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_50ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_DATA_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_50ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_DATA_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_50ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_DATA_L2L3Residual_AK4PFchs.txt");
    std::string jetcorrunc_filename_50ns_DATA = "CORE/Tools/jetcorr/data/run2_50ns/Summer15_50nsV4_DATA_Uncertainty_AK4PFchs.txt";
    //JEC files -- 25 ns MC
    std::vector<std::string> jetcorr_filenames_25ns_MC_pfL1;
    std::vector<std::string> jetcorr_filenames_25ns_MC_pfL1L2L3;
    std::vector<std::string> jetcorr_filenames_25ns_MC_pfL2L3;
    jetcorr_filenames_25ns_MC_pfL1.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_25ns_MC_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_25ns_MC_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_25ns_MC_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_25ns_MC_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_25ns_MC_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_25ns_MC_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_L2L3Residual_AK4PFchs.txt");
    std::string jetcorrunc_filename_25ns_MC = "CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt";
    //JEC files -- 25 ns DATA
    std::vector<std::string> jetcorr_filenames_25ns_DATA_pfL1;
    std::vector<std::string> jetcorr_filenames_25ns_DATA_pfL1L2L3;
    std::vector<std::string> jetcorr_filenames_25ns_DATA_pfL2L3;
    jetcorr_filenames_25ns_DATA_pfL1.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt");
    jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt");
    jetcorr_filenames_25ns_DATA_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt");
    jetcorr_filenames_25ns_DATA_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt");
    jetcorr_filenames_25ns_DATA_pfL2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt");
    std::string jetcorrunc_filename_25ns_DATA = "CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt";
    //Make JEC for each of these
    FactorizedJetCorrector *jet_corrector_50ns_MC_pfL1;
    FactorizedJetCorrector *jet_corrector_50ns_MC_pfL1L2L3;
    FactorizedJetCorrector *jet_corrector_50ns_MC_pfL2L3;
    FactorizedJetCorrector *jet_corrector_50ns_DATA_pfL1;
    FactorizedJetCorrector *jet_corrector_50ns_DATA_pfL1L2L3;
    FactorizedJetCorrector *jet_corrector_25ns_MC_pfL1;
    FactorizedJetCorrector *jet_corrector_25ns_MC_pfL1L2L3;
    FactorizedJetCorrector *jet_corrector_25ns_MC_pfL2L3;
    FactorizedJetCorrector *jet_corrector_25ns_DATA_pfL1;
    FactorizedJetCorrector *jet_corrector_25ns_DATA_pfL1L2L3;
    FactorizedJetCorrector *jet_corrector_25ns_DATA_pfL2L3;
    JetCorrectionUncertainty *jetUnc = 0;
    //Fill the JEC
    jet_corrector_50ns_MC_pfL1 = makeJetCorrector(jetcorr_filenames_50ns_MC_pfL1);
    jet_corrector_50ns_MC_pfL1L2L3 = makeJetCorrector(jetcorr_filenames_50ns_MC_pfL1L2L3);
    jet_corrector_50ns_MC_pfL2L3 = makeJetCorrector(jetcorr_filenames_50ns_MC_pfL2L3);
    jet_corrector_50ns_DATA_pfL1 = makeJetCorrector(jetcorr_filenames_50ns_DATA_pfL1);
    jet_corrector_50ns_DATA_pfL1L2L3 = makeJetCorrector(jetcorr_filenames_50ns_DATA_pfL1L2L3);
    jet_corrector_25ns_MC_pfL1 = makeJetCorrector(jetcorr_filenames_25ns_MC_pfL1);
    jet_corrector_25ns_MC_pfL1L2L3 = makeJetCorrector(jetcorr_filenames_25ns_MC_pfL1L2L3);
    jet_corrector_25ns_MC_pfL2L3 = makeJetCorrector(jetcorr_filenames_25ns_MC_pfL2L3);
    jet_corrector_25ns_DATA_pfL1 = makeJetCorrector(jetcorr_filenames_25ns_DATA_pfL1);
    jet_corrector_25ns_DATA_pfL1L2L3 = makeJetCorrector(jetcorr_filenames_25ns_DATA_pfL1L2L3);
    jet_corrector_25ns_DATA_pfL2L3 = makeJetCorrector(jetcorr_filenames_25ns_DATA_pfL2L3);
    //JECs
    FactorizedJetCorrector *jet_corrector_pfL1 = 0;
    FactorizedJetCorrector *jet_corrector_pfL1MC = 0;
    FactorizedJetCorrector *jet_corrector_pfL1L2L3 = 0;
    FactorizedJetCorrector *jet_corrector_pfL2L3 = 0;
    //Record filenames
    std::vector <string> jetcorr_filenames_pfL1;
    std::vector <string> jetcorr_filenames_pfL1L2L3;
    std::vector <string> jetcorr_filenames_pfL2L3;

    // ~-~-~-~-~-~-~-
    // The main loop.
    // ~-~-~-~-~-~-~-
    bool doFileIntegrityCheckTestRun = false; // Write a single faux-event and exit and let RSR check the integrity. This is a "shallow" test of seeing whether ROOT files open nicely.
    unsigned int nEventsDone = 0;
    unsigned int nEventsToDo = chain->GetEntries();
    if (nEvents >= 0) { nEventsToDo = nEvents; }
    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;
    while ((currentFile = (TFile*)fileIter.Next()))
    {

        // ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
        // Based on the current file name, set various configurations.
        // ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
        bool isPromptReco = TString(currentFile->GetTitle()).Contains("PromptReco");
        isDataFromFileName = TString(currentFile->GetTitle()).Contains("Run2015") || TString(currentFile->GetTitle()).Contains("Run2016");
        if (isPromptReco) { isDataFromFileName = true; }
        else if (TString(currentFile->GetTitle()).Contains("DoubleMuon")) { isDataFromFileName = true; }
        else if (TString(currentFile->GetTitle()).Contains("DoubleEG")) { isDataFromFileName = true; }
        int bx = 25;
        if (TString(currentFile->GetTitle()).Contains("Run2015B") || TString(currentFile->GetTitle()).Contains("50ns")) { bx = 50; }
        // Retrieve JEC from files, if using
        //// files for RunIISpring15 MC
        if (bx == 50 && isDataFromFileName)
        {
            jet_corrector_pfL1 = jet_corrector_50ns_DATA_pfL1;
            jet_corrector_pfL1MC = jet_corrector_50ns_MC_pfL1;
            jet_corrector_pfL1L2L3 = jet_corrector_50ns_DATA_pfL1L2L3;
            jet_corrector_pfL2L3 = jet_corrector_25ns_MC_pfL2L3; //just a kludge, we will never use this
            jetcorr_filenames_pfL1 = jetcorr_filenames_50ns_DATA_pfL1;
            jetcorr_filenames_pfL1L2L3 = jetcorr_filenames_50ns_DATA_pfL1L2L3;
            jetUnc = new JetCorrectionUncertainty(jetcorrunc_filename_50ns_DATA);
        }
        else if (bx == 50 && !isDataFromFileName)
        {
            jet_corrector_pfL1 = jet_corrector_50ns_MC_pfL1;
            jet_corrector_pfL1MC = jet_corrector_50ns_MC_pfL1;
            jet_corrector_pfL2L3 = jet_corrector_50ns_MC_pfL2L3;
            jet_corrector_pfL1L2L3 = jet_corrector_50ns_MC_pfL1L2L3;
            jetcorr_filenames_pfL1 = jetcorr_filenames_50ns_MC_pfL1;
            jetcorr_filenames_pfL1L2L3 = jetcorr_filenames_50ns_MC_pfL1L2L3;
            jetUnc = new JetCorrectionUncertainty(jetcorrunc_filename_50ns_MC);
        }
        else if (bx == 25 && isDataFromFileName)
        {
            jet_corrector_pfL1 = jet_corrector_25ns_DATA_pfL1;
            jet_corrector_pfL1MC = jet_corrector_25ns_MC_pfL1;
            jet_corrector_pfL1L2L3 = jet_corrector_25ns_DATA_pfL1L2L3;
            jet_corrector_pfL2L3 = jet_corrector_25ns_DATA_pfL2L3;
            jetcorr_filenames_pfL1 = jetcorr_filenames_25ns_DATA_pfL1;
            jetcorr_filenames_pfL1L2L3 = jetcorr_filenames_25ns_DATA_pfL1L2L3;
            jetUnc = new JetCorrectionUncertainty(jetcorrunc_filename_25ns_DATA);
        }
        else if (bx == 25 && !isDataFromFileName)
        {
            jet_corrector_pfL1 = jet_corrector_25ns_MC_pfL1;
            jet_corrector_pfL1MC = jet_corrector_25ns_MC_pfL1;
            jet_corrector_pfL1L2L3 = jet_corrector_25ns_MC_pfL1L2L3;
            jet_corrector_pfL2L3 = jet_corrector_25ns_MC_pfL2L3;
            jetcorr_filenames_pfL1 = jetcorr_filenames_25ns_MC_pfL1;
            jetcorr_filenames_pfL1L2L3 = jetcorr_filenames_25ns_MC_pfL1L2L3;
            jetUnc = new JetCorrectionUncertainty(jetcorrunc_filename_25ns_MC);
        }

        // Check whether to start looping over this 'currentFile'.
        if (nEventsDone >= nEventsToDo) { continue; }

        // Get file content and initialize to CMS3 class.
        TFile *file = TFile::Open(currentFile->GetTitle());
        TTree *tree = (TTree*) file->Get("Events");
        cms3.Init(tree);

        std::cout << file->GetTitle() << " " << file->IsZombie() << std::endl;

        // Loop over Events in current file.
        unsigned int nEventsTree = tree->GetEntriesFast();
        for (unsigned int evt = 0; evt < nEventsTree; evt++)
        {
            // Check whether to stop looping over this TTree in 'currentFile'
            if (nEventsDone >= nEventsToDo) { continue; }

            // Get event content into CMS3 class instancej.
            cms3.GetEntry(evt);

            if (tree->GetBranch(tree->GetAlias("evt_lumiBlock"))->GetEntry(evt) < 0)
            {
                std::cout << "Got an error reading an entry. " << std::endl;
                std::cout << "The corrupted filename is " << file->GetName() << std::endl;
                std::cout << "Please report to the relevant people for this corrupted file." << std::endl;
                std::cout << "Meanwhile, skipping this root file...." << std::endl;
                break;
            }

            // Increase counter.
            nEventsDone++;

            if (tas::evt_isRealData() && isPromptReco && tas::evt_run() <= 251562) { continue; }

            // If data, check good run list.
            if (applyJson && tas::evt_isRealData() && !goodrun(tas::evt_run(), tas::evt_lumiBlock())) { continue; }

            // Initialize output baby ntuple variables.
            InitBabyNtuple();

            // As soon as it gets to this point on the first event, if the following option is turned on, it will write an event to the ttree and exit the loop.
            // Then the rsr will check whether it passes the sweep. If not, it most likely means that the input CMS3/4 file is corrupted.
            // In that case, we need to re run CMS3.
            if (doFileIntegrityCheckTestRun)
            {
                BabyTree->Fill();
                break;
            }

            // Print progress.
            CMS3::progress(nEventsDone, nEventsToDo);

            // The following should never occur, if it does something is wrong about the CMS3/4 processing.
            if (tas::mus_dxyPV().size() != tas::mus_dzPV().size()) { continue; }

            // Calculate MET variables.
            metStruct trackMetStruct = trackerMET(0.2);
            pair<float, float> corrMETPair = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1L2L3);
            pair<float,float> corrMETPair_up = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1L2L3, jetUnc, true);
            pair<float,float> corrMETPair_dn = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1L2L3, jetUnc, false);

            // Fill easy Variables
            evt_pfmet = cms3.evt_pfmet();
            evt_pfmetPhi = cms3.evt_pfmetPhi();
            evt_trackmet = trackMetStruct.met;
            evt_trackmetPhi = trackMetStruct.metphi;
            evt_corrMET = corrMETPair.first;
            evt_corrMETPhi = corrMETPair.second;
            evt_corrMET_up    = corrMETPair_up.first;
            evt_corrMETPhi_up = corrMETPair_up.second;
            evt_corrMET_dn    = corrMETPair_dn.first;
            evt_corrMETPhi_dn = corrMETPair_dn.second;
            evt_pfsumet = cms3.evt_pfsumet();
            evt_pfmetSig = cms3.evt_pfmetSig();
            evt_event = tas::evt_event();
            evt_lumiBlock = tas::evt_lumiBlock();
            evt_run = tas::evt_run();
            evt_isRealData = tas::evt_isRealData();
            sample = Form("%s", file->GetName());

            // If not data, i.e. MC, save extra information.
            if (!evt_isRealData)
            {
                evt_xsec_incl = tas::evt_xsec_incl();
                evt_kfactor = tas::evt_kfactor();
                gen_met = tas::gen_met();
                gen_metPhi = tas::gen_metPhi();
            }

            // Count number of good vertices.
            nvtx = 0;
            for (unsigned int ivtx = 0; ivtx < tas::evt_nvtxs(); ivtx++)
            {
                if (!isGoodVertex(ivtx)) { continue; }
                nvtx++;
            }

            if (!evt_isRealData)
                if (tas::puInfo_trueNumInteractions().size() > 0)
                    pu_ntrue = tas::puInfo_trueNumInteractions().at(0);

            if (evt_isRealData)
                instantLumi = tas::evt_instantLumi();


            // PU density variables
            rho = tas::evt_fixgridfastjet_all_rho();
            rho_neut_centr = tas::evt_fixgridfastjet_centralneutral_rho();
            rho_calo = tas::evt_fixgridfastjet_allcalo_rho();
            rho_calo_centr = tas::evt_fixgridfastjet_centralcalo_rho();

            // Event filters.
            passes_met_filters = evt_isRealData ? passesMETfilter() : 1;
            filt_hbhe = evt_isRealData ? hbheNoiseFilter() : 1;
            filt_csc = evt_isRealData ? tas::evt_cscTightHaloId() : 1;
            filt_hcallaser = evt_isRealData ? tas::filt_hcalLaser() : 1;
            filt_ecaltp = evt_isRealData ? tas::filt_ecalTP() : 1;
            filt_trkfail = evt_isRealData ? tas::filt_trackingFailure() : 1;
            filt_eebadsc = evt_isRealData ? tas::filt_eeBadSc() : 1;

            // Weight of MC events scaled to 1 fb-1.
            scale1fb = evt_isRealData ? 1 : tas::evt_scale1fb();

            // Determine and save jet variables
            ht = 0;
            ht_SS = 0;
            // Loop over the pf jet collection
            for (unsigned int i = 0; i < tas::pfjets_p4().size(); i++)
            {
                // Get the raw p4 by undoing the JEC.
                LorentzVector raw_jet = tas::pfjets_p4().at(i) * tas::pfjets_undoJEC().at(i);

                // Require at least loose jet ID.
                if (!isLoosePFJet_50nsV1(i)) { continue; }

                // Recompute the JEC from the JEC tool configured at the beginning of the run.
                float jet_L1L2L3 = 1.;
                if (jetcorr_filenames_pfL1L2L3.size() > 0)
                {
                    //L1L2L3
                    jet_corrector_pfL1L2L3->setJetEta(raw_jet.eta());
                    jet_corrector_pfL1L2L3->setJetPt(raw_jet.pt());
                    jet_corrector_pfL1L2L3->setJetA(tas::pfjets_area().at(i));
                    jet_corrector_pfL1L2L3->setRho(rho);
                    jet_L1L2L3 = jet_corrector_pfL1L2L3->getCorrection();
                }

                // Compute the corrected jet p4.
                LorentzVector jet = raw_jet * jet_L1L2L3;

                // Kinematic jet cuts
                if (jet.pt() < 25) { continue; }

                // Save jets that make it this far.
                jets.push_back(jet);

                // Compute jet related variables.
                // HT is computed here.
                if (jet.pt() > 40) { ht += jet.pt(); }
                // HT in same-sign requires that the pf jets are cleaned against electrons and muons.
                if (jet.pt() > 40 && fabs(jet.eta()) < 2.4)
                {
                    bool isCleanJet = true;
                    // Loop over muons and kill the jet if overlaps with the jet at hand.
                    for (size_t j = 0; j < tas::mus_p4().size(); j++)
                    {
                        if (muonID(j, SS_fo_v5) && tas::mus_p4().at(j).pt() > 5. && (ROOT::Math::VectorUtil::DeltaR(jet, tas::mus_p4().at(j)) < 0.4))
                        {
                            isCleanJet = false;
                            if (verbose) { cout << "jet cleaned by muon p4: " << tas::mus_p4().at(j) << " pt=" << tas::mus_p4().at(j).pt() << endl; }
                        }
                    }
                    // Loop over electrons and kill the jet if overlaps with the jet at hand.
                    for (size_t j = 0; j < tas::els_p4().size(); j++)
                    {
                        if (electronID(j, SS_fo_looseMVA_v5) && tas::els_p4().at(j).pt() > 7. && (ROOT::Math::VectorUtil::DeltaR(jet, tas::els_p4().at(j)) < 0.4))
                        {
                            isCleanJet = false;
                            if (verbose) { cout << "jet cleaned by electron p4: " << tas::els_p4().at(j) << " pt=" << tas::els_p4().at(j).pt() << endl; }
                        }
                    }
                    if (isCleanJet) { ht_SS += jet.pt(); }
                }
                // Save b-tags.
                float disc = tas::pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag().at(i);
                jets_disc.push_back(disc);
                jets_area.push_back(tas::pfjets_area().at(i));
                jets_undoJEC.push_back(tas::pfjets_undoJEC().at(i));
                // Following jet uncertainty treatement taken from here:
                // https://github.com/cmstas/StopAnalysis/blob/8cdba10500dd12b7dc18300f321b83e09f038459/StopBabyMaker/JetTree.cc#L226-L231
                jetUnc->setJetEta(raw_jet.eta());
                jetUnc->setJetPt(jet.pt()); // Must use CORRECTED pt
                jets_unc.push_back(jetUnc->getUncertainty(true));
            }

            // Set the jet multiplicity.
            njets = jets.size();

            //Calculate number of fakeable objects for same sign analysis
            nFOs_SS = 0;
            for (size_t j = 0; j < tas::mus_p4().size(); j++)
            {
                if (muonID(j, SS_fo_v5) && tas::mus_p4().at(j).pt() > 10) { nFOs_SS++; }
            }

            for (size_t j = 0; j < tas::els_p4().size(); j++)
            {
                if (electronID(j, SS_fo_looseMVA_v5) && tas::els_p4().at(j).pt() > 10) { nFOs_SS++; }
            }

            // ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
            // These variables are persistent through the event, used for PFlepton saving
            // ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
            bool foundMuTag = false;
            bool foundElTag = false;
            vector<LorentzVector> savedMuP4s;
            vector<LorentzVector> savedElP4s;
            vector<LorentzVector> pfelP4;
            vector<LorentzVector> pfmuP4;
            vector<bool> pfelIsReco;
            vector<bool> pfmuIsReco;
            vector<int> pfelidx;
            vector<int> pfmuidx;
            vector<float> pfelAbsTrkIso;
            vector<float> pfmuAbsTrkIso;
            vector<float> pfelTrkAn04;
            vector<float> pfmuTrkAn04;

            usedMu = false;
            usedEl = false;
            TRandom r;
            rndm = r.Rndm();

            // Loop over muon candidates, which are our probes.
            for (unsigned int i = 0; i < tas::mus_p4().size(); i++)
            {

                // Require pT > 10 GeV.
                float maxPt = 10.;
                if (recoLeptonsDownTo5GeV) { maxPt = 5.; }
                if (recoLeptonsDownTo20GeV) { maxPt = 20.; }
                if (tas::mus_p4().at(i).pt() <= maxPt) { continue; }

                InitLeptonBranches();

                // Check for a tag.
                bool foundTag = checkMuonTag(i, false);

                // Require the following on the probe.
                if (foundTag) { foundMuTag = true; }
                if (muonID(i, SS_veto_noiso_v5) == 0 && muonID(i, HAD_loose_v3) == 0 && foundTag == false) { continue; }
                if (onlySaveTagProbePairs && foundTag == false) { continue; }

                // Get the p4 for the muon.
                p4 = tas::mus_p4().at(i);

                // Dilepton variables in case a tag to this probe is found.
                if (foundTag)
                {
                    dilep_p4 = p4 + tag_p4;
                    dilep_mass = dilep_p4.M();
                }
                if (onlySaveTagProbePairs && (dilep_mass < 60 || dilep_mass > 120)) { continue; }

                // At this point we save the lepton
                if (verbose) { cout << "Saving this muon." << endl; }
                savedMuP4s.push_back(p4);

                // Set ID & Index for muons.
                id = -13.0 * tas::mus_charge().at(i);
                idx = i;

                // Save truth information if it is a MC sample.
                if (!evt_isRealData)
                {
                    motherID = lepMotherID(Lep(id, idx));
                    mc_motherp4 = tas::mus_mc_motherp4().at(i);
                    mc_p4 = tas::mus_mc_p4().at(i);
                    mc_motherid = tas::mus_mc_motherid().at(i);
                    mc_id = tas::mus_mc_id().at(i);
                }

                //Impact parameter
                dxyPV = abs(id) == 11 ? tas::els_dxyPV().at(i) : tas::mus_dxyPV().at(i);
                dxyPV_err = abs(id) == 11 ? tas::els_d0Err().at(i) : tas::mus_d0Err().at(i);
                dZ = abs(id) == 11 ? tas::els_dzPV().at(i) : tas::mus_dzPV().at(i);
                ip3d = tas::mus_ip3d().at(i);
                ip3derr = tas::mus_ip3derr().at(i);

                //Isolation et al
                RelIso03 = (tas::mus_isoR03_pf_ChargedHadronPt().at(i) + tas::mus_isoR03_pf_NeutralHadronEt().at(i) + tas::mus_isoR03_pf_PhotonEt().at(i)) / tas::mus_p4().at(i).pt();
                RelIso03EA = muRelIso03EA(i);
                RelIso03EAv2 = muRelIso03EA(i, 2);
                RelIso04EAv2 = muRelIsoCustomCone(i, 0.4, /*useVetoCones=*/false, 0.5, false, true, -1, 2);
                RelIso03DB = muRelIso03DB(i);
                pfChargedHadronIso = tas::mus_isoR03_pf_ChargedHadronPt().at(i);
                pfPhotonIso = tas::mus_isoR03_pf_PhotonEt().at(i);
                pfNeutralHadronIso = tas::mus_isoR03_pf_NeutralHadronEt().at(i);
                tkIso = tas::mus_iso03_sumPt().at(i);
                sumPUPt = tas::mus_isoR03_pf_PUPt().at(i);
                iso03sumPt = tas::mus_iso03_sumPt().at(i);
                iso03emEt = tas::mus_iso03_emEt().at(i);
                iso03hadEt = tas::mus_iso03_hadEt().at(i);
                ptrelv0 = getPtRel(id, idx, false, ssWhichCorr);
                ptrelv1 = getPtRel(id, idx, true, ssWhichCorr);
                miniiso = muMiniRelIsoCMS3_EA(idx, ssEAversion);
                miniisoDB = muMiniRelIsoCMS3_DB(idx);
                int closeJetIdx = closestJetIdx(p4, 0.4, 3.0);
                if (closeJetIdx >= 0)
                {
                    jet_close_lep_idx = closeJetIdx;
                    jet_close_lep = tas::pfjets_p4().at(closeJetIdx);
                    jet_close_lep_undoJEC = tas::pfjets_undoJEC().at(closeJetIdx);
                    jet_close_lep_area = tas::pfjets_area().at(closeJetIdx);
                    if (jetcorr_filenames_pfL1L2L3.size() > 0)
                    {
                        //L1
                        jet_corrector_pfL1->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1->setRho(rho);
                        jet_close_L1 = jet_corrector_pfL1->getCorrection();
                        //L1, redo it with a different rho
                        jet_corrector_pfL1->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1->setRho(rho_neut_centr);
                        jet_close_L1nc = jet_corrector_pfL1->getCorrection();
                        //L1, redo it with a different rho and MC correction file
                        jet_corrector_pfL1MC->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1MC->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1MC->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1MC->setRho(rho_neut_centr);
                        jet_close_L1ncmc = jet_corrector_pfL1MC->getCorrection();
                        //L1L2L3
                        jet_corrector_pfL1L2L3->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1L2L3->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1L2L3->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1L2L3->setRho(rho);
                        jet_close_L1L2L3 = jet_corrector_pfL1L2L3->getCorrection();
                        //L2L3
                        LorentzVector raw_jet = jet_close_lep * tas::pfjets_undoJEC().at(closeJetIdx);
                        jet_corrector_pfL2L3->setJetEta(raw_jet.eta());
                        jet_corrector_pfL2L3->setJetPt(raw_jet.pt());
                        jet_corrector_pfL2L3->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL2L3->setRho(rho);
                        jet_close_L2L3 = jet_corrector_pfL2L3->getCorrection();
                    }
                }
                ptratio = jet_close_lep.pt() > 0 ? p4.pt() / jet_close_lep.pt() : 1;
                //MT
                mt = MT(p4.pt(), p4.phi(), evt_pfmet, evt_pfmetPhi);
                //Other muon Id
                pid_PFMuon = tas::mus_pid_PFMuon().at(i);
                gfit_chi2 = tas::mus_gfit_chi2().at(i);
                // gfit_ndof = tas::mus_gfit_ndof().at(i);
                gfit_validSTAHits = tas::mus_gfit_validSTAHits().at(i);
                numberOfMatchedStations = tas::mus_numberOfMatchedStations().at(i);
                validPixelHits = tas::mus_validPixelHits().at(i);
                nlayers = tas::mus_nlayers().at(i);
                type = tas::mus_type().at(i);
                chi2LocalPosition = tas::mus_chi2LocalPosition().at(i);
                trkKink = tas::mus_trkKink().at(i);
                validHits = tas::mus_validHits().at(i);
                lostHits = tas::mus_lostHits().at(i);
                exp_innerlayers = tas::mus_exp_innerlayers().at(i);
                exp_outerlayers = tas::mus_exp_outerlayers().at(i);
                segmCompatibility = tas::mus_segmCompatibility().at(i);
                ptErr = tas::mus_ptErr().at(i);
                trk_pt = tas::mus_trk_p4().at(i).pt();
                if (addAnnulus)
                {
                    reliso04 = muRelIsoCustomCone(i, 0.4, true, 0.5, false, true);
                    annulus04 = reliso04 - miniiso;
                }
                if (addPFCandidates || checkIsPFTrueFalse)
                {
                    int pfidx = isPFmuon(pfmuP4, pfmuIsReco, i);
                    if (pfidx != -1)
                    {
                        isPF = true;
                        AbsTrkIso = pfmuAbsTrkIso[pfidx]; // For this electron, save track iso produced earlier for PFmuon
                        if (addAnnulus) { TrkAn04 = pfmuTrkAn04[pfidx]; }
                    }
                }
                muID::setCache(idx, miniiso, ptratio, ptrelv1);
                //Save SS ID bools
                if (muonID(i, SS_tight_v3)) { passes_SS_tight_v3 = true; }
                if (muonID(i, SS_tight_noiso_v3)) { passes_SS_tight_noiso_v3 = true; }
                if (muonID(i, SS_fo_v3)) { passes_SS_fo_v3 = true; }
                if (muonID(i, SS_fo_noiso_v3)) { passes_SS_fo_noiso_v3 = true; }
                if (muonID(i, SS_veto_v3)) { passes_SS_veto_v3 = true; }
                if (muonID(i, SS_veto_noiso_v3)) { passes_SS_veto_noiso_v3 = true; }
                LorentzVector close_jet_v4 = closestJet(p4, 0.4, 3.0, 1);
                float ptrel_v4 = ptRel(p4, close_jet_v4, true);
                float ptratio_v4 = close_jet_v4.pt() > 0 ? p4.pt() / close_jet_v4.pt() : 1;
                muID::unsetCache();
                muID::setCache(idx, miniiso, ptratio_v4, ptrel_v4);
                if (muonID(i, SS_tight_v4)) { passes_SS_tight_v4 = true; }
                if (muonID(i, SS_tight_noiso_v4)) { passes_SS_tight_noiso_v4 = true; }
                if (muonID(i, SS_fo_v4)) { passes_SS_fo_v4 = true; }
                if (muonID(i, SS_fo_noiso_v4)) { passes_SS_fo_noiso_v4 = true; }
                if (muonID(i, SS_veto_v4)) { passes_SS_veto_v4 = true; }
                if (muonID(i, SS_veto_noiso_v4)) { passes_SS_veto_noiso_v4 = true; }
                LorentzVector close_jet_v5 = closestJet(p4, 0.4, 3.0, 2);
                float ptrel_v5 = ptRel(p4, close_jet_v5, true);
                float ptratio_v5 = close_jet_v5.pt() > 0 ? p4.pt() / close_jet_v5.pt() : 1;
                muID::unsetCache();
                muID::setCache(idx, miniiso, ptratio_v5, ptrel_v5);
                if (muonID(i, SS_tight_v5)) { passes_SS_tight_v5 = true; }
                if (muonID(i, SS_tight_noiso_v5)) { passes_SS_tight_noiso_v5 = true; }
                if (muonID(i, SS_fo_v5)) { passes_SS_fo_v5 = true; }
                if (muonID(i, SS_fo_noiso_v5)) { passes_SS_fo_noiso_v5 = true; }
                if (muonID(i, SS_veto_v5)) { passes_SS_veto_v5 = true; }
                if (muonID(i, SS_veto_noiso_v5)) { passes_SS_veto_noiso_v5 = true; }
                muID::unsetCache();
                muID::setCache(idx, miniiso, ptratio, ptrelv1);
                //Save WW ID bools
                if (muonID(i, WW_medium_v2)) { passes_WW_medium_v2 = true; }
                if (muonID(i, WW_medium_noiso_v2)) { passes_WW_medium_noiso_v2 = true; }
                if (muonID(i, WW_fo_v2)) { passes_WW_fo_v2 = true; }
                if (muonID(i, WW_fo_noiso_v2)) { passes_WW_fo_noiso_v2 = true; }
                if (muonID(i, WW_veto_v2)) { passes_WW_veto_v2 = true; }
                if (muonID(i, WW_veto_noiso_v2)) { passes_WW_veto_noiso_v2 = true; }
                //Save HAD ID bools
                if (muonID(i, HAD_loose_v3)) { passes_HAD_loose_v3 = true; }
                if (muonID(i, HAD_loose_noiso_v3)) { passes_HAD_loose_noiso_v3 = true; }
                // Save VVV ID bools
                if (muonID(i, VVV_cutbased_veto)) { passes_VVV_cutbased_veto = true; }
                if (muonID(i, VVV_cutbased_veto_noiso)) { passes_VVV_cutbased_veto_noiso = true; }
                if (muonID(i, VVV_cutbased_veto_noiso_noip)) { passes_VVV_cutbased_veto_noiso_noip = true; }
                if (muonID(i, VVV_cutbased_fo)) { passes_VVV_cutbased_fo = true; }
                if (muonID(i, VVV_cutbased_fo_noiso)) { passes_VVV_cutbased_fo_noiso = true; }
                if (muonID(i, VVV_baseline)) { passes_VVV_baseline = true; }
                if (muonID(i, VVV_cutbased_tight)) { passes_VVV_cutbased_tight = true; }
                if (muonID(i, VVV_cutbased_tight_noiso)) { passes_VVV_cutbased_tight_noiso = true; }
                //Save POG ID bools
                if (isLooseMuonPOG(i)) { passes_POG_looseID = true; }
                if (isMediumMuonPOG(i)) { passes_POG_mediumID = true; }
                if (isTightMuonPOG(i)) { passes_POG_tightID = true; }
                muID::unsetCache();
                //Fill trigger branches
                fillMuonTriggerBranches(p4, idx, false);
                //Fill baby once per probe
                ptratio = ptratio_v5;
                BabyTree->Fill();
            } //close muon loop

            //Electron Loop
            if (verbose) { cout << "Electron Loop" << endl; }
            for (unsigned int i = 0; i < tas::els_p4().size(); i++)
            {

                // Require pT > 10 GeV
                float maxPt = 10.;
                if (recoLeptonsDownTo5GeV) { maxPt = 5.; }
                if (recoLeptonsDownTo20GeV) { maxPt = 20.; }
                if (tas::els_p4().at(i).pt() <= maxPt) { continue; }

                InitLeptonBranches();

                //Check for a tag
                bool foundTag = checkElectronTag(i, v25nsMVAreader);

                // Require the following on the probe.
                if (foundTag) { foundElTag = true; }
                //Save the electron if we have a tag OR if it passes loose ID
                if (electronID(i, SS_veto_noiso_v4) == 0 && electronID(i, HAD_veto_v3) == 0 && foundTag == false) { continue; }
                if (onlySaveTagProbePairs && foundTag == false) { continue; }

                // Get the p4 for the electron.
                p4 = tas::els_p4().at(i);

                //Dilepton stuff
                if (foundTag)
                {
                    dilep_p4 = p4 + tag_p4;
                    dilep_mass = dilep_p4.M();
                }
                if (onlySaveTagProbePairs && (dilep_mass < 60 || dilep_mass > 120)) { continue; }

                // At this point we save the lepton
                if (verbose) { cout << "Saving this electron: pt/eta/phi " << p4.pt() << "/" << p4.eta() << "/" << p4.phi() << endl; }
                savedElP4s.push_back(p4);

                // Set ID & idx for electron
                id = -11.0 * tas::els_charge().at(i);
                idx = i;

                // Save truth information if it is a MC sample.
                if (!evt_isRealData)
                {
                    mc_p4 = tas::els_mc_p4().at(i);
                    mc_id = tas::els_mc_id().at(i);
                }

                //Impact Parameter
                dxyPV = abs(id) == 11 ? tas::els_dxyPV().at(i) : tas::mus_dxyPV().at(i);
                dxyPV_err = abs(id) == 11 ? tas::els_d0Err().at(i) : tas::mus_d0Err().at(i);
                dZ = abs(id) == 11 ? tas::els_dzPV().at(i) : tas::mus_dzPV().at(i);
                ip3d = tas::els_ip3d().at(i);
                ip3derr = tas::els_ip3derr().at(i);

                //Isolation et al
                RelIso03 = (tas::els_pfChargedHadronIso().at(i) + tas::els_pfNeutralHadronIso().at(i) + tas::els_pfPhotonIso().at(i)) / tas::els_p4().at(i).pt();
                RelIso03EA = eleRelIso03EA(i);
                RelIso03EAv2 = eleRelIso03EA(i, 2);
                RelIso04EAv2 = elRelIsoCustomCone(i, 0.4, false, 0.0, /*useDBCorr=*/false, /*useEACorr=*/true, /*mindr=*/-1, /*eaversion=*/2);
                RelIso03DB = eleRelIso03DB(i);
                pfChargedHadronIso = tas::els_pfChargedHadronIso().at(i);
                pfPhotonIso = tas::els_pfPhotonIso().at(i);
                pfNeutralHadronIso = tas::els_pfNeutralHadronIso().at(i);
                tkIso = tas::els_tkIso().at(i);
                ptrelv0 = getPtRel(id, idx, false, ssWhichCorr);
                ptrelv1 = getPtRel(id, idx, true, ssWhichCorr);
                if (verbose) { cout << "About to correct jets for this electron" << endl; }
                int closeJetIdx = closestJetIdx(p4, 0.4, 3.0);
                if (closeJetIdx >= 0)
                {
                    jet_close_lep_idx = closeJetIdx;
                    jet_close_lep = tas::pfjets_p4().at(closeJetIdx);
                    jet_close_lep_undoJEC = tas::pfjets_undoJEC().at(closeJetIdx);
                    jet_close_lep_area = tas::pfjets_area().at(closeJetIdx);
                    if (jetcorr_filenames_pfL1L2L3.size() > 0)
                    {
                        //L1
                        jet_corrector_pfL1->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1->setRho(rho);
                        jet_close_L1 = jet_corrector_pfL1->getCorrection();
                        //L1, redo it with a different rho
                        jet_corrector_pfL1->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1->setRho(rho_neut_centr);
                        jet_close_L1nc = jet_corrector_pfL1->getCorrection();
                        //L1, redo it with a different rho and MC correction file
                        jet_corrector_pfL1MC->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1MC->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1MC->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1MC->setRho(rho_neut_centr);
                        jet_close_L1ncmc = jet_corrector_pfL1MC->getCorrection();
                        //L1L2L3
                        jet_corrector_pfL1L2L3->setJetEta(jet_close_lep.eta());
                        jet_corrector_pfL1L2L3->setJetPt(jet_close_lep.pt()*jet_close_lep_undoJEC);
                        jet_corrector_pfL1L2L3->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL1L2L3->setRho(rho);
                        jet_close_L1L2L3 = jet_corrector_pfL1L2L3->getCorrection();
                        //L2L3
                        LorentzVector raw_jet = jet_close_lep * tas::pfjets_undoJEC().at(closeJetIdx);
                        jet_corrector_pfL2L3->setJetEta(raw_jet.eta());
                        jet_corrector_pfL2L3->setJetPt(raw_jet.pt());
                        jet_corrector_pfL2L3->setJetA(tas::pfjets_area().at(closeJetIdx));
                        jet_corrector_pfL2L3->setRho(rho);
                        jet_close_L2L3 = jet_corrector_pfL2L3->getCorrection();
                    }
                }
                if (verbose) { cout << "Finished jet corrections" << endl; }
                ptratio = (jet_close_lep.pt() > 0. ? p4.pt() / jet_close_lep.pt() : 1.);
                miniiso = elMiniRelIsoCMS3_EA(idx, ssEAversion);
                miniisoDB = elMiniRelIsoCMS3_DB(idx);
                //MT
                mt = MT(p4.pt(), p4.phi(), evt_pfmet, evt_pfmetPhi);
                //Other Electron ID stuff
                sumPUPt = tas::els_pfPUIso().at(i);
                sigmaIEtaIEta_full5x5 = tas::els_sigmaIEtaIEta_full5x5().at(i);
                etaSC = tas::els_etaSC().at(i);
                dEtaIn = tas::els_dEtaIn().at(i);
                dPhiIn = tas::els_dPhiIn().at(i);
                hOverE = tas::els_hOverE().at(i);
                ecalEnergy = tas::els_ecalEnergy().at(i);
                eOverPIn = tas::els_eOverPIn().at(i);
                conv_vtx_flag = tas::els_conv_vtx_flag().at(i);
                exp_innerlayers = tas::els_exp_innerlayers().at(i);
                exp_outerlayers = tas::els_exp_outerlayers().at(i);
                charge = tas::els_charge().at(i);
                sccharge = tas::els_sccharge().at(i);
                ckf_charge = tas::els_ckf_charge().at(i);
                trk_charge = tas::els_trk_charge().at(i);
                threeChargeAgree_branch = threeChargeAgree(i);
                mva = getMVAoutput(i);
                mva_25ns = v25nsMVAreader->MVA(i);
                type = tas::els_type().at(i);
                ecalIso = tas::els_ecalIso().at(i);
                hcalIso = tas::els_hcalIso().at(i);
                sigmaIEtaIEta = tas::els_sigmaIEtaIEta().at(i);
                ecalPFClusterIso = tas::els_ecalPFClusterIso().at(i);
                hcalPFClusterIso = tas::els_hcalPFClusterIso().at(i);
                ckf_laywithmeas = tas::els_ckf_laywithmeas().at(i);
                sigmaIPhiIPhi_full5x5 = tas::els_sigmaIPhiIPhi_full5x5().at(i);
                e1x5_full5x5 = tas::els_e1x5_full5x5().at(i);
                e5x5_full5x5 = tas::els_e5x5_full5x5().at(i);
                r9_full5x5 = tas::els_r9_full5x5().at(i);
                etaSCwidth = tas::els_etaSCwidth().at(i);
                phiSCwidth = tas::els_phiSCwidth().at(i);
                eSeed = tas::els_eSeed().at(i);
                scSeedEta = tas::els_scSeedEta().at(i);
                eSCRaw = tas::els_eSCRaw().at(i);
                eSC = tas::els_eSC().at(i);
                eSCPresh = tas::els_eSCPresh().at(i);
                ckf_chi2 = tas::els_ckf_chi2().at(i);
                ckf_ndof = tas::els_ckf_ndof().at(i);
                chi2 = tas::els_chi2().at(i);
                ndof = tas::els_ndof().at(i);
                fbrem = tas::els_fbrem().at(i);
                eOverPOut = tas::els_eOverPOut().at(i);
                dEtaOut = tas::els_dEtaOut().at(i);
                dPhiOut = tas::els_dPhiOut().at(i);
                gsf_validHits = tas::els_validHits().at(i);
                conv_vtx_prob = tas::els_conv_vtx_prob().at(i);
                if (addAnnulus)
                {
                    //https://github.com/cmstas/VVVBabyMaker/blob/098bfe59c52ca31f810416cc9c3e00958fdc8a79/dilepbabymaker/ScanChain.cc#L1223
                    // vec_lep_relIso04EAv2         .push_back(elRelIsoCustomCone(iEl, 0.4, false, 0.0, /*useDBCorr=*/false, /*useEACorr=*/true, /*mindr=*/-1, /*eaversion=*/2));
                    reliso04 = elRelIsoCustomCone(i, 0.4, false, 0.0, false, true, -1, 2);
                    annulus04 = reliso04 - miniiso;
                }
                if (addPFCandidates || checkIsPFTrueFalse)
                {
                    int pfidx = isPFelectron(pfelP4, pfelIsReco, i);
                    if (pfidx != -1)
                    {
                        isPF = true;
                        AbsTrkIso = pfelAbsTrkIso[pfidx]; // For this electron, save track iso produced earlier for PFmuon
                        if (addAnnulus) { TrkAn04 = pfelTrkAn04[pfidx]; }
                    }
                }
                elID::setCache(idx, mva, miniiso, ptratio, ptrelv1);
                if (verbose) { cout << "Starting electron IDs" << endl; }
                //Save SS ID bools
                if (electronID(i, SS_medium_v3)) { passes_SS_tight_v3 = true; }
                if (electronID(i, SS_medium_noiso_v3)) { passes_SS_tight_noiso_v3 = true; }
                if (electronID(i, SS_fo_v3)) { passes_SS_fo_v3 = true; }
                if (electronID(i, SS_fo_noiso_v3)) { passes_SS_fo_noiso_v3 = true; }
                if (electronID(i, SS_fo_looseMVA_v3)) { passes_SS_fo_looseMVA_v3 = true; }
                if (electronID(i, SS_fo_looseMVA_noiso_v3)) { passes_SS_fo_looseMVA_noiso_v3 = true; }
                if (electronID(i, SS_veto_v3)) { passes_SS_veto_v3 = true; }
                if (electronID(i, SS_veto_noiso_v3)) { passes_SS_veto_noiso_v3 = true; }
                LorentzVector close_jet_v4 = closestJet(p4, 0.4, 3.0, 1);
                float ptrel_v4 = ptRel(p4, close_jet_v4, true);
                float ptratio_v4 = close_jet_v4.pt() > 0 ? p4.pt() / close_jet_v4.pt() : 1;
                elID::unsetCache();
                elID::setCache(idx, mva_25ns, miniiso, ptratio_v4, ptrel_v4);
                if (electronID(i, SS_medium_v4)) { passes_SS_tight_v4 = true; }
                if (electronID(i, SS_medium_noiso_v4)) { passes_SS_tight_noiso_v4 = true; }
                if (electronID(i, SS_fo_v4)) { passes_SS_fo_v4 = true; }
                if (electronID(i, SS_fo_noiso_v4)) { passes_SS_fo_noiso_v4 = true; }
                if (electronID(i, SS_fo_looseMVA_v4)) { passes_SS_fo_looseMVA_v4 = true; }
                if (electronID(i, SS_fo_looseMVA_noiso_v4)) { passes_SS_fo_looseMVA_noiso_v4 = true; }
                if (electronID(i, SS_veto_v4)) { passes_SS_veto_v4 = true; }
                if (electronID(i, SS_veto_noiso_v4)) { passes_SS_veto_noiso_v4 = true; }
                LorentzVector close_jet_v5 = closestJet(p4, 0.4, 3.0, 2);
                float ptrel_v5 = ptRel(p4, close_jet_v5, true);
                float ptratio_v5 = close_jet_v5.pt() > 0 ? p4.pt() / close_jet_v5.pt() : 1;
                elID::unsetCache();
                elID::setCache(idx, mva_25ns, miniiso, ptratio_v5, ptrel_v5);
                if (electronID(i, SS_medium_v5)) { passes_SS_tight_v5 = true; }
                if (electronID(i, SS_medium_noiso_v5)) { passes_SS_tight_noiso_v5 = true; }
                if (electronID(i, SS_fo_v5)) { passes_SS_fo_v5 = true; }
                if (electronID(i, SS_fo_noiso_v5)) { passes_SS_fo_noiso_v5 = true; }
                if (electronID(i, SS_fo_looseMVA_v5)) { passes_SS_fo_looseMVA_v5 = true; }
                if (electronID(i, SS_fo_looseMVA_noiso_v5)) { passes_SS_fo_looseMVA_noiso_v5 = true; }
                if (electronID(i, SS_veto_v5)) { passes_SS_veto_v5 = true; }
                if (electronID(i, SS_veto_noiso_v5)) { passes_SS_veto_noiso_v5 = true; }
                if (verbose) { cout << "Done SS IDs" << endl; }
                elID::unsetCache();
                elID::setCache(idx, mva, miniiso, ptratio, ptrelv1);
                //Save WW ID bools
                if (electronID(i, WW_medium_v2)) { passes_WW_medium_v2 = true; }
                if (electronID(i, WW_medium_noiso_v2)) { passes_WW_medium_noiso_v2 = true; }
                if (electronID(i, WW_fo_v2)) { passes_WW_fo_v2 = true; }
                if (electronID(i, WW_fo_noiso_v2)) { passes_WW_fo_noiso_v2 = true; }
                if (electronID(i, WW_veto_v2)) { passes_WW_veto_v2 = true; }
                if (electronID(i, WW_veto_noiso_v2)) { passes_WW_veto_noiso_v2 = true; }
                //Save HAD ID bools
                if (electronID(i, HAD_veto_v3)) { passes_HAD_veto_v3 = true; }
                if (electronID(i, HAD_veto_noiso_v3)) { passes_HAD_veto_noiso_v3 = true; }
                if (electronID(i, HAD_loose_v3)) { passes_HAD_loose_v3 = true; }
                if (electronID(i, HAD_loose_noiso_v3)) { passes_HAD_loose_noiso_v3 = true; }
                if (verbose) { cout << "Done WW and HAD IDs" << endl; }
                // Save WWW ID bools
                if (electronID(i, VVV_cutbased_veto_bak1)) { passes_VVV_cutbased_veto_bak1 = true; }
                if (electronID(i, VVV_cutbased_veto_noiso_bak1)) { passes_VVV_cutbased_veto_noiso_bak1 = true; }
                if (electronID(i, VVV_cutbased_veto_noiso_noip_bak1)) { passes_VVV_cutbased_veto_noiso_noip_bak1 = true; }
                if (electronID(i, VVV_cutbased_veto)) { passes_VVV_cutbased_veto = true; }
                if (electronID(i, VVV_cutbased_veto_noiso)) { passes_VVV_cutbased_veto_noiso = true; }
                if (electronID(i, VVV_cutbased_veto_noiso_noip)) { passes_VVV_cutbased_veto_noiso_noip = true; }
                if (electronID(i, VVV_cutbased_fo)) { passes_VVV_cutbased_fo = true; }
                if (electronID(i, VVV_cutbased_fo_noiso)) { passes_VVV_cutbased_fo_noiso = true; }
                if (electronID(i, VVV_baseline)) { passes_VVV_baseline = true; }
                if (electronID(i, VVV_MVAbased_tight)) { passes_VVV_MVAbased_tight = true; }
                if (electronID(i, VVV_MVAbased_tight_noiso)) { passes_VVV_MVAbased_tight_noiso = true; }
                if (electronID(i, VVV_cutbased_tight)) { passes_VVV_cutbased_tight = true; }
                if (electronID(i, VVV_cutbased_tight_noiso)) { passes_VVV_cutbased_tight_noiso = true; }
                //Save POG ID bools
//                if (tas::els_passVetoId().at(i)) { passes_POG_vetoID = true; }
//                if (tas::els_passLooseId().at(i)) { passes_POG_looseID = true; }
//                if (tas::els_passMediumId().at(i)) { passes_POG_mediumID = true; }
//                if (tas::els_passTightId().at(i)) { passes_POG_tightID = true; }
                if (isVetoElectronPOGspring16_v1(i)) { passes_POG_vetoID = true; }
                if (isLooseElectronPOGspring16_v1(i)) { passes_POG_looseID = true; }
                if (isMediumElectronPOGspring16_v1(i)) { passes_POG_mediumID = true; }
                if (isTightElectronPOGspring16_v1(i)) { passes_POG_tightID = true; }
                // Save isTriggerSafe_v1
                if (isTriggerSafe_v1(i)) { passes_isTriggerSafe_v1 = true; }
                if (isTriggerSafe_v2(i)) { passes_isTriggerSafe_v2 = true; }
                if (verbose) { cout << "Done POG IDs" << endl; }
                elID::unsetCache();
                if (verbose) { cout << "Some MC properties" << endl; }
                if (!evt_isRealData)
                {
                    motherID = lepMotherID(Lep(id, idx));
                    mc_motherp4 = tas::els_mc_motherp4().at(i);
                    mc_motherid = tas::els_mc_motherid().at(i);
                }
                //Triggers
                if (verbose) { cout << "Electron triggers" << endl; }
                fillElectronTriggerBranches(p4, idx, false);
                if (verbose) { cout << "Saving electron branches" << endl; }
                //Fill tree once per tag
                ptratio = ptratio_v5;
                BabyTree->Fill();
                if (verbose) { cout << "Finished electron" << endl; }
            }

            ////////// Addition of PF LEPTONS that were not included before //////////////////
            // check if anything needs to be done:
            // - compare size of pfelp4 with probeelp4, and same for muons
            // - check whether there is a muon/electron tag
            // if something to be done, then we need to save the pflepton as well as tag properties and triggers...

            // Variables to keep track of PFElectrons and PFMuons.
            // We would like to save PFleptons if they don't overlap with something we've already saved.
            // If they do overlap, we want to save the fact that they overlap.
            // Load the pflepton p4s in memory, we'll have to check them on each lepton.
            for (unsigned int i = 0; i < tas::pfcands_p4().size(); i++)
            {
                if (fabs(tas::pfcands_particleId().at(i)) != 11 && fabs(tas::pfcands_particleId().at(i)) != 13) { continue; }
                if (tas::pfcands_p4().at(i).pt() < 5) { continue; }
                if (fabs(tas::pfcands_dz().at(i)) > 0.1) { continue; }
                if (fabs(tas::pfcands_p4().at(i).eta()) > 2.5) { continue; }
                if (fabs(tas::pfcands_particleId().at(i)) == 11)
                {
                    pfelidx.push_back(i);
                    pfelP4.push_back(tas::pfcands_p4().at(i));
                    pfelIsReco.push_back(false);
                    pfelAbsTrkIso.push_back(TrackIso(i, 0.3, 0.0, true, false));
                    pfelTrkAn04.push_back(PFCandRelIsoAn04(i));
                }
                else if (fabs(tas::pfcands_particleId().at(i)) == 13)
                {
                    pfmuidx.push_back(i);
                    pfmuP4.push_back(tas::pfcands_p4().at(i));
                    pfmuIsReco.push_back(false);
                    pfmuAbsTrkIso.push_back(TrackIso(i, 0.3, 0.0, true, false));
                    pfmuTrkAn04.push_back(PFCandRelIsoAn04(i));
                }
                continue;
            }

            if (verbose) { cout << "Addition of PF LEPTONS that were not included before" << endl; }
            bool addPFel = false;
            bool addPFmu = false;
            if (foundElTag && savedElP4s.size() != pfelP4.size()) { addPFel = true; }
            if (foundMuTag && savedMuP4s.size() != pfmuP4.size()) { addPFmu = true; }
            if (addPFel && addPFCandidates)
            {
                for (unsigned int i = 0; i < pfelP4.size(); i++)
                {
                    if (pfelIsReco[i]) { continue; }
                    InitLeptonBranches();
                    // set the tag branches (-1 means we are happy if any reco electron is a tag)
                    // checkElectronTag( -1 , 0);
                    checkElectronTag(-1, v25nsMVAreader);
                    // now let's look at our electron
                    int pfidx = pfelidx[i];
                    p4 = pfelP4[i];
                    id = tas::pfcands_particleId().at(pfidx);
                    isPF = true; // that's why we're here!
                    if (id > 0) { id = 1011; }
                    else { id = -1011; }
                    dZ = tas::pfcands_dz().at(pfidx);
                    charge = tas::pfcands_charge().at(pfidx);
                    AbsTrkIso = pfelAbsTrkIso[i]; // For this muon, save track iso produced earlier for PFmuon
                    TrkAn04 = pfelTrkAn04[i];
                    if (!evt_isRealData) { motherID = pfLepMotherID(pfidx); }
                    dilep_p4 = p4 + tag_p4;
                    dilep_mass = dilep_p4.M();
                    fillElectronTriggerBranches(p4, -1, false);
                    BabyTree->Fill();
                }
            } // addPFel

            if (addPFmu && addPFCandidates)
            {
                for (unsigned int i = 0; i < pfmuP4.size(); i++)
                {
                    if (pfmuIsReco[i]) { continue; }
                    InitLeptonBranches();
                    // set the tag branches (-1 means we are happy if any reco electron is a tag)
                    checkMuonTag(-1);
                    // now let's look at our electron
                    int pfidx = pfmuidx[i];
                    p4 = pfmuP4[i];
                    id = tas::pfcands_particleId().at(pfidx);
                    isPF = true; // that's why we're here!
                    if (id > 0) { id = 1013; }
                    else { id = -1013; }
                    dZ = tas::pfcands_dz().at(pfidx);
                    charge = tas::pfcands_charge().at(pfidx);
                    AbsTrkIso = pfmuAbsTrkIso[i]; // For this muon, save track iso produced earlier for PFmuon
                    TrkAn04 = pfmuTrkAn04[i];
                    if (!evt_isRealData) { motherID = pfLepMotherID(pfidx); }
                    dilep_p4 = p4 + tag_p4;
                    dilep_mass = dilep_p4.M();
                    fillMuonTriggerBranches(p4, -1, false);
                    BabyTree->Fill();
                }
            } // addPFmu

        } //close event loop
        file->Close();
        delete file;
        cout << "\nFile done" << endl;
    } //close file loop
    cout << "\nWriting file" << endl;
    BabyFile->cd();
    BabyTree->Write();
    BabyFile->Close();
    return 0;
}

//Main functions
//___________________________________________________________________________________________________________________________________________
void babyMaker::MakeBabyNtuple(const char* output_name)
{
    //Create Baby
    BabyFile = new TFile(Form("%s/%s", path.c_str(), output_name), "RECREATE");
    BabyFile->cd();
    BabyTree = new TTree("t", "Lepton Baby Ntuple");
    //General
    BabyTree->Branch("evt_pfmet", &evt_pfmet);
    BabyTree->Branch("evt_pfmetPhi", &evt_pfmetPhi);
    BabyTree->Branch("evt_trackmet", &evt_trackmet);
    BabyTree->Branch("evt_trackmetPhi", &evt_trackmetPhi);
    BabyTree->Branch("evt_corrMET", &evt_corrMET);
    BabyTree->Branch("evt_corrMETPhi", &evt_corrMETPhi);
    BabyTree->Branch("evt_corrMET_up", &evt_corrMET_up);
    BabyTree->Branch("evt_corrMETPhi_up", &evt_corrMETPhi_up);
    BabyTree->Branch("evt_corrMET_dn", &evt_corrMET_dn);
    BabyTree->Branch("evt_corrMETPhi_dn", &evt_corrMETPhi_dn);
    BabyTree->Branch("evt_pfsumet", &evt_pfsumet);
    BabyTree->Branch("evt_pfmetSig", &evt_pfmetSig);
    BabyTree->Branch("evt_event", &evt_event);
    BabyTree->Branch("evt_lumiBlock", &evt_lumiBlock);
    BabyTree->Branch("evt_run", &evt_run);
    BabyTree->Branch("filt_csc", &filt_csc);
    BabyTree->Branch("filt_hbhe", &filt_hbhe);
    BabyTree->Branch("passes_met_filters", &passes_met_filters);
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
    BabyTree->Branch("ht_SS", &ht_SS);
    BabyTree->Branch("jets", &jets);
    BabyTree->Branch("jets_disc", &jets_disc);
    BabyTree->Branch("jets_area", &jets_area);
    BabyTree->Branch("jets_undoJEC", &jets_undoJEC);
    BabyTree->Branch("jets_unc", &jets_unc);
    BabyTree->Branch("sample", &sample);
    BabyTree->Branch("nFOs_SS", &nFOs_SS);
    BabyTree->Branch("nvtx", &nvtx);
    BabyTree->Branch("pu_ntrue", &pu_ntrue);
    BabyTree->Branch("instantLumi", &instantLumi);
    BabyTree->Branch("rho", &rho);
    BabyTree->Branch("rho_neut_centr", &rho_neut_centr);
    BabyTree->Branch("rho_calo", &rho_calo);
    BabyTree->Branch("rho_calo_centr", &rho_calo_centr);
    //All leptons
    BabyTree->Branch("p4", &p4);
    BabyTree->Branch("tag_p4", &tag_p4);
    BabyTree->Branch("dilep_p4", &dilep_p4);
    BabyTree->Branch("mc_p4", &mc_p4);
    BabyTree->Branch("mc_motherp4", &mc_motherp4);
    BabyTree->Branch("mc_motherid", &mc_motherid);
    BabyTree->Branch("id", &id);
    BabyTree->Branch("isPF", &isPF);
    BabyTree->Branch("idx", &idx);
    BabyTree->Branch("dxyPV", &dxyPV);
    BabyTree->Branch("dZ", &dZ);
    BabyTree->Branch("dxyPV_err", &dxyPV_err);
    BabyTree->Branch("motherID", &motherID);
    BabyTree->Branch("mc_id", &mc_id);
    BabyTree->Branch("RelIso03", &RelIso03);
    BabyTree->Branch("RelIso03EA", &RelIso03EA);
    BabyTree->Branch("RelIso03EAv2", &RelIso03EAv2);
    BabyTree->Branch("RelIso04EAv2", &RelIso04EAv2);
    BabyTree->Branch("tag_RelIso03EA", &tag_RelIso03EA);
    BabyTree->Branch("RelIso03DB", &RelIso03DB);
    BabyTree->Branch("pfChargedHadronIso", &pfChargedHadronIso);
    BabyTree->Branch("pfPhotonIso", &pfPhotonIso);
    BabyTree->Branch("pfNeutralHadronIso", &pfNeutralHadronIso);
    BabyTree->Branch("tkIso", &tkIso);
    BabyTree->Branch("sumPUPt", &sumPUPt);
    BabyTree->Branch("passes_SS_tight_v3", &passes_SS_tight_v3);
    BabyTree->Branch("passes_SS_tight_noiso_v3", &passes_SS_tight_noiso_v3);
    BabyTree->Branch("passes_SS_fo_v3", &passes_SS_fo_v3);
    BabyTree->Branch("passes_SS_fo_noiso_v3", &passes_SS_fo_noiso_v3);
    BabyTree->Branch("passes_SS_fo_looseMVA_v3", &passes_SS_fo_looseMVA_v3);
    BabyTree->Branch("passes_SS_fo_looseMVA_noiso_v3", &passes_SS_fo_looseMVA_noiso_v3);
    BabyTree->Branch("passes_SS_veto_v3", &passes_SS_veto_v3);
    BabyTree->Branch("passes_SS_veto_noiso_v3", &passes_SS_veto_noiso_v3);
    BabyTree->Branch("passes_SS_tight_v4", &passes_SS_tight_v4);
    BabyTree->Branch("passes_SS_tight_noiso_v4", &passes_SS_tight_noiso_v4);
    BabyTree->Branch("passes_SS_fo_v4", &passes_SS_fo_v4);
    BabyTree->Branch("passes_SS_fo_noiso_v4", &passes_SS_fo_noiso_v4);
    BabyTree->Branch("passes_SS_fo_looseMVA_v4", &passes_SS_fo_looseMVA_v4);
    BabyTree->Branch("passes_SS_fo_looseMVA_noiso_v4", &passes_SS_fo_looseMVA_noiso_v4);
    BabyTree->Branch("passes_SS_veto_v4", &passes_SS_veto_v4);
    BabyTree->Branch("passes_SS_veto_noiso_v4", &passes_SS_veto_noiso_v4);
    BabyTree->Branch("passes_SS_tight_v5", &passes_SS_tight_v5);
    BabyTree->Branch("passes_SS_tight_noiso_v5", &passes_SS_tight_noiso_v5);
    BabyTree->Branch("passes_SS_fo_v5", &passes_SS_fo_v5);
    BabyTree->Branch("passes_SS_fo_noiso_v5", &passes_SS_fo_noiso_v5);
    BabyTree->Branch("passes_SS_fo_looseMVA_v5", &passes_SS_fo_looseMVA_v5);
    BabyTree->Branch("passes_SS_fo_looseMVA_noiso_v5", &passes_SS_fo_looseMVA_noiso_v5);
    BabyTree->Branch("passes_SS_veto_v5", &passes_SS_veto_v5);
    BabyTree->Branch("passes_SS_veto_noiso_v5", &passes_SS_veto_noiso_v5);
    BabyTree->Branch("passes_WW_medium_v2", &passes_WW_medium_v2);
    BabyTree->Branch("passes_WW_medium_noiso_v2", &passes_WW_medium_noiso_v2);
    BabyTree->Branch("passes_WW_fo_v2", &passes_WW_fo_v2);
    BabyTree->Branch("passes_WW_fo_noiso_v2", &passes_WW_fo_noiso_v2);
    BabyTree->Branch("passes_WW_veto_v2", &passes_WW_veto_v2);
    BabyTree->Branch("passes_WW_veto_noiso_v2", &passes_WW_veto_noiso_v2);
    BabyTree->Branch("passes_HAD_veto_v3", &passes_HAD_veto_v3);
    BabyTree->Branch("passes_HAD_veto_noiso_v3", &passes_HAD_veto_noiso_v3);
    BabyTree->Branch("passes_HAD_loose_v3", &passes_HAD_loose_v3);
    BabyTree->Branch("passes_HAD_loose_noiso_v3", &passes_HAD_loose_noiso_v3);
    BabyTree->Branch("passes_VVV_cutbased_veto_bak1", &passes_VVV_cutbased_veto_bak1);
    BabyTree->Branch("passes_VVV_cutbased_veto_noiso_bak1", &passes_VVV_cutbased_veto_noiso_bak1);
    BabyTree->Branch("passes_VVV_cutbased_veto_noiso_noip_bak1", &passes_VVV_cutbased_veto_noiso_noip_bak1);
    BabyTree->Branch("passes_VVV_cutbased_veto", &passes_VVV_cutbased_veto);
    BabyTree->Branch("passes_VVV_cutbased_veto_noiso", &passes_VVV_cutbased_veto_noiso);
    BabyTree->Branch("passes_VVV_cutbased_veto_noiso_noip", &passes_VVV_cutbased_veto_noiso_noip);
    BabyTree->Branch("passes_VVV_cutbased_fo", &passes_VVV_cutbased_fo);
    BabyTree->Branch("passes_VVV_cutbased_fo_noiso", &passes_VVV_cutbased_fo_noiso);
    BabyTree->Branch("passes_VVV_baseline", &passes_VVV_baseline);
    BabyTree->Branch("passes_VVV_MVAbased_tight", &passes_VVV_MVAbased_tight);
    BabyTree->Branch("passes_VVV_MVAbased_tight_noiso", &passes_VVV_MVAbased_tight_noiso);
    BabyTree->Branch("passes_VVV_cutbased_tight", &passes_VVV_cutbased_tight);
    BabyTree->Branch("passes_VVV_cutbased_tight_noiso", &passes_VVV_cutbased_tight_noiso);
    BabyTree->Branch("passes_POG_vetoID", &passes_POG_vetoID);
    BabyTree->Branch("passes_POG_looseID", &passes_POG_looseID);
    BabyTree->Branch("passes_POG_mediumID", &passes_POG_mediumID);
    BabyTree->Branch("passes_POG_tightID", &passes_POG_tightID);
    BabyTree->Branch("passes_isTriggerSafe_v1", &passes_isTriggerSafe_v1);
    BabyTree->Branch("passes_isTriggerSafe_v2", &passes_isTriggerSafe_v2);
    BabyTree->Branch("ip3d", &ip3d);
    BabyTree->Branch("ip3derr", &ip3derr);
    BabyTree->Branch("type", &type);
    BabyTree->Branch("mt", &mt);
    BabyTree->Branch("ptrelv0", &ptrelv0);
    BabyTree->Branch("ptrelv1", &ptrelv1);
    BabyTree->Branch("miniiso", &miniiso);
    BabyTree->Branch("miniisoDB", &miniisoDB);
    BabyTree->Branch("reliso04", &reliso04);
    BabyTree->Branch("annulus04", &annulus04);
    BabyTree->Branch("AbsTrkIso", &AbsTrkIso);
    BabyTree->Branch("TrkAn04", &TrkAn04);
    BabyTree->Branch("iso03sumPt", &iso03sumPt);
    BabyTree->Branch("iso03emEt", &iso03emEt);
    BabyTree->Branch("iso03hadEt", &iso03hadEt);
    BabyTree->Branch("jet_close_lep_idx", &jet_close_lep_idx);
    BabyTree->Branch("jet_close_lep", &jet_close_lep);
    BabyTree->Branch("jet_close_lep_undoJEC", &jet_close_lep_undoJEC);
    BabyTree->Branch("jet_close_lep_area", &jet_close_lep_area);
    BabyTree->Branch("jet_close_L1", &jet_close_L1);
    BabyTree->Branch("jet_close_L1nc", &jet_close_L1nc);
    BabyTree->Branch("jet_close_L1ncmc", &jet_close_L1ncmc);
    BabyTree->Branch("jet_close_L1L2L3", &jet_close_L1L2L3);
    BabyTree->Branch("jet_close_L2L3", &jet_close_L2L3);
    BabyTree->Branch("ptratio", &ptratio);
    BabyTree->Branch("tag_charge", &tag_charge);
    BabyTree->Branch("tag_mc_motherid", &tag_mc_motherid);
    BabyTree->Branch("tag_eSeed", &tag_eSeed);
    BabyTree->Branch("tag_eSCRaw", &tag_eSCRaw);
    BabyTree->Branch("tag_eSC", &tag_eSC);
    BabyTree->Branch("tag_ecalEnergy", &tag_ecalEnergy);
    BabyTree->Branch("exp_innerlayers", &exp_innerlayers);
    BabyTree->Branch("exp_outerlayers", &exp_outerlayers);
    //Tag triggers
    BabyTree->Branch("tag_HLT_Ele27_eta2p1_WPTight_Gsf", &tag_HLT_Ele27_eta2p1_WPTight_Gsf);
    BabyTree->Branch("tag_HLT_Ele32_eta2p1_WPTight_Gsf", &tag_HLT_Ele32_eta2p1_WPTight_Gsf);
    BabyTree->Branch("tag_HLT_IsoMu24", &tag_HLT_IsoMu24);
    BabyTree->Branch("tag_HLT_IsoTkMu24", &tag_HLT_IsoTkMu24);
    BabyTree->Branch("dilep_mass", &dilep_mass);
    BabyTree->Branch("isRandom", &isRandom);
    //Electrons
    BabyTree->Branch("sigmaIEtaIEta_full5x5", &sigmaIEtaIEta_full5x5);
    BabyTree->Branch("sigmaIEtaIEta", &sigmaIEtaIEta);
    BabyTree->Branch("etaSC", &etaSC);
    BabyTree->Branch("dEtaIn", &dEtaIn);
    BabyTree->Branch("dPhiIn", &dPhiIn);
    BabyTree->Branch("hOverE", &hOverE);
    BabyTree->Branch("eSeed", &eSeed);
    BabyTree->Branch("scSeedEta", &scSeedEta);
    BabyTree->Branch("ecalEnergy", &ecalEnergy);
    BabyTree->Branch("eOverPIn", &eOverPIn);
    BabyTree->Branch("conv_vtx_flag", &conv_vtx_flag);
    BabyTree->Branch("charge", &charge);
    BabyTree->Branch("sccharge", &sccharge);
    BabyTree->Branch("ckf_charge", &ckf_charge);
    BabyTree->Branch("threeChargeAgree", &threeChargeAgree_branch);
    BabyTree->Branch("mva", &mva);
    BabyTree->Branch("mva_25ns", &mva_25ns);
    BabyTree->Branch("tag_mva_25ns", &tag_mva_25ns);
    BabyTree->Branch("ecalIso", &ecalIso);
    BabyTree->Branch("hcalIso", &hcalIso);
    BabyTree->Branch("ecalPFClusterIso", &ecalPFClusterIso);
    BabyTree->Branch("hcalPFClusterIso", &hcalPFClusterIso);
    BabyTree->Branch("ckf_laywithmeas", &ckf_laywithmeas);
    BabyTree->Branch("sigmaIPhiIPhi_full5x5", &sigmaIPhiIPhi_full5x5);
    BabyTree->Branch("e1x5_full5x5", &e1x5_full5x5);
    BabyTree->Branch("e5x5_full5x5", &e5x5_full5x5);
    BabyTree->Branch("r9_full5x5", &r9_full5x5);
    BabyTree->Branch("tag_r9_full5x5", &tag_r9_full5x5);
    BabyTree->Branch("etaSCwidth", &etaSCwidth);
    BabyTree->Branch("phiSCwidth", &phiSCwidth);
    BabyTree->Branch("eSCRaw", &eSCRaw);
    BabyTree->Branch("eSC", &eSC);
    BabyTree->Branch("eSCPresh", &eSCPresh);
    BabyTree->Branch("ckf_chi2", &ckf_chi2);
    BabyTree->Branch("ckf_ndof", &ckf_ndof);
    BabyTree->Branch("chi2", &chi2);
    BabyTree->Branch("ndof", &ndof);
    BabyTree->Branch("fbrem", &fbrem);
    BabyTree->Branch("eOverPOut", &eOverPOut);
    BabyTree->Branch("dEtaOut", &dEtaOut);
    BabyTree->Branch("dPhiOut", &dPhiOut);
    BabyTree->Branch("gsf_validHits", &gsf_validHits);
    BabyTree->Branch("conv_vtx_prob", &conv_vtx_prob);
    //Muons
    BabyTree->Branch("pid_PFMuon", &pid_PFMuon);
    BabyTree->Branch("gfit_chi2", &gfit_chi2);
    BabyTree->Branch("gfit_validSTAHits", &gfit_validSTAHits);
    BabyTree->Branch("numberOfMatchedStations", &numberOfMatchedStations);
    BabyTree->Branch("validPixelHits", &validPixelHits);
    BabyTree->Branch("nlayers", &nlayers);
    BabyTree->Branch("chi2LocalPosition", &chi2LocalPosition);
    BabyTree->Branch("trkKink", &trkKink);
    BabyTree->Branch("validHits", &validHits);
    BabyTree->Branch("lostHits", &lostHits);
    BabyTree->Branch("segmCompatibility", &segmCompatibility);
    BabyTree->Branch("ptErr", &ptErr);
    BabyTree->Branch("trk_pt", &trk_pt);
    //Single Muon Triggers
    BabyTree->Branch("HLT_Mu8", &HLT_Mu8);
    BabyTree->Branch("HLT_Mu17", &HLT_Mu17);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL", &HLT_Mu8_TrkIsoVVL);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL);
    BabyTree->Branch("HLT_IsoMu24", &HLT_IsoMu24);
    BabyTree->Branch("HLT_IsoTkMu24", &HLT_IsoTkMu24);
    BabyTree->Branch("HLT_Mu50", &HLT_Mu50);
    BabyTree->Branch("HLT_Mu55", &HLT_Mu55);
    BabyTree->Branch("HLT_TkMu50", &HLT_TkMu50);
    BabyTree->Branch("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg", &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg);
    BabyTree->Branch("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg", &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg);
    BabyTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg);
    BabyTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg", &HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg", &HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_TrailingLeg", &HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_TrailingLeg);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_LeadingLeg", &HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_LeadingLeg);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_TrailingLeg", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_TrailingLeg);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_LeadingLeg", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_LeadingLeg);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_TrailingLeg", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_TrailingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_LeadingLeg", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_LeadingLeg);
    BabyTree->Branch("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg);
    BabyTree->Branch("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_TrailingLeg", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_TrailingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_LeadingLeg", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_LeadingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg);
    BabyTree->Branch("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg", &HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg);
    BabyTree->Branch("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg", &HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_TrailingLeg", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_TrailingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_LeadingLeg", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_LeadingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_TrailingLeg", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_TrailingLeg);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_LeadingLeg", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_LeadingLeg);
    //Single Electron Triggers
    BabyTree->Branch("HLT_Ele8_CaloIdM_TrackIdM_PFJet30", &HLT_Ele8_CaloIdM_TrackIdM_PFJet30);
    BabyTree->Branch("HLT_Ele12_CaloIdM_TrackIdM_PFJet30", &HLT_Ele12_CaloIdM_TrackIdM_PFJet30);
    BabyTree->Branch("HLT_Ele17_CaloIdM_TrackIdM_PFJet30", &HLT_Ele17_CaloIdM_TrackIdM_PFJet30);
    BabyTree->Branch("HLT_Ele23_CaloIdM_TrackIdM_PFJet30", &HLT_Ele23_CaloIdM_TrackIdM_PFJet30);
    BabyTree->Branch("HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30);
    BabyTree->Branch("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30);
    BabyTree->Branch("HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30);
    BabyTree->Branch("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30);
    BabyTree->Branch("HLT_Ele27_eta2p1_WPTight_Gsf", &HLT_Ele27_eta2p1_WPTight_Gsf);
    BabyTree->Branch("HLT_Ele32_eta2p1_WPTight_Gsf", &HLT_Ele32_eta2p1_WPTight_Gsf);
    BabyTree->Branch("HLT_Ele105_CaloIdVT_GsfTrkIdT", &HLT_Ele105_CaloIdVT_GsfTrkIdT);
    BabyTree->Branch("HLT_Ele115_CaloIdVT_GsfTrkIdT", &HLT_Ele115_CaloIdVT_GsfTrkIdT);
    //Double Electron Triggers
    BabyTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_L1", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_L1);
    BabyTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
    BabyTree->Branch("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_L1", &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_L1);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
    BabyTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL);
    BabyTree->Branch("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ);
    BabyTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
    BabyTree->Branch("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
    BabyTree->Branch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
    BabyTree->Branch("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL);
    BabyTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    BabyTree->Branch("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
}

//___________________________________________________________________________________________________________________________________________
void babyMaker::InitBabyNtuple()
{
    //General
    evt_pfmet = -1;
    evt_pfmetPhi = -99.;
    evt_trackmet = -1;
    evt_trackmetPhi = -99;
    evt_corrMET = -1;
    evt_corrMETPhi = -99.;
    evt_corrMET_up = -1;
    evt_corrMET_dn = -1;
    evt_corrMETPhi_up = -99.;
    evt_corrMETPhi_dn = -99.;
    evt_pfsumet = -1;
    evt_pfmetSig = -1;
    evt_event = -1;
    evt_lumiBlock = -1;
    evt_run = -1;
    filt_csc = 0;
    filt_hbhe = 0;
    passes_met_filters = 0;
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
    ht_SS = -1;
    sample = "";
    nFOs_SS = -1;
    nvtx = -1;
    pu_ntrue = -1;
    instantLumi = -1;
    rho = -1;
    rho_calo = -1;
    rho_calo_centr = -1;
    jets.clear();
    jets_disc.clear();
    jets_area.clear();
    jets_undoJEC.clear();
    jets_unc.clear();
    InitLeptonBranches();
}

//___________________________________________________________________________________________________________________________________________
void babyMaker::InitLeptonBranches()
{
    //Leptons
    p4 = LorentzVector(0, 0, 0, 0);
    tag_p4 = LorentzVector(0, 0, 0, 0);
    dilep_p4 = LorentzVector(0, 0, 0, 0);
    mc_p4 = LorentzVector(0, 0, 0, 0);
    mc_motherp4 = LorentzVector(0, 0, 0, 0);
    mc_motherid = -1;
    id = -1;
    isPF = false;
    idx = -1;
    dxyPV = -1;
    dZ = -1;
    dxyPV_err = -1;
    motherID = -1;
    mc_id = -1;
    RelIso03 = -1;
    RelIso03EA = -1;
    RelIso03EAv2 = -1;
    RelIso04EAv2 = -1;
    tag_RelIso03EA = -1;
    RelIso03DB = -1;
    pfChargedHadronIso = -1;
    pfPhotonIso = -1;
    pfNeutralHadronIso = -1;
    tkIso = -1;
    sumPUPt = -1;
    passes_SS_tight_v3 = 0;
    passes_SS_tight_noiso_v3 = 0;
    passes_SS_fo_v3 = 0;
    passes_SS_fo_noiso_v3 = 0;
    passes_SS_fo_looseMVA_v3 = 0;
    passes_SS_fo_looseMVA_noiso_v3 = 0;
    passes_SS_veto_v3 = 0;
    passes_SS_veto_noiso_v3 = 0;
    passes_SS_tight_v4 = 0;
    passes_SS_tight_noiso_v4 = 0;
    passes_SS_fo_v4 = 0;
    passes_SS_fo_noiso_v4 = 0;
    passes_SS_fo_looseMVA_v4 = 0;
    passes_SS_fo_looseMVA_noiso_v4 = 0;
    passes_SS_veto_v4 = 0;
    passes_SS_veto_noiso_v4 = 0;
    passes_SS_tight_v5 = 0;
    passes_SS_tight_noiso_v5 = 0;
    passes_SS_fo_v5 = 0;
    passes_SS_fo_noiso_v5 = 0;
    passes_SS_fo_looseMVA_v5 = 0;
    passes_SS_fo_looseMVA_noiso_v5 = 0;
    passes_SS_veto_v5 = 0;
    passes_SS_veto_noiso_v5 = 0;
    passes_WW_medium_v2 = 0;
    passes_WW_medium_noiso_v2 = 0;
    passes_WW_fo_v2 = 0;
    passes_WW_fo_noiso_v2 = 0;
    passes_WW_veto_v2 = 0;
    passes_WW_veto_noiso_v2 = 0;
    passes_HAD_veto_v3 = 0;
    passes_HAD_veto_noiso_v3 = 0;
    passes_HAD_loose_v3 = 0;
    passes_HAD_loose_noiso_v3 = 0;
    passes_VVV_cutbased_veto_bak1 = 0;
    passes_VVV_cutbased_veto_noiso_bak1 = 0;
    passes_VVV_cutbased_veto_noiso_noip_bak1 = 0;
    passes_VVV_cutbased_veto = 0;
    passes_VVV_cutbased_veto_noiso = 0;
    passes_VVV_cutbased_veto_noiso_noip = 0;
    passes_VVV_cutbased_fo = 0;
    passes_VVV_cutbased_fo_noiso = 0;
    passes_VVV_baseline = 0;
    passes_VVV_MVAbased_tight = 0;
    passes_VVV_MVAbased_tight_noiso = 0;
    passes_VVV_cutbased_tight = 0;
    passes_VVV_cutbased_tight_noiso = 0;
    passes_POG_vetoID = 0;
    passes_POG_looseID = 0;
    passes_POG_mediumID = 0;
    passes_POG_tightID = 0;
    passes_isTriggerSafe_v1 = 0;
    passes_isTriggerSafe_v2 = 0;
    type = -1;
    ip3d = -1;
    ip3derr = -1;
    mt = -1;
    ptrelv0 = -1;
    ptrelv1 = -1;
    miniiso = -1;
    miniisoDB = -1;
    reliso04 = -1;
    annulus04 = -1;
    AbsTrkIso = -1;
    TrkAn04 = -1;
    iso03sumPt = -1;
    iso03emEt = -1;
    iso03hadEt = -1;
    jet_close_lep_idx = -1;
    jet_close_lep = LorentzVector(0, 0, 0, 0);
    jet_close_lep_undoJEC = -1;
    jet_close_lep_area = -1;
    jet_close_L1 = -1;
    jet_close_L1nc = -1;
    jet_close_L1ncmc = -1;
    jet_close_L1L2L3 = -1;
    jet_close_L2L3 = -1;
    ptratio = -1;
    dilep_mass = -1.;
    isRandom = false;
    //Tag variables
    tag_charge = 0.;
    tag_mc_motherid = 0.;
    tag_eSeed = -1;
    tag_eSCRaw = -1;
    tag_eSC = -1;
    tag_ecalEnergy = -1;
    tag_HLT_Ele27_eta2p1_WPTight_Gsf = 0;
    tag_HLT_Ele32_eta2p1_WPTight_Gsf = 0;
    tag_HLT_IsoMu24 = 0;
    tag_HLT_IsoTkMu24 = 0;
    //Muons
    pid_PFMuon = -1;
    gfit_chi2 = -1;
    // gfit_ndof = -1;
    gfit_validSTAHits = -1;
    numberOfMatchedStations = -1;
    validPixelHits = -1;
    nlayers = -1;
    chi2LocalPosition = -99;
    trkKink = -99;
    validHits = -99;
    lostHits = -99;
    exp_outerlayers = -99;
    segmCompatibility = -99;
    ptErr = -99;
    trk_pt = -99;
    //Electrons
    sigmaIEtaIEta_full5x5 = -1;
    sigmaIEtaIEta = -1;
    etaSC = -1;
    dEtaIn = -1;
    dPhiIn = -99;
    hOverE = -1;
    eSeed = -1;
    eSC = -1;
    eSCRaw = -1;
    scSeedEta = -1;
    ecalEnergy = -1;
    eOverPIn = -1;
    conv_vtx_flag = 0;
    exp_innerlayers = -1;
    charge = 0;
    sccharge = 0;
    ckf_charge = 0;
    trk_charge = 0;
    threeChargeAgree_branch = 0;
    mva = -999.;
    mva_25ns = -999.;
    tag_mva_25ns = -999.;
    ecalIso = -1;
    hcalIso = -1;
    ecalPFClusterIso = -1;
    hcalPFClusterIso = -1;
    ckf_laywithmeas = -1;
    sigmaIPhiIPhi_full5x5 = -1;
    e1x5_full5x5 = -1;
    e5x5_full5x5 = -1;
    r9_full5x5 = -1;
    tag_r9_full5x5 = -1;
    etaSCwidth = -1;
    phiSCwidth = -1;
    eSCRaw = -1;
    eSC = -1;
    ecalEnergy = -1;
    eSCPresh = -1;
    ckf_chi2 = -1;
    ckf_ndof = -1;
    chi2 = -1;
    ndof = -1;
    fbrem = -1;
    eOverPOut = -1;
    dEtaOut = -1;
    dPhiOut = -1;
    gsf_validHits = -1;
    conv_vtx_prob = -1;
    //Single Muon Trigger
    HLT_Mu8_TrkIsoVVL = 0;
    HLT_Mu17_TrkIsoVVL = 0;
    HLT_Mu8 = 0;
    HLT_Mu17 = 0;
    HLT_IsoMu24 = 0;
    HLT_IsoTkMu24 = 0;
    HLT_Mu50 = 0;
    HLT_Mu55 = 0;
    HLT_TkMu50 = 0;
    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg = 0;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg = 0;
    HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_TrailingLeg = 0;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_LeadingLeg = 0;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_TrailingLeg = 0;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_LeadingLeg = 0;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg = 0;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg = 0;
    HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg = 0;
    HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg = 0;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_TrailingLeg = 0;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_LeadingLeg = 0;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_TrailingLeg = 0;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_LeadingLeg = 0;
    // Di lepton triggers
    HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = 0;
    HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL = 0;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = 0;
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = 0;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = 0;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = 0;
    HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = 0;
    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = 0;
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = 0;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = 0;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = 0;
    HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = 0;
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = 0;
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = 0;
    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL = 0;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = 0;
    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = 0;
    //Single Electron Trigger
    HLT_Ele8_CaloIdM_TrackIdM_PFJet30 = 0;
    HLT_Ele12_CaloIdM_TrackIdM_PFJet30 = 0;
    HLT_Ele17_CaloIdM_TrackIdM_PFJet30 = 0;
    HLT_Ele23_CaloIdM_TrackIdM_PFJet30 = 0;
    HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30 = 0;
    HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 = 0;
    HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30 = 0;
    HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 = 0;
    HLT_Ele27_eta2p1_WPTight_Gsf = 0;
    HLT_Ele32_eta2p1_WPTight_Gsf = 0;
    HLT_Ele105_CaloIdVT_GsfTrkIdT = 0;
    HLT_Ele115_CaloIdVT_GsfTrkIdT = 0;
    //Double Electron Trigger
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg = 0;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg = 0;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_L1 = 0;
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = 0;
    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_L1 = 0;
    //MuEl Trigger
    HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300 = 0;
    //Double Muon Trigger
    HLT_DoubleMu8_Mass8_PFHT300 = 0;
}

//___________________________________________________________________________________________________________________________________________
bool babyMaker::checkMuonTag(unsigned int i, bool oldTag)
{
    for (unsigned int j = 0; j < tas::mus_p4().size(); j++)
    {
        // Tag muon selection
        if (i == j)  { continue; }
        if (tas::mus_p4().at(j).pt() < 20.0)  { continue; }
        if (fabs(tas::mus_p4().at(j).eta()) > 2.4)  { continue; }
        if (fabs(tas::mus_dxyPV().at(j)) > 0.02)  { continue; }
        if (fabs(tas::mus_dzPV().at(j)) > 0.05)  { continue; }
        if (fabs(tas::mus_ip3d().at(j)
                    / tas::mus_ip3derr().at(j)) > 4)  { continue; }
        if (!isTightMuonPOG(j))  { continue; }
        if (muRelIso03EA(j) > 0.2)  { continue; }
        // Retrieve tag muon information
        tag_p4 = tas::mus_p4().at(j);
        tag_charge = tas::mus_charge().at(j);
        tag_RelIso03EA = muRelIso03EA(j);
        // If MC, get the motherID of the tag
        if (!evt_isRealData) { tag_mc_motherid = tas::mus_mc_motherid().at(j); }
        // Set the branch of the tag muons single lepton trigger bit
        setHLTBranch("HLT_IsoMu24_v", (j >= 0 ? tas::mus_HLT_IsoMu24().at(j) : 0), tag_HLT_IsoMu24);
        setHLTBranch("HLT_IsoTkMu24_v", (j >= 0 ? tas::mus_HLT_IsoTkMu24().at(j) : 0), tag_HLT_IsoTkMu24);
        //Randomize if needed
        if (usedMu == false && ((rndm < 0.5 && tag_charge < 0) || (rndm >= 0.5 && tag_charge > 0)))
        {
            isRandom = true;
            usedMu = true;
        }
        else
        {
            isRandom = false;
        }
        // Exit with true when tag muon found
        return true;
    }
    return false;
}

//___________________________________________________________________________________________________________________________________________
bool babyMaker::checkElectronTag(unsigned int i, readMVA* v25nsMVAreader)
{
    for (unsigned int j = 0; j < tas::els_p4().size(); j++)
    {
        // Tag electron selection
        if (i == j)  { continue; }
        if (tas::els_p4().at(j).pt() < 20.0)  { continue; }
        if (fabs(tas::els_etaSC().at(j)) > 2.5)  { continue; }
        if (!tas::els_passMediumId().at(j))  { continue; }
        if (fabs(tas::els_ip3d().at(j)
                    / tas::els_ip3derr().at(j)) > 4)  { continue; }
        // Retreive tag electron information
        tag_p4 = tas::els_p4().at(j);
        tag_charge = tas::els_charge().at(j);
        tag_eSeed = tas::els_eSeed().at(j);
        tag_eSCRaw = tas::els_eSCRaw().at(j);
        tag_eSC = tas::els_eSC().at(j);
        tag_ecalEnergy = tas::els_ecalEnergy().at(j);
        tag_r9_full5x5 = tas::els_r9_full5x5().at(j);
        if (v25nsMVAreader != 0)  { tag_mva_25ns = v25nsMVAreader->MVA(j); }
        tag_RelIso03EA = eleRelIso03EA(j);
        // If MC, get the motherID of the tag
        if (!evt_isRealData)
        { tag_mc_motherid = tas::els_mc_motherid().at(j); }
        // Set the branch of the tag electrons single lepton trigger bit
        setHLTBranch("HLT_Ele27_eta2p1_WPTight_Gsf_v", (j >= 0 ? tas::els_HLT_Ele27_eta2p1_WPTight_Gsf().at(j) : 0), tag_HLT_Ele27_eta2p1_WPTight_Gsf);
        setHLTBranch("HLT_Ele32_eta2p1_WPTight_Gsf_v", (j >= 0 ? tas::els_HLT_Ele32_eta2p1_WPTight_Gsf().at(j) : 0), tag_HLT_Ele32_eta2p1_WPTight_Gsf);
        // Randomize if needed
        if (usedEl == false && ((rndm < 0.5 && tag_charge < 0) || (rndm >= 0.5 && tag_charge > 0)))
        {
            isRandom = true;
            usedEl = true;
        }
        else
        {
            isRandom = false;
        }
        // Return true when tag electron found
        return true;
    }
    return false;
}

//___________________________________________________________________________________________________________________________________________
// To check whether a muon is a PF cand, match the candidate to a PF via deltaR matching
int babyMaker::isPFmuon(vector<LorentzVector> &pfP4, vector<bool> &pfmuIsReco, int idx)
{
    for (size_t i = 0; i < pfP4.size(); i++)
    {
        float dR2 = ROOT::Math::VectorUtil::DeltaR2(pfP4[i], tas::mus_p4().at(idx));
        if (dR2 < 0.0025)
        {
            pfmuIsReco[i] = true;
            return i;
        }
    }
    return -1;
}

//___________________________________________________________________________________________________________________________________________
// To check whether a muon is a PF cand, match the candidate to a PF via deltaR matching
int babyMaker::isPFelectron(vector<LorentzVector> &pfP4, vector<bool> &pfelIsReco, int idx)
{
    for (size_t i = 0; i < pfP4.size(); i++)
    {
        float dR2 = ROOT::Math::VectorUtil::DeltaR2(pfP4[i], tas::els_p4().at(idx));
        if (dR2 < 0.0025)
        {
            pfelIsReco[i] = true;
            return i;
        }
    }
    return -1;
}

//___________________________________________________________________________________________________________________________________________
// NJA June 6, 2016: some triggers matching p4 to last path will match jet and not lepton, so explicitly check match here
void babyMaker::alternativeFilterMatch(LorentzVector &p4, const char* trigName, const char* filtName, int& HLTbranch)
{
    if (abs(HLTbranch) == 0) { return; } // if we didn't previously see that we fired the trigger (1 or -1), give up and go home
    float test = 0;
    HLTbranch = matchToHLTFilter(trigName, filtName, p4, 0.2, &test);
}

//___________________________________________________________________________________________________________________________________________
void babyMaker::fillElectronTriggerBranches(LorentzVector &p4, int idx, bool oldTag)
{
    if (idx == -1) { return; }
    //Single Electron Trigger with Jet
    setHLTBranch("HLT_Ele8_CaloIdM_TrackIdM_PFJet30_v", tas::els_HLT_Ele8_CaloIdM_TrackIdM_PFJet30_ElectronLeg().at(idx), HLT_Ele8_CaloIdM_TrackIdM_PFJet30);
    setHLTBranch("HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v", tas::els_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_ElectronLeg().at(idx), HLT_Ele12_CaloIdM_TrackIdM_PFJet30);
    setHLTBranch("HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v", tas::els_HLT_Ele17_CaloIdM_TrackIdM_PFJet30_ElectronLeg().at(idx), HLT_Ele17_CaloIdM_TrackIdM_PFJet30);
    setHLTBranch("HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v", tas::els_HLT_Ele23_CaloIdM_TrackIdM_PFJet30_ElectronLeg().at(idx), HLT_Ele23_CaloIdM_TrackIdM_PFJet30);
    setHLTBranch("HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v", tas::els_HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg().at(idx), HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30);
    setHLTBranch("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v", tas::els_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg().at(idx), HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30);
    setHLTBranch("HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v", tas::els_HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg().at(idx), HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30);
    setHLTBranch("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v", tas::els_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_ElectronLeg().at(idx), HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30);
    //Single Electron Trigger
    setHLTBranch("HLT_Ele27_eta2p1_WPTight_Gsf_v", tas::els_HLT_Ele27_eta2p1_WPTight_Gsf().at(idx), HLT_Ele27_eta2p1_WPTight_Gsf);
    setHLTBranch("HLT_Ele32_eta2p1_WPTight_Gsf_v", tas::els_HLT_Ele32_eta2p1_WPTight_Gsf().at(idx), HLT_Ele32_eta2p1_WPTight_Gsf);
    setHLTBranch("HLT_Ele105_CaloIdVT_GsfTrkIdT_v", tas::els_HLT_Ele105_CaloIdVT_GsfTrkIdT().at(idx), HLT_Ele105_CaloIdVT_GsfTrkIdT);
    setHLTBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT_v", tas::els_HLT_Ele115_CaloIdVT_GsfTrkIdT().at(idx), HLT_Ele115_CaloIdVT_GsfTrkIdT);
    setHLTBranch("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v", tas::els_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL().at(idx), HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL);
//    setHLTBranch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", tas::els_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ().at(idx), HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
//    setHLTBranch("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", tas::els_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ().at(idx), HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg = tas::els_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg().at(idx);
    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg = tas::els_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg().at(idx);
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg = tas::els_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_TrailingLeg().at(idx);
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg = tas::els_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_LeadingLeg().at(idx);
}

//___________________________________________________________________________________________________________________________________________
void babyMaker::fillMuonTriggerBranches(LorentzVector &p4, int idx, bool oldTag)
{
    //temporary until we run on mc with the new tag
    if (oldTag) { idx = -1; }
    if (idx == -1) { return; }
    //Single Muon Triggers
    setHLTBranch("HLT_Mu8_v", tas::mus_HLT_Mu8().at(idx), HLT_Mu8);
    setHLTBranch("HLT_Mu17_v", tas::mus_HLT_Mu17().at(idx), HLT_Mu17);
    setHLTBranch("HLT_Mu8_TrkIsoVVL_v", tas::mus_HLT_Mu8_TrkIsoVVL().at(idx), HLT_Mu8_TrkIsoVVL);
    setHLTBranch("HLT_Mu17_TrkIsoVVL_v", tas::mus_HLT_Mu17_TrkIsoVVL().at(idx), HLT_Mu17_TrkIsoVVL);
    setHLTBranch("HLT_IsoMu24_v", tas::mus_HLT_IsoMu24().at(idx), HLT_IsoMu24);
    setHLTBranch("HLT_IsoTkMu24_v", tas::mus_HLT_IsoTkMu24().at(idx), HLT_IsoTkMu24);
    setHLTBranch("HLT_Mu50_v", tas::mus_HLT_Mu50().at(idx), HLT_Mu50);
    setHLTBranch("HLT_Mu55_v", tas::mus_HLT_Mu55().at(idx), HLT_Mu55);
    setHLTBranch("HLT_TkMu50_v", tas::mus_HLT_TkMu50().at(idx), HLT_TkMu50);
    setHLTBranch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", tas::mus_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ().at(idx), HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
    setHLTBranch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", tas::mus_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ().at(idx), HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
    setHLTBranch("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", tas::mus_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ().at(idx), HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
    setHLTBranch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v", tas::mus_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL().at(idx), HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
    setHLTBranch("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v", tas::mus_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL().at(idx), HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_TrailingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_TrailingLeg().at(idx);
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_LeadingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_LeadingLeg().at(idx);
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg().at(idx);
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg().at(idx);
    HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg = tas::mus_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_TrailingLeg().at(idx); // ALways turned off?
    HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg = tas::mus_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_LeadingLeg().at(idx); // ALways turned off?
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_TrailingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_TrailingLeg().at(idx);
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_LeadingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_LeadingLeg().at(idx);
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_TrailingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_TrailingLeg().at(idx);
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_LeadingLeg = tas::mus_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_LeadingLeg().at(idx);
}

//___________________________________________________________________________________________________________________________________________
int babyMaker::pfLepMotherID(int pfidx)
{
    for (unsigned int j = 0; j < tas::genps_id().size(); j++)
    {
        if (tas::genps_id().at(j) != tas::pfcands_particleId().at(pfidx)) { continue; }
        if (tas::genps_p4().at(j).pt() < 2) { continue; }
        if (!tas::genps_isPromptFinalState().at(j)) { continue; }
        if (ROOT::Math::VectorUtil::DeltaR(tas::pfcands_p4().at(pfidx), tas::genps_p4().at(j)) > 0.1) { continue; }
        // Found good match
        return 1;
    }
    return 0;
}

//___________________________________________________________________________________________________________________________________________
void babyMaker::SetOutputPath(std::string outputpath)
{
    path = outputpath;
}
