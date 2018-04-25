# LeptonBabyMaker
one lepton babymaker for common SS+OS effort

Instructions for 9X

```
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_9_2_8
cmsenv
cd -
git clone https://github.com/cmstas/CORE
```

Then setup Metis for batch submission

```
git clone https://github.com/aminnj/ProjectMetis/
cd ProjectMetis
. setup.sh
```

Edit
* `fakeratelooper.C`, `fakeratelooper.h` as this is the main looper
* `draw.py` makes some helper histograms from output babies (if needed)
* `lepmetis.py` is the main submission script with sample definitions/locations

Compile with `make -j4` and test with 
```
./main.exe ntuplepath outputname nevents
```

Submit with 
```
. make_tar.sh
python lepmetis.py
```
