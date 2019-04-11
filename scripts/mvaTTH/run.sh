for DIR in $(ls -d /hadoop/cms/store/user/phchang/nanoaod/*13TeV*); do
    echo ./convert -i $DIR/muons.dat -o $DIR/muonsv2.dat
    echo ./convert -i $DIR/electrons.dat -o $DIR/electronsv2.dat
done
