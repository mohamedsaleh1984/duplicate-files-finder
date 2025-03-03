# Duplicate Files Finder
Find Duplicate Files in specific directory based on file hash

Install
- Perl
- nasm
- make

Add both binary path to environment PATH

Follow Openssl Install Instructions
[OpenSSL](https://github.com/openssl/openssl/tree/openssl-3.4)

* Should find OpenSSL in Program Files for windows

| Dir | Content   
| :---:   | :---: 
| bin | binaries
| include | headers for OpenSSL
| html | documentation
| lib | link library dir

* OpenSSL for Linux
```
sudo apt-get install libssl-dev
```

* for VSCode add dir .vscode and create new file ```c_cpp_properties.json```

```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/Program Files (x86)/OpenSSL/include/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.22621.0",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-msvc-x64"
        }
    ],
    "version": 4
}
```
#### Installing xxhash for linux env
```
sudo apt install xxhash

sudo add-apt-repository ppa:reviczky/xxhash

sudo apt remove --autoremove xxhash

sudo add-apt-repository --remove ppa:reviczky/xxhash

```


build
```
make build
```

run
```
make run
```

test

```
make test
```

clean
```
make clean
```
