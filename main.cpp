#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include "fileHelper.h"
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class Demo
{
public:
    static void usingMD5()
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

    static void usingPrintDirs()
    {
        FileHelper::print_directories("Z:\\z");
    }

    static void usingGetFiles()
    {
        fs::path root = "Z:\\z";
        vector<fs::path> dirs = {};
        dirs.push_back(root);

        vector<fs::path> files = FileHelper::getFiles(dirs);
        for (auto &f : files)
            cout << f << endl;
    }

    static void usingGetFilesSubDirs()
    {
        fs::path root = "Z:\\z";
        vector<fs::path> dirs;
        FileHelper::getDirectories(root, dirs);

        vector<fs::path> files = FileHelper::getFiles(dirs);
        for (auto &f : files)
            cout << f << endl;
    }
};

int main()
{
    // Demo::usingPrintDirs();
    // Demo::usingGetFiles();
    Demo::usingGetFilesSubDirs();
    return 0;
}