#ifndef WKNN_H_
#define WKNN_H_

#include <iostream>
#include <map>
#include <Eigen/Core>

using Eigen::VectorXd;
using Eigen::MatrixXd;

void wknnSearch(const VectorXd& testdata,const MatrixXd& datasetMean,
        const MatrixXd& datasetWeight,VectorXd& indice,VectorXd& distance);

#endif