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
#include <vector>
#include <iostream>

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
Perceptron::Perceptron ( void ) { initialized = false; alpha = 0.1; }
/*******************************************************************************
* Constructor  : (Copy)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Perceptron::Perceptron ( Perceptron& obj ) {
    this->bias = obj.bias;
    this->learning_rate = obj.learning_rate;
    this->weights = obj.weights;
    this->inputs = obj.inputs;
    this->output = obj.output;
    this->initialized = obj.initialized;
    this->alpha = obj.alpha;
}
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Perceptron::~Perceptron ( void ) {
    weights.resize(0);
    inputs.resize(0);
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Perceptron& Perceptron::operator=( const Perceptron& obj ) {
    if (this != &obj) // prevent self-assignment
    {
        this->bias = obj.bias;
        this->learning_rate = obj.learning_rate;
        this->weights = obj.weights;
        this->inputs = obj.inputs;
        this->output = obj.output;
        this->initialized = obj.initialized;
        this->alpha = obj.alpha;
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
void Perceptron::set_weights ( vector<double>& _weigths ) {
    weights = _weigths;
    initialized = true;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
vector<double>& Perceptron::get_weights ( void ) {
    return weights;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::set_inputs ( vector<double>& _input ) {
    inputs = _input; 
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
vector<double>& Perceptron::get_inputs ( void ) {
    return inputs;
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
double Perceptron::get_output ( void ) {
    return alpha;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
bool Perceptron::is_initalized ( void ) {
    return initialized;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::set_bias ( double _bias )
{
    bias = _bias;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double Perceptron::get_bias ( void )
{
    return bias;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::set_learningrate ( double _learning_rate )
{
    learning_rate = _learning_rate;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
double Perceptron::get_learningrate ( void )
{
    return learning_rate;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::compute_output ( void ) {
    output = 0;

    if (weights.size() != inputs.size()) {
        return;
    }
    
    for ( size_t i = 0; i < inputs.size(); i++ )
    {
        output += weights[i]*inputs[i];
    }

    output += bias;

    output = tanh(output);

    if ( output > 0 )
    {
        alpha = 1;
    }
    else
    {
        alpha = 0;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Perceptron::train ( int goal )
{
    compute_output();
    for ( size_t i = 0; i < weights.size(); i++ )
    {
        weights[i] += learning_rate*(goal-alpha)*inputs[i];
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
