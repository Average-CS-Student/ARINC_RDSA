#pragma once

#include <cstdint>
#include <string>

class Arinc429 {
public:
	Arinc429();

	Arinc429(uint32_t arinc429Word);

	std::string label;
	uint8_t labelBNR;
    uint8_t SDI;
	std::string parameter;
	float value;
	std::string status;
	std::string extra;
    uint8_t error;

private:
    static std::string BNRStatus[4];

	static std::string getLabel(uint8_t label);

	void setArincFields(uint32_t arinc429Word, std::string& parameter, float& value, std::string& status, std::string& extra);

	static float decodeBNR(uint32_t arinc429Word, float maxValue, uint8_t sigBits);
};
