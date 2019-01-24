#include "knn.h"

void knnSearch(const VectorXd& test,const MatrixXd& dataset,
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

void eigenToarma(const MatrixXd& m_e,mat& m_a)
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