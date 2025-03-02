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

    md5_hash_result hash_result = FileHelper::calculate_md5_hash(file_path);
    if (hash_result.has_error)
    {
        cout << hash_result.error_message << endl;
    }
    else
    {
        cout << "MD5 has " << hash_result.md5_hash << endl;
    }
}