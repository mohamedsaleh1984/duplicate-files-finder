#include "finder.hpp"
using namespace ns_finder;

Finder::Finder()
{
}

void Finder::pre_search()
{
    // cout << "Pre-Search..." << endl;
}

void Finder::post_search()
{
    cout << "Total files : " << total_files() << endl;
    cout << "Total file size : " << bytesToSize(total_files_size()) << endl;
    cout << "Total Duplicate files : " << total_duplicate_files_count() << endl;
    cout << "Total Duplicate files size : " << bytesToSize(total_duplicate_files_size()) << endl;

    delete_duplicate_files();
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
    {
        count += it->second.size() - 1;
        it++;
    }

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

        it++;
    }

    return size;
}

unsigned long long Finder::total_duplicate_files_size()
{
    unsigned long long total_wasted_space = 0;
    map<string, vector<fs::path>>::iterator it = _findings.begin();
    while (it != _findings.end())
    {
        vector<fs::path> files = it->second;
        if (files.size() > 1)
        {
            unsigned long sfile = static_cast<unsigned long>(fs::file_size(files.at(0)));
            int wasted_space = (files.size() - 1) * sfile;
            total_wasted_space += wasted_space;
        }
        it++;
    }
    return total_wasted_space;
}

void Finder::delete_duplicate_files()
{
    bool bfetchInput = true;
    string strAnswer = "";

    while (bfetchInput)
    {
        cout << "Would you like to delete duplicate files? (yes/no)" << endl;
        cin >> strAnswer;

        std::transform(strAnswer.begin(), strAnswer.end(), strAnswer.begin(), ::tolower);

        if (strAnswer == "yes" || strAnswer == "no")
        {
            if (strAnswer == "yes")
            {
                map<string, vector<fs::path>>::iterator it = _findings.begin();
                while (it != _findings.end())
                {
                    vector<fs::path> files = it->second;
                    if (files.size() > 1)
                    {
                        for (int i = 1; i < files.size(); i++)
                        {
                            std::filesystem::remove(files[i]);
                            cout << files[i].filename().string() << " has been deleted successfully." << endl;
                        }
                    }
                    it++;
                }
                bfetchInput = false;
            }
            else if (strAnswer == "no")
            {
                bfetchInput = false;
            }
        }
        else
        {
            cout << "Invalid input." << endl;
        }
    }
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

    vector<fs::path> dirs = {};
    dirs.push_back(root);

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

std::string Finder::bytesToSize(unsigned long long bytes)
{
    const std::string sizes[] = {"Bytes", "KB", "MB", "GB", "TB"};
    if (bytes == 0)
        return "n/a";

    int i = static_cast<int>(std::floor(std::log(bytes) / std::log(1024)));
    if (i == 0)
        return std::to_string(bytes) + " " + sizes[i];

    char result[20];
    std::sprintf(result, "%.1f %s", bytes / std::pow(1024, i), sizes[i].c_str());

    return std::string(result);
}