/******************************************************************************
 * Filename      : Creature.hpp
 * Source File(s): Creature.cpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#ifndef CREATURE_H
#define CREATURE_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "Subregion.hpp"
#include "Transform.hpp"
#include "Perceptron.hpp"
#include <opencv2/core/core.hpp>
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
typedef std::vector<Transforms::Transform> TRANSORMS;

/*******************************************************************************
*  EXTERNALS
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
class Creature
{
    public: 
        /* constructors */
        Creature ( void ); /* default */
        Creature ( const Creature& ); /* copy */
        Creature& operator= ( const Creature& ); /* assign */
        ~Creature ( void );
        /* functions */
        void     initialize ( void );
    
        void     set_fitness ( double );
        double   get_fitness ( void ); 
        void     compute_fitness ( double );
        
        void                    set_subregion ( Subregions::Subregion& );
        Subregions::Subregion&  get_subregion ( void );     
      
        void        set_transforms ( TRANSORMS );
        TRANSORMS & get_transforms ( void );
        void        perform_transforms ( cv::Mat );
        void        train_perceptron ( void );
        void        output_perceptron ( bool );
        
        cv::Mat&    get_feature ( void );
        
        std::string to_string ( void );
        

    private:
        cv::Mat               feature;
        double                fitness;
        Subregions::Subregion subregion;
        TRANSORMS             transforms;
        Perceptron            perceptron;
        double                tp; // True positive = correctly identified
        double                tn; // True negative = correctly rejected
        double                fn; // False negative = incorrectly rejected
        double                fp; // False positive = incorrectly identified        
};
#endif