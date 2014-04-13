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
    GA ga;
    
    ga.load_images("data/training", "data/holding");
    
    ga.initialize(100);
    ga.run(1000);
    
    cout << "Done." << endl;
    
    return 0;
}