#ifndef PATH_H
#define PATH_H

#include <string>

class Path {
private:
    inline static std::string basePath = "../Files/";

public:
    static std::string get();
};

#endif // PATH_H