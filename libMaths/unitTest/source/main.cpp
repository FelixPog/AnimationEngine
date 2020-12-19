#include "pch.h"

#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>

int main(int /*argc*/, char* argv[])
{
	Catch::Session session; // There must be exactly one instance

	// Global setup

	int argc = 2;
	char* arg[2];
	arg[0] = argv[0];
	arg[1] = "~[trigo]"; // ask catch2 to not run trigo test

	int numFailed = session.run(argc, arg);

	// Global cleanup

	return numFailed;
}
