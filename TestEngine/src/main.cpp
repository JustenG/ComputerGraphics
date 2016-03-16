#include "TestEngineApp.h"
#include <vector>
#include "Components\ComponentManager.h"
#include "Components\Transform.h"

int main() 
{
	ComponentManager lol;
	int a = lol.AddComponent<Transform>();
	//TestEngineApp* App = new TestEngineApp();
	//
	//App->Run();
	//
	//delete App;
	return 0;
}
