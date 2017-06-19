/*------------------------------------------------------------------------------
author: andywm, 2016
description:
Primary simulation class, responsible for the main application loop, invokes 
calls to input handling, world updating, and rendering.
------------------------------------------------------------------------------*/
#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include "window_archtype.h"
#include "d3d_window.h"
#include "window_manager.h"
#include "environment.h"
#include "Registry.h"
#include "Scene.h"
#include "clock.h"

class Simulation
{
private:
	enum class INPUT_SCHEME { DEFAULT };
	struct UI_StateMachine
	{
		INPUT_SCHEME controlMode;
		bool mouseDown;
	}mUI_State;
	bool mResetRequired;
	bool mTerminate;

	WindowManager mWM;
	D3DWindow mWindow; // WindowArchtype
	std::shared_ptr<Assets::Registry> mRegister;
	std::unique_ptr<Environment::Environment> mWorld;
	std::shared_ptr<Render::Scene::Scene> mScene;

private:
	Utilities::Clock mWorldClock;
	void userInputHandling();
	void UI_Default();
	struct Cardinal
	{
		const glm::vec3 FORWARD;
		const glm::vec3	BACKWARD;
		const glm::vec3 LEFT;
		const glm::vec3 RIGHT;
		const glm::vec3 UP;
		const glm::vec3 DOWN;
	}const mCardinals;
	struct Rotational
	{
		const int UP;
		const int DOWN;
		const int LEFT;
		const int RIGHT;
	}const mRotation;

public:
	explicit Simulation(const std::string & assetDir);
	Simulation& operator=(const Simulation&) = delete;
	~Simulation() = default;
	Simulation(Simulation & sim) = delete;
	//const Simulation operator=(const Simulation & sim) = delete;
	//also delete move semantics...

public:	//ui stuff
	bool runSimulation();

};
#endif //SIMULATION_H