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
#include <random>
#include <ctime>
#include "GA.hpp"
#include "AdaBoost.hpp"

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace Transforms;
using namespace Subregions;
using namespace Data;
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
int main ( int argc, char* argv[] ) {
    GA ga(10,    // initial population size
          0.1,   // population growth rate
          5,     // number of generations
          0.95,  // fitness penalty
          0.25,  // mutation rate
          690,   // fitness score threshold
          3);    // {'cars': 0, 'airplanes': 1, 'Faces': 2, 'Motorbikes': 3}

    AdaBoost ab(10,  // boosted classifiers
                3);   // {'cars': 0, 'airplanes': 1, 'Faces': 2, 'Motorbikes': 3}

    DataList training_list, holding_list;
    training_list.load_images("data/traininglist-small.csv");
    holding_list.load_images("data/holdinglist-small.csv");

    clock_t start = clock();

    ga.initialize();

    ga.set_creature_iterations(10);

    ga.run(training_list, holding_list);

    POPULTATION &population = ga.get_population();

    if ( population.empty() ) {
        cout << "No creatures in population..." << endl;
    }
    else {
        if ( population.size() < ab.classifier_size() ) {
            cout << "Population size is smaller than initial boosted classifier size, using total creatures..." << endl;
            ab.set_classifier_size((int)population.size());
        }
        ab.train(population, training_list);
        ab.predict(holding_list, 0.5/*threshold*/);
    }
    cout << "Done. " << ((clock() - start) / (double)(CLOCKS_PER_SEC / 1000.)) / 1000. << " sec" << endl;
    
    return 0;
}