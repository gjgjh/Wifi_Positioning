# Wifi Positioning

This program is a simple wifi positioning demo, which uses WKNN (Weighted K-Nearest-Neighbor) algorithm. The repo also provides a wifi dataset in the data directory.

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

## 1.3 OpenCV (optional)
OpenCV is used to visualize the wifi positioning results. This library is optional.

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

We provide a read wifi dataset in the data directory. The data was collected on the fourth floor of the Science Academic Building of Peking University, and the collection equipment was an ASUS computer. The detailed file format is [here](https://github.com/gjgjh/WifiPositioning/blob/master/data/README.md). A simple usage example can be found in the test directory.


<img src="https://github.com/gjgjh/WifiPositioning/blob/master/support_files/figure1.png" width = 45% height = 45% div align=left/> <img src="https://github.com/gjgjh/WifiPositioning/blob/master/support_files/figure2.png" width = 45% height = 45% div align=center/>

# 4. License

The source code is released under [GPLv3](http://www.gnu.org/licenses/) license.

We are still working on improving the code reliability. For any technical issues or commercial inquiries, please contact GJH <guojh_rs@pku.edu.cn>.
