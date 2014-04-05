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
#define MORPHOLOGICAL_DILATE_PARAMETER_NUMBER 1
#define ADAPTIVE_THRESHOLDING_PARAMETER_NUMBER 3
#define HOUGH_LINES_PARAMETER_NUMBER 2
#define HARRIS_CORNER_STRENGTH_PARAMETER_NUMBER 3
#define HISTOGRAM_EQUALIZATION_PARAMETER_NUMBER 0
#define LOG_PARAMETER_NUMBER 0
#define MEDIAN_BLUR_PARAMETER_NUMBER 1
#define DISTANCE_TRANSFORM_PARAMETER_NUMBER 2
#define LAPLACIAN_EDGED_ETECTION_PARAMETER_NUMBER 1
#define RANK_TRANSFORM_PARAMETER_NUMBER 0
#define CONVERT_PARAMETER_NUMBER 0
/*******************************************************************************
*  MACROS
********************************************************************************/

/*******************************************************************************
*  DATA TYPES
********************************************************************************/
typedef enum _TRANFORM_TYPE {
    NIL = 0,
    GABOR_FILTER,
    MORPHOLOGICAL_ERODE,
    GAUSSIAN_BLUR,
    HISTOGRAM,
    HOUGH_CIRCLES,
    NORMALIZE,
    DISCRETE_FOURIER_TRANSFORM,
    SQUARE_ROOT,
    CANNY_EDGE,
    INTEGRAL_IMAGE,
    DIFFERENCE_GAUSSIANS,
    CENSUS_TRANSFORM,
    SOBEL_OPERATOR,
    MORPHOLOGICAL_DILATE,
    ADAPTIVE_THRESHOLDING,
    HOUGH_LINES,
    HARRIS_CORNER_STRENGTH,
    HISTOGRAM_EQUALIZATION,
    LOG,
    MEDIAN_BLUR,
    DISTANCE_TRANSFORM,
    LAPLACIAN_EDGED_ETECTION,
    RANK_TRANSFORM,
    CONVERT
}TRANFORM_TYPE;

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
        Transform ( Transform& ); /* copy */
        Transform& operator= ( const Transform& ); /* assign */
        ~Transform ( void );
        
        /* functions */
        void perform_transform ( cv::Mat );
        void perform_transform ( cv::Mat, TRANFORM_TYPE );
        cv::Mat get_transform ( void );
        void set_transform_type ( TRANFORM_TYPE );
        TRANFORM_TYPE get_transform_type ( void );
        
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
        void laplacian_edged_etection ( cv::Mat );
        void rank_transform ( cv::Mat );
        void convert ( cv::Mat );        
};
}
#endif
