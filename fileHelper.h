#ifndef __FILE_HELPER__
#define __FILE_HELPER__

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
using namespace std;

class FileHelper
{
public:
    static std::string calculate_md5_hash(const std::string &file_path)
    {
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open())
        {
            return ""; // Return an empty string if the file cannot be opened
        }

        MD5_CTX md5Context;
        MD5_Init(&md5Context);

        char buffer[1024];
        while (file.read(buffer, sizeof(buffer)))
        {
            MD5_Update(&md5Context, buffer, file.gcount());
        }

        unsigned char hash[MD5_DIGEST_LENGTH];
        MD5_Final(hash, &md5Context);

        std::stringstream ss;
        for (unsigned char i : hash)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
        }

        return ss.str();
    }
};

#endif