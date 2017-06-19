#include <string>
#include "simulation.h"

int 
main(int, char* [])
{
	const std::string ASSETS = "SimulationAssets";
	
	//only exits if run_simulation rtns false
	bool restart = false;
	do
	{
		Simulation sim(ASSETS);
		restart = sim.runSimulation();
	} while (restart);

	return 0;
}

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif

#ifndef GLM_LEFT_HANDED
#define GLM_LEFT_HANDED
#endif

#if defined(_MSC_VER)
#  pragma comment(lib, "d3d11.lib")
#  pragma comment(lib, "SDL2.lib")
#  pragma comment(lib, "SDL2main.lib")
#  pragma comment(lib, "tinyobjloader.lib")
#  pragma comment(lib, "AntTweakBar.lib")
#endif
