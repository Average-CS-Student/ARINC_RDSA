#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <map>
#include <memory>
#include <mutex>
#include "Arinc429.h"

extern std::mutex bufferMutex;
extern std::shared_ptr<const std::map<uint16_t, Arinc429>> buffer;

#endif // SHAREDBUFFER_H
