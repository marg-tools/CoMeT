#include "dvfsConstFreq.h"
#include <iomanip>
#include <iostream>

using namespace std;

DVFSConstFreq::DVFSConstFreq(const PerformanceCounters *performanceCounters, int numberOfCores, int activeCoreFreq, int idleCoreFreq)
	: performanceCounters(performanceCounters), numberOfCores(numberOfCores), activeCoreFreq(activeCoreFreq), idleCoreFreq(idleCoreFreq) {

}

std::vector<int> DVFSConstFreq::getFrequencies(const std::vector<int> &oldFrequencies, const std::vector<bool> &activeCores) {
	std::vector<int> frequencies(numberOfCores);

	for (unsigned int coreCounter = 0; coreCounter < numberOfCores; coreCounter++) {
		if (activeCores.at(coreCounter)) {
			float power = performanceCounters->getPowerOfCore(coreCounter);
			float temperature = performanceCounters->getTemperatureOfCore(coreCounter);
			int frequency = oldFrequencies.at(coreCounter);
			float utilization = performanceCounters->getUtilizationOfCore(coreCounter);

			cout << "[Scheduler][DVFS_MAX_FREQ]: Core " << setw(2) << coreCounter << ":";
			cout << " P=" << fixed << setprecision(3) << power << " W";
			cout << "  f=" << frequency << " MHz";
			cout << "  T=" << fixed << setprecision(1) << temperature << " C";  // avoid the '°' symbol, it is not ASCII
			cout << "  utilization=" << fixed << setprecision(3) << utilization << endl;
			frequencies.at(coreCounter) = activeCoreFreq;
		} else {
			frequencies.at(coreCounter) = idleCoreFreq;
		}
	}

	return frequencies;
}
