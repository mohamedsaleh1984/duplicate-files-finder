# Duplicate Files Finder
Cross platform tool to find duplicate files based on file hash using fast hashing algorithm xxhash.

# Main function
- Read give directory and fetch all files in sub-directories as well and hash map them via hash code

build : build source code and generate and link libs binaries to executables 
```
make build
```

clean : remove all executables and libs for clean re-build 
```
make clean
```

run : clean, build and run binary file 
```
make run
```

test : run test cases using catch library
```
make test
```

# Next Step
- Add Parameters 
    - Delete files without asking user.
    - Show duplicate files.
    - Resume option to avoid start over and lose previous processed files.
    - provide Output file as parameter to delete duplicate files.
    - Add note for the user to warn about altering the file


# Notes
- create new struct search result retaining search results.
    - Needs to serialize findings, files
    - store the last processed hash
    - write them in binary
- use system pause to ask user if they want to retain search result
- add another parameter to read last search result
- need to come up with faster hashing for big files 
    - (Read first and last 100 MB concat both hashes as a new key) size >= 500 MB && size <= 1 GB
    - (Read first and last 300 MB concat both hashes as a new key) size > 1 GB
    -  create new temp file out of the big files and generate hash for it.

    