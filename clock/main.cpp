#include "graphics.cpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


int main(int argc, char **argv)
{
	initializeDisplays(argc, argv);
	updateLargeTime(3,12);	

	return 0;
}