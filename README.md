# ArcadeBT
__ArcadeBT__ is a safety verification tool for behavior trees which utilize constrained horn clauses.

# Building ArcadeBT
__ArcadeBT__ is supported on Ubuntu Linux 20.04.
The following command installs Google Test and Google Log dependencies:
> sudo apt install libgtest-dev libgoogle-glog-dev pkg-config

Z3 has to be manually installed (version _4.8.15.0_).

# Benchmark
To execute the benchmarks using the linear constrained horn clause encoding, run `apps/bench N` where N is a number between 0 and 42.
In folder _c_ are C files encoding the correspding examples which can be used as input for SeaHorn.
