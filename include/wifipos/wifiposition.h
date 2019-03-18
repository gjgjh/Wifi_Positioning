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

#ifndef WIFIPOSITION_H
#define WIFIPOSITION_H

#include "wifipos/common_include.h"
#include "wifipos/utils.h"
#include "wifipos/strategy.h"

namespace wifipos
{
enum Strategy{KNN,WKNN};

class WifiPosition{
public:

    WifiPosition();
    ~WifiPosition();

    // interface
    void loadDatabase(string db_fname,string db_pos_fname);
    void loadTestdata(string fname);
    int numAP()const{ return numAP_;}
    int numSample()const{ return numSample_;}
    void startpositioning(Strategy,int k);
    const vector<Vector3d>& predictedPos()const{ return predict_pos_;}
    const vector<Vector3d>& databasePos()const{ return database_pos_;}

private:
    void knnSearch(const VectorXd& test,const MatrixXd& dataset,
                   VectorXd& indice,VectorXd& distance);
    void eigenToarma(const MatrixXd& m_e,mat& m_a);

    int numAP_;                              // total number of Access Points
    int numSample_;                          // total number of Sample Points

    MatrixXd database_;                      // wifi database matrix(size: numSample*numAP)
    vector<Vector3d> database_pos_;          // wifi database sample points' ground truth positions(size: numSample*3)

    vector<VectorXd> testdata_;              // wifi test data(size: numTest*numAP)
    vector<long> timestamp_;                 // wifi test data's timestamps(size: numTest*1)

    vector<Vector3d> predict_pos_;           // wifi positioning results(size: numTest*3)
};
}

#endif // WIFIPOSITION_H