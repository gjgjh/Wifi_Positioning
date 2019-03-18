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

#include "wifipos/strategy.h"

namespace wifipos
{
Vector3d knn::estimatePos(const vector<Vector3d>& database_pos,const VectorXd& indice,const VectorXd& distance)
{
    vector<Vector3d> pos;
    pos.reserve(database_pos.size());
    double x,y,z;
    for(int i=0;i<database_pos.size();++i)
    {
        x=database_pos[i](0,0);
        y=database_pos[i](1,0);
        z=database_pos[i](2,0);
        pos.push_back(Vector3d(x,y,z));
    }

    // calculate prediction position
    Vector3d sum=Vector3d::Zero();
    int k=indice.rows();
    for(int i=0;i<k;i++)
        sum+=pos[indice(i,0)];
    Vector3d meanPos=sum/k;

    return meanPos;
}

Vector3d wknn::estimatePos(const vector<Vector3d>& database_pos,const VectorXd& indice,const VectorXd& distance)
{
    vector<Vector3d> pos;
    pos.reserve(database_pos.size());
    double x,y,z;
    for(int i=0;i<database_pos.size();++i)
    {
        x=database_pos[i](0,0);
        y=database_pos[i](1,0);
        z=database_pos[i](2,0);
        pos.push_back(Vector3d(x,y,z));
    }

    // calculate weighted (1/distance) prediction position
    Vector3d sum=Vector3d::Zero();
    int k=indice.rows();
    double sum2=0;
    for(int i=0;i<k;i++)
    {
        sum+=pos[indice(i,0)]*1/distance(i,0);
        sum2+=1/distance(i,0);
    }
    Vector3d meanPos=sum/sum2;

    return meanPos;
}

}