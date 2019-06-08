//////////////////////////////////////////////////////////////////////////////
// Timer.h
// =========
// High Resolution Timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system 
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2017-03-30
// http://www.songho.ca/misc/timer/timer.html
// Copyright (c) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////

#ifndef TIMER_H_DEF
#define TIMER_H_DEF

#if defined(WIN32) || defined(_WIN32)   // Windows system specific
#include <windows.h>
#else          // Unix based system specific
#include <sys/time.h>
#endif
#include <stdlib.h>

class Timer
{

private:
	double startTimeInMicroSec;                 // starting time in micro-second
	double endTimeInMicroSec;                   // ending time in micro-second
	int    stopped;                             // stop flag 
#if defined(WIN32) || defined(_WIN32)
	LARGE_INTEGER frequency;                    // ticks per second
	LARGE_INTEGER startCount;                   //
	LARGE_INTEGER endCount;                     //
#else
	timeval startCount;                         //
	timeval endCount;                           //
#endif

public:
	Timer() {
#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceFrequency(&frequency);
		startCount.QuadPart = 0;
		endCount.QuadPart = 0;
#else
		startCount.tv_sec = startCount.tv_usec = 0;
		endCount.tv_sec = endCount.tv_usec = 0;
#endif

		stopped = 0;
		startTimeInMicroSec = 0;
		endTimeInMicroSec = 0;
	}
	~Timer() = default;
	//start timer
	inline void   start()                            
	{
		stopped = 0; // reset stop flag
#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceCounter(&startCount);
#else
		gettimeofday(&startCount, NULL);
#endif
	}
	// stop the timer
	inline void   stop()
	{
		stopped = 1; // set timer stopped flag

#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceCounter(&endCount);
#else
		gettimeofday(&endCount, NULL);
#endif
	}

	///////////////////////////////////////////////////////////////////////////////
	// same as getElapsedTimeInSec()
	///////////////////////////////////////////////////////////////////////////////
	inline double getElapsedTime()                   // get elapsed time in second
	{
		return this->getElapsedTimeInSec();
	}
	///////////////////////////////////////////////////////////////////////////////
    // divide elapsedTimeInMicroSec by 1000000
    ///////////////////////////////////////////////////////////////////////////////
	inline double getElapsedTimeInSec()               // get elapsed time in second (same as getElapsedTime)
	{
		return this->getElapsedTimeInMicroSec() * 0.000001;
	}

	///////////////////////////////////////////////////////////////////////////////
	// divide elapsedTimeInMicroSec by 1000
	///////////////////////////////////////////////////////////////////////////////
	inline double getElapsedTimeInMilliSec()          // get elapsed time in milli-second
	{
		return this->getElapsedTimeInMicroSec() * 0.001;
	}
	///////////////////////////////////////////////////////////////////////////////
	// compute elapsed time in micro-second resolution.
	// other getElapsedTime will call this first, then convert to correspond resolution.
	///////////////////////////////////////////////////////////////////////////////
	inline double getElapsedTimeInMicroSec()          // get elapsed time in micro-second
	{
#if defined(WIN32) || defined(_WIN32)
		if (!stopped)
			QueryPerformanceCounter(&endCount);

		startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
		endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
#else
		if (!stopped)
			gettimeofday(&endCount, NULL);

		startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
		endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
#endif

		return endTimeInMicroSec - startTimeInMicroSec;
	}
 


};

#endif // TIMER_H_DEF
