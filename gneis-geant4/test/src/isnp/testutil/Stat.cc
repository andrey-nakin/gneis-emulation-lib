#include <algorithm>
#include <cmath>

#include "isnp/testutil/Stat.hh"

isnp::testutil::Stat::Stat() :
		count(0), sum(0.0), sum2(0.0), minValue(0.0), maxValue(0.0) {

}

G4double isnp::testutil::Stat::GetMean() const {
	return count ? sum / count : 0.0;
}

G4double isnp::testutil::Stat::GetMeanStd() const {
	return count > 0 ? GetStd() / std::sqrt(count) : 0.0;
}

G4double isnp::testutil::Stat::GetStd() const {
	auto const var = GetVar();
	return var < 0.0 ? 0.0 : std::sqrt(var);
}

G4double isnp::testutil::Stat::GetVar() const {
	return count > 1 ? (sum2 - sum * sum / count) / (count - 1) : 0.0;
}

G4double isnp::testutil::Stat::GetMin() const {
	return minValue;
}

G4double isnp::testutil::Stat::GetMax() const {
	return maxValue;
}

isnp::testutil::Stat& isnp::testutil::Stat::operator+=(G4double const value) {
	sum += value;
	sum2 += value * value;

	if (count > 0) {
		minValue = std::min(minValue, value);
		maxValue = std::max(maxValue, value);
	} else {
		minValue = maxValue = value;
	}

	++count;

	return *this;
}

bool isnp::testutil::Stat::Is(G4double const value) const {
	auto const ConfLevel999Quantile = 3.29;

	auto const mean = GetMean();
	auto const meanStd = GetMeanStd();

	return value >= mean - meanStd * ConfLevel999Quantile
			&& value <= mean + meanStd * ConfLevel999Quantile;
}
