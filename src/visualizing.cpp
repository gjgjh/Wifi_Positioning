#include <iostream>
#include <fstream>
#include <utility>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "testdataPrepare.h"

using cv::Mat;
using namespace std;
using Eigen::Vector2d;

void visualizing(vector<Vector2d>& positions);
int main(int argc,char** argv)
{
    // TODO
    // visualizing(positions);

    return 0;
}

void visualizing(vector<Vector2d>& positions)
{
    Mat imgout=Mat(6000,5000,CV_8UC3,cv::Scalar(255,255,255));
    vector<pair<double,double>> pos;

    // load position file
    ifstream fin("Config/PositionOfAP.txt");
    if(!fin.good())
    {
        std::cerr<<"Cannot load file from Config/PositionOfAP.txt\n";
        return;
    }

    // plot AP position
    int offsetX=1000;
    int offsetY=1000;
    string nameAP;
    double x,y;
    while(fin>>nameAP)
    {
        fin>>x>>y;
        // some coordinates are negative
        cv::circle(imgout,cv::Point(x+offsetX,y+offsetY),10,cv::Scalar(0,0,0),-1);
    }
    fin.close();

    cv::Point beginpoint=cv::Point(positions[0].x()+offsetX,positions[0].y()+offsetY);
    cv::circle(imgout,beginpoint,15,cv::Scalar(255,0,0),-1);
    if(positions.size()>1) //draw lines only when there are more than 2 points
    {
        for(int i=1;i<positions.size();i++)
        {
            cv::Point currpoint=cv::Point(positions[i].x()+offsetX,positions[i].y()+offsetY);
            cv::circle(imgout,currpoint,15,cv::Scalar(0,0,255),-1);
            if(beginpoint!=currpoint)
                cv::line(imgout,beginpoint,currpoint,cv::Scalar(0,0,255),5);
            beginpoint=currpoint;
        }
    }

    cv::resize(imgout,imgout,cv::Size(),0.15,0.15);
    cv::imshow(" ",imgout);
    cv::waitKey(0);
}

