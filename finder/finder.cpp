#include "finder.hpp"
using namespace ns_finder;
Finder::Finder()
{
}

void Finder::pre_search()
{
    cout << "Pre-Search..." << endl;
}

void Finder::post_search()
{
    cout << "Post-Search..." << endl;
}

void Finder::start_search(fs::path root)
{
    if (root.generic_string().length() == 0)
    {
        throw std::runtime_error("Root path is empty.");
    }

    if (!fs::exists(root))
    {
        throw std::runtime_error("Root path is not exists.");
    }

    _root = root;
    pre_search();

    vector<fs::path> dirs;
    getDirectories(_root, dirs);
    getFiles(dirs);

    //  cout << "Start-Hashing processs - Files Count " << files.size() << endl;

    map<string, vector<fs::path>>::iterator it;

    for (const auto &f : _files)
    {
        string filePath = f.generic_string();
        cout << "Path:" << filePath << endl;

        string hashResult = calculate_hash(filePath);

        if (hashResult == "")
        {
            cout << "error hash is empty" << endl;
            continue;
        }

        //    cout << "hash " << hashResult.md5_hash << endl;

        it = _findings.find(hashResult);
        if (it != _findings.end())
        {
            // found
            _findings[hashResult].push_back(f);
            cout << "found hash " << hashResult<< endl;
        }
        else
        {
            // construct new element
            pair<string, vector<fs::path>> elem;
            vector<fs::path> paths;
            paths.push_back(f);

            elem.first = hashResult;
            elem.second = paths;

            _findings.insert(elem);
            cout << "New hash " << hashResult<< endl;
        }
    }

    post_search();
}

/// @brief Calculate MD5 has for file
string Finder::
    calculate_hash(const std::string &file_path)
{
    fs::path p = file_path;
    size_t hash_value = fs::hash_value(p);
    string res =  to_string(hash_value);
    return res;
}

/// @brief Printout directiorys for desired path
/// @param path
void Finder::print_directories(const fs::path &path)
{
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (fs::is_directory(entry))
        {
            std::cout << entry.path() << std::endl;
            print_directories(entry.path()); // Recursive call for subdirectories
        }
    }
}

/// @brief Get directories in root
/// @param root
/// @param dirsOut
void Finder::getDirectories(const fs::path &root, vector<fs::path> &dirsOut)
{
    for (const auto &entry : fs::directory_iterator(root))
    {
        if (fs::is_directory(entry))
        {
            dirsOut.push_back(entry.path());
            getDirectories(entry.path(), dirsOut);
        }
    }
}

/// @brief Printout file in specific dirs.
/// @param dirs
void Finder::print_files(vector<fs::path> &dirs)
{
    vector<fs::path> files;

    for (const auto &entry : dirs)
    {
        for (const auto &entry : fs::directory_iterator(entry))
        {
            if (fs::is_regular_file(entry))
            {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
    }
}

/// @brief Return list of files in Dirs directories
/// @param dirs
/// @return
vector<fs::path> Finder::getFiles(vector<fs::path> &dirs)
{
    struct stat sb;
    for (const auto &entry : dirs)
    {
        for (const auto &entry : fs::directory_iterator(entry))
        {
            // Converting the path to const char * in the
            // subsequent lines
            std::filesystem::path outfilename = entry.path();
            std::string outfilename_str = outfilename.string();
            const char *path = outfilename_str.c_str();

            // Testing whether the path points to a
            // non-directory or not If it does, displays path
            if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
            {
                // cout << path << endl;
                // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                _files.push_back(path);
            }
        }
    }
    return _files;
}
