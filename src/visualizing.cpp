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

#include "wifipos/visualizing.h"

namespace wifipos
{
Mat visualizing(const vector<Vector3d>& predict_pos,const vector<Vector3d>& database_pos)
{
    Mat imgout=Mat(6000,5000,CV_8UC3,cv::Scalar(255,255,255));

    // plot AP position, some coordinates are negative so set a offset
    int offsetX=1000;
    int offsetY=1000;
    double x,y,z;
    for(int i=0;i<database_pos.size();++i)
    {
        x=database_pos[i](0,0);
        y=database_pos[i](1,0);
        z=database_pos[i](2,0); // not used
        cv::circle(imgout,cv::Point(x+offsetX,y+offsetY),10,cv::Scalar(0,0,0),-1);
    }

    cv::Point beginpoint=cv::Point(predict_pos[0].x()+offsetX,predict_pos[0].y()+offsetY);
    cv::circle(imgout,beginpoint,15,cv::Scalar(255,0,0),-1);
    if(predict_pos.size()>1) //draw lines only when there are more than 2 points
    {
        for(int i=1;i<predict_pos.size();i++)
        {
            cv::Point currpoint=cv::Point(predict_pos[i].x()+offsetX,predict_pos[i].y()+offsetY);
            cv::circle(imgout,currpoint,15,cv::Scalar(0,0,255),-1);
            if(beginpoint!=currpoint)
                cv::line(imgout,beginpoint,currpoint,cv::Scalar(0,0,255),5);
            beginpoint=currpoint;
        }
    }

    cv::resize(imgout,imgout,cv::Size(),0.15,0.15);
    return imgout.clone();
}

}
