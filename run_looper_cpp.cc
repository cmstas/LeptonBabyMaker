#include "fakeratelooper.h"
#include "TSystem.h"

int main(int argc, char **argv)
  try
    {std::cout<<__LINE__<<std::endl;
      //gSystem->Load("CORE/CMS3_CORE.so");std::cout<<__LINE__<<std::endl;
      //gSystem->Load("fakeratelooper.so"); std::cout<<__LINE__<<std::endl;
      babyMaker *mylooper = new babyMaker();std::cout<<__LINE__<<std::endl;
      TChain *result = new TChain("Events");std::cout<<__LINE__<<std::endl;
      result->Add("/hadoop/cms/store/user/gzevi/DoubleElectron/crab_DoubleElectron_CMSSW_7_4_0_pre9_ROOT6-GR_R_74_V8_1Apr_RelVal_zEl2012D-v1/cmssw_74x/merged/merged_ntuple_1.root");
      mylooper->looper(result, "na", 100);std::cout<<__LINE__<<std::endl;
      return 0;std::cout<<__LINE__<<std::endl;
    }
  catch (std::exception& e)
    {
      std::cerr << "[tnp_compare] Error: failed..." << std::endl;
      std::cerr << e.what() << std::endl;
      return 1;
    }
