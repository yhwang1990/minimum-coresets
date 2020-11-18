# Generalized-RMS

A C++ implementation of algorithms in our paper "GRMR: Generalized Regret-Minimizing Representatives".

## Dependencies

- Ubuntu: 18.04.3 LTS
- GCC: 7.4+
- CMake: 3.5+
- GLPK: 4.65

## How to run

### Compilation

```sh
mkdir build
cd build
cmake  ../
make all
```

### Run E-GRMR

```sh
./build/ExactGRMR <dataset_path> <output_path>
```

- dataset_path: string, the dataset file
- output_path: string, the result file

For example,

```sh
./build/ExactGRMR examples/test_2d.txt examples/E-GRMR-test_2d.txt
```

### Run H-GRMR

```sh
./build/HeurGRMR <dim> <dataset_path> <topk_path> <dirs_path> <validation_path> <output_path> <all>
```

- dim: int, the dimensionality of dataset
- dataset_path: string, the dataset file
- topk_path: string, the file stored the top-k results used in IPDG construction, use "na" for d=2
- dirs_path: string, the file stored the random directions for validation
- validation_path: string, the file stored the top-1 results of random directions in <dirs_path> for validation
- output_path: string, the result file
- all: int, "1" for all epsilon values from 0.01 to 0.1; "0" for epsilon=0.1 only

For example,

```sh
./build/HeurGRMR 2 examples/test_2d_extremes.txt na examples/dirs_2d.txt examples/test_2d_validation.txt examples/H-GRMR-test_2d.txt 1
./build/HeurGRMR 3 examples/test_3d_extremes.txt examples/test_3d_top2.txt examples/dirs_3d.txt examples/test_3d_validation.txt examples/H-GRMR-test_3d.txt 1
```

## Baselines

- eps-Kernel/HittingSet: See folder 'baselines1_epsKernel_HittingSet'. This implementation is based on <https://users.cs.duke.edu/~ssintos/kRMS_SEA/>. Note that two additional libraries [Boost 1.60.0](http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz) and [ANN 1.1.2](http://www.cs.umd.edu/~mount/ANN/Files/1.1.2/ann_1.1.2.tar.gz) are required for compilation.
- Greedy/HD-RRMS/Sphere: See folder 'baselines2_RMS_hd'. This implementation is based on <https://www.cse.ust.hk/~raywong/code/sigmod18-sphere.zip>.
- 2D-RRMS: See folder 'baselines3_RMS_2d' for our implementation of 2D-RRMS in "Efficient Computation of Regret-ratio Minimizing Set: A Compact Maxima Representative" (SIGMOD 2018).

## Contact

If there is any question, feel free to contact [Yanhao Wang](mailto:yanhao90@comp.nus.edu.sg).
