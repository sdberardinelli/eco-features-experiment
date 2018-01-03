/******************************************************************************
 * Filename      : AdaBoost.hpp
 * Source File(s): AdaBoost.cpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#ifndef ADABOOST_H
#define ADABOOST_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "GA.hpp"
#include "DataList.hpp"
#include "Creature.hpp"
#include <opencv2/core/core.hpp>
#include <vector>
#include <string>


/*******************************************************************************
*  DEFINES
********************************************************************************/

/*******************************************************************************
*  MACROS
********************************************************************************/

/*******************************************************************************
*  DATA TYPES
********************************************************************************/

/*******************************************************************************
*  EXTERNALS
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
class AdaBoost
{
    public: 
        /* constructors */
        AdaBoost ( void ); /* default */
        AdaBoost ( int, int );
        AdaBoost ( AdaBoost& ); /* copy */
        AdaBoost& operator= ( const AdaBoost& ); /* assign */
        ~AdaBoost ( void );

        /* functions */
        void train ( POPULTATION&, Data::DataList& );
        void predict (Data::DataList &, double );
        int classifier_size ( void );
        void set_classifier_size ( int );

private:
        std::vector<Creature> alpha;
        std::vector<double> delta_M;
        std::vector<double> delta_w;
        std::vector<double> rho;
        std::vector<double> delta_omega;
        int X;
        int learning_label;
};
#endif