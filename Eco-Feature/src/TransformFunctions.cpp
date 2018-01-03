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
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
#include <iostream>
#include <random>

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
void Transform::randomize_gabor_filter_parameters( int seed ){
    mt19937 rnd(seed);

    paramaters.resize(GABOR_FILTER_PARAMETER_NUMBER);

    uniform_int_distribution<int> size_dist(0,20);
    uniform_int_distribution<int> sigma_dist(0,180);
    uniform_int_distribution<int> theta_dist(0,180);
    uniform_int_distribution<int> lambda_dist(0,100);
    uniform_int_distribution<int> gamma_dist(0,100);
    uniform_int_distribution<int> psi_dist(0,360);

    int size = size_dist(rnd);
    if ( size % 2 == 0 ) { size++; };

    paramaters[0] = size;
    paramaters[1] = sigma_dist(rnd);
    paramaters[3] = theta_dist(rnd);
    paramaters[2] = lambda_dist(rnd);
    paramaters[4] = gamma_dist(rnd);
    paramaters[5] = psi_dist(rnd);
};
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::gabor_filter ( Mat src ) {
    Mat tmp = src.clone(); 
    //tmp.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != GABOR_FILTER_PARAMETER_NUMBER )
        return;
    
    Size size(paramaters[0],paramaters[0]);
    double sigma  = paramaters[1]/((paramaters[0]==0)?1:paramaters[0]);
    double theta  = paramaters[2]*CV_PI/180;
    double lambda = paramaters[3];
    double gamma  = paramaters[4];
    double psi    = paramaters[5]*CV_PI/180;

    filter2D(tmp, tmp, CV_32F, getGaborKernel(size,
                               sigma,
                               theta,
                               lambda,
                               gamma,
                               psi,
                               CV_32F)); 
    
    tmp.convertTo(tmp,CV_8UC1, 255);
    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::randomize_morphological_erode_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(MORPHOLOGICAL_ERODE_PARAMETER_NUMBER);

    uniform_int_distribution<int> element_dist(0,2);
    uniform_int_distribution<int> kernel_size_dist(1,20);

    paramaters[0] = element_dist(rnd);
    paramaters[1] = kernel_size_dist(rnd);

    if ( !(int(paramaters[1])%2) ) {
        paramaters[1]++;
    }
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::morphological_erode ( Mat src ) {
    Mat tmp = src.clone();

    if ( paramaters.size() != MORPHOLOGICAL_ERODE_PARAMETER_NUMBER )
        return;

    int erosion_type = paramaters[0];    
    Size size(2*paramaters[1]+1,2*paramaters[1]+1);
    Point point(paramaters[1],paramaters[1]);
    
    erode( tmp, tmp, getStructuringElement( erosion_type, 
                                            size, 
                                            point ) );

    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_gaussian_blur_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(GAUSSIAN_BLUR_PARAMETER_NUMBER);

    uniform_int_distribution<int> sigmaX_dist(0,10);
    uniform_int_distribution<int> sigmaY_dist(0,10);
    uniform_int_distribution<int> kernel_size_dist(0,20);

    paramaters[0] = kernel_size_dist(rnd);
    paramaters[1] = sigmaX_dist(rnd);
    paramaters[2] = sigmaY_dist(rnd);

    if ( !(int(paramaters[0])%2) ) {
        paramaters[0]++;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::gaussian_blur ( Mat src ) {
    Mat tmp = src.clone();

    if ( paramaters.size() != GAUSSIAN_BLUR_PARAMETER_NUMBER )
        return;
    
    int size = paramaters[0];
    int sigmaX = paramaters[1]; 
    int sigmaY = paramaters[2];
     
    GaussianBlur( tmp, tmp, Size( size, size ), sigmaX, sigmaY );

    transformed_image = tmp.clone();    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::randomize_histogram_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(HISTOGRAM_PARAMETER_NUMBER);

    uniform_int_distribution<int> hbins_dist(1,100);
    uniform_int_distribution<int> sbins_dist(10,100);

    paramaters[0] = hbins_dist(rnd);
    paramaters[1] = sbins_dist(rnd);
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::histogram ( Mat src ) {
    Mat tmp = src.clone();

    if ( paramaters.size() != HISTOGRAM_PARAMETER_NUMBER )
        return;

    int hbins = paramaters[0];
    int sbins = paramaters[1];
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0};

    calcHist( &tmp, 1, channels, Mat(), // do not use mask
              hist, 1, histSize, ranges,
              true, // the histogram is uniform
              false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ ) {
        for (int s = 0; s < sbins; s++) {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal * 255 / maxVal);
            rectangle(histImg, Point(h * scale, s * scale),
                      Point((h + 1) * scale - 1, (s + 1) * scale - 1),
                      Scalar::all(intensity),
                      CV_FILLED);
        }
    }
    cvtColor(histImg, histImg, COLOR_BGR2GRAY);
    resize(histImg,tmp,tmp.size());

    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::randomize_hough_circles_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(HOUGH_CIRCLES_PARAMETER_NUMBER);

    uniform_int_distribution<int> threshold1_dist(50,85);
    uniform_int_distribution<int> threshold2_dist(5,20);
    //uniform_int_distribution<int> distance_dist(1,8);
    //uniform_int_distribution<int> radius_dist(10,30);

    paramaters[0] = threshold1_dist(rnd);
    paramaters[1] = threshold2_dist(rnd);

    while ( paramaters[0] - paramaters[1] > 40 ) {
        paramaters[0] = threshold1_dist(rnd);
        paramaters[1] = threshold2_dist(rnd);
    }
    //paramaters[2] = pow(2,distance_dist(rnd));
    //paramaters[3] = radius_dist(rnd);
    //radius_dist = uniform_int_distribution<int>((int)paramaters[3],100);
    //paramaters[4] = radius_dist(rnd);
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::hough_circles ( Mat src ) {
    Mat tmp = src.clone();

    if ( paramaters.size() != HOUGH_CIRCLES_PARAMETER_NUMBER )
        return;

    medianBlur(tmp,tmp,3);

    int threshold1 = paramaters[0];
    int threshold2 = paramaters[1];
    //int dist = paramaters[2];
    //int min_rad = paramaters[3];
    //int max_rad = paramaters[4];
    int dist = 8;
    int min_rad = 1;
    int max_rad = 30;

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles( tmp, 
                  circles, 
                  CV_HOUGH_GRADIENT, 
                  1, 
                  tmp.rows/dist,
                  threshold1,
                  threshold2,
                  min_rad,
                  max_rad );

    Mat tmp1(tmp.rows,tmp.cols,CV_8UC3,Scalar(0,0,0));

    /// Draw the circles detected
    //for( size_t i = 0; i < circles.size(); i++ ) {
    for ( auto c : circles ) {
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        // circle center
        circle( tmp1, center, 3, Scalar(255,255,255), -1, 8, 0 );
        // circle outline
        circle( tmp1, center, radius, Scalar(255,255,255), 3, 8, 0 );
     }    

    Mat tmp2;
    cvtColor(tmp1,tmp2,CV_BGR2GRAY);
    transformed_image = tmp2.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_normalize_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(NORMALIZE_PARAMETER_NUMBER);

    uniform_int_distribution<int> alpha_dist(0,255);
    uniform_int_distribution<int> beta_dist(0,255);
    uniform_int_distribution<int> norm_dist(1,3);

    paramaters[0] = alpha_dist(rnd);
    paramaters[1] = beta_dist(rnd);
    paramaters[2] = norm_dist(rnd);

    if ( paramaters[2] == 3 ) {
        paramaters[2] = 4;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::normalize ( Mat src ) {
    Mat tmp = src.clone();

    if ( paramaters.size() != NORMALIZE_PARAMETER_NUMBER )
        return;

    int alpha = paramaters[0];
    int beta = paramaters[1];
    int norm = paramaters[2];
    
    cv::normalize(tmp, tmp, alpha, beta, norm);    

    transformed_image = tmp.clone();    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::square_root ( Mat src ) {
    Mat tmp = src.clone();    
    tmp.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != SQUARE_ROOT_PARAMETER_NUMBER )
        return;        
    
    cv::sqrt(tmp,tmp);

    tmp.convertTo(tmp, CV_8UC1, 255, 0);
    transformed_image = tmp.clone(); 
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_canny_edge_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(CANNY_EDGE_PARAMETER_NUMBER);

    uniform_int_distribution<int> threshold_dist(0,100);
    uniform_int_distribution<int> ratio_dist(0,5);

    paramaters[0] = threshold_dist(rnd);
    paramaters[1] = ratio_dist(rnd);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::canny_edge ( Mat src ) {
    Mat tmp = src.clone();

    if ( paramaters.size() != CANNY_EDGE_PARAMETER_NUMBER )
        return; 

    int threshold = (int)paramaters[0];
    int ratio = (int)paramaters[1];

    blur( tmp, tmp, Size(3,3) );

    Canny( tmp, tmp, threshold, threshold*ratio, 3);

    transformed_image = tmp.clone();   
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_integral_image_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(INTEGRAL_IMAGE_PARAMETER_NUMBER);

    uniform_int_distribution<int> type_dist(1,3);
    paramaters[0] = type_dist(rnd);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::integral_image ( cv::Mat src ) {
    Mat tmp = src.clone();
    tmp.convertTo(tmp, CV_32F, 1.0/255.0);
    
    if ( paramaters.size() != INTEGRAL_IMAGE_PARAMETER_NUMBER )
        return;   

    int type = paramaters[0];    
    
    Mat tmp1, tmp2, tmp3;
    
    integral(tmp,tmp1,tmp2,tmp3,CV_32F);
    
    switch ( type )
    {
        case 1: {
            resize(tmp2,tmp,tmp.size());
            tmp.convertTo(tmp,CV_8UC1, 255);
            transformed_image = tmp.clone();
        }
            break;
        case 2: {
            resize(tmp2,tmp,tmp.size());
            tmp.convertTo(tmp,CV_8UC1, 255);
            transformed_image = tmp.clone();
        }
            break;
        case 3: {
            resize(tmp3,tmp,tmp.size());
            tmp.convertTo(tmp,CV_8UC1, 255);
            transformed_image = tmp.clone();
        }
            break;
        default: {
            transformed_image = src.clone();
        }
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
void Transform::randomize_difference_gaussians_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(DIFFERENCE_GAUSSIANS_PARAMETER_NUMBER);

    uniform_int_distribution<int> kern1_dist(1,20);
    uniform_int_distribution<int> kern2_dist(1,20);
    paramaters[0] = kern1_dist(rnd);
    paramaters[1] = kern2_dist(rnd);

    if ( !(int(paramaters[0])%2) )
        paramaters[0]++;

    if ( !(int(paramaters[1])%2) )
        paramaters[1]++;

}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::difference_gaussians ( Mat src ) {
    Mat tmp = src.clone();
    tmp.convertTo(tmp,CV_32F, 1.0/255.0);

    if ( paramaters.size() != DIFFERENCE_GAUSSIANS_PARAMETER_NUMBER )
        return;

    Mat g1, g2;
    int kern1 = paramaters[0];
    int kern2 = paramaters[1];

    GaussianBlur(tmp, g1, Size(kern1,kern1), 0);
    GaussianBlur(tmp, g2, Size(kern2,kern2), 0);
    
    tmp = g1-g2;

    tmp.convertTo(tmp,CV_8U, 255);
    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_census_transform_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(CENSUS_TRANSFORM_PARAMETER_NUMBER);

    //uniform_int_distribution<int> n_dist(1,50);
    //uniform_int_distribution<int> m_dist(1,50);
    uniform_int_distribution<int> n_dist(1,15);
    uniform_int_distribution<int> m_dist(1,15);
    paramaters[0] = n_dist(rnd);
    paramaters[1] = m_dist(rnd);

    if ( !(int(paramaters[0])%2) )
        paramaters[0]++;

    if ( !(int(paramaters[1])%2) )
        paramaters[1]++;

}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : http://hangyinuml.wordpress.com/2012/09/08/census-transform-c-implementation/
********************************************************************************/
void Transform::census_transform ( Mat src ) {
    Mat tmp = src.clone(),tmp1; 
    
    if ( paramaters.size() != CENSUS_TRANSFORM_PARAMETER_NUMBER )
        return;  

    Size imgSize = tmp.size();
    tmp1 = Mat::zeros(imgSize, CV_8U);

    unsigned int census = 0;
    unsigned int bit = 0;
    int m = paramaters[0];
    int n = paramaters[1];//window size
    int i,j,x,y;
    int shiftCount = 0;

    for (x = m/2; x < imgSize.height - m/2; x++)
    {
      for(y = n/2; y < imgSize.width - n/2; y++)
      {
        census = 0;
        shiftCount = 0;
        for (i = x - m/2; i <= x + m/2; i++)
        {
          for (j = y - n/2; j <= y + n/2; j++)
          {

            if( shiftCount != m*n/2 )//skip the center pixel
            {
                census <<= 1;
                if( tmp.at<uchar>(i,j) < tmp.at<uchar>(x,y) )//compare pixel values in the neighborhood
                    bit = 1;
                else
                    bit = 0;

                census = census + bit;
            }
            shiftCount ++;
          }
        }

       //tmp1.ptr<uchar>(x,y) = census;
          tmp1.at<uchar>(x,y) = (unsigned char)census;
      }
    } 

    transformed_image = tmp1.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_sobel_operator_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(SOBEL_OPERATOR_PARAMETER_NUMBER);

    uniform_int_distribution<int> scale_dist(1,10);
    uniform_int_distribution<int> delta_dist(1,10);
    uniform_real_distribution<double> weight_dist(0,1);

    paramaters[0] = scale_dist(rnd);
    paramaters[1] = delta_dist(rnd);
    paramaters[2] = weight_dist(rnd);
    paramaters[3] = weight_dist(rnd);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::sobel_operator ( Mat src ) {
    Mat tmp = src.clone();
    
    if ( paramaters.size() != SOBEL_OPERATOR_PARAMETER_NUMBER )
        return;
    
    int scale = paramaters[0];
    int delta = paramaters[1];
    double x_weight = paramaters[2];    
    double y_weight = paramaters[3];

    GaussianBlur( tmp, tmp, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    Sobel( tmp, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    Sobel( tmp, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, x_weight, abs_grad_y, y_weight, 0, tmp );
    
    tmp.convertTo(tmp,CV_8UC1);
    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_morphological_dilate_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(MORPHOLOGICAL_DILATE_PARAMETER_NUMBER);

    uniform_int_distribution<int> element_dist(0,2);
    uniform_int_distribution<int> kernel_size_dist(0,20);

    int size = kernel_size_dist(rnd);
    if ( size % 2 == 0 ) { size++; };

    paramaters[0] = element_dist(rnd);
    paramaters[1] = size;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::morphological_dilate ( Mat src ) {
    Mat tmp = src.clone();

    if ( paramaters.size() != MORPHOLOGICAL_DILATE_PARAMETER_NUMBER )
        return;

    int dilate_type = paramaters[0];    
    Size size(2*paramaters[1]+1,2*paramaters[1]+1);
    Point point(paramaters[1],paramaters[1]);
    
    dilate( tmp, tmp, getStructuringElement( dilate_type, 
                                             size, 
                                             point ) );    
    
    tmp.convertTo(tmp,CV_8UC1);
    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_adaptive_thresholding_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(ADAPTIVE_THRESHOLDING_PARAMETER_NUMBER);

    uniform_int_distribution<int> threshold_dist(0,255);
    uniform_int_distribution<int> method_dist(0,1);
    uniform_int_distribution<int> type_dist(0,1);
    uniform_int_distribution<int> blocksize_dist(3,20);
    uniform_int_distribution<int> c_dist(1,10);

    paramaters[0] = threshold_dist(rnd);
    paramaters[1] = method_dist(rnd);
    paramaters[2] = type_dist(rnd);
    paramaters[3] = blocksize_dist(rnd);
    paramaters[4] = c_dist(rnd);

    if ( !(int(paramaters[3])%2) ) {
        paramaters[3]++;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::adaptive_thresholding ( Mat src ) {
    Mat tmp = src.clone();
    
    if ( paramaters.size() != ADAPTIVE_THRESHOLDING_PARAMETER_NUMBER )
        return;
    
    int threshold = paramaters[0];
    int method = paramaters[1];
    int type = paramaters[2];
    int blocksize = paramaters[3];
    int c = paramaters[4];

    adaptiveThreshold( tmp, tmp, threshold, method, type, blocksize, c);
    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::randomize_hough_lines_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(HOUGH_LINES_PARAMETER_NUMBER);

    uniform_int_distribution<int> threshold_dist(1,100);
    uniform_int_distribution<int> minlinelength_dist(0,100);
    uniform_int_distribution<int> maxlinegap_dist(0,20);

    paramaters[0] = threshold_dist(rnd);
    paramaters[1] = minlinelength_dist(rnd);
    paramaters[2] = maxlinegap_dist(rnd);
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::hough_lines ( Mat src ) {
    Mat tmp = src.clone(), tmp1;
    if ( paramaters.size() != HOUGH_LINES_PARAMETER_NUMBER )
        return;    

    int threshold = paramaters[0];
    int minlinelength = paramaters[1];
    int maxlinegap = paramaters[2];

    tmp1 = tmp.clone();

    Canny( tmp, tmp1, threshold, threshold*3, 3 );

    vector<Vec4i> lines;
    HoughLinesP(tmp, lines, 1, CV_PI/180, threshold, minlinelength, maxlinegap );

    Mat tmp2(tmp.rows,tmp.cols,CV_8UC1,Scalar(0));
    
    for ( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( tmp2, Point(l[0], l[1]),
                                 Point(l[2], l[3]), 
                                 Scalar(255),
                                 1, 
                                 CV_AA);
    }

    transformed_image = tmp2.clone();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::randomize_harris_corner_strength_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(HARRIS_CORNER_STRENGTH_PARAMETER_NUMBER);

    uniform_int_distribution<int> threshold_dist(3,10);
    uniform_int_distribution<int> minlinelength_dist(10,20);
    uniform_real_distribution<double> k_dist(0,1);

    paramaters[0] = threshold_dist(rnd);
    paramaters[1] = minlinelength_dist(rnd);
    paramaters[2] = k_dist(rnd);

    if ( !(int(paramaters[1])%2) ) {
        paramaters[1]++;
    }

}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::harris_corner_strength ( Mat src ) {
    Mat tmp = src.clone(),tmp1 = src.clone();
    
    if ( paramaters.size() != HARRIS_CORNER_STRENGTH_PARAMETER_NUMBER )
        return;   

    int blockSize = paramaters[0];
    int apertureSize = paramaters[1];
    double k =  paramaters[2];
      
    cornerHarris( tmp, tmp, blockSize, apertureSize, k, BORDER_DEFAULT );  
    cv::normalize( tmp, tmp, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    
    convertScaleAbs( tmp, tmp );


    tmp.convertTo(tmp1,CV_8U,255);
    transformed_image = tmp1.clone();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::histogram_equalization ( Mat src ) {
    Mat tmp = src.clone();
    tmp.convertTo(tmp,CV_8UC1);

    if ( paramaters.size() != HISTOGRAM_EQUALIZATION_PARAMETER_NUMBER )
        return;      

    equalizeHist( tmp, tmp );
    
    tmp.convertTo(tmp,CV_8UC1);
    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::log ( Mat src ) {
    Mat tmp = src.clone();
    
    if ( paramaters.size() != LOG_PARAMETER_NUMBER )
        return; 
    
    src.convertTo(tmp,CV_32F);
    cv::log(tmp, tmp);
    
    tmp.convertTo(tmp,CV_8UC1);
    transformed_image = tmp.clone();;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_median_blur_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(MEDIAN_BLUR_PARAMETER_NUMBER);

    uniform_int_distribution<int> ksize_dist(0,21);

    paramaters[0] = ksize_dist(rnd);

    if ( !(int(paramaters[0])%2) ) {
        paramaters[0]++;
    }
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::median_blur ( Mat src ) {
    Mat tmp = src.clone();
    
    if ( paramaters.size() != MEDIAN_BLUR_PARAMETER_NUMBER )
        return;     

    
    int ksize = paramaters[0];
    
    src.convertTo(tmp,CV_8UC1);
    medianBlur(tmp, tmp, ksize);
    
    transformed_image = tmp.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_distance_transform_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(DISTANCE_TRANSFORM_PARAMETER_NUMBER);

    uniform_int_distribution<int> distance_dist(1,3);
    uniform_int_distribution<int> mask_dist(0,2);
    uniform_int_distribution<int> thresh_dist(0,255);

    paramaters[0] = distance_dist(rnd);
    paramaters[1] = mask_dist(rnd);
    paramaters[2] = thresh_dist(rnd);

    if ( paramaters[1] == 1 ) {
        paramaters[1] = 3;
    } else if ( paramaters[1] == 2 ) {
        paramaters[1] = 5;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      :
********************************************************************************/
void Transform::distance_transform ( Mat src ) {
    Mat tmp1 = src.clone(),tmp = src.clone();
    
    if ( paramaters.size() != DISTANCE_TRANSFORM_PARAMETER_NUMBER )
        return;    

    int dist = paramaters[0];
    int mask = paramaters[1];
    int thresh = paramaters[2];

    tmp.convertTo(tmp1,CV_32FC1, 1.0/255);
    threshold(tmp, tmp, thresh, 255, CV_THRESH_BINARY);
    distanceTransform(tmp, tmp1, dist, mask); 
    cv::normalize(tmp1, tmp1, 0, 1.0, NORM_MINMAX);
    
    tmp1.convertTo(tmp1,CV_8UC1, 255);
    transformed_image = tmp1.clone();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_laplacian_edged_detection_parameters ( int seed ) {
    mt19937 rnd(seed);

    paramaters.resize(DISTANCE_TRANSFORM_PARAMETER_NUMBER);

    uniform_int_distribution<int> ksize_dist(1,21);
    uniform_int_distribution<int> scale_dist(0,10);
    uniform_int_distribution<int> delta_dist(0,10);

    paramaters[0] = ksize_dist(rnd);
    paramaters[1] = scale_dist(rnd);
    paramaters[2] = delta_dist(rnd);

    if ( !(int(paramaters[0])%2) )
        paramaters[0]++;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::laplacian_edged_detection ( cv::Mat src ) {
    Mat tmp = src.clone();
    
    if ( paramaters.size() != DISTANCE_TRANSFORM_PARAMETER_NUMBER )
        return;    

    GaussianBlur( tmp, tmp, Size(3,3), 0, 0, BORDER_DEFAULT );    

    int kernel_size = paramaters[0];
    int scale = paramaters[1];
    int delta = paramaters[2];

    Laplacian( tmp, tmp, CV_16S, kernel_size, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( tmp, tmp );
    
    tmp.convertTo(tmp,CV_8UC1);
    transformed_image = tmp.clone();
}