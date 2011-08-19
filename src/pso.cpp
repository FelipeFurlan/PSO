/*
*	This file contains the class that creates the particle swarm
*	
*	Author: Felipe Fernando Furlan
*/

#include "../include/pso.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <exception>
#include <ctime>
#include <string>
using namespace std;

PSO::PSO (int _numberOfParticles,
            int _numberOfVariables,
            double *_lowerBounds,
            double *_upperBounds,
            double *_vmax,
            void (*_objectiveFunction)(Particle *),
            double _lowerWeight,
            double _upperWeight,
            int _maxIteration,
            double _c1,
            double _c2,
            double _threshold,
            string _stoppingCriteria,
            string _psoType)
{
    int i = 0;

    srand((unsigned)time(0));

    numberOfParticles = _numberOfParticles;
    maxIteration = _maxIteration;
    upperWeight = _upperWeight;
    lowerWeight = _lowerWeight;
    stoppingCriteria = _stoppingCriteria;
    psoType = _psoType;
    threshold = _threshold;
    
	if (numberOfParticles <= 0) 
		throw "Number of particles can't be less or equal than zero.";

	particles = new Particle *[numberOfParticles];

	for ( i = 0; i < numberOfParticles; i++)
		particles[i] = new Particle	(_numberOfVariables,
		                                _lowerBounds,
		                                _upperBounds,
		                                _vmax,
		                                _c1, _c2,
		                                &weight,
		                                _objectiveFunction);

	bestParticleIndex = 0;

	updateGlobalBest ();
}

PSO::~PSO ()
{
	for (int i = 0; i < numberOfParticles; i++)
	    delete particles[i];
	delete [] particles;
		
}

void PSO::updateParticles ()
{
    for (int i = 0; i < numberOfParticles; i++) {
        particles[i]->updateParticle(particles[bestParticleIndex]->getBestPosition());
    }
}

void PSO::updateGlobalBest ()
{
    for (int i = 0; i < numberOfParticles; i++)
        if (particles[i]->getFeasible() || !particles[bestParticleIndex]->getBestFeasible())
            if (particles[i]->getFeasible() != particles[bestParticleIndex]->getBestFeasible() || particles[i]->getValue() <= particles[bestParticleIndex]->getBestValue())
                bestParticleIndex = i;
}


void PSO::optimize ()
{
	int i = 0;
	if (stoppingCriteria.compare("none") != 0) {
	
		while ( i < maxIteration)
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
	
	} else if (stoppingCriteria.compare("impBest") != 0) {
	
		while ( (i < maxIteration) && (impBest() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("impAv") != 0) {
	
		while ( (i < maxIteration) && (impAv() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
	
	} else if (stoppingCriteria.compare("noAce") != 0) {
	
		while ( (i < maxIteration) && (noAce() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("movObj") != 0) {
	
		while ( (i < maxIteration) && (movObj() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("movPor") != 0) {
	
		while ( (i < maxIteration) && (movPor() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("stdDev") != 0) {
	
		while ( (i < maxIteration) && (stdDev() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("maxDist") != 0) {
	
		while ( (i < maxIteration) && (maxDist() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("maxDistQuick") != 0) {
	
		while ( (i < maxIteration) && (maxDistQuick() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("comCrit") != 0) {
	
		while ( (i < maxIteration) && (comCrit() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
			
	} else if (stoppingCriteria.compare("diffMaxDistQuick") != 0) {
	
		while ( (i < maxIteration) && (diffMaxDistQuick() >= threshold))
			{
				updateParticles ();
				updateGlobalBest ();
				i++;
				weight = upperWeight - i / maxIteration * (upperWeight - lowerWeight);
			}
	} else {
		throw "stopping Criteria value not identified";
	}
	
	cout << i << endl;
}

void PSO::printBest ()
{
    particles[bestParticleIndex]->printParticleBest ();
}

double PSO::impBest ()
{
	return threshold + 1;
}

double PSO::impAv () 
{
	return threshold + 1;
}

double PSO::noAce () 
{
	return threshold + 1;
}

double PSO::movObj () 
{
	return threshold + 1;
}

double PSO::movPor()
{
	return threshold + 1;
}

double PSO::stdDev ()
{
	return threshold + 1;
}

double PSO::maxDist ()
{
	return threshold + 1;
}

double PSO::maxDistQuick ()
{
	return threshold + 1;
}

double PSO::comCrit ()
{
	return threshold + 1;
}

double PSO::diffMaxDistQuick ()
{
	return threshold + 1;
}

