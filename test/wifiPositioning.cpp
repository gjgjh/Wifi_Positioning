#include "wknn.h"
#include "knn.h"
#include "datasetPrepare.h"
#include "testdataPrepare.h"
#include "estimatePosition.h"

int main(int argc,char** argv)
{
	if(argc!=5)
	{
		cerr<<"Usage: wifiPositioning <pathtodataset> <pathtotestdata> k <knn/wknn/wknn2>";
		return -1;
	}
	if(!(strcmp(argv[4],"knn")==0||
	strcmp(argv[4],"wknn")==0||
	strcmp(argv[4],"wknn2")==0))
	{
        cerr<<"method can only be \"knn\",\"wknn\" or \"wknn2\"\n";
        return -1;
	}

	// prepare dataset and testdata from raw data
    MatrixXd datasetMean;
    MatrixXd datasetWeight;
    buildDataset(argv[1],datasetMean,datasetWeight);

    int numSample=datasetMean.rows();
    int numAP=datasetMean.cols();

    vector<VectorXd> testdata;
    vector<long> timestamps;
    if(!buildTestdata(argv[2],numAP,testdata,timestamps))
    {
        cerr<<"Build test data failed!\n";
        return -1;
    }

    // k nearest
    int k=stoi(argv[3]);
    VectorXd indice(k);
    VectorXd distance(k);
    vector<Vector2d> positions;

    for(int i=0;i<testdata.size();i++)
    {
        // wknn2: improved wknn (not recommended)
        // wknn:  classic wknn (recommended)
        if(strcmp(argv[4],"wknn2")==0)
        {
            wknnSearch(testdata[i],datasetMean,datasetWeight,indice,distance);
        }else{
            knnSearch(testdata[i],datasetMean,indice,distance);
        }

        // print current timestamp
        cout<<timestamps[i]<<" : "<<endl;

        // print the result
        cout<<indice<<endl<<distance<<endl;

        // print the estimate position
        Vector2d currpos;
        // knn: classic knn (recommended)
        if(strcmp(argv[4],"knn")==0)
        {
            currpos=estimatePos(indice,distance);
        } else{
            currpos=estimateWeightedPos(indice,distance);
        }

        positions.push_back(currpos);
        cout<<"position:\n"<<currpos<<endl<<endl;
    }

    return 0;

}