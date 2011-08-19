#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
public:

    //Class constructor
    Particle (int, const double *, const double *, const double *, double , double , const double *, void (*)(Particle *));

    ~Particle ();

    //Inicialize particle position, velocity, value, bestPosition,
    //bestValue and feasible
    void inicializeParticle ();

    void updateParticle (const double *);

    void printParticle ();

    void printParticleBest ();

    bool getBestFeasible ();

    double getBestValue ();

    const double *getBestPosition ();

    const double *getPosition ();

    double getValue ();

    bool getFeasible ();

    void setValue (double);

    void setConstraits (double);

    void setFeasible (bool);

    static int getNumberOfVariables ();

private:

    void updateParticleBest ();

    static int numberOfVariables;

    //Particle position
    double *position;

    //Particle velocity
    double *velocity;

    //Function value over particle position
    double value;

    //Particle feasibility
    bool feasible;

    //Particle best position
    double *bestPosition;

    //Function value over particle best position
    double bestValue;

    bool bestFeasible;

    static const double *weight;

    //Variables upper bounds
    static const double *upperBounds;

    //Variables lower bounds
    static const double *lowerBounds;

    static const double *maxVelocity;

    //synthony parameters
    static double c1, c2;

    double constraits;

    //pointer to the objective function
    //returns the feasibility of the particle
    static void (*functionPtr) (Particle *);
};
#endif
