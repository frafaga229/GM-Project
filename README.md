# GM-Project
Intrinsic Dimension(ID) estimation via 2 nearest neighbors

## Quick start Windows 10

You need first to install gnuplot to be able to plot the ID estimator. For more details, please take a look at: [gnuplot download release 5.4.3](http://www.gnuplot.info).

To see a quick result, please just download the repository and build the executable 'main.exe' with the CMakeList.txt as follows:

  ```
    cmake -S . -B build/ -G "MinGW Makefiles"

    cd build
    cmake ..
    cmake --build . --config Release

  ```
## Test Case

You can either download and work directly on the respository, or install ProtoryNet with pip by running:

Task 2:
```
main.exe -input ../datasets/cauchy20 -discard 0.1
main.exe -input ../datasets/swissroll -discard 0.1
main.exe -input ../datasets/uniform14 -discard 0.1
```
Task 3:

```
main.exe -input ../datasets/swissroll -discard 0.1
main.exe -input ../datasets/uniform14 -discard 0.1
```

## Results

For the hotel dataset, the accuracy should be ~ 0.95-0.96%.

## Generalizing the algorithm
