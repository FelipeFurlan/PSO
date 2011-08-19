#include <iostream>
#include "../include/pso.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

void objectiveFunction (Particle *);

int main()
{
    double *lower, *upper, *vmax;
	int numberOfParticles = -1;
	int numberOfVariables = -1;
	int maxIteration = -1;
	double lowerWeight = -1;
	double upperWeight = -1;
	double c1 = -1, c2 = -1;
	string text;
	clock_t begin = clock();
	double timeElapsed;
	string stoppingCriteria ("none");
	string psoType ("Classic");
	double threshold;
	ifstream datafile;
	
	datafile.exceptions( ifstream::failbit | ifstream::badbit | ifstream::eofbit );
	try
	{
		datafile.open("input");
		while (datafile >> text)
		{
			if(!text.compare("numberOfVariables:")) {
				if (datafile.peek() == '\n') {
					throw "numberOfVariables' value is missing";
				}
								
				datafile >> numberOfVariables;
				
				if (numberOfVariables <= 0) {
					throw "numberOfVariables must be greater than zero.";
				}
				
			} else if (!text.compare("numberOfParticles:")) {
				if (datafile.peek() == '\n') {
					throw "numberOfVariables' value is missing";
				}
				
				datafile >> numberOfParticles;
			} else if (!text.compare("lowerBounds:")) {
					
				if (numberOfVariables == -1) {
					throw "numberOfVariables must come before lowerBounds";
				}
				
				lower = new double [numberOfVariables];
					
				for (int i = 0; i < numberOfVariables; i++) {
					if (datafile.peek() == '\n') {
						throw "lowerBounds' value missing";
					}
					
					datafile >> lower[i];
				}
				
			} else if (!text.compare("upperBounds:")) {
					
				if (numberOfVariables == -1) {
					throw "numberOfVariables must come before upperBounds";
				}
				
				upper = new double [numberOfVariables];
					
				for (int i = 0; i < numberOfVariables; i++) {
					if (datafile.peek() == '\n') {
						throw "upperBounds' value missing";
					}
					
					datafile >> upper[i];
				}
			} else if (!text.compare("maxVelocity:")) {
					
				if (numberOfVariables == -1) {
					throw "numberOfVariables must come before maxVelocity";
				}
				
				vmax = new double [numberOfVariables];
					
				for (int i = 0; i < numberOfVariables; i++) {
					if (datafile.peek() == '\n') {
						throw "maxVelocity's value missing";
					}
					
					datafile >> vmax[i];
				}
			} else if (!text.compare("lowerWeight:")) {
				if (datafile.peek() == '\n') {
					throw "lowerWeight's value is missing";
				}
					
				datafile >> lowerWeight;
				
			} else if (!text.compare("upperWeight:")) {
				if (datafile.peek() == '\n') {
					throw "upperWeight's value is missing";
				}
				
				datafile >> upperWeight;
			} else if (!text.compare("maxIteration:")) {
				if (datafile.peek() == '\n') {
					throw "maxIteration's value is missing.";
				}
				
				datafile >> maxIteration;
			} else if (!text.compare("c1:")) {
				if (datafile.peek() == '\n') {
					throw "c1 value is missing";
				}
				
				datafile >> c1;
			} else if (!text.compare("c2:")) {
				if (datafile.peek() == '\n') {
					throw "c2 value is missing.";
				}
				
				datafile >> c2;
			} else if (!text.compare("stoppingCriteria:")) {
				if (datafile.peek() == '\n') {
					throw "stoppingCriteria value is missing.";
				}
				
				datafile >> stoppingCriteria;
			
			} else if (!text.compare("psoType:")) {
				if (datafile.peek() == '\n') {
					throw "psoType value is missing.";
				}
				
				datafile >> psoType;
				
			} else if (!text.compare("threshold:")) {
				if (datafile.peek() == '\n') {
					throw "threshold value is missing.";
				}
				
				datafile >> threshold;
			
			} else {
				cout << "Parameter " << text << " not recognized" << endl;
				throw;
			}
		}
	}
	catch (const char *e)
	{
		cerr << e << endl;
		if (datafile.is_open()) {
			datafile.close();
		}
		return 0;
	}
    catch (ifstream::failure e)
	{
		if (!datafile.eof()) {
			cerr << "Error with input file." << e.what() << endl;
			
			if (datafile.is_open()) {
				datafile.close();
			}
			return 0;
		}
	}
	catch (...)
	{
		cerr << "Unexpected error." << endl;
		
		if (datafile.is_open()) {
			datafile.close();
		}
		return 0;
	}
	
	if (datafile.is_open()) {
		datafile.close();
	}
	
	try
	{
		PSO pso(numberOfParticles, numberOfVariables, lower, upper, vmax, objectiveFunction, lowerWeight, upperWeight, maxIteration, c1, c2, threshold, stoppingCriteria, psoType);

		pso.optimize();

		pso.printBest();
	}
	catch (const char *e)
	{
		cerr << e << endl;
	}
	catch (...)
	{
		cerr << "Unexpected error." << endl;
	}
	
	timeElapsed = 1000 * (clock() - begin)/CLOCKS_PER_SEC;
	
	cout << "Time elapsed = " << timeElapsed << " miliseconds" << endl;
    return 0;

}

//function to be minimized
void objectiveFunction (Particle *Particle)
{
    const double *_position = Particle->getPosition ();
    double _constraits;

    if (Particle::getNumberOfVariables () != 2) {
        throw "Number of variables in Particles does not match number of variables in objective function" ;
    }

    Particle->setValue(100 * pow((_position[1] - pow(_position[0], 2)), 2) + pow((1 - _position[0]), 2));
    _constraits = _position[1] + _position[0] > 1 ? 10000000 * (_position[1] + _position[0] - 1) : 0;
    Particle->setConstraits(_constraits);
    Particle->setFeasible(_constraits ? false : true);
    return;
}
