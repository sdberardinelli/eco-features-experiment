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
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Transform::Transform ( void ) { transform_type = NIL; }
/*******************************************************************************
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Transform::Transform ( TRANFORM_TYPE _transform_type ) {
    transform_type = _transform_type;
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Transform::Transform ( const Transform& obj ) {
    this->paramaters = obj.paramaters;
    this->transform_type = obj.transform_type;
    this->transformed_image = obj.transformed_image;   
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Transform::~Transform ( void ) {
    paramaters.resize(0);
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Transform& Transform::operator=( const Transform& obj ) {
    if (this != &obj) // prevent self-assignment
    {
        this->paramaters = obj.paramaters;
        this->transform_type = obj.transform_type;
        this->transformed_image = obj.transformed_image;
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
void Transform::set_transform_type ( TRANFORM_TYPE _transform_type) {
    transform_type = _transform_type;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
TRANFORM_TYPE Transform::get_transform_type ( void ) {
    return transform_type;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::set_parameters ( valarray<double>& _paramaters ) {
    paramaters = _paramaters;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::set_parameter ( int i, double value ) {
    if ( i < 0 || i > paramaters.size() )
        return;
    
    paramaters[i] = value;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
valarray<double>& Transform::get_paramaters ( void ) {
    return paramaters;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Mat Transform::get_transform ( void ) {
    return transformed_image;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::perform_transform ( Mat src ) {
    switch ( transform_type )
    {
        case GABOR_FILTER:               { gabor_filter(src);               } break;
        case MORPHOLOGICAL_ERODE:        { morphological_erode(src);        } break;
        case GAUSSIAN_BLUR:              { gaussian_blur(src);              } break;
        case HISTOGRAM:                  { histogram(src);                  } break;
        case HOUGH_CIRCLES:              { hough_circles(src);              } break;
        case NORMALIZE:                  { normalize(src);                  } break;
        case SQUARE_ROOT:                { square_root(src);                } break;
        case CANNY_EDGE:                 { canny_edge(src);                 } break;
        case INTEGRAL_IMAGE:             { integral_image(src);             } break;
        case DIFFERENCE_GAUSSIANS:       { difference_gaussians(src);       } break;
        case CENSUS_TRANSFORM:           { census_transform(src);           } break;
        case SOBEL_OPERATOR:             { sobel_operator(src);             } break;
        case MORPHOLOGICAL_DILATE:       { morphological_dilate(src);       } break;
        case ADAPTIVE_THRESHOLDING:      { adaptive_thresholding(src);      } break;
        case HOUGH_LINES:                { hough_lines(src);                } break;
        case HARRIS_CORNER_STRENGTH:     { harris_corner_strength(src);     } break;
        case HISTOGRAM_EQUALIZATION:     { histogram_equalization(src);     } break;
        case LOG:                        { log(src);                        } break;
        case MEDIAN_BLUR:                { median_blur(src);                } break;
        case DISTANCE_TRANSFORM:         { distance_transform(src);         } break;
        case LAPLACIAN_EDGED_ETECTION:   { laplacian_edged_detection(src);  } break;
        default: { transformed_image = src; } break;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::perform_transform ( Mat src, TRANFORM_TYPE _transform_type ) {
    switch ( _transform_type )
    {
        case GABOR_FILTER:               { gabor_filter(src);               } break;
        case MORPHOLOGICAL_ERODE:        { morphological_erode(src);        } break;
        case GAUSSIAN_BLUR:              { gaussian_blur(src);              } break;
        case HISTOGRAM:                  { histogram(src);                  } break;
        case HOUGH_CIRCLES:              { hough_circles(src);              } break;
        case NORMALIZE:                  { normalize(src);                  } break;
        case SQUARE_ROOT:                { square_root(src);                } break;
        case CANNY_EDGE:                 { canny_edge(src);                 } break;
        case INTEGRAL_IMAGE:             { integral_image(src);             } break;
        case DIFFERENCE_GAUSSIANS:       { difference_gaussians(src);       } break;
        case CENSUS_TRANSFORM:           { census_transform(src);           } break;
        case SOBEL_OPERATOR:             { sobel_operator(src);             } break;
        case MORPHOLOGICAL_DILATE:       { morphological_dilate(src);       } break;
        case ADAPTIVE_THRESHOLDING:      { adaptive_thresholding(src);      } break;
        case HOUGH_LINES:                { hough_lines(src);                } break;
        case HARRIS_CORNER_STRENGTH:     { harris_corner_strength(src);     } break;
        case HISTOGRAM_EQUALIZATION:     { histogram_equalization(src);     } break;
        case LOG:                        { log(src);                        } break;
        case MEDIAN_BLUR:                { median_blur(src);                } break;
        case DISTANCE_TRANSFORM:         { distance_transform(src);         } break;
        case LAPLACIAN_EDGED_ETECTION:   { laplacian_edged_detection(src);  } break;
        default: { transformed_image = src; } break;
    }
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Transform::randomize_parameters ( int seed ) {
    switch ( transform_type )
    {
        case GABOR_FILTER:               { randomize_gabor_filter_parameters(seed);               } break;
        case MORPHOLOGICAL_ERODE:        { randomize_morphological_erode_parameters(seed);        } break;
        case GAUSSIAN_BLUR:              { randomize_gaussian_blur_parameters(seed);              } break;
        case HISTOGRAM:                  { randomize_histogram_parameters(seed);                  } break;
        case HOUGH_CIRCLES:              { randomize_hough_circles_parameters(seed);              } break;
        case NORMALIZE:                  { randomize_normalize_parameters(seed);                  } break;
        case CANNY_EDGE:                 { randomize_canny_edge_parameters(seed);                 } break;
        case INTEGRAL_IMAGE:             { randomize_integral_image_parameters(seed);             } break;
        case DIFFERENCE_GAUSSIANS:       { randomize_difference_gaussians_parameters(seed);       } break;
        case CENSUS_TRANSFORM:           { randomize_census_transform_parameters(seed);           } break;
        case SOBEL_OPERATOR:             { randomize_sobel_operator_parameters(seed);             } break;
        case MORPHOLOGICAL_DILATE:       { randomize_morphological_dilate_parameters(seed);       } break;
        case ADAPTIVE_THRESHOLDING:      { randomize_adaptive_thresholding_parameters(seed);      } break;
        case HOUGH_LINES:                { randomize_hough_lines_parameters(seed);                } break;
        case HARRIS_CORNER_STRENGTH:     { randomize_harris_corner_strength_parameters(seed);     } break;
        case MEDIAN_BLUR:                { randomize_median_blur_parameters(seed);                } break;
        case DISTANCE_TRANSFORM:         { randomize_distance_transform_parameters(seed);         } break;
        case LAPLACIAN_EDGED_ETECTION:   { randomize_laplacian_edged_detection_parameters(seed);  } break;
        default: { ; } break;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
string Transform::to_string ( void ) {
    string transform_str;
    switch ( transform_type ) {
        case GABOR_FILTER: { transform_str = "GABOR_FILTER" ;} break;
        case MORPHOLOGICAL_ERODE: { transform_str = "MORPHOLOGICAL_ERODE" ;} break;
        case GAUSSIAN_BLUR: { transform_str = "GAUSSIAN_BLUR" ;} break;
        case HISTOGRAM: { transform_str = "HISTOGRAM" ;} break;
        case HOUGH_CIRCLES: { transform_str = "HOUGH_CIRCLES" ;} break;
        case NORMALIZE: { transform_str = "NORMALIZE" ;} break;
        case SQUARE_ROOT: { transform_str = "SQUARE_ROOT" ;} break;
        case CANNY_EDGE: { transform_str = "CANNY_EDGE" ;} break;
        case INTEGRAL_IMAGE: { transform_str = "INTEGRAL_IMAGE" ;} break;
        case DIFFERENCE_GAUSSIANS: { transform_str = "DIFFERENCE_GAUSSIANS" ;} break;
        case CENSUS_TRANSFORM: { transform_str = "CENSUS_TRANSFORM" ;} break;
        case SOBEL_OPERATOR: { transform_str = "SOBEL_OPERATOR" ;} break;
        case MORPHOLOGICAL_DILATE: { transform_str = "MORPHOLOGICAL_DILATE" ;} break;
        case ADAPTIVE_THRESHOLDING: { transform_str = "ADAPTIVE_THRESHOLDING" ;} break;
        case HOUGH_LINES: { transform_str = "HOUGH_LINES" ;} break;
        case HARRIS_CORNER_STRENGTH: { transform_str = "HARRIS_CORNER_STRENGTH" ;} break;
        case HISTOGRAM_EQUALIZATION: { transform_str = "HISTOGRAM_EQUALIZATION" ;} break;
        case LOG: { transform_str = "LOG" ;} break;
        case MEDIAN_BLUR: { transform_str = "MEDIAN_BLUR" ;} break;
        case DISTANCE_TRANSFORM: { transform_str = "DISTANCE_TRANSFORM" ;} break;
        case LAPLACIAN_EDGED_ETECTION: { transform_str = "LAPLACIAN_EDGED_ETECTION" ;} break;
        default: { transform_str = "none"; }
    }
    return transform_str;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
int Transform::get_paramater_size ( void ) {
    switch ( transform_type ) {
        case GABOR_FILTER:             { return GABOR_FILTER_PARAMETER_NUMBER;}
        case MORPHOLOGICAL_ERODE:      { return MORPHOLOGICAL_ERODE_PARAMETER_NUMBER;}
        case GAUSSIAN_BLUR:            { return GAUSSIAN_BLUR_PARAMETER_NUMBER;}
        case HISTOGRAM:                { return HISTOGRAM_PARAMETER_NUMBER;}
        case HOUGH_CIRCLES:            { return HOUGH_CIRCLES_PARAMETER_NUMBER;}
        case NORMALIZE:                { return NORMALIZE_PARAMETER_NUMBER;}
        case SQUARE_ROOT:              { return SQUARE_ROOT_PARAMETER_NUMBER;}
        case CANNY_EDGE:               { return CANNY_EDGE_PARAMETER_NUMBER;}
        case INTEGRAL_IMAGE:           { return INTEGRAL_IMAGE_PARAMETER_NUMBER;}
        case DIFFERENCE_GAUSSIANS:     { return DIFFERENCE_GAUSSIANS_PARAMETER_NUMBER;}
        case CENSUS_TRANSFORM:         { return CENSUS_TRANSFORM_PARAMETER_NUMBER;}
        case SOBEL_OPERATOR:           { return SOBEL_OPERATOR_PARAMETER_NUMBER;}
        case MORPHOLOGICAL_DILATE:     { return MORPHOLOGICAL_DILATE_PARAMETER_NUMBER;}
        case ADAPTIVE_THRESHOLDING:    { return ADAPTIVE_THRESHOLDING_PARAMETER_NUMBER;}
        case HOUGH_LINES:              { return HOUGH_LINES_PARAMETER_NUMBER;}
        case HARRIS_CORNER_STRENGTH:   { return HARRIS_CORNER_STRENGTH_PARAMETER_NUMBER;}
        case HISTOGRAM_EQUALIZATION:   { return HISTOGRAM_EQUALIZATION_PARAMETER_NUMBER;}
        case LOG:                      { return LOG_PARAMETER_NUMBER;}
        case MEDIAN_BLUR:              { return MEDIAN_BLUR_PARAMETER_NUMBER;}
        case DISTANCE_TRANSFORM:       { return DISTANCE_TRANSFORM_PARAMETER_NUMBER;}
        case LAPLACIAN_EDGED_ETECTION: { return LAPLACIAN_EDGED_ETECTION_PARAMETER_NUMBER;}
        default: { return 0; }
    }
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/




