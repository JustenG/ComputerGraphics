#include "TestEngineApp.h"
int main() 
{
	TestEngineApp* App = new TestEngineApp();
	
	App->Run();
	
	delete App;
	return 0;
}
