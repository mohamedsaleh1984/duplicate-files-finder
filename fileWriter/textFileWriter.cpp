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

class TextFileWriter : public FileWriter
{
public:
    void WriteDuplicate(map<string, vector<fs::path>> _findings)
    {

        // Write to text file
        std::ofstream outFile("output.txt");

        if (outFile.is_open())
        {
            map<string, vector<fs::path>>::iterator it = _findings.begin();
            outFile << std::setw(30) << std::left << "File Name" << setw(10) << "Status " << endl;

            int counter = 0;
            while (it != _findings.end())
            {
                vector<fs::path> files = it->second;
                if (files.size() > 1)
                {
                    counter++;
                    outFile << to_string(counter) << ") " << std::setw(30) << std::left << Utilities::shorten_file_name(files[0].filename().string()) << setw(10) << std::left << to_string(files.size() - 1) + " Duplicates" << endl;
                    outFile << " -" << Utilities::shorten_file_name(files[0].filename().string()) << setw(10) << std::left << "Located at:" << files[0].generic_string() << endl;
                    for (int i = 1; i < files.size(); i++)
                    {
                        outFile << " --" << files[i].generic_string() << endl;
                    }
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
    }
};