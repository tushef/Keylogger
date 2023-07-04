#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer {
private:
	//Threads are new to C++
    //this will allow us to run asynchronous code execution
    //without blocking the main thread in main.cpp (the while loop)
	std::thread Thread;
	bool Alive = false; //Timer Thread Check
	long CallNumber = -1L; 
	long repeat_count = -1L;
	std::chrono::milliseconds interval = std::chrono::milliseconds(0);

	//c++ 11: std::function -> new data type that can contain functions.
	//void(void) -> type_of_function(parameter types)
	std::function<void(void)> funct = nullptr;

	void SleepAndRun()
	{
		std::this_thread::sleep_for(interval);
		if (Alive)
		{
			Function()();  //double parentheses: 1st pair calls the function to return a function
							//second pair calls the function the 1st function returns
		}
	}

	void ThreadFunc()
	{
		if (CallNumber == Infinite)
		{
			while (Alive)
			{
				SleepAndRun();
			}
		}
		else
		{
			while (repeat_count--)
			{
				SleepAndRun();
			}

		}
	}

public:
	static const long Infinite = -1L;

	//constructors
	Timer() {}

	Timer(const std::function<void(void)>& f) : funct(f) {}

	Timer(const std::function<void(void)>& f,
		const unsigned long& i,
		const long repeat = Timer::Infinite) : funct(f),
		interval(std::chrono::milliseconds(i)),
		CallNumber(repeat) {}

	//starts the timer
	void Start(bool Async = true)
	{
		if (IsAlive()){
			return;
		}

		Alive = true;
		repeat_count = CallNumber;

		if (Async){
			//this is creating the Thread we initialized above
			//ThreadFunc is the function we created
			//it is being called to run on this thread
			//[this] is the parameter needed for the ThreadFunc function
			Thread = std::thread(&Timer::ThreadFunc, this);
		}else{
			//call the ThreadFunc()
			this->ThreadFunc();

		}
	}

	//manually stops the timer
	void Stop()
	{
		Alive = false;
		//joining means the invoked Thread will finish execution before joining the main thread
		//so basically stop the timer
		Thread.join();

	}

	//sets the function to be executed
	void SetFunction(const std::function<void(void)>& f)
	{
		funct = f;
	}

	bool IsAlive() const { return Alive; }

	void RepeatCount(const long r)
	{
		if (Alive)
		{
			return;
		}
		CallNumber = r;
	}

	long GetLeftCount() const { return repeat_count; }

	long RepeatCount() const { return CallNumber; }

	void SetInterval(const unsigned long& i)
	{
		if (Alive)
		{
			return;
		}
		interval = std::chrono::milliseconds(i);
	}

	//.count() converts from chrono milliseconds to long
	unsigned long Interval() const { return (unsigned long)interval.count(); } // fetching interval to long type


	const std::function<void(void)>& Function() const
	{
		return funct;
	}


};

#endif // !TIMER_H