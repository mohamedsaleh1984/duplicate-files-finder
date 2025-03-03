#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include "misc/misc.hpp"
#include "finder/finder.hpp"

using namespace std;
using namespace ns_finder;

int main()
{
    // fs::path p("E:\\YouTube-Channels");
    // Finder f;
    // f.start_search(p);

    Finder f;
    struct md5_hash_result result  = f.calculate_md5_hash("./README.md");
    if(result.has_error){
        cout << result.error_message << endl;  
    }else{
        cout << result.md5_hash << endl;
    }

    
    return 0;
}