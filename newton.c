#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PARTICLES 1

// Two dimensional vector.
typedef struct
{
    float x;
    float y;
} Vector2;

// Two dimensional particle.
typedef struct
{
    Vector2 position;
    Vector2 velocity;
    float mass;
} Particle;

// Global array of particles.
Particle particles[NUM_PARTICLES];

// Prints all particles' position to the output. We could instead draw them on screen
// in a more interesting application.
void PrintParticles()
{
    for (int i = 0; i < NUM_PARTICLES; ++i)
    {
        Particle *particle = &particles[i];
        printf("particle[%i] (%.2f, %.2f)\n", i, particle->position.x, particle->position.y);
    }
}

// Initializes all particles with random positions, zero velocities and 1kg mass.
void InitializeParticles()
{
    for (int i = 0; i < NUM_PARTICLES; ++i)
    {
        particles[i].position = (Vector2){arc4random_uniform(50), arc4random_uniform(50)};
        particles[i].velocity = (Vector2){0, 0};
        particles[i].mass = 1;
    }
}

// Just applies Earth's gravity force (mass times gravity acceleration 9.81 m/s^2) to each particle.
Vector2 ComputeForce(Particle *particle)
{
    return (Vector2){0, particle->mass * -9.81};
}

void RunSimulation()
{
    float totalSimulationTime = 10; // The simulation will run for 10 seconds.
    float currentTime = 0;          // This accumulates the time that has passed.
    float dt = 1;                   // Each step will take one second.

    InitializeParticles();
    PrintParticles();

    while (currentTime < totalSimulationTime)
    {
        // We're sleeping here to keep things simple. In real applications you'd use some
        // timing API to get the current time in milliseconds and compute dt in the beginning
        // of every iteration like this:
        // currentTime = GetTime()
        // dt = currentTime - previousTime
        // previousTime = currentTime
        sleep(dt);

        for (int i = 0; i < NUM_PARTICLES; ++i)
        {
            Particle *particle = &particles[i];
            Vector2 force = ComputeForce(particle);
            Vector2 acceleration = (Vector2){force.x / particle->mass, force.y / particle->mass};
            particle->velocity.x += acceleration.x * dt;
            particle->velocity.y += acceleration.y * dt;
            particle->position.x += particle->velocity.x * dt;
            particle->position.y += particle->velocity.y * dt;
        }

        PrintParticles();
        currentTime += dt;
    }
}

int main(int argc, char **argv)
{
    RunSimulation();
    return 0;
}