/******************************************************************************
 * Filename      : Transform.hpp
 * Source File(s): Transform.cpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#ifndef TRANSFORM_H
#define TRANSFORM_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <opencv2/core/core.hpp>
#include <valarray>

/*******************************************************************************
*  DEFINES
********************************************************************************/
namespace Transforms
{
#define GABOR_FILTER_PARAMETER_NUMBER 6
#define MORPHOLOGICAL_ERODE_PARAMETER_NUMBER 2
#define GAUSSIAN_BLUR_PARAMETER_NUMBER 3
#define HISTOGRAM_PARAMETER_NUMBER 2
#define HOUGH_CIRCLES_PARAMETER_NUMBER 2
#define NORMALIZE_PARAMETER_NUMBER 3
#define SQUARE_ROOT_PARAMETER_NUMBER 0
#define CANNY_EDGE_PARAMETER_NUMBER 2
#define INTEGRAL_IMAGE_PARAMETER_NUMBER 1
#define DIFFERENCE_GAUSSIANS_PARAMETER_NUMBER 2
#define CENSUS_TRANSFORM_PARAMETER_NUMBER 2
#define SOBEL_OPERATOR_PARAMETER_NUMBER 4
#define MORPHOLOGICAL_DILATE_PARAMETER_NUMBER 2
#define ADAPTIVE_THRESHOLDING_PARAMETER_NUMBER 5
#define HOUGH_LINES_PARAMETER_NUMBER 3
#define HARRIS_CORNER_STRENGTH_PARAMETER_NUMBER 3
#define HISTOGRAM_EQUALIZATION_PARAMETER_NUMBER 0
#define LOG_PARAMETER_NUMBER 0
#define MEDIAN_BLUR_PARAMETER_NUMBER 1
#define DISTANCE_TRANSFORM_PARAMETER_NUMBER 3
#define LAPLACIAN_EDGED_ETECTION_PARAMETER_NUMBER 3

/*******************************************************************************
*  MACROS
********************************************************************************/

/*******************************************************************************
*  DATA TYPES
********************************************************************************/
typedef enum _TRANFORM_TYPE {
    NIL = 0,
    GABOR_FILTER                =1,
    MORPHOLOGICAL_ERODE         =2,
    GAUSSIAN_BLUR               =3,
    HISTOGRAM                   =4,
    HOUGH_CIRCLES               =5,
    NORMALIZE                   =6,
    SQUARE_ROOT                 =7,
    CANNY_EDGE                  =8,
    INTEGRAL_IMAGE              =9,
    DIFFERENCE_GAUSSIANS        =10,
    CENSUS_TRANSFORM            =11,
    SOBEL_OPERATOR              =12,
    MORPHOLOGICAL_DILATE        =13,
    ADAPTIVE_THRESHOLDING       =14,
    HOUGH_LINES                 =15,
    HARRIS_CORNER_STRENGTH      =16,
    HISTOGRAM_EQUALIZATION      =17,
    LOG                         =18,
    MEDIAN_BLUR                 =19,
    DISTANCE_TRANSFORM          =20,
    LAPLACIAN_EDGED_ETECTION    =21,
    TRANSORM_NUM
}TRANFORM_TYPE;

inline int parametersize ( TRANFORM_TYPE in )
{
    switch ( in )
    {
        case GABOR_FILTER:                return GABOR_FILTER_PARAMETER_NUMBER;
        case MORPHOLOGICAL_ERODE:         return MORPHOLOGICAL_ERODE_PARAMETER_NUMBER;
        case GAUSSIAN_BLUR:               return GAUSSIAN_BLUR_PARAMETER_NUMBER;
        case HISTOGRAM:                   return HISTOGRAM_PARAMETER_NUMBER;
        case HOUGH_CIRCLES:               return HOUGH_CIRCLES_PARAMETER_NUMBER;
        case NORMALIZE:                   return NORMALIZE_PARAMETER_NUMBER;
        case SQUARE_ROOT:                 return SQUARE_ROOT_PARAMETER_NUMBER;
        case CANNY_EDGE:                  return CANNY_EDGE_PARAMETER_NUMBER;
        case INTEGRAL_IMAGE:              return INTEGRAL_IMAGE_PARAMETER_NUMBER;
        case DIFFERENCE_GAUSSIANS:        return DIFFERENCE_GAUSSIANS_PARAMETER_NUMBER;
        case CENSUS_TRANSFORM:            return CENSUS_TRANSFORM_PARAMETER_NUMBER;
        case SOBEL_OPERATOR:              return SOBEL_OPERATOR_PARAMETER_NUMBER;
        case MORPHOLOGICAL_DILATE:        return MORPHOLOGICAL_DILATE_PARAMETER_NUMBER;
        case ADAPTIVE_THRESHOLDING:       return ADAPTIVE_THRESHOLDING_PARAMETER_NUMBER;
        case HOUGH_LINES:                 return HOUGH_LINES_PARAMETER_NUMBER;
        case HARRIS_CORNER_STRENGTH:      return HARRIS_CORNER_STRENGTH_PARAMETER_NUMBER;
        case HISTOGRAM_EQUALIZATION:      return HISTOGRAM_EQUALIZATION_PARAMETER_NUMBER;
        case LOG:                         return LOG_PARAMETER_NUMBER;
        case MEDIAN_BLUR:                 return MEDIAN_BLUR_PARAMETER_NUMBER;
        case DISTANCE_TRANSFORM:          return DISTANCE_TRANSFORM_PARAMETER_NUMBER;
        case LAPLACIAN_EDGED_ETECTION:    return LAPLACIAN_EDGED_ETECTION_PARAMETER_NUMBER;
        default: break;
    }

    return 0;
} 

/*******************************************************************************
*  EXTERNALS
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
class Transform
{
    public: 
        /* constructors */
        Transform ( void ); /* default */
        Transform ( TRANFORM_TYPE ); /* default */
        Transform ( const Transform& ); /* copy */
        Transform& operator= ( const Transform& ); /* assign */
        ~Transform ( void );
        
        /* functions */
        void perform_transform ( cv::Mat );
        void perform_transform ( cv::Mat, TRANFORM_TYPE );
        cv::Mat get_transform ( void );
        void set_transform_type ( TRANFORM_TYPE );
        TRANFORM_TYPE get_transform_type ( void );
        std::string to_string ( void );
        
        void set_parameter ( int, double );
        void set_parameters ( std::valarray<double>& );
        std::valarray<double>& get_paramaters ( void );
        void randomize_parameters ( int );
        int get_paramater_size ( void );

    private:
        
        std::valarray<double> paramaters;
        TRANFORM_TYPE transform_type;
        cv::Mat transformed_image;

        void randomize_gabor_filter_parameters ( int );
        void gabor_filter ( cv::Mat );
        void randomize_morphological_erode_parameters ( int );
        void morphological_erode ( cv::Mat );
        void randomize_gaussian_blur_parameters ( int );
        void gaussian_blur ( cv::Mat );
        void randomize_histogram_parameters ( int );
        void histogram ( cv::Mat );
        void randomize_hough_circles_parameters ( int );
        void hough_circles ( cv::Mat );
        void randomize_normalize_parameters ( int );
        void normalize  ( cv::Mat );
        void square_root ( cv::Mat );
        void randomize_canny_edge_parameters ( int );
        void canny_edge ( cv::Mat );
        void randomize_integral_image_parameters ( int );
        void integral_image ( cv::Mat );
        void randomize_difference_gaussians_parameters ( int );
        void difference_gaussians ( cv::Mat );
        void randomize_census_transform_parameters ( int );
        void census_transform ( cv::Mat );
        void randomize_sobel_operator_parameters ( int );
        void sobel_operator ( cv::Mat );
        void randomize_morphological_dilate_parameters ( int );
        void morphological_dilate ( cv::Mat );
        void randomize_adaptive_thresholding_parameters ( int );
        void adaptive_thresholding ( cv::Mat );
        void randomize_hough_lines_parameters ( int );
        void hough_lines ( cv::Mat );
        void randomize_harris_corner_strength_parameters ( int );
        void harris_corner_strength ( cv::Mat );
        void histogram_equalization ( cv::Mat );
        void log ( cv::Mat );
        void randomize_median_blur_parameters ( int );
        void median_blur ( cv::Mat );
        void randomize_distance_transform_parameters ( int );
        void distance_transform ( cv::Mat );
        void randomize_laplacian_edged_detection_parameters ( int );
        void laplacian_edged_detection ( cv::Mat );
    };
}
#endif
