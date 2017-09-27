#include "fakeratelooper.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//usage: ./main.exe QCD_Test 1000 1 ./

vector<TString> load(const char *type, char *input){

  vector<TString> output;
  char buffer[400];
  char StringValue[1000];
  ifstream IN(input);
  while( IN.getline(buffer, 400, '\n') ){
    // ok = false;
    if (buffer[0] == '#') {
      continue; // Skip lines commented with '#'
    }
    if( !strcmp(buffer, "SAMPLE")){
      bool add = false;
      IN.getline(buffer, 400, '\n');
      sscanf(buffer, "Name\t%s", StringValue);
      if((string)StringValue==(string)type) add=true;
      IN.getline(buffer, 400, '\n');
      sscanf(buffer, "Path\t%s", StringValue);
      if(add){
	std::ostringstream addStream;
	addStream << StringValue;
	TString addString = addStream.str().c_str();
	output.push_back(addString);
      }
    }
  }
  return output;
}

bool doesFileExist(TString fname, bool useXrootd) {
  if(useXrootd) {
    return system(Form("lcg-ls -b -D srmv2 \"srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=%s\" > /dev/null", fname.Data())) == 0;
  } else {
    std::ifstream infile(fname.Data());
    return infile.good();
  }
}

int main(int argc, char **argv)
  try{
    TString sample = "";
    babyMaker *mylooper = new babyMaker();
    TChain *result = new TChain("Events");
    char *input = "philip_sample.dat";

    if (argc < 2) {
//      sample = "default";
//      cout<<"Using default file. "<<endl;
      cout<<"ERROR - Check your arguments:"<<endl;
      cout<<"Usage: ./main.exe SAMPLE NEVENTS [FILENUMBER=default runs over all files in the sample]"<<endl;
      return 0;
    }
    else {
      sample = (TString) argv[1];
      cout<<"Using files corresponding to sample "<<sample<<endl;
    }

    int nevents = -1;
    if (sample == "default") nevents = 100;
    if (argc < 3) {
      cout<<"Number of events not specified. Running over "<<nevents<<" events"<<endl;
    }
    else {
      TString n = (TString) argv[2];
      nevents = n.Atoi();
      cout<<"Running over "<<nevents<<" events"<<endl;
    }

    int file=0;
    if (argc < 4) {
      cout<<"File number not specified. Running over all files "<<endl;
    }
    else {
      file = atoi(argv[3]);
    }
    // const char* filename = (file == 0 ? "merged_ntuple_*.root" : Form("merged_ntuple_%i.root", file));
    TString filename = TString(file == 0 ? "merged_ntuple_*.root" : Form("merged_ntuple_%i.root", file));
    cout<<"Running over files with names "<<filename<<endl;
    TString suffix = TString(file == 0 ? "" : Form("_%i", file));

    string dirpath = "./";  
    if (argc < 5) {
      cout<<"No directory specified, default ./" <<endl;
    } else {
      dirpath = argv[4];
      cout<<"Output directory is" << dirpath <<endl;
    }

    bool useXrootd = true;
    if (system("hostname | grep ucsd") == 0) {
        std::cout << "Based on your hostname, you are on UCSD, so turning xrootd accessing off!" << std::endl;
        useXrootd = false;
    }
    
    vector<TString> samplelist = load(sample.Data(), input);//new
    if(samplelist.size()==0) cout<<"Could not find files corresponding to sample "<<sample<<endl;
    for(unsigned int i = 0; i<samplelist.size(); ++i){

      if (doesFileExist(samplelist[i], useXrootd)) {
        if(!(samplelist[i].Contains(".root"))) {
          samplelist[i] = samplelist[i] + filename;
          if (!doesFileExist(samplelist[i], useXrootd) && !(TString(filename).Contains("*"))) {
            cout << "Warning! File: " << samplelist[i] << " does not exist. Not added to files to be processed." << endl;
            continue;
          }
        }
        cout << "Add sample " << samplelist[i] << " to files to be processed." << endl;
        if(useXrootd) {
          TString pfn = samplelist[i].ReplaceAll("/hadoop/cms", "root://cmsxrootd.fnal.gov/");
          std::cout << pfn << std::endl;
          result->Add(pfn);
        } else {
          result->Add(samplelist[i].Data());
        }
      } else {
        cout << "Warning! File: " << samplelist[i] << " does not exist ab exist. Not added to files to be processed." << endl;
      }
    }

    mylooper->SetOutputPath(dirpath);
    mylooper->looper(result, Form("%s%s", sample.Data(),suffix.Data()), nevents);
    return 0;

  }
  catch (std::exception& e)
    {
      std::cerr << "[LeptonBabyMaker] Error: failed..." << std::endl;
      std::cerr << e.what() << std::endl;
      return 1;
    }


