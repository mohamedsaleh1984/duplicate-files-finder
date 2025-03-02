#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include "filehelper/fileHelper.hpp"
#include "misc/misc.hpp"
using namespace std;
using namespace ns_fileHelper;

int main()
{
    md5_hash_result s = FileHelper::calculate_md5_hash("test.txt");
    cout << s.md5_hash << endl;
    loading();
    return 0;
}