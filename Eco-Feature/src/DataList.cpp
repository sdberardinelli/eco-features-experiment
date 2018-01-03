/******************************************************************************
 * Filename      : DataList.cpp
 * Header File(s): DataList.hpp
 * Description   :
 * Authors(s)    :
 * Date Created  :
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers
 ************************************/
#include "main.hpp"
#include "DataList.hpp"
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

/************************************
 * Namespaces
 ************************************/
using namespace std;
using namespace cv;
using namespace Data;
using namespace boost;

/************************************
 * Local Variables
 ************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
DataList::DataList ( void ) { ; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
DataList::DataList ( const DataList& obj )
{
    ;
}
/*******************************************************************************
* Deconstructor:
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
DataList::~DataList ( void )
{
    ;
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
DataList& DataList::operator=( const DataList& obj )
{
    if (this != &obj) // prevent self-assignment
    {
        list = obj.list;
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
void DataList::load_images ( string pth_annotations )
{
    Mat image;
    string line;
    ifstream infile( pth_annotations );
    vector<string> strs;
    vector<string>::iterator s_itr;
    while (getline(infile, line))
    {
        boost::split(strs,line,boost::is_any_of(","));
        string name = strs[0];
        auto label = boost::lexical_cast<int>(strs[1]);
        image = imread(name, CV_LOAD_IMAGE_COLOR);
        resize(image,image,Size(MAXIMUM_WIDTH,MAXIMUM_HEIGHT));
        list.emplace_back(Image(name,image,label));
#if ROI
        vector<int> roi;
        for ( s_itr = strs.begin()+1; s_itr != strs.end(); s_itr++) {
            auto i = boost::lexical_cast<int>(*s_itr);
            roi.push_back(i);
        }
        list.emplace_back(Image(name,image,roi));
#endif
    }
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
vector<Image>& DataList::get ( void ) {
    return list;
};
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/




