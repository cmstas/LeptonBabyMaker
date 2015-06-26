#!/bin/bash

if [ "$USER" == "cgeorge" ]
then 
  ln -s /home/users/cgeorge/CORE . 
else 
  git clone git@github.com:cmstas/CORE.git
  cd CORE
  git checkout cmssw74x
  make -j 8
  cd ..
fi
