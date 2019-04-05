
## Install

    eval $(ssh-agent -s)
    ssh-add ~/.ssh/id_rsa.pub
    git clone --recurse-submodules git@github.com:sgnoohc/WVZBabyMaker.git
    cd WVZBabyMaker
    source setup.sh
    make clean; make -j;
