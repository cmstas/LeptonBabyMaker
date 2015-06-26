#include "fakeratelooper.h"
#include "TSystem.h"
#include "TString.h"

int main(int argc, char **argv)
{

  TString outfile;
  TString infile;
  int nevents = -1;
  
  if (argc < 3) {
    std::cout << "USAGE: processBaby <input file> <output file>" << std::endl;
    std::cout<<"using default parameters, running over 100 events: "<<std::endl;
    std::cout<<"input file: /hadoop/cms/store/user/gzevi/DoubleElectron/crab_DoubleElectron_CMSSW_7_4_0_pre9_ROOT6-GR_R_74_V8_1Apr_RelVal_zEl2012D-v1/cmssw_74x/merged/merged_ntuple_1.root"<<std::endl;
    std::cout<<"output file: test.root"<<std::endl;
    infile="/hadoop/cms/store/user/gzevi/DoubleElectron/crab_DoubleElectron_CMSSW_7_4_0_pre9_ROOT6-GR_R_74_V8_1Apr_RelVal_zEl2012D-v1/cmssw_74x/merged/merged_ntuple_1.root";
    outfile="test.root";
    nevents = 100;
      
  }
  else {
    outfile=argv[1]; 
    infile=argv[2]; 
  }

  babyMaker *mylooper = new babyMaker();
  TChain *result = new TChain("Events");
  result->Add(infile.Data());
  mylooper->looper(result, (char*) outfile.Data(), nevents);
  return 0;
}
