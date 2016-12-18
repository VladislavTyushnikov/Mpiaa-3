#pragma once
#include<windows.h>
#include <windowsx.h>
#include <stdio.h>
struct tmr_s_
{
	LARGE_INTEGER time_start, time_stop, freq;
} tmr_s;

inline void timer_start()
{
	QueryPerformanceFrequency(&tmr_s.freq);
	QueryPerformanceCounter(&tmr_s.time_start);
}

inline double timer_check() // Сколько прошло с предыдущего чека или запуска таймера
{
	QueryPerformanceCounter(&tmr_s.time_stop);
	double time_delta = (double)(tmr_s.time_stop.QuadPart - tmr_s.time_start.QuadPart) / (double)(tmr_s.freq.QuadPart);
	QueryPerformanceCounter(&tmr_s.time_start);
	return time_delta;

}