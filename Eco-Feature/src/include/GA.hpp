/******************************************************************************
 * Filename      : GA.hpp
 * Source File(s): GA.cpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#ifndef GA_H
#define GA_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "Creature.hpp"
#include <opencv2/core/core.hpp>
#include <vector>
#include <string>

/*******************************************************************************
*  DEFINES
********************************************************************************/
#define MUTATION_RATE 0.05

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
class GA
{
    public: 
        /* constructors */
        GA ( void ); /* default */
        GA ( int,int,double,int );
        GA ( GA& ); /* copy */
        GA& operator= ( const GA& ); /* assign */
        ~GA ( void );
        
        /* functions */
        Creature crossover ( Creature, Creature );
        void     mutate ( Creature );
        void     initialize ( void );
        void     run ( void );
        void     load_images ( std::string, std::string );
        
    private:
        int                   pop_size;
        int                   num_gen;
        double                fit_pen;
        int                   fit_thresh;
        std::vector<Creature> population;
        std::vector<cv::Mat>  training_images;
        std::vector<cv::Mat>  holding_images;
};
#endif