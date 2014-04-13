/******************************************************************************
 * Filename      : Creature.cpp
 * Header File(s): Creature.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "Creature.hpp"
#include "Transform.hpp"
#include "Subregion.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace cv;
using namespace Transforms;
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
Creature::Creature ( void ) { srand(time(NULL)); }
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Creature::Creature ( const Creature& obj )
{ 
    this->subregion = obj.subregion;
    this->transforms = obj.transforms;
    this->perceptron = obj.perceptron;
    this->fitness = obj.fitness;
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Creature::~Creature ( void )
{ 
    transforms.clear();
    subregion.~Subregion();
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Creature& Creature::operator=( const Creature& obj ) 
{
    if (this != &obj) // prevent self-assignment
    {
        this->subregion = obj.subregion;
        this->transforms = obj.transforms;
        this->fitness = obj.fitness;
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
void Creature::set_fitness ( double _fitness )
{
    fitness = _fitness;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double Creature::get_fitness ( void )
{
    return fitness;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::initialize ( void )
{
    vector<double> weights;
    
    for ( vector<int>::size_type i = 0; i < MAXIMUM_WIDTH*MAXIMUM_HEIGHT;  i++ )
    {
        weights.push_back(0.0);
    }
    
    perceptron.set_weights(weights);
    perceptron.set_learningrate(0.1);
    perceptron.set_threshold(0.0);
    perceptron.set_bias(0.0);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::set_subregion ( Subregions::Subregion& _subregion )
{
    subregion = _subregion;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Subregions::Subregion& Creature::get_subregion ( void )
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
void Creature::set_transforms ( TRANSORMS _transorms )
{
    transforms = _transorms;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
TRANSORMS & Creature::get_transforms ( void )
{
    return transforms;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Mat & Creature::get_feature ( void )
{
    return feature;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::perform_transforms ( Mat _image )
{    
    Mat image;
    cvtColor(_image, image, CV_BGR2GRAY);
        
    subregion.set_original(image);
    image = subregion.get_subregion();
        
    for ( vector<int>::size_type i = 0; i < transforms.size();  i++ )
    {
        transforms[i].perform_transform(image);
        image = transforms[i].get_transform();  
    }
    
    feature = image;    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::train_perceptron ( void )
{    
    vector<double> inputs(MAXIMUM_WIDTH*MAXIMUM_HEIGHT);
    
    valarray<int> subregion_values = subregion.get_subregion_values();
    
    int x1 = subregion_values[0];
    int x2 = subregion_values[1];
    int y1 = subregion_values[2];
    int y2 = subregion_values[3];

    for ( int row = 0; row < MAXIMUM_WIDTH; ++row)
    {
        for ( int col = 0; col < MAXIMUM_HEIGHT; ++col)
        {
            if ( row > x1 && 
                 row < x2 && 
                 col > y1 && 
                 col < y2 )
            {
                if ( feature.at<uchar>(row,col) < 254 )
                {
                    inputs.push_back(1.0);
                }
                else
                {
                    inputs.push_back(0.0);
                }
            }
        }
    }    
    
    perceptron.set_inputs(inputs);
    perceptron.train(1);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::train_perceptron ( void )
{    
    vector<double> inputs(MAXIMUM_WIDTH*MAXIMUM_HEIGHT);
    
    valarray<int> subregion_values = subregion.get_subregion_values();
    
    int x1 = subregion_values[0];
    int x2 = subregion_values[1];
    int y1 = subregion_values[2];
    int y2 = subregion_values[3];

    for ( int row = 0; row < MAXIMUM_WIDTH; ++row)
    {
        for ( int col = 0; col < MAXIMUM_HEIGHT; ++col)
        {
            if ( row > x1 && 
                 row < x2 && 
                 col > y1 && 
                 col < y2 )
            {
                if ( feature.at<uchar>(row,col) < 254 )
                {
                    inputs.push_back(1.0);
                }
                else
                {
                    inputs.push_back(0.0);
                }
            }
        }
    }    
    
    perceptron.set_inputs(inputs);
    perceptron.compute_output();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
string Creature::to_string ( void )
{
    stringstream ss;
    
    valarray<int> subregion_values = subregion.get_subregion_values();
    
    int i;
    ss << "[";
    for ( i = 0; i < subregion_values.size()-1; i++ )
        ss << subregion_values[i] << ",";
    ss << subregion_values[i] << "] ";
    
    
    for ( vector<int>::size_type i = 0; i < transforms.size(); i++ )
    {
        valarray<double> tmp = transforms[i].get_paramaters();
        
        ss << "[" << transforms[i].get_transform_type() << " (";
        
        for ( vector<int>::size_type j = 0; j < tmp.size(); j++ )
        {
            ss << tmp[j] << ",";
        }        
        ss << ")] ";
    }
    
    return ss.str();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/