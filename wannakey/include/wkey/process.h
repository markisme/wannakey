#ifndef WKEY_PROCESS_H
#define WKEY_PROCESS_H

#include <string>
#include <cstdint>
#include <map>

#include <wkey/filesystem.h>

namespace wkey {

struct ProcInfo {
  std::string FullPath;
  uint32_t Pid;
};

typedef std::map<FileID, ProcInfo> MapFilesPID;

MapFilesPID getProcessList();
uint32_t getPIDByPath(MapFilesPID const& PIDs, const char* Path);
std::string getProcessPath(MapFilesPID const& Procs, uint32_t Pid);

} // wkey

#endif
