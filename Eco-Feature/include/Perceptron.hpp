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
#include <vector>

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
        
        std::vector<double>& get_weights ( void );
        void set_weights ( std::vector<double>& );
        
        std::vector<double>& get_inputs ( void );
        void set_inputs ( std::vector<double>& );
        
        double get_output ( void );
        void set_output ( double );
        
        double get_bias ( void );
        void set_bias ( double );
        
        double get_learningrate ( void );
        void set_learningrate ( double );

        void compute_output ( void );

        bool is_initalized ( void );
        
    private:
        double                 bias;
        double                 learning_rate;
        std::vector<double>    weights;
        std::vector<double>    inputs;
        double                 output;
        bool                   initialized;
        double                 alpha;
};
#endif