#!/bin/bash

OUTPUTDIR=$1
OUTPUTNAME=$2
INPUTFILENAMES=$3
IFILE=$4
CMSSWVERSION=$5
SCRAMARCH=$6

# Make sure OUTPUTNAME doesn't have .root since we add it manually
OUTPUTNAME=$(echo $OUTPUTNAME | sed 's/\.root//')

echo -e "\n--- begin header output ---\n" #                     <----- section division
echo "OUTPUTDIR: $OUTPUTDIR"
echo "OUTPUTNAME: $OUTPUTNAME"
echo "INPUTFILENAMES: $INPUTFILENAMES"
echo "IFILE: $IFILE"
echo "CMSSWVERSION: $CMSSWVERSION"
echo "SCRAMARCH: $SCRAMARCH"

echo "hostname: $(hostname)"
echo "uname -a: $(uname -a)"
echo "time: $(date +%s)"
echo "args: $@"

echo -e "\n--- end header output ---\n" #                       <----- section division

source /cvmfs/cms.cern.ch/cmsset_default.sh

export SCRAM_ARCH=${SCRAMARCH}

eval `scramv1 project CMSSW $CMSSWVERSION`
cd $CMSSWVERSION
eval `scramv1 runtime -sh`
[ -e ../package.tar.gz ] && { 
    mv ../package.tar.gz package.tar.gz;
    tar xzf package.tar.gz;
}

echo "before running: ls -lrth"
ls -lrth 

echo -e "\n--- begin running ---\n" #                           <----- section division

echo Executing: python draw.py "$INPUTFILENAMES"
python draw.py "$INPUTFILENAMES"

echo -e "\n--- end running ---\n" #                             <----- section division

echo "after running: ls -lrth"
ls -lrth

echo -e "\n--- begin copying output ---\n" #                    <----- section division
echo "Sending output file $OUTPUTNAME.root"
gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTPUTNAME}.root gsiftp://gftp.t2.ucsd.edu${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root --checksum ADLER32
echo -e "\n--- end copying output ---\n" #                      <----- section division

