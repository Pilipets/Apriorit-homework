#pragma once
#include<iostream>
#include<chrono>
class SimpleTimer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
public:
	SimpleTimer();
	~SimpleTimer();
};

