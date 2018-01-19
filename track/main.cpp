// main for aruco tracking


#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

int startWebcam(float markerDim)//, const Mat& cameraMatrix, const Mat& distortionCoefficients)
{
    Mat frame;// holds the frame from a webcam
    vector<int> markerIds;

    vector<vector<Point2f>> markerCorners, rejectedCandidates;
    aruco::DetectorParameters parameters;

    Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary( aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50 );

    VideoCapture vid(0);// init webcam

    if(!vid.isOpened() )
    {
	return -1;
    }

    // make window to show output
    namedWindow("webcam", CV_WINDOW_AUTOSIZE );

    vector<Vec3d> rotationVectors, translationVectors;

    while(true)
    {
	if(!vid.read(frame) )
	    break;

	aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds );

	if( markerIds.size()>0 )
	{
	    // get the pose
	    /*
	      aruco::estimatePoseSingleMarkers(markerCorners,markerDim, cameraMatrix, distortionCoefficients, rotationVectors, translationVectors);
	      draw 
	      for 
	

	      for (int i = 0; i < markerIds.size(); ++i)
	      {
	      aruco::drawAxis(frame, cameraMatrix, distortionCoefficients, rotationVectors, translationVectors, 0.1f);
	      }
	    */

	    aruco::drawDetectedMarkers( frame, markerCorners, markerIds );

	    
	}

	// show it
	imshow("webcam", frame);
	// if something is wrong after 30s:
	if(waitKey(30)>=0) break;

	
    }// while true

    return 1;
}


int main(int argc, char *argv[])
{
    float markerDim;
    if( argc>1 )
    {
	markerDim = stof( argv[1], nullptr );
    }else
    {
	cout<< "Please specify square marker dimension\n";
	return 1;
    }
	
    startWebcam( markerDim );
    return 0;
}
