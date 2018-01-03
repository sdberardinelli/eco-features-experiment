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
#include "main.hpp"
#include "GA.hpp"
#include <boost/filesystem.hpp>
#include <random>
#include <iostream>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace Subregions;
using namespace Transforms;
using namespace Data;
using namespace cv;
using namespace boost::filesystem;


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
* Constructor  : 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
GA::GA ( int population_size, double _growth_rate, int number_generations,
         double fitness_penalty, double _mutation_rate, double fitness_threshold, int _learning_label ) {
    pop_size = population_size;
    num_gen  = number_generations;
    growth_rate = _growth_rate;
    fit_pen  = fitness_penalty;
    fit_thresh  = fitness_threshold;
    learning_label = _learning_label;
    mutation_rate = _mutation_rate;
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
GA::GA ( GA& obj ) {
    pop_size = obj.pop_size;
    num_gen = obj.num_gen;
    fit_pen = obj.fit_pen;
    fit_thresh = obj.fit_thresh;
    population = obj.population;
    learning_label = obj.learning_label;
    mutation_rate = obj.mutation_rate;
    population_total = obj.population_total;
    growth_rate = obj.growth_rate;
    creature_iterations = obj.creature_iterations;
}
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
GA& GA::operator=( const GA& obj ) {
    if (this != &obj) // prevent self-assignment
    {
        pop_size = obj.pop_size;
        num_gen = obj.num_gen;
        fit_pen = obj.fit_pen;
        fit_thresh = obj.fit_thresh;
        population = obj.population;
        learning_label = obj.learning_label;
        mutation_rate = obj.mutation_rate;
        population_total = obj.population_total;
        growth_rate = obj.growth_rate;
        creature_iterations = obj.creature_iterations;
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
POPULTATION& GA::get_population ( void ) {
    return population;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::mutate ( Creature& a ) {
#if GA_MUTATE_SEED
    mt19937 rnd(GA_SEED+GA_MUTATE_SEED);
#else
    random_device rd;
    mt19937 rnd(rd());
#endif
    TRANSORMS& a_transorms = a.get_transforms();

    uniform_int_distribution<int> _choice(0,(int)a_transorms.size()-1);

    int transform_choice = _choice(rnd);

    Transform a_transform = a_transorms[transform_choice];

    if ( a_transform.get_paramater_size() == 0 ) {
        return;
    }

    //cout << "Mutating Creature " << a.get_id() << ": " << a.to_string() << endl;

    Transform transform((a_transform.get_transform_type()));
    transform.randomize_parameters(GA_MUTATE_SEED+a.get_id());

    valarray<double>& original_parameters = a_transorms[transform_choice].get_paramaters();
    valarray<double>& parameters = transform.get_paramaters();

    _choice = uniform_int_distribution<int>(0,a_transform.get_paramater_size()-1);

    int parameters_choice = _choice(rnd);

    original_parameters[parameters_choice] = parameters[parameters_choice];

    //cout << "                  " << a.get_id() << ": " << a.to_string() << endl;
    cout << "creature " << a.get_id() << " mutated" << endl;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Creature GA::crossover ( Creature& a, Creature& b ) {
#if GA_SEED
    //mt19937 rnd(SEED+(unsigned long)(a.get_id() + b.get_id()));
    mt19937 rnd(GA_SEED+GA_CROSSOVER_SEED);
#else
    random_device rd;
    mt19937 rnd(rd());
#endif
    Creature child;
    uniform_int_distribution<int> _choice(0,1);

    //cout << "Crossing Creature " << a.get_id() << ": " << a.to_string() << endl;
    //cout << "         Creature " << b.get_id() << ": " << b.to_string() << endl;

    Subregion subregion;
    TRANSORMS& a_transorms = a.get_transforms();
    TRANSORMS& b_transorms = b.get_transforms();
    TRANSORMS transforms;
    Perceptron perceptron;
    if ( _choice(rnd) == 0 ) {
        subregion = a.get_subregion();
        perceptron = a.get_perception();
        child.set_perception(perceptron);
    } else {
        subregion = b.get_subregion();
        perceptron = b.get_perception();
    }
    child.set_perception(perceptron);

    _choice = uniform_int_distribution<int>(0,(int)a_transorms.size()-1);
    for ( int i = 0; i < _choice(rnd); i++) {
        transforms.push_back(a_transorms[i]);
    }

    _choice = uniform_int_distribution<int>(0,(int)b_transorms.size()-1);
    for ( int i = _choice(rnd); i < (int)b_transorms.size(); i++) {
        transforms.push_back(b_transorms[i]);
    }

    child.set_subregion(subregion);
    child.set_transforms(transforms);

    child.set_id(population_total);
    population_total++;

    cout << "crossing " << a.get_id() << " (x) " << b.get_id() << " = " <<  child.get_id() << endl;
    //cout << "Child Creature: " << child.get_id() << ": " << child.to_string() << endl;
    return child;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::initialize ( void ) {
    cout << "initalizing creatures" << endl;

#if GA_INIT_SEED
    mt19937 rnd(GA_SEED+GA_INIT_SEED);
#else
    random_device rd;
    mt19937 rnd(rd());
#endif

    uniform_int_distribution<int> transformation_choice(1,TRANSORM_NUM-1);
    uniform_int_distribution<int> transformation_count(MINIMUM_TRANFORMS,MAXIMUM_TRANFORMS);

    for ( int i = 0; i < pop_size; i++ ) {
        Creature current_creature(i);
        TRANSORMS transforms;
        int count = transformation_count(rnd);
        for ( int j = 0; j < count; j++ ) {
            Transform transform((TRANFORM_TYPE)transformation_choice(rnd));
            transform.randomize_parameters(i+j);
            transforms.push_back(transform);
        }
        uniform_int_distribution<int> x1_dist(2,MAXIMUM_WIDTH-2);
        int x1 = x1_dist(rnd);
        uniform_int_distribution<int> x2_dist(x1+1,MAXIMUM_WIDTH-1);
        int x2 = x2_dist(rnd);
        uniform_int_distribution<int> y1_dist(2,MAXIMUM_HEIGHT-2);
        int y1 = y1_dist(rnd);
        uniform_int_distribution<int> y2_dist(y1+1,MAXIMUM_HEIGHT-1);
        int y2 = y2_dist(rnd);
        Subregion subregion(x1,x2,y1,y2);
        current_creature.set_subregion(subregion);
        current_creature.set_transforms(transforms);
        current_creature.initialize();
        population.push_back(current_creature);
    }

    population_total = pop_size;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void GA::run ( DataList& training_list, DataList& holding_list ) {
#if GA_RUN_SEED
    mt19937 rnd(GA_SEED+GA_RUN_SEED);
#else
    random_device rd;
    mt19937 rnd(rd());
#endif
    int gen = 0;
    while ( true ) {

        clock_t start = std::clock();

        int i = 0;
        for (auto&& creature : population) {

            stringstream out;
            out << "training... creature " << creature.get_id() << " (" << (i++ +1) << "/" <<population.size() << ") in generation " << gen + 1;
            string line = out.str();
            cout << "\r" << line;
            cout.flush();
            if ( i < population.size()-1 ){ string freshline = "\r"; for (int j = 0; j < line.length(); j++ ) { freshline += " "; }; cout << freshline;}

            for ( int j = 0; j < creature_iterations; j++ ) {
                for (auto &&obj : training_list.get()) {
                    Mat image = obj.get_image();
                    creature.perform_transforms(image);
                    int label = (obj.get_label() == learning_label) ? 1 : 0;
                    creature.train_perceptron(label);
                }
            }
            for (auto &&obj : holding_list.get()) {
                Mat image = obj.get_image();
                creature.perform_transforms(image);
                int label = ( obj.get_label() == learning_label ) ? 1 : 0;
                creature.output_perceptron(label);
            }
            creature.compute_fitness(fit_pen);
        }
        cout << endl;
        cout << "time: " << ((clock() - start) / (double)(CLOCKS_PER_SEC / 1000.)) / 1000. << " sec" << endl;

        for ( auto creature = population.begin(); creature != population.end(); ) {
            auto fitness = creature->get_fitness();
            cout << "creature " << creature->get_id() << ": " << fitness;

            if ( creature->get_fitness() < fit_thresh ) {
                cout << " (removed)";

                creature = population.erase(creature);

                if ( population.empty() ) {
                    cout << endl << "population count: " << population.size() << endl;
                    return;
                }
            } else {
                ++creature;
            }
            cout << endl;
            creature->reset();
        }

        if ( ++gen >= num_gen ) {
            break;
        }

        if ( population.size() >= 2 ) {

            uniform_int_distribution<int> pick_dist(0, (int) population.size() - 1);

            auto growth = (population.size() + (double) population.size() * log(1 + growth_rate));
            growth -= population.size();
            growth = (int)growth;

            auto original_size = (int)population.size();

            vector<Creature> new_generation;

            while (growth) {
                //Select creatures that make it to next generation
                int idx1 = pick_dist(rnd);
                int idx2 = pick_dist(rnd);

                while (idx2 == idx1) {
                    idx2 = pick_dist(rnd);
                }

                Creature a = population[idx1];
                Creature b = population[idx2];

                //Create new creatures using cross over
                Creature child = crossover(a, b);

                new_generation.push_back(child);
                growth--;
            }

            // add creatures to the population
            for ( auto&& creature : new_generation ) {
                population.push_back(creature);
            }

            cout << "population growth from " << original_size << " to " << population.size() << endl;
        }

        uniform_real_distribution<double> mutate_dist(0,1);
        //Apply mutations to the population
        for (auto &&creature : population) {
            if ( mutate_dist(rnd) < mutation_rate ) {
                mutate(creature);
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
void GA::set_creature_iterations ( int _creature_iterations ) {
    creature_iterations = _creature_iterations;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
int GA::get_creature_iterations ( void ) {
    return creature_iterations;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/