#include "performance_counters.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

PerformanceCounters::PerformanceCounters(
	std::string instPowerFileName,
	std::string instTemperatureFileName,
	std::string instCPIStackFileName,
	std::string instRvalueFileName,
	std::string instVddFileName,
	std::string instDeltaVthFileName) :
		instPowerFileName(instPowerFileName),
		instTemperatureFileName(instTemperatureFileName),
		instCPIStackFileName(instCPIStackFileName),
		instRvalueFileName(instRvalueFileName),
		instVddFileName(instVddFileName),
		instDeltaVthFileName(instDeltaVthFileName) {
}

/** getPowerOfComponent
    Returns the latest power consumption of a component being tracked using base.cfg. Return -1 if power value not found.
*/
double PerformanceCounters::getPowerOfComponent (string component) const {
	ifstream powerLogFile(instPowerFileName);
	string header;
	string footer;

	if (powerLogFile.good()) {
		getline(powerLogFile, header);
		getline(powerLogFile, footer);
	}

	std::istringstream issHeader(header);
	std::istringstream issFooter(footer);
	std::string token;

	while(getline(issHeader, token, '\t')) {
		std::string value;
		getline(issFooter, value, '\t');
		if (token == component) {
			return stod (value);
		}
	}

	return -1;
}

/** getPowerOfCore
 * Return the latest total power consumption of the given core. Requires "tp" (total power) to be tracked in base.cfg. Return -1 if power is not tracked.
 */
double PerformanceCounters::getPowerOfCore(int coreId) const {
	string component = "C_" + std::to_string(coreId);
	return getPowerOfComponent(component);
}


/** getPeakTemperature
    Returns the latest peak temperature of any component
*/
double PerformanceCounters::getPeakTemperature () const {
	ifstream temperatureLogFile(instTemperatureFileName);
	string header;
	string footer;

	if (temperatureLogFile.good()) {
		getline(temperatureLogFile, header);
		getline(temperatureLogFile, footer);
	}

	std::istringstream issFooter(footer);

	double maxTemp = -1;
	std::string value;
	while(getline(issFooter, value, '\t')) {
		double t = stod (value);
		if (t > maxTemp) {
			maxTemp = t;
		}
	}

	return maxTemp;
}

/** getTemperatureOfComponent
    Returns the latest temperature of a component being tracked using base.cfg. Return -1 if power value not found.
*/
double PerformanceCounters::getTemperatureOfComponent (string component) const {
	ifstream temperatureLogFile(instTemperatureFileName);
	string header;
	string footer;

	if (temperatureLogFile.good()) {
		getline(temperatureLogFile, header);
		getline(temperatureLogFile, footer);
	}

	std::istringstream issHeader(header);
	std::istringstream issFooter(footer);
	std::string token;

	while(getline(issHeader, token, '\t')) {
		std::string value;
		getline(issFooter, value, '\t');

		if (token == component) {
			return stod (value);
		}
	}

	return -1;
}

/** getTemperatureOfCore
 * Return the latest temperature of the given core. Requires "tp" (total power) to be tracked in base.cfg. Return -1 if power is not tracked.
 */
double PerformanceCounters::getTemperatureOfCore(int coreId) const {
	string component = "C_" + std::to_string(coreId);
	return getTemperatureOfComponent(component);
}

/** getTemperatureOfBank
 * Return the latest temperature of the given memory bank. Requires "tp" (total power) to be tracked in base.cfg. Return -1 if power is not tracked.
 */
double PerformanceCounters::getTemperatureOfBank(int bankId) const {
	string component = "B_" + std::to_string(bankId);
	return getTemperatureOfComponent(component);
}

vector<string> PerformanceCounters::getCPIStackParts() const {
	ifstream cpiStackLogFile(instCPIStackFileName);
    string line;
	std::istringstream issLine;

	vector<string> parts;
	if (cpiStackLogFile.good()) {
		getline(cpiStackLogFile, line); // consume first line containing the CSV header
		getline(cpiStackLogFile, line); // consume second line containing total values
		while (cpiStackLogFile.good()) {
			getline(cpiStackLogFile, line);
			issLine.str(line);
			issLine.clear();
			std::string m;
			getline(issLine, m, '\t');
			if (m.length() > 0) {
				parts.push_back(m);
			}
		}
	}
	return parts;
}

/**
 * Get a performance metric for the given core.
 * Available performance metrics can be checked in InstantaneousPerformanceCounters.log
 */
double PerformanceCounters::getCPIStackPartOfCore(int coreId, std::string metric) const {
	ifstream cpiStackLogFile(instCPIStackFileName);
    string line;
	std::istringstream issLine;

	// first find the line in the logfile that contains the desired metric
	bool metricFound = false;
	while (!metricFound) {
		if (cpiStackLogFile.good()) {
			getline(cpiStackLogFile, line);
			issLine.str(line);
			issLine.clear();
			std::string m;
			getline(issLine, m, '\t');
			metricFound = (m == metric);
		} else {
			return 0;
		}
	}

	// then split the coreId-th value from this line (first value is metric name, but already consumed above)
	std::string value;
	for (int i = 0; i < coreId + 1; i++) {
		getline(issLine, value, '\t');
		if ((i == 0) && (value == "-")) {
			return 0;
		}
	}

	return stod(value);
}

/**
 * Get the utilization of the given core.
 */
double PerformanceCounters::getUtilizationOfCore(int coreId) const {
	float cpi = 0;
	for (const string & part : getCPIStackParts()) {
		// exclude non-memory-related parts
		if ((part.find("mem") == std::string::npos) &&
		    (part.find("ifetch") == std::string::npos) &&
		    (part.find("sync") == std::string::npos) &&
		    (part.find("dvfs-transition") == std::string::npos) &&
		    (part.find("imbalance") == std::string::npos) &&
		    (part.find("other") == std::string::npos)) {

			cpi += getCPIStackPartOfCore(coreId, part);
		}
	}
	float total = getCPIOfCore(coreId);
	return cpi / total;
}

/**
 * Get the CPI of the given core.
 */
double PerformanceCounters::getCPIOfCore(int coreId) const {
	return getCPIStackPartOfCore(coreId, "total");
}

/**
 * Get the frequency of the given core.
 */
int PerformanceCounters::getFreqOfCore(int coreId) const {
	if (coreId >= (int)frequencies.size()) {
		return -1;
	} else {
		return frequencies.at(coreId);
	}
}

/**
 * Notify new frequencies
 */
void PerformanceCounters::notifyFreqsOfCores(std::vector<int> newFrequencies) {
	frequencies = newFrequencies;
}

/**
 * Get the frequency of the given core.
 */
double PerformanceCounters::getIPSOfCore(int coreId) const {
	return 1e6 * getFreqOfCore(coreId) / getCPIOfCore(coreId);
}

/** getRvalueOfComponent
    Returns the latest reliability value of the component `component`.
    Return -1 if rvalue value not found.
*/
double PerformanceCounters::getRvalueOfComponent (std::string component) const {
    ifstream rvalueLogFile(instRvalueFileName);
    string header;
    string footer;

    if (rvalueLogFile.good()) {
        getline(rvalueLogFile, header);
        getline(rvalueLogFile, footer);
    }

    std::istringstream issHeader(header);
    std::istringstream issFooter(footer);
    std::string token;

    while(getline(issHeader, token, '\t')) {
        std::string value;
        getline(issFooter, value, '\t');

        if (token == component) {
            return stod(value);
        }
    }

    return -1;
}

/** getRvalueOfCore
 * Return the latest reliability value of the given core.
 * Requires "tp" (total power) to be tracked in base.cfg.
 * Return -1 if power is not tracked.
 */
double PerformanceCounters::getRvalueOfCore (int coreId) const {
    string component = "Core" + std::to_string(coreId) + "-TP";
    return getRvalueOfComponent(component);
}

vector<double> PerformanceCounters::getVddOfCores (int numberOfCores) const {
	ifstream vddLogFile(instVddFileName);
	string header;
	string data;

	if (vddLogFile.good()) {
		getline(vddLogFile, header);
		getline(vddLogFile, data);
	}

	std::istringstream issData(data);

	vector<double> vdds;
	for (int i = 0; i < numberOfCores; i++) {
		std::string value;
		getline(issData, value, '\t');
		vdds.push_back(stod(value));
	}

	return vdds;
}

vector<double> PerformanceCounters::getDeltaVthOfCores (int numberOfCores) const {
	ifstream deltaVthLogFile(instDeltaVthFileName);
	string data;

	if (deltaVthLogFile.good()) {
		getline(deltaVthLogFile, data);
	}

	std::istringstream issData(data);

	vector<double> delta_vs;
	for (int i = 0; i < numberOfCores; i++) {
		std::string value;
		getline(issData, value, '\t');
		delta_vs.push_back(stod(value));
	}

	return delta_vs;
}
