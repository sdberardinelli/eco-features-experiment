/******************************************************************************
 * Filename      : Image.cpp
 * Header File(s): Image.hpp
 * Description   :
 * Authors(s)    :
 * Date Created  :
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers
 ************************************/
#include "Image.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/************************************
 * Namespaces
 ************************************/
using namespace std;
using namespace cv;
using namespace Data;

/************************************
 * Local Variables
 ************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
Image::Image ( void ) { ; }
/*******************************************************************************
* Constructor  :
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
Image::Image ( string _name, Mat _image, vector<int> _roi ) : name(_name),
                                                              image(_image),
                                                              roi(_roi ) { ; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
Image::Image ( string _name, Mat _image,int _label ) : name(_name),
                                                       image(_image),
                                                       label(_label ) { ; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
Image::Image ( const Image& obj )
{
    name = obj.name;
    image = obj.image;
    roi = obj.roi;
    label = obj.label;
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
Image& Image::operator= ( const Image& obj )
{
    if (this != &obj) // prevent self-assignment
    {
        name = obj.name;
        image = obj.image;
        roi = obj.roi;
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
Image::~Image ( void )
{
    roi = std::vector<int>();
    image.release();
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Image::set_image ( Mat _image ) {
    image = _image;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
Mat Image::get_image ( void ){
    return image;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Image::set_roi ( vector<int>& _roi ) {
    roi = _roi;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
vector<int> Image::get_roi ( void ) {
    return roi;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
string Image::get_name ( void ) {
    return name;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Image::set_name ( string _name ) {
    name = _name;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
int Image::get_label ( void ) {
    return label;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Image::set_label ( int _label ) {
    label = _label;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/



