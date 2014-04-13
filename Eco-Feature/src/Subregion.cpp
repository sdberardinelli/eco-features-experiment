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
#include <opencv2/highgui/highgui.hpp>
#include <valarray>
#include <iostream>

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
Subregion::Subregion ( void ) { ; }
/*******************************************************************************
* Constructor  : 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Subregion::Subregion ( int _x1, int _x2, int _y1, int _y2 ) 
{ 
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
}
/*******************************************************************************
* Constructor  :
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
Subregion::Subregion ( const Subregion& obj )
{ 
    this->x1 = obj.x1;
    this->x2 = obj.x2;
    this->x1 = obj.x1;
    this->y2 = obj.y2;
    this->original = obj.original;
    this->subregion = obj.subregion;
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Subregion::~Subregion ( void )
{ 
    this->original.release();
    this->subregion.release();
}
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
        this->x1 = obj.x1;
        this->x2 = obj.x2;
        this->y1 = obj.y1;
        this->y2 = obj.y2;
        this->original = obj.original;
        this->subregion = obj.subregion;
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
void Subregion::set_original ( Mat _original )
{
    Mat croppedRef(_original);
    croppedRef.copyTo(original);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Subregion::set_subregion ( Mat _original, int _x1, int _x2, int _y1, int _y2 )
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
    construct_subregion(); 
    
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
    Rect crop(x2-x1, y2-y1, x1, y1);
    
    // Crop the full image to that image contained by the rectangle myROI
    // Note that this doesn't copy the data
    Mat croppedRef(original, crop);

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
valarray<int> Subregion::get_subregion_values ( void )
{   
    valarray<int> subregion_values(4);
    subregion_values[0] = x1;
    subregion_values[1] = x2;
    subregion_values[2] = y1;
    subregion_values[3] = y2;    
    return subregion_values;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
int Subregion::get_area ( void )
{
    Rect crop(x2-x1, y2-y1, x1, y1);    
    return crop.area();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Rect Subregion::get_rect ( void )
{
    Rect rect(x2-x1, y2-y1, x1, y1);    
    return rect;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/