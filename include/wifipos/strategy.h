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

#ifndef STRATEGY
#define STRATEGY

#include "wifipos/common_include.h"

namespace wifipos
{
// strategy class
class PositionMethod{
public:
    typedef shared_ptr<PositionMethod> Ptr;
    virtual Vector3d estimatePos(const vector<Vector3d>& database_pos,const VectorXd& indice,const VectorXd& distance)=0;
};

class knn:public PositionMethod{
public:
    knn(){};
    virtual Vector3d estimatePos(const vector<Vector3d>& database_pos,const VectorXd& indice,const VectorXd& distance);
};

class wknn:public PositionMethod{
public:
    wknn(){};
    virtual Vector3d estimatePos(const vector<Vector3d>& database_pos,const VectorXd& indice,const VectorXd& distance);
};
}

#endif // STRATEGY