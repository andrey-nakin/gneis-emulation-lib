#include <cmath>

#include <gtest/gtest.h>

#include "isnp/util/RandomNumberGenerator.hh"
#include "isnp/testutil/Stat.hh"

namespace isnp {

namespace util {

static void ScatteringTest(G4double const significant, unsigned const precision,
		G4double const expectedRange) {

	testutil::Stat v;

	for (int i = 0; i < 1000000; i++) {
		v += RandomNumberGenerator::locality(significant, precision);
	}

	EXPECT_TRUE(v.Is(significant));
	EXPECT_NEAR(expectedRange / std::sqrt(12), v.GetStd(),
			expectedRange / 1000);

}

TEST(RandomNumberGenerator, LocalityScattering)
{

	ScatteringTest(1.23456, 6, 1e-5);
	//ScatteringTest(1.23456e-5, 6, 1e-10);
	//ScatteringTest(1.23456e5, 6, 1e-0);

}

}

}
