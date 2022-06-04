# Minimum Coresets

A C++ implementation of algorithms in our paper "Minimum Coresets for Maxima Representation of Multidimensional Data".

## Dependencies

- Ubuntu: 18.04.3 LTS
- GCC: 7.4+
- CMake: 3.5+
- ANN: 1.1.2
- GLPK: 4.65

## How to run

See the bash file "run-examples.sh" for examples of compilation and execution using the exemplar datasets in folder "examples".

### Compilation

```sh
mkdir build
cd build
cmake  ../
make all
```

### Run OptMC

```sh
./build/opt <is_full> <dataset_path> <dirs_path> <valid_path> <output_path>
```
- is_full: 0 or 1, 0 for eps=0.1 and 1 for all eps values
- dataset_path: string, the file of points in the dataset
- dirs_path: string, the file of vectors used for validation
- valid_path: string, the file of precomputed results for validation
- output_path: string, the file of output results

### Run SCMC

```sh
./build/approx <dim> <eps> <dataset_path> <dirs_path> <validation_path> <output_path>
```
- dim: int, the dimensionality of dataset
- eps: double, the value of epsilon
- dataset_path: string, the file of points in the dataset
- dirs_path: string, the file of vectors used for validation
- valid_path: string, the file of precomputed results for validation
- output_path: string, the file of output results

### Run DSMC

For dominance graph construction:
```sh
./build/heur 0 <dim> <dataset_path> <ipdg_path> <dg_path>
```

For solution computation
```sh
./build/heur 1 <dim> <eps> <dataset_path> <dg_path> <dirs_path> <validation_path> <output_path>
```

- dim: int, the dimensionality of dataset
- dataset_path: string, the file of points in the dataset
- ipdg_path: string, the file of IPDG, "na" for d=2
- dg_path: string, the file of dominance graph
- eps: double, the value of epsilon
- dirs_path: string, the file of vectors used for validation
- valid_path: string, the file of precomputed results for validation
- output_path: string, the file of output results

## Baselines

- ANN: See folder 'ANN'. This implementation is based on <https://users.cs.duke.edu/~ssintos/kRMS_SEA/>. Note that two additional libraries [Boost 1.60.0](http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz) and [ANN 1.1.2](http://www.cs.umd.edu/~mount/ANN/Files/1.1.2/ann_1.1.2.tar.gz) are required for compilation.

## Contact

If there is any question, feel free to contact [Yanhao Wang](mailto:yhwang@dase.ecnu.edu.cn).
