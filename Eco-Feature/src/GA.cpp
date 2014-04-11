/******************************************************************************
 * Filename      : GA.cpp
 * Header File(s): GA.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "GA.hpp"
#include "Creature.hpp"
#include "Subregion.hpp"
#include "Transform.hpp"
#include <vector>
#include <opencv2/core/core.hpp>
#include <random>
#include <iostream>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace Subregions;
using namespace Transforms;
using namespace cv;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
GA::GA ( void ) { ; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
GA::GA ( GA& obj ) { ; }
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
GA::~GA ( void ) { ; }
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
GA& GA::operator=( const GA& obj ) 
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
void GA::mutate ( Creature a )
{
    ;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Creature GA::crossover ( Creature a, Creature b )
{
    Creature child;
    return child;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double GA::fitness ( Creature a )
{
    return 0.0;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::initialize ( int size )
{
    random_device rd;
    mt19937 rnd(rd());
    uniform_int_distribution<int> trans_dist(1,TRANSORM_NUM);
    uniform_int_distribution<int> trans1_dist(MINIMUM_TRANFORMS,MAXIMUM_TRANFORMS);
    uniform_int_distribution<int> param_dist(0,360);
    
    for ( int i = 0; i < size; i++ )
    {
        Creature current_creature;       
        TRANSORMS transforms;
        int transform_count = trans1_dist(rnd);
        for ( int j = 0; j < transform_count; j++ )
        {
            Transform transform((TRANFORM_TYPE)trans_dist(rnd));  
            
            valarray<double> parameters(ParamterSize(transform.get_transform_type()));

            for ( int k = 0; k < parameters.size(); k++ )
            {
                parameters[k] = param_dist(rnd);
            }
            transform.set_parameters(parameters);
            
            transforms.push_back(transform);
        }
        uniform_int_distribution<int> x1_dist(0,MAXIMUM_WIDTH);
        int x1 = x1_dist(rnd);
        uniform_int_distribution<int> x2_dist(x1,MAXIMUM_WIDTH);
        int x2 = x2_dist(rnd);
        uniform_int_distribution<int> y1_dist(0,MAXIMUM_HEIGHT);        
        int y1 = y1_dist(rnd);
        uniform_int_distribution<int> y2_dist(0,MAXIMUM_HEIGHT);        
        int y2 = y2_dist(rnd);
        Subregion subregion(x1,x2,y1,y2);
        current_creature.set_subregion(subregion);
        current_creature.set_transforms(transforms);
        population.push_back(current_creature);
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::run ( int generations )
{
    for ( int generation = 0; generation < generations; generation++ )
    {
        for ( vector<int>::size_type creature_i = 0; 
              creature_i < population.size(); 
              creature_i++ )
        {
            for ( vector<int>::size_type training_images_i = 0; 
                 training_images_i < training_images.size(); 
                 training_images_i++ )
            {
                ;
            }
            for ( vector<int>::size_type holding_images_i = 0; 
                 holding_images_i < holding_images.size(); 
                 holding_images_i++ )
            {
                ;
            }            
        }
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
