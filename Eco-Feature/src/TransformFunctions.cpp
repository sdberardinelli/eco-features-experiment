/******************************************************************************
 * Filename      : TransformFunctions.cpp
 * Header File(s): Transform.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "Transform.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdlib>
#include <iostream>

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
void Transform::gabor_filter ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != GABOR_FILTER_PARAMETER_NUMBER )
        return;
    
    if ( paramaters[0] < 0 ) /* kernel size */
        paramaters[0] = 0;
    if ( !(int(paramaters[0])%2) )
        paramaters[0]++;
    
    if ( paramaters[1] < 0 ) /* sigma */
        paramaters[1] = 0;
    if ( paramaters[1] > paramaters[0] )
        paramaters[1] = paramaters[0];
    
    if ( paramaters[2] < 0 ) /* theta */
        paramaters[2] = 0;
    if ( paramaters[2] > 180 ) 
        paramaters[2] = 180;
        
    if ( paramaters[3] < 0 ) /* lambda */
        paramaters[3] = 0;
    if ( paramaters[3] > 100 )
        paramaters[3] = 100;
    
    if ( paramaters[4] < 0.2 ) /* gamma */
        paramaters[4] = 0.2;
    if ( paramaters[4] > 1 )
        paramaters[4] = rand() / double(RAND_MAX);
    
    if ( paramaters[5] < 0 ) /* psi */
        paramaters[5] = 0;
     if ( paramaters[5] > 360 )
        paramaters[5] = 360;
    
    Size size(paramaters[0],paramaters[0]);
    double sigma  = paramaters[1]/((paramaters[0]==0)?1:paramaters[0]);
    double theta  = paramaters[2]*CV_PI/180;
    double lambda = paramaters[3];
    double gamma  = paramaters[4];
    double psi    = paramaters[5]*CV_PI/180;
    

    filter2D(tmp, transformed_image, CV_32F, getGaborKernel(size,
                                                            sigma,
                                                            theta,
                                                            lambda,
                                                            gamma,
                                                            psi,
                                                            CV_32F));   
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::morphological_erode ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != MORPHOLOGICAL_ERODE_PARAMETER_NUMBER )
        return;
    
    switch (int(paramaters[0]))/* erode type */
    {
        case MORPH_RECT:
            break;
        case MORPH_CROSS:
            break;
        case MORPH_ELLIPSE:
            break;
        default:
            paramaters[0] = MORPH_RECT;
    }
    
    if ( paramaters[1] < 0 ) /* kernel size */
        paramaters[1] = 0;
    if ( paramaters[1] > 21 )
        paramaters[1] = 21;
    

    int erosion_type = paramaters[0];    
    Size size(2*paramaters[1]+1,2*paramaters[1]+1);
    Point point(paramaters[1],paramaters[1]);
    
    erode( tmp, transformed_image, getStructuringElement( erosion_type, 
                                                          size, 
                                                          point ) );
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::gaussian_blur ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != GAUSSIAN_BLUR_PARAMETER_NUMBER )
        return;
    
    if ( !(int(paramaters[0])%2) )
        paramaters[0]++; 
    
    if ( paramaters[0] < 0 ) /* kernel size */
        paramaters[0] = 0;
    if ( paramaters[0] > 25 )
        paramaters[0] = 25;  
    
    if ( paramaters[1] < 0 ) /* kernel size */
        paramaters[1] = 0;
    if ( paramaters[1] > 10 )
        paramaters[1] = 10;  
    
    if ( paramaters[2] < 0 ) /* kernel size */
        paramaters[2] = 0;
    if ( paramaters[2] > 10 )
        paramaters[2] = 10;     
    
    
    int size = paramaters[0];
    int sigmaX = paramaters[1]; 
    int sigmaY = paramaters[2];
     
    GaussianBlur( tmp, transformed_image, Size( size, size ), sigmaX, sigmaY );
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::histogram ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != HISTOGRAM_PARAMETER_NUMBER )
        return;
    
    equalizeHist(tmp, transformed_image);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::hough_circles ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    //transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != HOUGH_CIRCLES_PARAMETER_NUMBER )
        return;
    
    GaussianBlur( transformed_image, transformed_image, Size(9, 9), 2, 2 );
    
    if ( paramaters[0] < 0 ) /* kernel size */
        paramaters[0] = 0;
    if ( paramaters[0] > 200 )
        paramaters[0] = 200;  
    
    if ( paramaters[1] < 0 ) /* kernel size */
        paramaters[1] = 0;
    if ( paramaters[1] > 100 )
        paramaters[1] = 100;  
    
    int param1 = paramaters[0];
    int param2 = paramaters[1];    

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles( transformed_image, 
                  circles, 
                  CV_HOUGH_GRADIENT, 
                  1, 
                  transformed_image.rows/8, 
                  param1, 
                  param2, 
                  0, 
                  0 );

    /// Draw the circles detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( transformed_image, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( transformed_image, center, radius, Scalar(0,0,255), 3, 8, 0 );
     }    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::normalize ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != NORMALIZE_PARAMETER_NUMBER )
        return;
    
    
    if ( paramaters[0] < 0 ) /* kernel size */
        paramaters[0] = 0;
    if ( paramaters[0] > 255 )
        paramaters[0] = 255;  
    
    if ( paramaters[1] < 0 ) /* kernel size */
        paramaters[1] = 0;
    if ( paramaters[1] > 255 )
        paramaters[1] = 255; 
    
    if ( paramaters[2] < 0 ) /* kernel size */
        paramaters[2] = 0;
    if ( paramaters[2] > 8 )
        paramaters[2] = 32;    
    
    int alpha = paramaters[0];
    int beta = paramaters[1];
    int norm = paramaters[2];
    
    cv::normalize(transformed_image, transformed_image, alpha, beta, norm);    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::discrete_fourier_transform ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != DISCRETE_FOURIER_TRANSFORM_PARAMETER_NUMBER )
        return;    
    
    if ( paramaters[0] < 0 ) /* kernel size */
        paramaters[0] = 0;
    if ( paramaters[0] > 10 )
        paramaters[0] = 10; 
   
    int threshold = paramaters[0];    
    
    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( transformed_image.rows );
    int n = getOptimalDFTSize( transformed_image.cols ); // on the border add zero values
    copyMakeBorder(transformed_image, padded, 0, m - transformed_image.rows, 0, n - transformed_image.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    cv::log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    //Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    cv::normalize(magI, transformed_image, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::square_root ( cv::Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != SQUARE_ROOT_PARAMETER_NUMBER )
        return;        
    
    cv::sqrt(tmp,transformed_image);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::canny_edge ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != CANNY_EDGE_PARAMETER_NUMBER )
        return; 
    
    if ( paramaters[0] < 0 )
        paramaters[0] = 0;
    if ( paramaters[0] > 100 )
        paramaters[0] = 100;
    
    int threshold = paramaters[0];
    
    blur( transformed_image, tmp, Size(3,3) );
    
    Canny( tmp, tmp, threshold, threshold*3, 3 );
    
    transformed_image = tmp;   
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::integral_image ( cv::Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0); 
    
    if ( paramaters.size() != INTEGRAL_IMAGE_PARAMETER_NUMBER )
        return;   
    
    if ( paramaters[0] < 1 )
        paramaters[0] = 1;
    if ( paramaters[0] > 3 )
        paramaters[0] = 3;
    
    int type = paramaters[0];    
    
    Mat tmp1, tmp2, tmp3;
    
    cv::integral(src,tmp1,tmp2,tmp3,CV_32F);
    
    switch ( type )
    {
        case 1:
            transformed_image = tmp1;
            break;
        case 2:
            transformed_image = tmp1;
            break;
        case 3:
            transformed_image = tmp1;
            break;
    }
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::difference_gaussians ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::census_transform ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::sobel_operator ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::morphological_dilate ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::adaptive_thresholding ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::hough_lines ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::harris_corner_strength ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::histogram_equalization ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::log ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::median_blur ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::distance_transform ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::laplacian_edged_etection ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::rank_transform ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::convert ( cv::Mat src )
{
    
}
