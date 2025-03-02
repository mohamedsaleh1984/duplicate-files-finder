#ifndef __FILE_HELPER__
#define __FILE_HELPER__

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
using namespace std;

const unsigned long int BUFFER_SIZE = 4096;
/// @brief Retain error information.
struct md5_hash_result
{
    // mdf hash value
    string md5_hash;
    // error message if there has error
    string error_message;
    // error indicator
    bool has_error = false;
};

/// @brief Helper class to perform basic functions on files, directories
class FileHelper
{
public:
    static struct md5_hash_result calculate_md5_hash(const std::string &file_path)
    {
        struct md5_hash_result res;
        MD5_CTX md5Context;
        MD5_Init(&md5Context);

        // read file content
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open())
        {
            res.has_error = true;
            res.error_message = "Error opening file.";
            return res;
        }

        char buffer[BUFFER_SIZE];
        while (file.read(buffer, sizeof(buffer)))
        {
            MD5_Update(&md5Context, buffer, file.gcount());
        }

        if (file.fail() && !file.eof())
        {
            res.has_error = true;
            res.error_message = "Error read file.";
            return res;
        }

        unsigned char hash[MD5_DIGEST_LENGTH];

        MD5_Final(hash, &md5Context);

        std::stringstream ss;
        for (unsigned char i : hash)
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);

        if (ss.str().length() == 0)
        {
            res.has_error = true;
            res.error_message = "Error calculating MD5 hash";
            return res;
        }

        res.md5_hash = ss.str();
        return res;
    }
};

#endif