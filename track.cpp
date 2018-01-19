// aruco tracker for matlab interface

#include "opencvmex.hpp"
#include <opencv2/aruco.hpp>

#include <vector>
#include <iostream>

using namespace cv;
using namespace std;


void mexFunction(int nlhs, mxArray *plhs[], int nrhs,  const mxArray *prhs[])
{
    // ----------------- convert and initialize
    Mat frame;
    ocvMxArrayToImage_uint8(prhs[0],frame);
    
    vector<int> markerIds;

    vector<vector<Point2f>> markerCorners;

    Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary( aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50 );

    //vector<Vec3d> rotationVectors, translationVectors;

/*
    // ----------------- detect
    aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds );

    
    if( markerIds.size()>0 )
    {
	aruco::drawDetectedMarkers( frame, markerCorners, markerIds);
    }
*/

    plhs[0] = ocvMxArrayFromImage_uint8(frame);


}

