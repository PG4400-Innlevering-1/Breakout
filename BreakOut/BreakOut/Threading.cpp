#include "Threading.h"
#include "GameManager.h"


Threading::Threading()
{
}

Threading::~Threading()
{
}


// C style generic code (had to do this because of SDL)
int Threading::threadedFunction(void* data)
{
	// print the data
	std::cout << "Running thread with value = " << reinterpret_cast<int>(data) << std::endl;

	genericThreadFunction(data);
	return 0;
}




// C++ Style generic code
template <class T>
void Threading::genericThreadFunction(T &data)
{
	std::cout << "Running thread with value = " << reinterpret_cast<int>(data) << std::endl;

	auto* logBall = static_cast<Ball*>(data);

	std::thread threadOne(stdThreadFunction, logBall);

	threadOne.join();
}


// Demonstrating some template code (couldn't find any use for it in the game)
template <class T>
T const& Threading::max(T const& a, T const& b)
{
	return a < b ? b : a;
}


void Threading::stdThreadFunction(Ball* ball)
{
	auto count = 1;

	double time_counter = 0;

	auto this_time = clock();
	auto last_time = this_time;

	const auto NUM_SECONDS = 10;

	while(threadRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

		std::cout << "Ball values = (" << ball->getPosX() << "," << ball->getPosY() << ") - ["
			<< ball->getVelX() << "," << ball->getVelY() << "]" << std::endl;


	}
}

void Threading::endThread()
{
	threadRunning = false;
}
