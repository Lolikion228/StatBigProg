rm -rf ./build
mkdir build
qmake ./big_prog -o ./build/Makefile
make -C ./build -j8
make -C ./build clean
