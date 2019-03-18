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

#include "wifipos/wifiposition.h"

namespace wifipos
{
WifiPosition::WifiPosition():
    numAP_(0),numSample_(0)
{}

WifiPosition::~WifiPosition()
{}

void WifiPosition::loadDatabase(string db_fname,string db_pos_fname)
{
    ifstream fin;
    fin.open(db_fname);
    string temp;
    getline(fin,temp);
    int cnt=0;
    while(getline(fin,temp))
        cnt++;
    numSample_=cnt;
    fin.close();
    fin.clear();

    // load database
    fin.open(db_fname);
    CSVRow row;
    fin>>row;
    numAP_=row.size()-1;
    database_=MatrixXd::Zero(numSample_,numAP_);

    int id=0;
    while (fin>>row)
    {
        for(int i=0;i<numAP_;++i)
            database_(id,i)=stoi(row[i+1]);
        ++id;
    }
    fin.close();

    // load database position
    fin.close();
    fin.clear();
    fin.open(db_pos_fname);
    fin>>row;
    database_pos_=vector<Vector3d>(numSample_,Vector3d());
    id=0;
    while (fin>>row)
    {
        database_pos_[id](0,0)=stoi(row[1]);
        database_pos_[id](1,0)=stoi(row[2]);
        database_pos_[id](2,0)=stoi(row[3]);
        ++id;
    }
    fin.close();
}

void WifiPosition::loadTestdata(string fname)
{
    ifstream fin;
    fin.open(fname);
    CSVRow row;
    fin>>row;
    if(row.size()-1!=numAP_)
    {
        cerr<<"Testdata is in a wrong format\n";
        return;
    }
    int cnt=0;
    while(fin>>row)
        cnt++;
    fin.close();
    fin.clear();

    // load test data
    fin.open(fname);
    vector<VectorXd> temp(cnt,VectorXd(numAP_));
    testdata_=temp;
    timestamp_=vector<long>(cnt,0);
    fin>>row;
    int id=0;
    while (fin>>row)
    {
        timestamp_[id]=stol(row[0]);
        for(int i=0;i<numAP_;++i)
            testdata_[id](i,0)=stoi(row[i+1]);
        ++id;
    }
    fin.close();
}

void WifiPosition::startpositioning(Strategy s,int k)
{
    if(numAP_==0||numSample_==0)
    {
        cerr<<"Please load wifi database first\n";
        return;
    }

    if(timestamp_.size()==0||testdata_.size()==0)
    {
        cerr<<"Please load wifi test data first\n";
        return;
    }

    PositionMethod::Ptr pMethod;
    if(s==KNN)
        pMethod=PositionMethod::Ptr(new knn);
    else
        pMethod=PositionMethod::Ptr(new wknn);

    VectorXd indice(k);
    VectorXd distance(k);
    for(int i=0;i<testdata_.size();i++)
    {
        knnSearch(testdata_[i],database_,indice,distance);

        Vector3d currpos;
        currpos=pMethod->estimatePos(database_pos_,indice,distance);
        predict_pos_.push_back(currpos);
    }
}

void WifiPosition::knnSearch(const VectorXd& test,const MatrixXd& dataset,
               VectorXd& indice,VectorXd& distance)
{
    mat basedata;
    mat testdata;
    eigenToarma(dataset,basedata);
    eigenToarma(test,testdata);
    basedata=basedata.st(); // need to transpose

    NeighborSearch<NearestNeighborSort,EuclideanDistance> nn(basedata);

    Mat<size_t> neighbors;
    mat distances;

    int k=indice.rows();
    nn.Search(testdata,k,neighbors,distances);

    for(int i=0;i<k;i++)
    {
        indice(i,0)=neighbors[i];
        distance(i,0)=distances[i];
    }
}

void WifiPosition::eigenToarma(const MatrixXd& m_e,mat& m_a)
{
    m_a=mat(m_e.rows(),m_e.cols());
    for(int i=0;i<m_e.rows();i++)
    {
        for(int j=0;j<m_e.cols();j++)
        {
            m_a(i,j)=m_e(i,j);
        }
    }
}

}