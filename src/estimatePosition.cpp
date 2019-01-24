#include "estimatePosition.h"

Vector2d estimatePos(const VectorXd& indice,const VectorXd& distance)
{
    vector<Vector2d> pos;

    // load position file
    ifstream fin("Config/PositionOfAP.txt");
    string nameAP;
    double x,y;
    while(fin>>nameAP)
    {
        fin>>x>>y;
        pos.push_back(Vector2d(x,y));
    }
    fin.close();

    // calculate prediction position
    Vector2d sum=Vector2d::Zero();
    int k=indice.rows();
    for(int i=0;i<k;i++)
    {
        sum+=pos[indice(i,0)];
    }
    Vector2d meanPos=sum/k;

    return meanPos;
}

Vector2d estimateWeightedPos(const VectorXd& indice,const VectorXd& distance)
{
    vector<Vector2d> pos;

    // load position file
    ifstream fin("Config/PositionOfAP.txt");
    string nameAP;
    double x,y;
    while(fin>>nameAP)
    {
        fin>>x>>y;
        pos.push_back(Vector2d(x,y));
    }
    fin.close();

    // calculate weighted (1/distance) prediction position
    Vector2d sum=Vector2d::Zero();
    int k=indice.rows();
    double sum2=0;
    for(int i=0;i<k;i++)
    {
        sum+=pos[indice(i,0)]*1/distance(i,0);
        sum2+=1/distance(i,0);
    }
    Vector2d meanPos=sum/sum2;

    return meanPos;
}