/******************************************************************************
 * Filename      : Subregion.hpp
 * Source File(s): Subregion.cpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#ifndef SUBREGION_H
#define SUBREGION_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <opencv2/core/core.hpp>
#include <valarray>

/*******************************************************************************
*  DEFINES
********************************************************************************/
namespace Subregions
{
#define MAXIMUM_WIDTH  1000
#define MAXIMUM_HEIGHT 749
    
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
class Subregion
{
    public: 
        /* constructors */
        Subregion ( void ); /* default */
        Subregion ( cv::Mat ); 
        Subregion ( int,int,int,int ); 
        Subregion ( cv::Mat,int,int,int,int ); 
        Subregion ( const Subregion& ); /* copy */
        Subregion& operator= ( const Subregion& ); /* assign */
        ~Subregion ( void );
        
        /* functions */
        void    set_original  ( cv::Mat );
        void    set_subregion ( cv::Mat, int,int,int,int );
        void    set_subregion ( int,int,int,int );
        cv::Mat get_subregion ( void );   
        std::valarray<int>
        get_subregion_values ( void );
        
    private:
        
        void    construct_subregion ( void );
        int     x1;
        int     x2;
        int     y1;
        int     y2;      
        cv::Mat original;
        cv::Mat subregion;      
};
}
#endif
