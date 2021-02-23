#pragma once
#include "Build.h"

class MainBuild : public Build
{
	public:
		MainBuild();
		void creatWorker();
		void show(RenderWindow& window);
	protected:
		int *workerMas;
		int workWorkers;
};

