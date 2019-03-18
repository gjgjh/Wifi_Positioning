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
#include "wifipos/visualizing.h"

int main()
{
    wifipos::WifiPosition wp;

    // load wifi database file and wifi database position file
    wp.loadDatabase("../data/wifi_database.csv","../data/wifi_database_pos.csv");
    // load test data
    wp.loadTestdata("../data/wifi_testdata1.csv");
    //wp.loadTestdata("../data/wifi_testdata2.csv");
    //wp.loadTestdata("../data/wifi_testdata3.csv");

    // start wifi positioning
    wp.startpositioning(wifipos::WKNN,3);
    auto res=wp.predictedPos();

    // visualizing if you have OpenCV
    cv::Mat result=wifipos::visualizing(res,wp.databasePos());
    cv::imshow("res1",result);

    cv::waitKey(0);

    return 0;
}