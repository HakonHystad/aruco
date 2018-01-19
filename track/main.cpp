// main for aruco tracking


#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

#include <time.h>

using namespace cv;
using namespace std;

int startWebcam(float markerDim, const Mat& cameraMatrix, const Mat& distortionCoefficients)
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

    // --------- timing -------------
    struct timespec start, finish;
    double elapsed;

    while(true)
    {
	if(!vid.read(frame) )
	    break;
	//clock_gettime(CLOCK_MONOTONIC, &start);

	aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds );

	/*
	clock_gettime(CLOCK_MONOTONIC, &finish);

	      elapsed = (finish.tv_sec - start.tv_sec);
	      elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	      cout << "1 frame elapsed: " << elapsed << endl;
	*/
	if( markerIds.size()>0 )
	{
	    // get the pose
	      aruco::estimatePoseSingleMarkers(markerCorners,markerDim, cameraMatrix, distortionCoefficients, rotationVectors, translationVectors);
	
	      for (int i = 0; i < markerIds.size(); ++i)
	      {
		  aruco::drawAxis(frame, cameraMatrix, distortionCoefficients, rotationVectors, translationVectors, 0.1f);
	      }
	    

	    aruco::drawDetectedMarkers( frame, markerCorners, markerIds );

	    
	}

	// show it
	imshow("webcam", frame);
	// if something is wrong after 30s:
	if(waitKey(30)>=0) break;

	
    }// while true

    return 1;
}

bool loadCameraCalibration( string name, Mat& cameraMatrix, Mat& distortionCoefficients )
{
    ifstream inStream(name);
    if( !inStream )
	return false;

    uint16_t rows;
    uint16_t cols;

    inStream >> rows;
    inStream >> cols;

    // camera matrix
    cameraMatrix = Mat(Size(cols, rows), CV_64F );

    for (int r = 0; r < rows; ++r)
    {
	for (int c = 0; c < cols; ++c)
	{
	    double tmp = 0.0f;
	    inStream >> tmp;
	    cameraMatrix.at<double>(r,c) = tmp;
	    
	}
    }

    // distortionCoefficients
    inStream >> rows;
    inStream >> cols;

    distortionCoefficients = Mat::zeros(rows, cols, CV_64F);

    for (int r = 0; r < rows; ++r)
    {
	for (int c = 0; c < cols; ++c)
	{
	    double tmp = 0.0f;
	    inStream >> tmp;
	    distortionCoefficients.at<double>(r,c) = tmp;
	    
	}
    }

    inStream.close();

    return true;


}



    


int main(int argc, char *argv[])
{
    float markerDim;
    Mat calibrationMatrix;
    Mat distortionCoefficients;
    
    if( argc>2 )
    {
	markerDim = stof( argv[1], nullptr );
	if(!loadCameraCalibration( argv[2], calibrationMatrix, distortionCoefficients ) )
	{
	    cout << "Could not load file\n";
	    return 1;
	}
	    
    }else
    {
	cout<< "Please specify square marker dimension and a calibration filename\n";
	return 1;
    }
	
    startWebcam( markerDim, calibrationMatrix, distortionCoefficients );
    return 0;
}
