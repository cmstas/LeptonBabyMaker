#!/bin/env python

import time
import json

from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask

from metis.StatsParser import StatsParser

import sys
import os

# Configurations
job_tag = "2016_tnp_sample_v1"
exec_path = "run.sh"
tar_path = "package.tar.gz"
hadoop_path = "metis/lepbaby/{}".format(job_tag)
args = "dummy output.root Events -1 dummy" # dummy arguments are there because the executable run.sh was copied from another framework.

# Get into the directory where this lepmetis.py sits. So we can tar up the condor package.
os.system("tar -czvf package.tar.gz fakeratelooper.h fakeratelooper.C main.C LinkDef.h sample.dat Makefile CORE goodRunList run.C run.sh root.sh hadoopmap.cc hadoopmap.txt")

dslocs = [
    ["/ZZ"                                                , "/hadoop/cms/store/group/snt/run2_moriond17/EWK_LNuJJ_MJJ-120_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ] , 
    ["/DY"                                                , "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/V08-00-16/" ] , 
    ["/Run2016B_SingleElectron_MINIAOD_03Feb2017_ver2-v2" , "/nfs-7/userdata/dataTuple/kludge/Run2016B_SingleElectron_MINIAOD_03Feb2017_ver2-v2/merged/V08-00-18/"                                                                         ] , 
    ["/Run2016C_SingleElectron_MINIAOD_03Feb2017-v1"      , "/nfs-7/userdata/dataTuple/kludge/Run2016C_SingleElectron_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                              ] , 
    ["/Run2016D_SingleElectron_MINIAOD_03Feb2017-v1"      , "/nfs-7/userdata/dataTuple/kludge/Run2016D_SingleElectron_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                              ] , 
    ["/Run2016E_SingleElectron_MINIAOD_03Feb2017-v1"      , "/nfs-7/userdata/dataTuple/kludge/Run2016E_SingleElectron_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                              ] , 
    ["/Run2016F_SingleElectron_MINIAOD_03Feb2017-v1"      , "/nfs-7/userdata/dataTuple/kludge/Run2016F_SingleElectron_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                              ] , 
    ["/Run2016G_SingleElectron_MINIAOD_03Feb2017-v1"      , "/nfs-7/userdata/dataTuple/kludge/Run2016G_SingleElectron_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                              ] , 
    ["/Run2016H_SingleElectron_MINIAOD_03Feb2017_ver2-v1" , "/nfs-7/userdata/dataTuple/kludge/Run2016H_SingleElectron_MINIAOD_03Feb2017_ver2-v1/merged/V08-00-18/"                                                                         ] , 
    ["/Run2016H_SingleElectron_MINIAOD_03Feb2017_ver3-v1" , "/nfs-7/userdata/dataTuple/kludge/Run2016H_SingleElectron_MINIAOD_03Feb2017_ver3-v1/merged/V08-00-18/"                                                                         ] , 
    ["/Run2016B_SingleMuon_MINIAOD_03Feb2017_ver2-v2"     , "/nfs-7/userdata/dataTuple/kludge/Run2016B_SingleMuon_MINIAOD_03Feb2017_ver2-v2/merged/V08-00-18/"                                                                             ] , 
    ["/Run2016C_SingleMuon_MINIAOD_03Feb2017-v1"          , "/nfs-7/userdata/dataTuple/kludge/Run2016C_SingleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                                  ] , 
    ["/Run2016D_SingleMuon_MINIAOD_03Feb2017-v1"          , "/nfs-7/userdata/dataTuple/kludge/Run2016D_SingleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                                  ] , 
    ["/Run2016E_SingleMuon_MINIAOD_03Feb2017-v1"          , "/nfs-7/userdata/dataTuple/kludge/Run2016E_SingleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                                  ] , 
    ["/Run2016F_SingleMuon_MINIAOD_03Feb2017-v1"          , "/nfs-7/userdata/dataTuple/kludge/Run2016F_SingleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                                  ] , 
    ["/Run2016G_SingleMuon_MINIAOD_03Feb2017-v1"          , "/nfs-7/userdata/dataTuple/kludge/Run2016G_SingleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/"                                                                                  ] , 
    ["/Run2016H_SingleMuon_MINIAOD_03Feb2017_ver2-v1"     , "/nfs-7/userdata/dataTuple/kludge/Run2016H_SingleMuon_MINIAOD_03Feb2017_ver2-v1/merged/V08-00-18/"                                                                             ] , 
    ["/Run2016H_SingleMuon_MINIAOD_03Feb2017_ver3-v1"     , "/nfs-7/userdata/dataTuple/kludge/Run2016H_SingleMuon_MINIAOD_03Feb2017_ver3-v1/merged/V08-00-18/"                                                                             ] , 
]

total_summary = {}
while True:
    allcomplete = True
    for ds,loc in dslocs:
        task = CondorTask(
                sample = DirectorySample( dataset=ds, location=loc ),
                open_dataset = False,
                flush = True,
                files_per_output = 1,
                output_name = "merged.root",
                tag = job_tag,
                cmssw_version = "CMSSW_9_2_1", # doesn't do anything
                arguments = args,
                executable = exec_path,
                tarfile = tar_path,
                special_dir = hadoop_path
                )
        task.process()
        allcomplete = allcomplete and task.complete()
        # save some information for the dashboard
        total_summary[ds] = task.get_task_summary()
    # parse the total summary and write out the dashboard
    StatsParser(data=total_summary, webdir="~/public_html/dump/lepmetis/").do()
    os.system("chmod -R 755 ~/public_html/dump/lepmetis")
    if allcomplete:
        print ""
        print "Job={} finished".format(job_tag)
        print ""
        break
    print "Sleeping 300 seconds ..."
    time.sleep(300)
