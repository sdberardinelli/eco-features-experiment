/******************************************************************************
 * Filename      : Transform.cpp
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
#include <valarray>

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
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Transform::Transform ( void ) { ; }
/*******************************************************************************
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Transform::Transform ( TRANFORM_TYPE _transform_type )
{ 
    transform_type = _transform_type;
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Transform::Transform ( Transform& obj ) { ; }
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Transform::~Transform ( void ) { ; }
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Transform& Transform::operator=( const Transform& obj ) 
{
    if (this != &obj) // prevent self-assignment
    {
        ;
    }
    return *this;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::set_transform_type ( TRANFORM_TYPE _transform_type)
{
    transform_type = _transform_type;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
TRANFORM_TYPE Transform::get_transform_type ( void )
{
    return transform_type;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::set_parameters ( valarray<double>& _paramaters )
{
    paramaters = _paramaters;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
valarray<double>& Transform::get_paramaters ( void )
{
    return paramaters;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Mat Transform::get_transform ( void )
{
    return transformed_image;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::perform_transform ( Mat src )
{
    switch ( transform_type )
    {
        case GABOR_FILTER:
            gabor_filter(src);
            break;
        case MORPHOLOGICAL_ERODE:
            morphological_erode(src);
            break;
        case HAUSSIAN_BLUR:
            haussian_blur(src);
            break;
        case HISTOGRAM:
            histogram(src);
            break;
        case HOUGH_CIRCLES:
            hough_circles(src);
            break;
        case NORMALIZE:
            normalize(src);
            break;
        case DISCRETE_FOURIER_TRANSFORM:
            discrete_fourier_transform(src);
            break;
        case SQUARE_ROOT:
            square_root(src);
            break;
        case CANNY_EDGE:
            canny_edge(src);
            break;
        case INTEGRAL_IMAGE:
            integral_image(src);
            break;
        case DIFFERENCE_GAUSSIANS:
            difference_gaussians(src);
            break;
        case CENSUS_TRANSFORM:
            census_transform(src);
            break;
        case SOBEL_OPERATOR:
            sobel_operator(src);
            break;
        case MORPHOLOGICAL_DILATE:
            morphological_dilate(src);
            break;
        case ADAPTIVE_THRESHOLDING:
            adaptive_thresholding(src);
            break;
        case HOUGH_LINES:
            hough_lines(src);
            break;
        case HARRIS_CORNER_STRENGTH:
            harris_corner_strength(src);
            break;
        case HISTOGRAM_EQUALIZATION:
            histogram_equalization(src);
            break;
        case LOG:
            log(src);
            break;
        case MEDIAN_BLUR:
            median_blur(src);
            break;
        case DISTANCE_TRANSFORM:
            distance_transform(src);
            break;
        case LAPLACIAN_EDGED_ETECTION:
            laplacian_edged_etection(src);
            break;
        case RANK_TRANSFORM:
            rank_transform(src);
            break;
        case CONVERT:
            convert(src);
            break;
        default:
            transformed_image = src;
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
void Transform::perform_transform ( Mat src, TRANFORM_TYPE _transform_type )
{
    switch ( _transform_type )
    {
        case GABOR_FILTER:
            gabor_filter(src);
            break;
        case MORPHOLOGICAL_ERODE:
            morphological_erode(src);
            break;
        case HAUSSIAN_BLUR:
            haussian_blur(src);
            break;
        case HISTOGRAM:
            histogram(src);
            break;
        case HOUGH_CIRCLES:
            hough_circles(src);
            break;
        case NORMALIZE:
            normalize(src);
            break;
        case DISCRETE_FOURIER_TRANSFORM:
            discrete_fourier_transform(src);
            break;
        case SQUARE_ROOT:
            square_root(src);
            break;
        case CANNY_EDGE:
            canny_edge(src);
            break;
        case INTEGRAL_IMAGE:
            integral_image(src);
            break;
        case DIFFERENCE_GAUSSIANS:
            difference_gaussians(src);
            break;
        case CENSUS_TRANSFORM:
            census_transform(src);
            break;
        case SOBEL_OPERATOR:
            sobel_operator(src);
            break;
        case MORPHOLOGICAL_DILATE:
            morphological_dilate(src);
            break;
        case ADAPTIVE_THRESHOLDING:
            adaptive_thresholding(src);
            break;
        case HOUGH_LINES:
            hough_lines(src);
            break;
        case HARRIS_CORNER_STRENGTH:
            harris_corner_strength(src);
            break;
        case HISTOGRAM_EQUALIZATION:
            histogram_equalization(src);
            break;
        case LOG:
            log(src);
            break;
        case MEDIAN_BLUR:
            median_blur(src);
            break;
        case DISTANCE_TRANSFORM:
            distance_transform(src);
            break;
        case LAPLACIAN_EDGED_ETECTION:
            laplacian_edged_etection(src);
            break;
        case RANK_TRANSFORM:
            rank_transform(src);
            break;
        case CONVERT:
            convert(src);
            break;
        default:
            transformed_image = src;
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


