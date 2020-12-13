# build
mkdir build
cd build
cmake  ../
make all
cd ../

# OptMC
./build/opt 0 examples/test_2d.txt examples/dirs_2d.txt examples/test_2d_validation.txt results_OptMC_test_2d.txt

# SCMC
./build/approx 2 0.1 examples/test_2d.txt examples/dirs_2d.txt examples/test_2d_validation.txt results_SCMC_test_2d.txt
./build/approx 3 0.1 examples/test_3d.txt examples/dirs_3d.txt examples/test_3d_validation.txt results_SCMC_test_3d.txt

# DSMC
./build/heur 1 2 0.1 examples/test_2d_extremes.txt examples/test_2d_dom_graph.txt examples/dirs_2d.txt examples/test_2d_validation.txt results_DSMC_test_2d.txt
./build/heur 1 3 0.1 examples/test_3d_extremes.txt examples/test_3d_dom_graph.txt examples/dirs_3d.txt examples/test_3d_validation.txt results_DSMC_test_3d.txt

# ANN
./coreset/coreset 0.1 2 examples/test_2d.txt examples/dirs_2d.txt examples/test_2d_validation.txt results_ANN_test_2d.txt
./coreset/coreset 0.1 3 examples/test_3d.txt examples/dirs_3d.txt examples/test_3d_validation.txt results_ANN_test_3d.txt