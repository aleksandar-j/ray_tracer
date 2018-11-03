#pragma once

extern int AA;

extern bool AA_OPTIMIZE;
extern double AA_OPTIMIZE_AVGDIFFACCEPTED;
extern double AA_OPTIMIZE_MAXDIFFACCEPTED;

extern int NUM_SCREENS;
extern int NUM_THREADS;

// Rendering switches
extern bool RUN_REFLECTION;
extern bool RUN_REFLECTION_DIFFUSE;
extern bool RUN_REFLECTION_SPECULAR;
extern bool RUN_LIGHT;
extern bool RUN_LIGHT_ATMOSPHEREREF;

// What is the maximum times these could get called, given that they are only ones called
extern int STACK_DEPTH_ATMOSPHERE;
extern int STACK_DEPTH_DIFFUSE;
extern int STACK_DEPTH_SPECULAR;

// Maximum depth baseline (only affects precision of above values)
extern double MAX_STACK_DEPTH;
// How much do we increase depth for any operation
extern int STACK_DEPTH_ATMOSPHERE_ADD;
extern int STACK_DEPTH_DIFFUSE_ADD;
extern int STACK_DEPTH_SPECULAR_ADD;

// How many times do we run the atmosphere light check in the worst case, best case is half that
extern int MAX_ATMOSPHERE_ITERATIONS;



void load_settings();