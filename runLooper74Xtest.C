#include "fakeratelooper.h"
void runLooper74Xtest() {
  //gSystem->Load("CORE/CMS3_CORE.so");
  //gSystem->Load("fakeratelooper.so"); 
  babyMaker *mylooper = new babyMaker();
  TChain *result = new TChain("Events");
  result->Add("/hadoop/cms/store/user/gzevi/DoubleElectron/crab_DoubleElectron_CMSSW_7_4_0_pre9_ROOT6-GR_R_74_V8_1Apr_RelVal_zEl2012D-v1/cmssw_74x/merged/merged_ntuple_1.root");
  mylooper->looper(result, (char*)"na", 100);
  return;
}
