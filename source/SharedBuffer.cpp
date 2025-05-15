#include "SharedBuffer.h"

std::mutex bufferMutex;
std::shared_ptr<const std::map<uint16_t, Arinc429>> buffer = std::make_shared<std::map<uint16_t, Arinc429>>();
