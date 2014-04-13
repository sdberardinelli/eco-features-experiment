/******************************************************************************
 * Filename      : Perceptron.hpp
 * Source File(s): Perceptron.cpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#ifndef PERCEPTRON_H
#define PERCEPTRON_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <valarray>

/*******************************************************************************
*  DEFINES
********************************************************************************/
#define LEARNING_RATE 0.1

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
class Perceptron
{
    public: 
        /* constructors */
        Perceptron ( void ); /* default */
        Perceptron ( Perceptron& ); /* copy */
        Perceptron& operator= ( const Perceptron& ); /* assign */
        ~Perceptron ( void );
        /* functions */
        void train ( int );
        
        double get_output ( void );
        void set_output ( double );
        
        
        void set_weight_size ( int );
        
        std::valarray<double>& get_weights ( void );
        void set_weights ( std::valarray<double>& );
        
        double compute_coefficient ( double );
        
    private:
        double                learning_rate;
        std::valarray<double> weigths;
        double                output;
};
#endif