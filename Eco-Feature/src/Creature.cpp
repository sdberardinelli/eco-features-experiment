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
#include "main.hpp"
#include "Creature.hpp"
#include "Perceptron.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <random>

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
Creature::Creature ( void ) { Perceptron p; perceptron = p; id = -1; reset(); }
/*******************************************************************************
* Constructor  : (Default
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
Creature::Creature ( int _id ) : id(_id) { Perceptron p; perceptron = p; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Creature::Creature ( const Creature& obj ) {
    this->id = obj.id;
    this->subregion = obj.subregion;
    this->transforms = obj.transforms;
    this->perceptron = obj.perceptron;
    this->fitness = obj.fitness;
    this->feature = obj.feature;
    this->tp = obj.tp;
    this->tn = obj.tn;
    this->fn = obj.fn;
    this->fp = obj.fp;
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Creature::~Creature ( void ) {
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
Creature& Creature::operator=( const Creature& obj ) {
    if (this != &obj) // prevent self-assignment
    {
        this->id = obj.id;
        this->subregion = obj.subregion;
        this->transforms = obj.transforms;
        this->perceptron = obj.perceptron;
        this->fitness = obj.fitness;
        this->feature = obj.feature;
        this->tp = obj.tp;
        this->tn = obj.tn;
        this->fn = obj.fn;
        this->fp = obj.fp;
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
void Creature::set_fitness ( double _fitness ) {
    fitness = _fitness;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double Creature::get_fitness ( void ) {
    return fitness;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Creature::set_id ( int _id ) {
    id = _id;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
int Creature::get_id ( void ) {
    return id;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::compute_fitness ( double p ) {
    //cout << "tp: " << tp << ", ";
    //cout << "fn: " << fn << ", ";
    //cout << "fp: " << fp << ", ";
    //cout << "tn: " << tn << ", ";

    fitness =  tp*500.0/(fn+tp) + tn*500.0/(p*fp+tn);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::initialize ( void ) {
#if CREATURE_INIT_SEED
    mt19937 rnd((size_t)CREATURE_INIT_SEED+id);
#else
    random_device rd;
        mt19937 rnd(rd());
#endif
    uniform_real_distribution<double> dist(0.0001,0.9999);
    auto lr = dist(rnd);
    perceptron.set_learningrate(lr);
    dist = uniform_real_distribution<double>(-1.,1.);
    auto bias = dist(rnd);
    perceptron.set_bias(bias);
    tp = 0;
    tn = 0;
    fn = 0;
    fp = 0;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Creature::reset ( void ) {
    tp = 0;
    tn = 0;
    fn = 0;
    fp = 0;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::set_subregion ( Subregions::Subregion& _subregion ) {
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
void Creature::set_transforms ( TRANSORMS _transorms ) {
    transforms = _transorms;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
TRANSORMS& Creature::get_transforms ( void ) {
    return transforms;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
vector<double> Creature::get_feature ( void ) {
    vector<double> inputs;
    auto min_value = numeric_limits<double>::max();
    auto max_value = numeric_limits<double>::min();
    for ( int i = 0; i < feature.rows; i++ ) {
        for ( int j = 0; j < feature.cols; j++ ) {
            unsigned char val = feature.at<unsigned char>(i,j);
            auto intensity = double(val);
            if ( intensity < min_value ) {
                min_value = intensity;
            }
            if ( intensity < max_value ) {
                max_value = intensity;
            }
            inputs.push_back(intensity);
        }
    }

    auto diff = max_value - min_value;
    auto N = (diff == 0 ) ? 1 : diff;
    for ( auto input : inputs) {
        input = 2. * ( (input - min_value) / N ) - 1;
    }

    return inputs;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Perceptron& Creature::get_perception ( void ) {
    return perceptron;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Creature::set_perception ( Perceptron& _perceptron ) {
    perceptron = _perceptron;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Creature::perform_transforms ( Mat& _image ) {
    Mat image = _image.clone();

    cvtColor(image, image, CV_BGR2GRAY);

    subregion.set_original(image);
    Mat _subregion_image = subregion.get_subregion();

    for (auto&& transform : transforms) {
        try {
            transform.perform_transform(_subregion_image);
            _subregion_image = transform.get_transform();
        }
        catch (cv::Exception e) {
            cout << endl;
            cout << "TRANSFORM " << transform.to_string();
            for (auto&& parm : transform.get_paramaters() )
                cout << " " << parm;
            cout << " FAILED :: ";
            cout << e.err << endl;
            //getchar();
        }
    }

    feature = _subregion_image;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::train_perceptron ( int goal ) {

    vector<double> inputs = get_feature();

    if ( !perceptron.is_initalized() ) {
#if CREATURE_TRAIN_PERCEPTION_SEED
        mt19937 rnd((size_t)CREATURE_TRAIN_PERCEPTION_SEED+id);
#else
        random_device rd;
        mt19937 rnd(rd());
#endif
        // Xavier initialization
        normal_distribution<double> dist(0,sqrt(3./(inputs.size() + 1)));

        vector<double> weights;
        for ( size_t i = 0; i < inputs.size(); i++ ) {
            weights.push_back(dist(rnd));
        }

        perceptron.set_weights(weights);
    }
    
    perceptron.set_inputs(inputs);

    perceptron.train(goal);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Creature::output_perceptron ( int goal ) {
    vector<double> inputs = get_feature();

    perceptron.set_inputs(inputs);
    perceptron.compute_output();
    auto output = (int)perceptron.get_output();
    if (  output == 1 && goal == 1 )
    {
        tp++; // True positive = correctly identified
    }
    else if ( output == 1 && goal == 0  )
    {
        fp++; // False positive = incorrectly identified  
    }
    else if ( output == 0 && goal == 1  )
    {
        fn++; // False negative = incorrectly rejected
    }
    else if ( output == 0 && goal == 0  )
    {
        tn++; // True negative = correctly rejected
    }
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void Creature::compute_output( void ) {
    vector<double> inputs = get_feature();
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
int Creature::get_output( void ) {
    return (int)perceptron.get_output();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
string Creature::to_string ( void ) {
    stringstream ss;

    cout << subregion.to_string() << " : ";

    for (auto&& transform : transforms) {
        ss << "[" << transform.to_string() << " (";
        for (auto&& paramater : transform.get_paramaters()) {
            ss << paramater << ",";
        }        
        ss << ")] ";
    }

    ss << perceptron.get_weights().size();

    return ss.str();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/