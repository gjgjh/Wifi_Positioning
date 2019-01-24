#include "wknn.h"

void wknnSearch(const VectorXd& testdata,const MatrixXd& datasetMean,
        const MatrixXd& datasetWeight,VectorXd& indice,VectorXd& distance)
{
    int numSample=datasetMean.rows();
    int numAP=datasetMean.cols();
    int k=indice.rows();
    VectorXd onedatasetMean,diff;

    // calculate weighted distances between current feature and each samples
    double sum;
    std::multimap<double,int>dists;
    for(int i=0;i<numSample;i++)
    {
        onedatasetMean=datasetMean.block(i,0,1,numAP).transpose();
        diff=onedatasetMean-testdata;

        sum=0;
        for(int j=0;j<numAP;j++)
        {
            sum+=diff(j,0)*datasetWeight(i,j)*diff(j,0);
        }
        dists.insert({sum,i});
    }

    // only save k nearest distance(s)
    int cnt=0;
    for(auto iter=dists.begin();;iter++,cnt++)
    {
        distance(cnt,0)=(*iter).first;
        indice(cnt,0)=(*iter).second;

        if(cnt==k-1)
            break;
    }

}