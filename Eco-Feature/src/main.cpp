/*******************************************************************************
 * Filename      : main.cpp
 * Header File(s): 
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <valarray>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Transform.hpp"

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace cv;
using namespace Transforms;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
int main ( int argc, char* argv[] ) 
{
    srand((unsigned)time(NULL));
    
    Transform transform(CANNY_EDGE);
    Mat image = imread("data/image.jpg", CV_LOAD_IMAGE_COLOR);    
        
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    
    valarray<double> tmp(1);
    tmp[0] = 50;
    transform.set_parameters(tmp);
    transform.perform_transform(image);
    
    imshow( "Display window", transform.get_transform() );

    waitKey(0);
    
    return 0;
}