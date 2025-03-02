#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include "fileHelper.h"
using namespace std;

int main()
{
    std::string file_path = "test.txt";
    std::ofstream file(file_path);
    file << "Hello, world!";
    file.close();

    std::string hash_value = FileHelper::calculate_md5_hash(file_path);
    if (!hash_value.empty())
    {
        std::cout << "MD5 hash of " << file_path << ": " << hash_value << std::endl;
    }
    else
    {
        std::cerr << "Error calculating MD5 hash or opening file." << std::endl;
    }
}