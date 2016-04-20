//#include "TestEngineApp.h"


//TODO 
//Move TO Utils.h
template <typename... TArgs>
std::vector<size_t> GetTypes()
{
	vector<size_t> result = { typeid(TArgs).hash_code()... };
	return result;
}

int main() 
{
	//TestEngineApp* App = new TestEngineApp();
	//
	//App->Run(1280,720);
	//
	//delete App;
	printf((std::string("Type List: \n") + std::to_string(GetTypes<int, int, char>()[0])).c_str());

	return 0;
}
