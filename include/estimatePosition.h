#ifndef ESTIMATEPOSITION_H_
#define ESTIMATEPOSITION_H_

#include "testdataPrepare.h"

using Eigen::Vector2d;

Vector2d estimatePos(const VectorXd& indice,const VectorXd& distance);
Vector2d estimateWeightedPos(const VectorXd& indice,const VectorXd& distance);

#endif