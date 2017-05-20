#include <Windows.h>
#include <Shlwapi.h>

#include <iostream>
#include <algorithm>

#include <wkey/filesystem.h>

// See below. Just keep this here as a remeinder.
//typedef uint64_t FileID;
//static uint64_t FileIDInvalid = (uint64_t)-1;

namespace wkey {

FileID FileIDInvalid;

FileID getFileID(const char* path)
{
  /* Original implementaion: somehow I can't get GetFileInformationByHandle working with a 32 bits process (on win10 at least!) :/
     HANDLE hFile = CreateFile(path, 0, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
     NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);

     if (!hFile) {
     std::cerr << "unable to open '" << path << "' for reading: " << getLastErrorMsg() << std::endl;
     return FileIDInvalid;
     }
     BY_HANDLE_FILE_INFORMATION FI;
     if (!GetFileInformationByHandle(hFile, &FI)) {
     std::cerr << "unable to get file information for '" << path << "': " << getLastErrorMsg() << std::endl;
     return FileIDInvalid;
     }
     return ((uint64_t)FI.nFileIndexLow) | (((uint64_t)FI.nFileIndexHigh) << 32);*/
  char Buf[MAX_PATH + 1];
  if (!PathCanonicalize(Buf, path)) {
    std::cerr << "unable to canonicalize '" << path << "' !" << std::endl;
    return FileIDInvalid;
  }
  std::string Ret(Buf);
  std::transform(Ret.begin(), Ret.end(), Ret.begin(), ::tolower);
  return Ret;
}

} // wkey
