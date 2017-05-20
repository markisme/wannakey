#ifndef WKEY_FILESYSTEM_H
#define WKEY_FILESYSTEM_H

#include <string>

namespace wkey {

typedef std::string FileID;
extern FileID FileIDInvalid;

FileID getFileID(const char* path);

}

#endif
