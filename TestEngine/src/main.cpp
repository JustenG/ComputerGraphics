#include "TestEngineApp.h"
int main() 
{
	TestEngineApp* App = new TestEngineApp();
	
	App->Run(1280,720);
	
	delete App;
	return 0;
}
