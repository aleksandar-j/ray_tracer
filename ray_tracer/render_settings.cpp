
#include "render_settings.hpp"

/* Default values */
int AA = 2;

bool AA_OPTIMIZE = false;
double AA_OPTIMIZE_AVGDIFFACCEPTED = 2.0;
double AA_OPTIMIZE_MAXDIFFACCEPTED = 200.0;

int NUM_SCREENS = 16;
int NUM_THREADS = 4;

bool RUN_REFLECTION = true;
bool RUN_REFLECTION_DIFFUSE = true;
bool RUN_REFLECTION_SPECULAR = true;
bool RUN_LIGHT = true;
bool RUN_LIGHT_ATMOSPHERE = true;

int STACK_DEPTH_ATMOSPHERE = 1;
int STACK_DEPTH_DIFFUSE = 5;
int STACK_DEPTH_SPECULAR = 5;

double MAX_STACK_DEPTH = 100.0;

int STACK_DEPTH_ATMOSPHERE_ADD = MAX_STACK_DEPTH / STACK_DEPTH_ATMOSPHERE;
int STACK_DEPTH_DIFFUSE_ADD = MAX_STACK_DEPTH / STACK_DEPTH_DIFFUSE;
int STACK_DEPTH_SPECULAR_ADD = MAX_STACK_DEPTH / STACK_DEPTH_SPECULAR;

int MAX_ATMOSPHERE_ITERATIONS = 2;


//#include <Windows.h>

void load_settings()
{
    /*
    // load from file
    char* directory = new char[512];
    GetCurrentDirectory(512, directory);

    char filename[] = "\\settings.ini";
    char section[] = "settings";

    strcat_s(directory, 512, filename);

    // Loading...
    AA = GetPrivateProfileInt(section, "AA", AA, directory);

    AA_OPTIMIZE = (GetPrivateProfileInt(section, "AA_OPTIMIZE", AA_OPTIMIZE, directory) == 1) ? true : false;

    NUM_SCREENS = GetPrivateProfileInt(section, "NUM_SCREENS", NUM_SCREENS, directory);
    NUM_THREADS = GetPrivateProfileInt(section, "NUM_THREADS", NUM_THREADS, directory);

    RUN_REFLECTION = (GetPrivateProfileInt(section, "RUN_REFLECTION", RUN_REFLECTION, directory) == 0) ? false : true;
    RUN_REFLECTION_DIFFUSE = (GetPrivateProfileInt(section, "RUN_REFLECTION_DIFFUSE", RUN_REFLECTION_DIFFUSE, directory) == 0) ? false : true;
    RUN_REFLECTION_SPECULAR = (GetPrivateProfileInt(section, "RUN_REFLECTION_SPECULAR", RUN_REFLECTION_SPECULAR, directory) == 0) ? false : true;
    RUN_LIGHT = (GetPrivateProfileInt(section, "RUN_LIGHT", RUN_LIGHT, directory) == 0) ? false : true;
    RUN_LIGHT_ATMOSPHERE = (GetPrivateProfileInt(section, "RUN_LIGHT_ATMOSPHERE", RUN_LIGHT_ATMOSPHERE, directory) == 0) ? false : true;

    MAX_ATMOSPHERE_ITERATIONS = GetPrivateProfileInt(section, "MAX_ATMOSPHERE_ITERATIONS", MAX_ATMOSPHERE_ITERATIONS, directory);

    STACK_DEPTH_DIFFUSE = GetPrivateProfileInt(section, "STACK_DEPTH_DIFFUSE", STACK_DEPTH_DIFFUSE, directory);
    STACK_DEPTH_SPECULAR = GetPrivateProfileInt(section, "STACK_DEPTH_SPECULAR", STACK_DEPTH_SPECULAR, directory);
    STACK_DEPTH_ATMOSPHERE = GetPrivateProfileInt(section, "STACK_DEPTH_ATMOSPHERE", STACK_DEPTH_ATMOSPHERE, directory);
    */
}
