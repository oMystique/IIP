#include "application.h"


int main() {
	unique_ptr<Application> application(new Application());
	application->Run();
	return 0;
}