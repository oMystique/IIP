#include "application.h"


int main() {
	unique_ptr<Application> application(new Application());
	return 0;
}