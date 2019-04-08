
## Install

    eval $(ssh-agent -s)
    ssh-add ~/.ssh/id_rsa.pub
    git clone --recurse-submodules git@github.com:sgnoohc/WVZBabyMaker.git
    cd WVZBabyMaker
    source setup.sh
    make clean; make -j;
    python scripts/runMetis.py --tag v0.0.5 --sample_sets WVZ2018 -p
