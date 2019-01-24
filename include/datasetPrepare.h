#ifndef DATASETPREPARE_H_
#define DATASETPREPARE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <experimental/filesystem>
#include <algorithm>

#include "wknn.h"

#include <Eigen/Core>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using namespace std;

struct Wifi{
    string address;
    string essid;
    long timestamp;
    double rss;
    double weight=0;
};

// when collecting wifi data, we sampled 10 times at each point
// change it to your sample frequency
const int SampleFrequency=10;

void loadWifiFromRaw(string filename,vector<Wifi>& wifis);
string strsplit(const string& str,int startpos,int endpos);
void removeUnstableWifi(const vector<Wifi>& wifis,map<string,vector<Wifi>>& map);
void calWifiMeanAndWeight(const map<string,vector<Wifi>>& wifis_tmp,vector<Wifi>& wifis);
void calMeanAndVar(const vector<Wifi>& wifis,double& mean,double& weight);
void buildDataset(const string& filepath,MatrixXd& datasetMean,MatrixXd& datasetWeight);

#endif