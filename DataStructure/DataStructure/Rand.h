#pragma once
#include <random>
#include <functional>
#include <chrono>
#include <ratio>
namespace ZXXXE
{
	using namespace std;
	using namespace chrono;
	class RandInt
	{
	public:
		RandInt(int low, int high) :p{ low,high } {}
		int operator()() const { return r(); }
	private:
		uniform_int_distribution<>::param_type p;
		function<int()> r = bind(uniform_int_distribution<>{p}, default_random_engine{
			static_cast<unsigned>(system_clock::now().time_since_epoch().count())
			});
	};
}
using RandInt = ZXXXE::RandInt;