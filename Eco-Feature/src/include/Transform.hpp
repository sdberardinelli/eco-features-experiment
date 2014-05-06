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
#define HISTOGRAM_PARAMETER_NUMBER 0
#define HOUGH_CIRCLES_PARAMETER_NUMBER 2
#define NORMALIZE_PARAMETER_NUMBER 3
#define DISCRETE_FOURIER_TRANSFORM_PARAMETER_NUMBER 1
#define SQUARE_ROOT_PARAMETER_NUMBER 0
#define CANNY_EDGE_PARAMETER_NUMBER 1
#define INTEGRAL_IMAGE_PARAMETER_NUMBER 1
#define DIFFERENCE_GAUSSIANS_PARAMETER_NUMBER 2
#define CENSUS_TRANSFORM_PARAMETER_NUMBER 1
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
#define RANK_TRANSFORM_PARAMETER_NUMBER 0
#define CONVERT_PARAMETER_NUMBER 0
    
#define MINIMUM_TRANFORMS 2
#define MAXIMUM_TRANFORMS 8
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
    DISCRETE_FOURIER_TRANSFORM  =7,
    SQUARE_ROOT                 =8,
    CANNY_EDGE                  =9,
    INTEGRAL_IMAGE              =10,
    DIFFERENCE_GAUSSIANS        =11,
    CENSUS_TRANSFORM            =12,
    SOBEL_OPERATOR              =13,
    MORPHOLOGICAL_DILATE        =14,
    ADAPTIVE_THRESHOLDING       =15,
    HOUGH_LINES                 =16,
    HARRIS_CORNER_STRENGTH      =17,
    HISTOGRAM_EQUALIZATION      =18,
    LOG                         =19,
    MEDIAN_BLUR                 =20,
    DISTANCE_TRANSFORM          =21,
    LAPLACIAN_EDGED_ETECTION    =22,
    TRANSORM_NUM
}TRANFORM_TYPE;

inline int ParamterSize ( TRANFORM_TYPE in )
{
    switch ( in )
    {
        case GABOR_FILTER:                return GABOR_FILTER_PARAMETER_NUMBER;
        case MORPHOLOGICAL_ERODE:         return MORPHOLOGICAL_ERODE_PARAMETER_NUMBER;
        case GAUSSIAN_BLUR:               return GAUSSIAN_BLUR_PARAMETER_NUMBER;
        case HISTOGRAM:                   return HISTOGRAM_PARAMETER_NUMBER;
        case HOUGH_CIRCLES:               return HOUGH_CIRCLES_PARAMETER_NUMBER;
        case NORMALIZE:                   return NORMALIZE_PARAMETER_NUMBER;
        case DISCRETE_FOURIER_TRANSFORM:  return DISCRETE_FOURIER_TRANSFORM_PARAMETER_NUMBER;
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
        
        void set_parameter ( int, double );
        void set_parameters ( std::valarray<double>& );
        std::valarray<double>& get_paramaters ( void );       
        
    private:
        
        std::valarray<double> paramaters;
        TRANFORM_TYPE transform_type;
        cv::Mat transformed_image;
        
        void gabor_filter ( cv::Mat );
        void morphological_erode ( cv::Mat );
        void gaussian_blur ( cv::Mat );
        void histogram ( cv::Mat );
        void hough_circles ( cv::Mat );
        void normalize  ( cv::Mat );
        void discrete_fourier_transform ( cv::Mat );
        void square_root ( cv::Mat );
        void canny_edge ( cv::Mat );
        void integral_image ( cv::Mat );
        void difference_gaussians ( cv::Mat );
        void census_transform ( cv::Mat );
        void sobel_operator ( cv::Mat );
        void morphological_dilate ( cv::Mat );
        void adaptive_thresholding ( cv::Mat );
        void hough_lines ( cv::Mat );
        void harris_corner_strength ( cv::Mat );
        void histogram_equalization ( cv::Mat );
        void log ( cv::Mat );
        void median_blur ( cv::Mat );
        void distance_transform ( cv::Mat );
        void laplacian_edged_detection ( cv::Mat );    
};
}
#endif
