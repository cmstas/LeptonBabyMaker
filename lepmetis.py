import time
import glob

from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask
from metis.StatsParser import StatsParser

if __name__ == "__main__":

    for _ in range(10):
        print "MAKE SURE TO MAKE NEW TAR FILE and increment tag!"

    # tag = "v3" # v5 IDs
    # tag = "v4" # v6 IDs
    # tag = "v6" # back to v5 IDs but with nmisshits<=1
    # tag = "v8" # new EG ids with new EA and with nmisshits<=1
    tag = "v9" # new EG ids with new EA and with nmisshits<=1

    total_summary = {}

    samples = []
    dirs = []

    # dirs.extend(glob.glob("/hadoop/cms/store/group/snt/run2_data2017/SingleElectron_Run2017*-31Mar2018-v1_MINIAOD_CMS4_V09-04-12"))
    # dirs.extend(glob.glob("/hadoop/cms/store/group/snt/run2_data2017/DoubleMuon_Run2017*-31Mar2018-v1_MINIAOD_CMS4_V09-04-12"))
    # for thedir in dirs:
    #     dsname = "/FakeRate/{0}/LEPTON".format(thedir.split("/")[7].rsplit("_",3)[0])
    #     samples.append(
    #             DirectorySample(dataset=dsname, location=thedir)
    #             )
    samples.extend([
            DirectorySample(dataset="/FakeRate/WJets-2017v1/LEPTON", location="/hadoop/cms/store/group/snt/run2_mc2017/WJets*RunIIFall17MiniAODv2*_CMS4_V09-04-13"),
            # DirectorySample(dataset="/FakeRate/DYJets-2017v1/LEPTON", location="/hadoop/cms/store/group/snt/run2_mc2017//DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_CMS4_V09-04-13/"),
            # DirectorySample(dataset="/FakeRate/TTJets-2017v1/LEPTON", location="/hadoop/cms/store/group/snt/run2_mc2017//TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"),
            # DirectorySample(dataset="/FakeRate/QCD_EMEnriched-2017v1/LEPTON", location="/hadoop/cms/store/group/snt/run2_mc2017/QCD_*EMEnriched*CMS4_V09-04-13*/"),
            # DirectorySample(dataset="/FakeRate/QCD_MuEnriched-2017v1/LEPTON", location="/hadoop/cms/store/group/snt/run2_mc2017/QCD_*MuEnriched*CMS4_V09-04-13*/"),
            # DirectorySample(dataset="/FakeRate/QCD_bcToE-2017v1/LEPTON", location="/hadoop/cms/store/group/snt/run2_mc2017/QCD_*bcToE*CMS4_V09-04-13*/"),
            ])


    for _ in range(100):

        for sample in samples:

            baby_task = CondorTask(
                    sample = sample,
                    files_per_output = 3,
                    output_name = "output.root",
                    executable = "condor_fakerate_exe.sh",
                    special_dir = "fakerate/2017/ProjectMetis",
                    tag = tag,
                    cmssw_version = "CMSSW_9_2_8",
                    condor_submit_params = {"sites":"T2_US_UCSD"},
                    # condor_submit_params = {"use_xrootd":True},
                    publish_to_dis = False,
                    tarfile = "package.tar.gz",
            )

            hist_task = CondorTask(
                    sample = DirectorySample(
                        dataset=sample.get_datasetname().replace("LEPTON","HIST"),
                        location=baby_task.get_outputdir(),
                        ),
                    executable = "condor_hist.sh",
                    open_dataset = False,
                    files_per_output = 15,
                    output_name = "hists.root",
                    special_dir = "fakerate/2017/ProjectMetis",
                    condor_submit_params = {"sites":"T2_US_UCSD"},
                    output_is_tree = False,
                    check_expectedevents = False,
                    tag = tag,
                    cmssw_version = "CMSSW_9_2_8",
                    tarfile = "package_hists.tar.gz",
                    )

            baby_task.process()
            if baby_task.complete():
                hist_task.process()

            total_summary[baby_task.get_sample().get_datasetname()] = baby_task.get_task_summary()
            total_summary[hist_task.get_sample().get_datasetname()] = hist_task.get_task_summary()

        StatsParser(data=total_summary, webdir="~/public_html/dump/lepmetis/").do()

        time.sleep(2*60.*60)
