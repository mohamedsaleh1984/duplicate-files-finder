# Duplicate Files Finder
Cross platform tool to find duplicate files based on file hash using fast hashing algorithm xxhash.

# Dependencies
- C++17

# Main function
- Read give directory and fetch all files in sub-directories as well and hash map them via hash code

# License
This software is proprietary. All rights reserved.  
Unauthorized copying, modification, or distribution is strictly prohibited.  
For licensing inquiries, please contact mohamedsaleh1984@hotmail.com.

### build : build source code and generate and link libs binaries to executables 
```
make build
```

### clean : remove all executables and libs for clean re-build 
```
make clean
```

### run : clean, build and run binary file 
```
make run
```

### test : run test cases using catch library
```
make test
```

# Change Log
| Description  | Date |
| ------------- | ------------- |
|Fixed hashing big files > 500mb|03/12/2025|
|Abstracted hashing big files function|03/12/2025|
|create new struct search result retaining search results.|03/11/2025|
|Needs to serialize findings, files|03/11/2025|
|store the last processed index|03/11/2025|
|write them in binary|03/11/2025|
|need to come up with faster hashing for big files --> DONE|03/11/2025|
|(Read first and last 100 MB concat both hashes as a new key) size >= 500 MB && size <= 1 GB --> DONE|03/11/2025|
|(Read first and last 300 MB concat both hashes as a new key) size > 1 GB --> DONE|03/11/2025|
|create new temp file out of the big files and generate hash for it. --> DONE  | 03/11/2025|

# Next Step
- Add Parameters 
    - Delete files without asking user.
    - Show duplicate files.
    - Resume option to avoid start over and lose previous processed files.
    - provide Output file as parameter to delete duplicate files.
    - Add note for the user to warn about altering the file
    - add another parameter to read last search result
- Enhancement
    - Add a flag in output file to make which file to delete
    - Parse output file
    - Construct search duplicate file structure
    - All files should be in MD format not text format for better parsing.
    - Need to add gitmodule to keep things up to date with maddy (MD Parser lib)
    - Use MD tables to mark desired files to delelete instead of text files.   

# Notes

- use system pause to ask user if they want to retain search result

# Commit type abbreviation
- t: add/remove/modify typo
- c: add/remove/modify comments/readme
- r: refactor code for better readability/maintenance
- f: fix a bug/change ds
- wip: add/remove/modify code
