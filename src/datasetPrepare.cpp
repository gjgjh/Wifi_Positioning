#include "datasetPrepare.h"

string strsplit(const string& str,int startpos,int endpos)
{
    string temp;

    for(auto iter=str.begin()+startpos;iter!=str.end()&&iter!=str.begin()+endpos;iter++)
        temp.push_back(*iter);

    return temp;
}

/*
 * Load wifi from raw data.
 * Note that repeat wifis didn't get removed!
 */
void loadWifiFromRaw(string filename,vector<Wifi>& wifis)
{
    ifstream fin(filename);
    string temp;
    long time=0;
    int count=0;
    while(fin>>temp)
    {
        if(temp=="==========")
        {
            // if it's the first '=========='
            count++;
            if(count%2==1)
            {
                fin>>temp;
                istringstream iss(temp);
                iss>>time;
            }
        }

        int cnt=0;
        if(temp=="Address:")
        {
            Wifi wifi;
            fin>>temp;
            wifi.address=temp;

            while(fin>>temp)
            {
                if(temp=="Signal")
                {
                    fin>>temp;
                    auto loc=temp.find("=");
                    temp=temp.substr(loc+1,temp.size()-loc);
                    double rss;
                    if(temp.find("/")!=string::npos)
                    {
                        istringstream iss(temp);
                        iss>>rss;
                        double rss2;
                        char chuhao;
                        iss>>chuhao;
                        iss>>rss2;
                        rss=(rss/rss2)*100/2-100;
                    } else{
                        istringstream iss(temp);
                        iss>>rss;
                    }

                    wifi.rss=rss;

                    cnt++;
                }
                if(temp.find("ESSID:")!=string::npos)
                {
                    auto loc=temp.find("ESSID:");

                    string temp2;
                    getline(fin,temp2);
                    if(temp2.size()==0)
                    {
                        temp=strsplit(temp,loc+7,temp.size()-1);
                        temp2=strsplit(temp2,0,temp2.size()-1);
                        temp+=temp2;
                    }else{
                        temp=strsplit(temp,loc+7,temp.size());
                        temp2=strsplit(temp2,0,temp2.size()-1);
                        temp+=temp2;
                    }
                    wifi.essid=temp;

                    cnt++;
                }
                if(cnt==2)
                {
                    wifi.timestamp=time;
                    wifis.push_back(wifi);
                    break;
                }

            }

        }
    }
    fin.close();
}

/*
 * Remove unstable Wifis, which didn't appear > 7 times in 10 scanning. 10=SampleFrequency
 */
void removeUnstableWifi(const vector<Wifi>& wifis,map<string,vector<Wifi>>& map)
{
    // add repeat wifis together into a vector
    for(auto& w:wifis)
    {
        map[w.address].push_back(w);
    }

    // remove unstable wifis
    for(auto& it:map)
    {
        if(it.second.size()<SampleFrequency-2)
            map.erase(it.first);
    }

}

/*
 * calculate wifis mean and weight at one sampling spot
 */
void calWifiMeanAndWeight(const map<string,vector<Wifi>>& wifis_tmp,vector<Wifi>& wifis)
{
    double mean,var;
    double sum=0;
    vector<double> means;
    vector<double> weights;
    for(auto& it:wifis_tmp)
    {
        calMeanAndVar(it.second,mean,var);
        means.push_back(mean);
        sum+=1.0/(var+1);
        weights.push_back(1.0/(var+1)); // weight is normalized 1/(1+var)
    }

//    for(auto& it:wifis_tmp)
//    {
//        calMeanAndVar(it.second,mean,var);
//        means.push_back(mean);
//        sum+=var+1;
//        weights.push_back(var+1); // weight is normalized 1/(1+var)
//    }

    int cnt=0;
    for(auto& it:wifis_tmp)
    {
        Wifi temp;
        temp.address=it.second[0].address;
        temp.essid=it.second[0].essid;
        temp.rss=means[cnt];
        temp.weight=weights[cnt]/sum;

        wifis.push_back(temp);
        cnt++;
    }

}

/*
 * calculate each wifi's mean and var in 10 (SampleFrequency) times sampling
 */
void calMeanAndVar(const vector<Wifi>& wifis,double& mean,double& var)
{
    double sum=0;
    for(auto& w:wifis)
    {
        sum+=w.rss;
    }
    mean=sum/wifis.size();

    sum=0;
    for(auto& w:wifis)
    {
        sum+=(w.rss-mean)*(w.rss-mean);
    }
    var=sum/(wifis.size()-1);
}

void buildDataset(const string& filepath,MatrixXd& datasetMean,MatrixXd& datasetWeight)
{

    vector<string> filenames;
    for(const auto& file:experimental::filesystem::directory_iterator(filepath))
        filenames.push_back(file.path());
    sort(filenames.begin(),filenames.end());

    // generate All AP names
    int numSample=filenames.size();
    vector<map<string,vector<Wifi>>> allWifis;
    map<string,int> namesAP;
    int cnt=0;
    for(auto& fn:filenames)
    {
        vector<Wifi> wifisTemp;
        map<string,vector<Wifi>> map;
        loadWifiFromRaw(fn,wifisTemp);
        removeUnstableWifi(wifisTemp,map);
        allWifis.push_back(map);

        for(auto& m:map)
        {
            if(namesAP.find(m.first)==namesAP.end()) // if this AP haven't shown before
            {
                namesAP.insert({m.first,cnt});
                cnt++;
            }
        }

    }

    // save All AP names
    vector<string> namesAP2(namesAP.size(),"");
    for(auto& it:namesAP)
    {
        namesAP2[it.second]=it.first;
    }

    ofstream fout("Config/NamesOfAP.txt");
    for(auto& it:namesAP2)
        fout<<it<<endl;
    fout.close();

    cout<<"dataset generated successfully!\n"
        <<"AP's names are saved in path: Config/NamesOfAP.txt\n";

    // generate Mean and Weight Matrix
    int numAP=namesAP.size();
    datasetMean=MatrixXd::Zero(numSample,numAP);
    datasetWeight=MatrixXd::Zero(numSample,numAP);

    for(int i=0;i<numSample;i++)
    {
        auto wifis_tmp=allWifis[i];
        vector<Wifi> wifis;
        calWifiMeanAndWeight(wifis_tmp,wifis);

        for(auto& w:wifis)
        {
            datasetMean(i,namesAP[w.address])=w.rss;
            datasetWeight(i,namesAP[w.address])=w.weight;
        }
    }

}
