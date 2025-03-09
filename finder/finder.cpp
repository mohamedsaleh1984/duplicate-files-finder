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
    cout << "Total files " << total_files() << endl;
    cout << "Total file size " << total_files_size() << endl;
    cout << "Total Duplicate files " << total_duplicate_files_count() << endl;
    cout << "Total Duplicate files size " << total_duplicate_files_size() << endl;
}

int Finder::total_files()
{
    return this->_files.size();
}
unsigned long int Finder::total_duplicate_files_count()
{
    unsigned long int count = 0;
    map<string, vector<fs::path>>::iterator it = _findings.begin();
    while (it != _findings.end())
        count += it->second.size() - 1;
    return count;
}

unsigned long long Finder::total_files_size()
{
    unsigned long long size = 0;
    map<string, vector<fs::path>>::iterator it = _findings.begin();
    while (it != _findings.end())
    {
        vector<fs::path> files_per_key = it->second;
        for (const auto &filePath : files_per_key)
            size += static_cast<unsigned long long>(fs::file_size(filePath));
    }

    return size;
}

unsigned long long Finder::total_duplicate_files_size()
{
    unsigned long long size = 0;
    map<string, vector<fs::path>>::iterator it = _findings.begin();
    while (it != _findings.end())
    {
        vector<fs::path> files = it->second;
        if (files.size() > 1)
        {
            unsigned long long sfile = static_cast<unsigned long long>(fs::file_size(files.at(0)));
            unsigned long long wasted_space = files.size() - 1 * sfile;
            size += wasted_space;
        }
    }
    return size;
}

void Finder::delete_duplicate_files()
{
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

    map<string, vector<fs::path>>::iterator it;

    for (const auto &f : _files)
    {
        string filePath = f.generic_string();
        // cout << "Path:" << filePath << endl;
        hash_result hashResult = calculate_xxhash(filePath);
        if (hashResult.has_error)
        {
            cout << "error " << hashResult.error_message << endl;
            continue;
        }

        it = _findings.find(hashResult.hash);
        if (it != _findings.end())
        {
            // found
            _findings[hashResult.hash].push_back(f);
            // cout << "found hash " << hashResult.hash << endl;
        }
        else
        {
            // construct new element
            pair<string, vector<fs::path>> elem;
            vector<fs::path> paths;
            paths.push_back(f);

            elem.first = hashResult.hash;
            elem.second = paths;

            _findings.insert(elem);
        }
    }

    post_search();
}

/// @brief Calculate MD5 has for file
struct hash_result Finder::
    calculate_md5_hash(const std::string &file_path)
{
    struct hash_result res;
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

    res.hash = ss.str();
    //  cout << "md5 " << res.md5_hash << endl;
    return res;
}

/// @brief Printout directiorys for desired path
/// @param path
// void Finder::print_directories(const fs::path &path)
// {
//     for (const auto &entry : fs::directory_iterator(path))
//     {
//         if (fs::is_directory(entry))
//         {
//             std::cout << entry.path() << std::endl;
//             print_directories(entry.path()); // Recursive call for subdirectories
//         }
//     }
// }

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
// void Finder::print_files(vector<fs::path> &dirs)
// {
//     vector<fs::path> files;

//     for (const auto &entry : dirs)
//     {
//         for (const auto &entry : fs::directory_iterator(entry))
//         {
//             if (fs::is_regular_file(entry))
//             {
//                 std::cout << entry.path().filename().string() << std::endl;
//             }
//         }
//     }
// }

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

/// @brief Calculate hash using xxhash
struct hash_result Finder::calculate_xxhash(const std::string &file_path)
{
    struct hash_result res;
    const char *p = file_path.c_str();
    FILE *file = fopen(p, "rb");
    if (!file)
    {
        res.has_error = true;
        res.error_message = "Error opening file.";
        return res;
    }

    XXH64_state_t *state = XXH64_createState();
    XXH64_reset(state, 0); // Seed = 0

    unsigned char buffer[CHUNK_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file)) > 0)
    {
        XXH64_update(state, buffer, bytes_read);
    }

    fclose(file);
    XXH64_hash_t hash = XXH64_digest(state);
    XXH64_freeState(state);
    res.hash = to_string(hash);
    return res;
}