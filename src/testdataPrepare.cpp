#include "testdataPrepare.h"

void testdataCompl(const vector<Wifi>& wifis,VectorXd& data)
{
    // load AP names file
    vector<string> namesAP;
    string name;
    ifstream fin("Config/NamesOfAP.txt");
    while(fin>>name)
        namesAP.push_back(name);
    fin.close();

    data.setZero();
    for(const auto& w:wifis)
    {
        // if current Wifi is found in the AP dataset
        auto loc=find(namesAP.begin(),namesAP.end(),w.address);
        if(loc!=namesAP.end())
        {
            data(loc-namesAP.begin(),0)=w.rss;
        }
    }
}

bool buildTestdata(const string& filepath,int numAP,vector<VectorXd>& datas,vector<long>& timestamps)
{
    vector<string> filenames;
    for(const auto& file:experimental::filesystem::directory_iterator(filepath))
        filenames.push_back(file.path());
    if(filenames.size()==0)
    {
        cerr<<"No test file found!\n";
        return false;
    }
    sort(filenames.begin(),filenames.end());

    vector<Wifi> wifis;
    for(auto& fn:filenames)
    {
        loadWifiFromRaw(fn,wifis);
    }

    map<long,vector<Wifi>> map; // timestamps and Wifis
    for(auto& w:wifis)
        map[w.timestamp].push_back(w);

    for(auto& m:map)
    {
        timestamps.push_back(m.first);
        VectorXd data(numAP);
        testdataCompl(m.second,data);
        datas.push_back(data);
    }

    return true;
}