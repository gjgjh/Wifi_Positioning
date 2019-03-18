/*******************************************************
 * Copyright (C) 2019, Navigation And Location Group, Peking University
 * 
 * This file is part of wifi_positioning.
 * 
 * Licensed under the GNU General Public License v3.0;
 * you may not use this file except in compliance with the License.
 *
 * Author: GJH (guojh_rs@pku.edu.cn)
 *******************************************************/

// define the commonly included file to avoid a long include list
#ifndef COMMON_INCLUDE_H
#define COMMON_INCLUDE_H

// std
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
using namespace std;

// eigen
#include <Eigen/Core>
using Eigen::Vector3d;
using Eigen::VectorXd;
using Eigen::MatrixXd;

// mlpack
#include <mlpack/core.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
using namespace arma;
using namespace mlpack;
using namespace mlpack::neighbor;
using namespace mlpack::metric;

#endif // COMMON_INCLUDE_H