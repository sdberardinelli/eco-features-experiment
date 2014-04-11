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
#include "Subregion.hpp"

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace cv;
using namespace Transforms;
using namespace Subregions;

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
   
    Mat image = imread("data/lena.png", CV_LOAD_IMAGE_COLOR);    
        
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    
    Subregion subregion( image, image.rows/4, image.rows/2, image.cols/4, image.cols/2 );
    
    imshow( "Display window", subregion.get_subregion() );
//    imshow( "Display window Original", image );
    
    Transform transform(HISTOGRAM);    
//    
////    valarray<double> tmp(3);
////    tmp[0] = 3;
//    tmp[1] = 1;
//    tmp[2] = 0;
//    transform.set_parameters(tmp);
    transform.perform_transform(subregion.get_subregion());
//    
    imshow( "Display window", transform.get_transform() );
//
//    imshow( "Display window Original", image );
    
    waitKey(0);
    
    return 0;
}