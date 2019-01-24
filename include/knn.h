#ifndef KNN_H_
#define KNN_H_

#include <mlpack/core.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include "datasetPrepare.h"

using namespace arma;
using namespace mlpack;
using namespace mlpack::neighbor;
using namespace mlpack::metric;

void knnSearch(const VectorXd& test,const MatrixXd& dataset,
               VectorXd& indice,VectorXd& distance);

void eigenToarma(const MatrixXd& m_e,mat& m_a);

#endif