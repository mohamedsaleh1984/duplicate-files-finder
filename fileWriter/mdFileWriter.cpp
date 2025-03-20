/*
    Copyright © 2025 Mohamed Saleh. All Rights Reserved.

    This software and its source code are the exclusive property of Mohamed Saleh.
    Unauthorized copying, modification, distribution, or use of this software,
    in whole or in part, is strictly prohibited.

    For licensing inquiries, please contact mohamedsaleh1984@hotmail.com.

*/

#include "fileWriter.h"
#include "../utils/Utilities.h"

using namespace ns_finder;

class MdFileWriter : public FileWriter
{
public:
    void WriteDuplicate(map<string, vector<fs::path>> _findings)
    {
        // Write to text file
        std::ofstream outFile("output.md");
        if (outFile.is_open())
        {
            map<string, vector<fs::path>>::iterator it = _findings.begin();
            outFile << "| File Name | Status | Delete Marker |" << endl;
            outFile << "| --------- | ------ | ------------- |" << endl;
            int counter = 0;
            while (it != _findings.end())
            {
                vector<fs::path> files = it->second;
                if (files.size() > 1)
                {
                    counter++;
                    outFile << "|" << Utilities::shorten_file_name(files[0].filename().string()) << "|" << to_string(files.size() - 1) + " Duplicates" << "| |" << endl;
                    outFile << "|" << Utilities::shorten_file_name(files[0].filename().string()) << "|" << files[0].generic_string() << "| |" << endl;
                    for (int i = 1; i < files.size(); i++)
                    {
                        outFile << "| | " << files[i].generic_string() << "| |" << endl;
                    }
                }

                it++;
            }

            outFile << endl;
            outFile << "#### mark desired files with x to delete them." << endl;

            outFile.close();
            cout << "Please check output.md" << endl;
        }
        else
        {
            cout << "Failed to create file." << endl;
        }
    }
};