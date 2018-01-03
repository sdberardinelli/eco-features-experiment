/******************************************************************************
 * Filename      : Image.hpp
 * Source File(s): Image.cpp
 * Description   :
 * Authors(s)    :
 * Date Created  :
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#ifndef IMAGE_H
#define IMAGE_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

/*******************************************************************************
*  DEFINES
********************************************************************************/
namespace Data
{
/*******************************************************************************
*  MACROS
********************************************************************************/

/*******************************************************************************
*  DATA TYPES
********************************************************************************/

/*******************************************************************************
*  EXTERNALS
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
class Image
{
    public:
        /* constructors */
        Image ( void ); /* default */
        Image ( std::string, cv::Mat, std::vector<int> );
        Image ( std::string, cv::Mat, int );
        Image ( const Image& ); /* copy */
        Image& operator= ( const Image& ); /* assign */
        ~Image ( void );

        /* functions */
        void set_image ( cv::Mat );
        cv::Mat get_image ( void );

        void set_roi ( std::vector<int>& );
        std::vector<int> get_roi ( void );

        void set_name ( std::string );
        std::string get_name ( void );

        void set_label ( int );
        int get_label ( void );

    private:
        std::string name;
        cv::Mat image;
        std::vector<int> roi;
        int label;
};
}
#endif
