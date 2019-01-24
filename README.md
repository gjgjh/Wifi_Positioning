# Wifi Positioning

This program is a simple wifi positioning demo, which uses WKNN (Weighted K-Nearest-Neighbor) algorithm.

# 1. Prerequisites
This program has been tested on Ubuntu 16.04. It has several dependecies.

## 1.1 Mlpack

You can simply install mlpack with the following command:
```bash
sudo apt-get install libmlpack-dev
```

But this may not have the most recent version of mlpack available. Or you can follow [mlpack installation](http://www.mlpack.org/docs/mlpack-3.0.4/doxygen/build.html) if you want to install with a manual build.

## 1.2 Eigen
You can simply install Eigen with the following command:
```bash
sudo apt-get install libeigen3-dev
```

# 2. Build
Clone the repository and build:
```bash
git clone https://github.com/gjgjh/WifiPositioning
cd ~/WifiPositioning
mkdir build
cd build
cmake ..
make -j4
```

# 3. Example

Usage:
wifiPositioning <pathtodataset> <pathtotestdata> k <knn/wknn/wknn2>

`k` : the number of nearest neighbor used in searching

`knn` : K-Nearest-Neighbor

`wknn` : Weighted K-Nearest-Neighbor

`wknn2` : Weighted K-Nearest-Neighbor version 2 (not recommended)

For example:
```bash
cd ~/WifiPositioning
bin/wifiPositioning data/wifi_basedata data/wifi_testdata/ 3 wknn
```

# 4. License

This program is licensed under the MIT.