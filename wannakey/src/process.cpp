#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

#include <iostream>

#include <wkey/process.h>
#include <wkey/tools.h>

namespace wkey {

// Adapted from http://stackoverflow.com/questions/20874381/get-a-process-id-in-c-by-name
MapFilesPID getProcessList()
{
  HANDLE hProcessSnap;
  PROCESSENTRY32 pe32;
  uint32_t result = NULL;

  // Take a snapshot of all processes in the system.
  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (INVALID_HANDLE_VALUE == hProcessSnap) {
    std::cerr << "Unable to create process list snapshot!" << std::endl;
    return{};
  }

  pe32.dwSize = sizeof(MODULEENTRY32);

  // Retrieve information about the first process,
  // and exit if unsuccessful
  if (!Process32First(hProcessSnap, &pe32))
  {
    CloseHandle(hProcessSnap);          // clean the snapshot object
    std::cerr << "Failed to gather information on system processes!" << std::endl;
    return{};
  }

  MapFilesPID Ret;

  do
  {
    const uint32_t pid = pe32.th32ProcessID;
    char Path[MAX_PATH + 1];
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (hProc == NULL) {
      auto Err = getLastEC();
      if (Err && Err.value() != ERROR_ACCESS_DENIED) {
        std::cerr << "Warning: unable to open process " << pid << ": " << Err.message() << std::endl;
      }
      continue;
    }
    uint32_t size = MAX_PATH;
    if (!GetModuleFileNameEx(hProc, NULL, Path, MAX_PATH)) {
      std::cerr << "Warning: unable to retrieve the full path of the process for PID " << pid << ": " << getLastErrorMsg() << std::endl;
      continue;
    }
    CloseHandle(hProc);
    FileID fid = getFileID(Path);
    if (fid == FileIDInvalid) {
      continue;
    }

    Ret.insert(std::make_pair(fid, ProcInfo{ std::string{Path}, pe32.th32ProcessID }));
  } while (Process32Next(hProcessSnap, &pe32));

  CloseHandle(hProcessSnap);

  return Ret;
}

uint32_t getPIDByPath(MapFilesPID const& PIDs, const char* Path)
{
  FileID fid = getFileID(Path);
  if (fid == FileIDInvalid) {
    return -1;
  }
  auto It = PIDs.find(fid);
  if (It == PIDs.end()) {
    std::cerr << "Unable to find a running process that is mapped to '" << Path << "'!" << std::endl;
    return -1;
  }
  return It->second.Pid;
}

std::string getProcessPath(MapFilesPID const& Procs, uint32_t Pid)
{
  for (auto const& P : Procs) {
    if (P.second.Pid == Pid) {
      return P.second.FullPath;
    }
  }
  return std::string{};
}


} // wcry
