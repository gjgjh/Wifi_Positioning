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

#ifndef VISUALIZING_H
#define VISUALIZING_H

//#include <utility>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "wifipos/common_include.h"
#include "wifipos/visualizing.h"

namespace wifipos
{
using cv::Mat;
Mat visualizing(const vector<Vector3d>& predict_pos,const vector<Vector3d>& database_pos);
}

#endif // VISUALIZING_H