/*******************************************************************************
 * Filename      : main.cpp
 * Header File(s): 
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include <iostream>
#include "GA.hpp"
#include "Creature.hpp"
#include "Transform.hpp"
#include "Subregion.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <random>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace Transforms;
using namespace Subregions;
using namespace cv;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
int main ( int argc, char* argv[] ) 
{
    TRANSORMS transforms;
    Creature creature;
    Mat image;
    random_device rd;
    mt19937 rnd(rd());
    uniform_int_distribution<int> param_dist(0,360);
    
    for ( int j = 1; j < TRANSORM_NUM; j++ )
    {
        Transform transform((TRANFORM_TYPE)j);  

        valarray<double> parameters(ParamterSize(transform.get_transform_type()));

        for ( int k = 0; k < parameters.size(); k++ )
        {
            parameters[k] = param_dist(rnd);
        }
        transform.set_parameters(parameters);

        transforms.push_back(transform);
    }    
    
    image = imread("data/training/0001.jpg", CV_LOAD_IMAGE_COLOR);
    
    uniform_int_distribution<int> x1_dist(0,MAXIMUM_WIDTH);
    int x1 = x1_dist(rnd);
    uniform_int_distribution<int> x2_dist(x1,MAXIMUM_WIDTH);
    int x2 = x2_dist(rnd);
    uniform_int_distribution<int> y1_dist(0,MAXIMUM_HEIGHT);        
    int y1 = y1_dist(rnd);
    uniform_int_distribution<int> y2_dist(y1,MAXIMUM_HEIGHT);        
    int y2 = y2_dist(rnd);
    Subregion subregion(x1,x2,y1,y2);

    creature.set_subregion(subregion);
    creature.set_transforms(transforms);
    creature.perform_transforms(image);

            
//    GA ga;
//    
//    ga.load_images("data/training", "data/holding");
//    
//    ga.initialize(100);
//    ga.run(1000);
//    
//    cout << "Done." << endl;
    
    return 0;
}