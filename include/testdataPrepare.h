#ifndef TESTDATAPREPARE_H_
#define TESTDATAPREPARE_H_

#include "datasetPrepare.h"

void loadWifiFromRaw(string filename,vector<Wifi>& wifis);
void testdataCompl(const vector<Wifi>& wifis,VectorXd& data);
bool buildTestdata(const string& filepath,int numAP,vector<VectorXd>& datas,vector<long>& timestamps);

#endif