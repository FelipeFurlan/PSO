
#ifndef PSO_H
#define PSO_H

#include "particle.h"
#include <string>
using namespace std;

class PSO
{
public:

    PSO (int,
            int ,
            double *,
            double *,
            double *,
            void (*)(Particle *),
            double,
            double,
            int,
            double,
            double,
            double,
            string,
            string);

    ~PSO ();

    void optimize();

    //double getConvergence ();

    double getBestValue ();

    const double *getBestPosition ();

    bool getBestFeasibility ();

    void printBest ();

private:

    void initializeParticles ();

    void updateParticles ();

    void updateGlobalBest ();

    void updateConvergence ();

    void printParticle (int);

    Particle **particles;

    int numberOfParticles;

    int bestParticleIndex;

    double weight;

    double lowerWeight;

    double upperWeight;

    int maxIteration;

    double threshold;
    
    string psoType;
    
    string stoppingCriteria;
    
    double impBest ();
    
	double impAv ();

	double noAce ();

	double movObj ();
	
	double movPor ();

	double stdDev ();

	double maxDist ();

	double maxDistQuick ();

	double comCrit ();

	double diffMaxDistQuick ();
    
};

#endif
