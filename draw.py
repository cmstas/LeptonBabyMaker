import sys
import ROOT as r

# fpatts = "/hadoop/cms/store/user/namin/fakerate/2017/ProjectMetis/FakeRate_SingleElectron_Run2017F-PromptReco-v1_LEPTON_v1/output_*.root"
fpatts = sys.argv[-1]

ch = r.TChain("t")
for fpatt in fpatts.split(","):
    print "Adding {}".format(fpatt)
    ch.Add(fpatt)

ele_trigs = [
        "HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30",
        "HLT_Ele17_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30",
        "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30",
        "HLT_Ele23_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele8_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30",
        ]

mu_trigs = [
        "HLT_Mu17_TrkIsoVVL",
        "HLT_Mu17",
        "HLT_Mu8_TrkIsoVVL",
        "HLT_Mu8",
        "HLT_IsoMu27",  # unprescaled
        ]


trigs = []
ismc = False
if "SingleElectron" in fpatts:
    ismc = False
    trigs.extend(ele_trigs)
elif "DoubleMu" in fpatts:
    ismc = False
    trigs.extend(mu_trigs)
else:
    ismc = True
    trigs.extend(ele_trigs)
    trigs.extend(mu_trigs)

hists = []
for trigname in trigs:
    idlep = 11
    if "_Ele" in trigname or "_IsoE" in trigname:
        idlep = 11
    elif "_Mu" in trigname or "_IsoMu" in trigname:
        idlep = 13

    hname = "mll_{}".format(trigname)
    mult = "1"
    if ismc:
        mult = "41.3*scale1fb*puweight"
    mll = r.TH1F(hname,hname,80,0,200)
    mll.Sumw2()
    sel = "{}*{}*(abs(id)=={} && passes_SS_tight_v5 && {}>0 && tag_p4.pt()>30. && p4.pt()>25.)".format(mult,trigname,idlep,trigname)
    ch.Draw("dilep_mass>>{}".format(hname),sel,"e")
    h1 = r.gDirectory.Get(hname)
    hists.append(h1)
    print h1

f1 = r.TFile("hists.root","RECREATE")
[h.Write() for h in hists]
f1.Write()
f1.Close()
