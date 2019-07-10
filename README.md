
## Install

    eval $(ssh-agent -s)
    ssh-add ~/.ssh/id_rsa.pub
    git clone --recurse-submodules git@github.com:sgnoohc/WVZBabyMaker.git
    cd WVZBabyMaker
    source setup.sh
    make clean; make -j;

    # ./processBaby PATHTOCMS4ROOTFILE  NEVENTS  OUTPUT_FILE_INDEX  BABYMODE
    # NEVENTS=-1 (run over all events)
    # output file of ./processBaby is of the form output_<OUTPUT_FILE_INDEX>.root
    # BABYMODE=1 (>=4 lepton filtered, "WVZ" type sample)
    # BABYMODE=3 (>=3 lepton filtered, "Trilep" type sample)

    # For example
    ./processBaby /hadoop/cms/store/group/snt/run2_mc2018//WWZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2_MINIAODSIM_CMS4_V10-02-04/merged_ntuple_1.root -1 0 1

    # To submit 2018 years for WVZ
    python scripts/runMetis.py --tag v0.1.11 --sample_sets WVZ2018 -p

    # To submit all years for WVZ
    python scripts/runMetis.py --tag v0.1.11 --sample_sets WVZ2016,WVZ2017,WVZ2018 -p

    # To submit all years for Trilep samples (for fake lepton validation)
    python scripts/runMetis.py --tag v0.1.11 --sample_sets Trilep2016,Trilep2017,Trilep2018 -p
