#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>

void overwriteAndDeleteFile(const std::string& filePath) {
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) != 0) {
        std::cerr << "file doesnt exist" << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    int fd = open(filePath.c_str(), O_WRONLY);
    if (fd == -1) {
        std::cerr << "cant open file" << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    off_t fileSize = fileStat.st_size;
    char buffer[4096] = { '\0' };
    for (off_t i = 0; i < fileSize; i += sizeof(buffer)) {
        size_t writeSize = std::min(static_cast<off_t>(sizeof(buffer)), fileSize - i);
        if (write(fd, buffer, writeSize) != static_cast<ssize_t>(writeSize)) {
            std::cerr << "failed to write" << strerror(errno) << std::endl;
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    close(fd);

    if (unlink(filePath.c_str()) != 0) {
        std::cerr << "failed to delette" << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "erased" << filePath << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "./hacker-rm <file_to_erase>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filePath = argv[1];
    overwriteAndDeleteFile(filePath);

    return EXIT_SUCCESS;
}