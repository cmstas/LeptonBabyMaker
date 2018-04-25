#include "fakeratelooper.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[]){

    TString filenames;
    char* outname = "output.root";
    int nevents_max = 0;
    // bool useXrootd = false;
    char hostnamestupid[100];
    gethostname(hostnamestupid, 100);
    TString hostname(hostnamestupid);
    std::cout << ">>> Hostname is " << hostname << std::endl;  
    bool useXrootd = !(hostname.Contains("t2.ucsd.edu"));
    if (hostname.Contains("uafino")) {
        std::cout << ">>> We're on uafino, so using xrootd!" << std::endl;  
        useXrootd = true;
    }
    useXrootd = true;

    if (argc > 1) filenames = TString(argv[1]);
    if (argc > 2) outname     = argv[2];
    if (argc > 3) nevents_max = atoi(argv[3]);

    std::cout << ">>> Args: " << std::endl;
    std::cout << "     filenames:    " << filenames << std::endl;
    std::cout << "     outname:     " << outname << std::endl;
    std::cout << "     nevents_max: " << nevents_max << std::endl;

    if (argc <= 1) { 
        std::cout << ">>> [!] Not enough arguments!" << std::endl;  
        return 0;
    }

    if (useXrootd) {
        filenames = filenames.ReplaceAll("/hadoop/cms", "root://cmsxrootd.fnal.gov/");
    }

    babyMaker *mylooper = new babyMaker();
    TChain *chain = new TChain("Events");
    string dirpath = "./";  

    TObjArray *files = filenames.Tokenize(",");
    for (Int_t i = 0; i < files->GetEntries(); i++)  {
        TString fname(((TObjString *)(files->At(i)))->String());
        std::cout << ">>> Adding file: " << fname << std::endl;  
        chain->Add(fname);
    }
    std::cout << ">>> Events in TChain: " << chain->GetEntries() << std::endl;  


    mylooper->SetOutputPath(dirpath);
    mylooper->looper(chain, outname, nevents_max);

    return 0;
}


/* vim: set ft=cpp: */
