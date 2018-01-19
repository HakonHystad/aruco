// main for generating markers


#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

#include <sstream>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

void createArucoMarkers()
{
    Mat outputMarker;

    Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

    for (int i = 0; i < 50; ++i)
    {
	aruco::drawMarker(markerDictionary, i, 500, outputMarker, 1);
	ostringstream convert;
	string imageName = "4x4_marker_";
	convert << imageName << i << ".png";
	imwrite( convert.str(), outputMarker );
    }
}

int main(int argc, char *argv[])
{
    createArucoMarkers();
    return 0;
}
