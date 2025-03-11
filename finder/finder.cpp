// finder.cpp
// author: mohamed.saleh2@snhu.edu
// date: 03/03/2025

#include "finder.hpp"
using namespace ns_finder;

/// @brief Finder Constructor
/// @param root
Finder::Finder()
{
}

/// @brief Printout Duplicate file stats
void Finder::printout_stat()
{
    cout << "Total files : " << total_files() << endl;
    cout << "Total file size : " << bytesToSize(total_files_size()) << endl;
    cout << "Total Duplicate files : " << total_duplicate_files_count() << endl;
    cout << "Total Duplicate files size : " << bytesToSize(total_duplicate_files_size()) << endl;
}

/// @brief Action(s) to perform before finder kickoff.
void Finder::pre_search()
{
    cout << "Please wait...working on your request." << endl;
}

/// @brief Action(s) to perform after finder finish work.
void Finder::post_search()
{
    printout_stat();
    export_duplicate_files();
    delete_duplicate_files();
}

/// @brief Get total number of processed files
/// @return
int Finder::total_files()
{
    return this->_files.size();
}

/// @brief Get total number of duplicate files
/// @return
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

/// @brief Total processed files sizes in bytes.
/// @return
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

/// @brief Total duplicate files sizes in bytes.
/// @return
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

/// @brief Delete Duplicate Files
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

/// @brief Shorten File Name
/// @param fileNameWOExt give file name without extension
/// @return new file name
string Finder::shorten_file_name(string fileNameWOExt)
{
    if (fileNameWOExt.length() > 25)
    {
        return fileNameWOExt.substr(0, 22).append("...");
    }
    return fileNameWOExt;
}

/// @brief Start Processing
/// @param root
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

    if (DEBUG_MODE)
    {
        // delete hashing stat
        if (fs::exists("hashing_stat.txt"))
            fs::remove("hashing_stat.txt");

        ofstream hashing_stat_file("hashing_stat.txt");
        hashing_stat_file.close();
    }

    for (const auto &f : _files)
    {
        string filePath = f.generic_string();

        auto start = std::chrono::high_resolution_clock::now();
        hash_result hashResult = calculate_xxhash(filePath);
        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        unsigned long long file_siz = std::filesystem::file_size(filePath);

        if (DEBUG_MODE)
        {
            ofstream hashing_stat_file("hashing_stat.txt", ios::app);
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            hashing_stat_file << "Time taken ::" << milliseconds.count() << " ms, " << seconds.count() << " sec "
                              << " file ::" << f.filename().string()
                              << " size ::" << bytesToSize(file_siz) << endl;
            hashing_stat_file.close();
        }

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
        }
        else
        {
            cout << "Working on " << f.filename().string() << endl;
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            if (DEBUG_MODE)
            {
                cout << "Processing Time is " << seconds.count() << " seconds for file size " << bytesToSize(file_siz) << endl;
                cout << endl;
            }

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
                _files.push_back(path);
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

/// @brief Present bytes in readable format.
/// @param bytes
/// @return
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

/// @brief Export duplicate files to text file.
void Finder::export_duplicate_files()
{
    bool bfetchInput = true;
    string strAnswer = "";

    while (bfetchInput)
    {
        cout << "Would you like to export duplicate files? (yes/no)" << endl;
        cin >> strAnswer;

        std::transform(strAnswer.begin(), strAnswer.end(), strAnswer.begin(), ::tolower);

        if (strAnswer == "yes" || strAnswer == "no")
        {
            if (strAnswer == "yes")
            {
                string fiveTabs = "\t\t\t\t\t";
                // Write to a file
                std::ofstream outFile("output.txt");
                if (outFile.is_open())
                {
                    map<string, vector<fs::path>>::iterator it = _findings.begin();
                    outFile << "File Name" + fiveTabs + "Status " << endl;
                    while (it != _findings.end())
                    {
                        vector<fs::path> files = it->second;

                        if (files.size() > 1)
                        {
                            outFile << shorten_file_name(files[0].filename().string()) + fiveTabs + to_string(files.size()) + " Duplicates" << endl;
                        }
                        else
                        {
                            outFile << shorten_file_name(files[0].filename().string()) + fiveTabs + "No Duplicates" << endl;
                        }
                        it++;
                    }

                    outFile.close();
                }
                else
                {
                    cout << "Failed to create file." << endl;
                }

                cout << "Please check output.txt" << endl;
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