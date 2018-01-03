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
#include "DataList.hpp"
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
typedef std::vector<Creature> POPULTATION;

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
        GA ( int,double,int,double,double,double,int );
        GA ( GA& ); /* copy */
        GA& operator= ( const GA& ); /* assign */
        ~GA ( void );
        
        /* functions */
        Creature crossover ( Creature&, Creature& );
        void     mutate ( Creature& );
        void     initialize ( void );
        void     run ( Data::DataList&, Data::DataList& );
        void     set_creature_iterations ( int );
        int      get_creature_iterations ( void );

        POPULTATION& get_population ( void );
        
    private:
        int                   pop_size;
        int                   num_gen;
        double                fit_pen;
        double                fit_thresh;
        POPULTATION           population;
        int                   learning_label;
        double                mutation_rate;
        int                   population_total;
        double                growth_rate;
        int                   creature_iterations;

};
#endif