/******************************************************************************
 * Filename      : Subregion.cpp
 * Header File(s): Subregion.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "Subregion.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace cv;
using namespace Subregions;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Subregion::Subregion ( Mat _original )
{
    Mat croppedRef(_original);
    croppedRef.copyTo(original);
    
    x1 = 0;
    x2 = _original.rows;
    y1 = 0;
    y2 = _original.cols;   
    
    construct_subregion();     
}
/*******************************************************************************
* Constructor  : 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Subregion::Subregion ( Mat _original, int _x1, int _x2, int _y1, int _y2 ) 
{ 
    Mat croppedRef(_original);
    croppedRef.copyTo(original);
  
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;   
    
    construct_subregion();    
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Subregion::Subregion ( Subregion& obj ) { ; }
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Subregion::~Subregion ( void ) { ; }
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Subregion& Subregion::operator=( const Subregion& obj ) 
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
void Subregion::set_subregion ( int _x1, int _x2, int _y1, int _y2 )
{
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
    
    construct_subregion(); 
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Mat Subregion::get_subregion ( void )
{       
    return subregion;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Subregion::construct_subregion ( void )
{       
    // Setup a rectangle to define your region of interest
    cv::Rect crop(x1, x2, y1, y2);

    // Crop the full image to that image contained by the rectangle myROI
    // Note that this doesn't copy the data
    cv::Mat croppedRef(original, crop);

    // Copy the data into new matrix
    croppedRef.copyTo(subregion); 
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/



