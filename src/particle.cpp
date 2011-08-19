/*
*	Author: Felipe Fernando Furlan
*
*/

#include "../include/particle.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <exception>
using namespace std;

#include <cmath>

int Particle::numberOfVariables = 1;

const double *Particle::lowerBounds = NULL;

const double *Particle::upperBounds = NULL;

const double *Particle::maxVelocity = NULL;

double Particle::c1 = 2;

double Particle::c2 = 2;

const double *Particle::weight = NULL;

void (*Particle::functionPtr) (Particle *);

Particle::Particle(int _numberOfVariables,
                const double *_lowerBounds,
                const double *_upperBounds,
                const double *_vmax,
                double _c1, double _c2,
                const double *_weight,
                void (*_functionPtr)(Particle *))
{
    lowerBounds = _lowerBounds;
    upperBounds = _upperBounds;

	numberOfVariables = _numberOfVariables;
	
	if (numberOfVariables <= 0) 
		throw "Number of variables can't be less or equal than zero.";
	
	c1 = _c1;
	c2 = _c2;
	weight = _weight;
	functionPtr = _functionPtr;
	maxVelocity = _vmax;

	position = new double [numberOfVariables];
	velocity = new double [numberOfVariables] ;
	bestPosition = new double [numberOfVariables];

	inicializeParticle();
}

Particle::~Particle ()
{	
	delete [] position;
	delete [] velocity;
	delete [] bestPosition;
}

void Particle::inicializeParticle ()
{
    for (int i = 0; i < numberOfVariables; i++) {
        double random = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1);
        position[i] = lowerBounds[i] + (upperBounds[i] - lowerBounds[i]) * random;
        velocity[i] = 0;
    }

    (*functionPtr)(this);

    bestValue = value;
    bestFeasible = feasible;
    for (int i = 0; i < numberOfVariables; i++)
        bestPosition[i] = position[i];

}

void Particle::updateParticle (const double *globalBestPosition)
{
    double random1;
    double random2;

    for (int i = 0; i < numberOfVariables; i++) {
        random1 = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1);
        random2 = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1);
        velocity[i] = *weight * velocity[i] + c1 * random1 * (bestPosition[i] - position[i]) + c2 * random2 * (globalBestPosition[i] - position[i]);

        //tests if velocity doesn't exceed maximum velocity
        if (fabs(velocity[i]) > maxVelocity[i])
            velocity[i] = maxVelocity[i] * velocity[i] / fabs(velocity[i]);

        //update position
        position[i] = position[i] + velocity[i];

        //tests if position doesn't exceed upper or lower bounds
        if (position[i] >= upperBounds[i])
            position[i] = upperBounds[i];

        if (position[i] <= lowerBounds[i])
            position[i] = lowerBounds[i];
    }

    (*functionPtr)(this);

    value += constraits;

    updateParticleBest ();
}

const double *Particle::getBestPosition ()
{
    return bestPosition;
}

double Particle::getBestValue ()
{
    return bestValue;
}

bool Particle::getBestFeasible ()
{
    return bestFeasible;
}

double Particle::getValue ()
{
    return value;
}

void Particle::setValue (double _value)
{
    value = _value;
}

void Particle::setConstraits (double _constraits)
{
    constraits = _constraits;
}

bool Particle::getFeasible ()
{
    return feasible;
}

void Particle::setFeasible (bool _feasible)
{
    feasible = _feasible;
}

void Particle::printParticle ()
{
    cout << "Position = ";
    for (int i = 0; i < numberOfVariables; i++)
        cout << position[i] << "   ";
    cout << endl;
    cout << "Value = " << value << endl;
    cout << "Constraints = " << constraits << endl;
    cout << "Feasible? " << (feasible ? "true" : "false") << endl;
}

void Particle::printParticleBest ()
{
    cout << "Position = ";
    for (int i = 0; i < numberOfVariables; i++)
        cout << bestPosition[i] << "   ";
    cout << endl;
    cout << "Value = " << bestValue << endl;
    cout << "Feasible? " << (bestFeasible ? "true" : "false") << endl;
}

int Particle::getNumberOfVariables ()
{
    return Particle::numberOfVariables;
}

const double *Particle::getPosition ()
{
    return position;
}

///private
void Particle::updateParticleBest ()
{
    //improve this conditional
    if (feasible || !bestFeasible) {
        if (feasible != bestFeasible || value <= bestValue) {
            bestValue = value;
            bestFeasible = feasible;

            for (int i = 0; i < numberOfVariables; i++)
                bestPosition[i] = position[i];
        }
    }
}

