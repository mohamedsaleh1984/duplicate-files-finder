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

        md5_hash_result hashResult = calculate_md5_hash(filePath);

        if (hashResult.has_error)
        {
            cout << "error " << hashResult.error_message << endl;
            // log
            continue;
        }

        //    cout << "hash " << hashResult.md5_hash << endl;

        it = _findings.find(hashResult.md5_hash);
        if (it != _findings.end())
        {
            // found
            _findings[hashResult.md5_hash].push_back(f);
            cout << "found hash " << hashResult.md5_hash << endl;
        }
        else
        {
            // construct new element
            pair<string, vector<fs::path>> elem;
            vector<fs::path> paths;
            paths.push_back(f);

            elem.first = hashResult.md5_hash;
            elem.second = paths;

            _findings.insert(elem);
            cout << "New hash " << hashResult.md5_hash << endl;
        }
    }

    post_search();
}

/// @brief Calculate MD5 has for file
struct md5_hash_result Finder::
    calculate_md5_hash(const std::string &file_path)
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
    //  cout << "md5 " << res.md5_hash << endl;
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
