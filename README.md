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

#### Next Step
- Add Parameters 
    - Delete files without asking user.
    - Show duplicate files.
    - Resume option to avoid start over and lose previous processed files.
    - provide Output file as parameter to delete duplicate files.
    