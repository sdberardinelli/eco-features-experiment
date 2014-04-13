/******************************************************************************
 * Filename      : Perceptron.cpp
 * Header File(s): Perceptron.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "Perceptron.hpp"
#include <cmath>
#include <valarray>

/************************************
 * Namespaces 
 ************************************/
using namespace std;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Perceptron::Perceptron ( void )
{ 
    learning_rate = LEARNING_RATE;
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Perceptron::Perceptron ( Perceptron& obj )
{ 
     this->output = obj.output;
     this->weigths = obj.weigths;
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Perceptron::~Perceptron ( void )
{ 
    weigths.resize(0);
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Perceptron& Perceptron::operator=( const Perceptron& obj ) 
{
    if (this != &obj) // prevent self-assignment
    {
        this->output = obj.output;
        this->weigths = obj.weigths;
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
void Perceptron::set_weights ( valarray<double>& _weigths )
{
    weigths = _weigths;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
valarray<double>& Perceptron::get_weights ( void )
{
    return weigths;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::set_weight_size ( int _size )
{
    weigths.resize(_size);
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::set_output ( double _output )
{
    output = _output;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double Perceptron::get_output ( void )
{
    return output;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double Perceptron::compute_coefficient ( double _delta_w )
{
    double _coefficient;
    
    _coefficient = 0.5*log((1.0-_delta_w)/_delta_w);
    
    return _coefficient;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::train ( int bias )
{
    for (auto it = begin(weigths); it != end(weigths); ++it)
    {
        ;//cout << ' ' << *it;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
