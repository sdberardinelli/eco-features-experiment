/******************************************************************************
 * Filename      : AdaBoost.cpp
 * Header File(s): AdaBoost.hpp
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
#include <limits>
#include "AdaBoost.hpp"

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace Data;
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
AdaBoost::AdaBoost ( void ) { ; }
/*******************************************************************************
* Constructor  :
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
AdaBoost::AdaBoost ( int _classifiers, int _learning_label ) : X(_classifiers), learning_label(_learning_label) { ; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
AdaBoost::AdaBoost ( AdaBoost& obj ) {
    this->delta_M = obj.delta_M;
    this->delta_w = obj.delta_w;
    this->rho = obj.rho;
    this->alpha = obj.alpha;
    this->X = obj.X;
    this->learning_label = obj.learning_label;
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
AdaBoost::~AdaBoost ( void ) { ; }
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
AdaBoost& AdaBoost::operator=( const AdaBoost& obj ) {
    if (this != &obj) // prevent self-assignment
    {
        this->delta_M = obj.delta_M;
        this->delta_w = obj.delta_w;
        this->rho = obj.rho;
        this->alpha = obj.alpha;
        this->X = obj.X;
        this->learning_label = obj.learning_label;
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
int AdaBoost::classifier_size ( void ) {
    return X;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
void AdaBoost::set_classifier_size ( int _X ) {
    X = _X;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void AdaBoost::train ( POPULTATION& population, DataList & datalist ) {
    cout << "boosting..." << population.size() << endl;
    delta_M.resize(datalist.get_size(),1./datalist.get_size());
    delta_w.resize(population.size(), 0.0);
    delta_omega.resize(population.size(), 0.0);
    alpha.resize((size_t)X);
    rho.resize((size_t)X, 0.0);

    vector<int> classifications(datalist.get_size(),0);

    for ( int x = 0; x < X; x++ ) {
        auto w = 0;
        for ( auto&& creature : population ) {
            auto m = 0;
            auto tp = 0, fp = 0, fn = 0, tn = 0;
            delta_w[w] = numeric_limits<double>::min();
            for ( auto&& obj : datalist.get() ) {
                Mat image = obj.get_image();
                creature.perform_transforms(image);
                creature.compute_output();
                auto output = creature.get_output();
                int label = (obj.get_label() == learning_label) ? 1 : 0;

                classifications[m] = output;

                if ( output != label ) {
                    delta_w[w] += delta_M[m];
                }

                if (  output == 1 && label == 1 )
                {
                    tp++; // True positive = correctly identified
                }
                else if ( output == 1 && label == 0  )
                {
                    fp++; // False positive = incorrectly identified

                }
                else if ( output == 0 && label == 1  )
                {
                    fn++; // False negative = incorrectly rejected
                }
                else if ( output == 0 && label == 0  )
                {
                    tn++; // True negative = correctly rejected
                }

                m++;
            }

            delta_omega[w] = (tp+tn)*1. / (tp+tn+fp+fn)*1.;
            w++;
        }

        auto min_error = numeric_limits<double>::max();
        auto omega = 0;
        for ( w = 0; w < delta_w.size(); w++ ) {
            if (delta_w[w] < min_error) {
                min_error = delta_w[w];
                omega = w;
            }
        }

        if ( 1. - delta_omega[omega] >= 0.5  && delta_w[omega] > 1.0 ) {
            X = x;
            break;
        }

        rho[x] = 0.5 * log( (1 - delta_w[omega]) / delta_w[omega] );
        alpha[x] = population[omega];

        population.erase(population.begin()+omega);
        delta_w.erase(delta_w.begin()+omega);

        if ( population.empty() ) {
            break;
        }

        auto m = 0;
        auto N = 0.;
        for ( auto&& obj : datalist.get() ) {
            int label = (obj.get_label() == learning_label) ? 1 : 0;
            auto c  = (classifications[m] == label) ? 1 : -1;
            delta_M[m] = (delta_M[m] * exp(-(rho[x] * c)));
            N += delta_M[m];
            m++;
        }

        for ( m = 0; m < datalist.get_size(); m++ ) {
            delta_M[m] /= N;
            m++;
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
void AdaBoost::predict ( DataList & datalist, double tao ) {
    cout << "prediction..." << X << endl;
    int tp = 0, fp = 0, fn = 0, tn = 0;
    for ( auto&& obj : datalist.get() ) {
        Mat image = obj.get_image();
        int label = (obj.get_label() == learning_label) ? 1 : 0;
        double c1 = 0;

        for ( int x = 0; x < X; x++ ) {
            alpha[x].perform_transforms(image);
            alpha[x].compute_output();
            c1 += rho[x]*alpha[x].get_output();
        }

        auto c = ( c1 > tao ) ? 1 : 0;

        cout << obj.get_name() << endl;
        cout << label << " " << c << " : " << c1 << endl << endl;

        if (  c == 1 && label == 1 )
        {
            tp++; // True positive = correctly identified
        }
        else if ( c == 1 && label == 0  )
        {
            fp++; // False positive = incorrectly identified
        }
        else if ( c == 0 && label == 1  )
        {
            fn++; // False negative = incorrectly rejected
        }
        else if ( c == 0 && label == 0  )
        {
            tn++; // True negative = correctly rejected
        }
    }

    cout << "tp: " << tp << ", ";
    cout << "fp: " << fp << ", ";
    cout << "fn: " << fn << ", ";
    cout << "tn: " << tn << ", ";

    double accuracy = (tp+tn)*1. / (tp+tn+fp+fn)*1.;

    cout << "accuracy: " << accuracy*100. << endl;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/