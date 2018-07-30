# 16 games in C++/[SFML](https://www.sfml-dev.org/index.php)

* From youtube series [Let's make 16 games in C++/SFML!](https://www.youtube.com/playlist?list=PLB_ibvUSN7mzUffhiay5g5GUHyJRO4DYr)
* [source code download](https://drive.google.com/uc?export=download&id=1naW_v6WAWYPgCIWNDskxtBsM84FoaOLh)

## Build and Run

Can compile each from command line on Mac via

```sh
# clang
clang++ \
-framework sfml-window \
-framework sfml-graphics \
-framework sfml-system \
-framework sfml-audio \
-framework sfml-network \
main.cpp -o main

# gcc
g++ \
-framework sfml-window \
-framework sfml-graphics \
-framework sfml-system \
-framework sfml-audio \
-framework sfml-network \
main.cpp -o main

# run
./main

```

> NOTE: assumes [SFML](https://www.sfml-dev.org/index.php) installed.  Frameworks should exist in `/Library/Frameworks`