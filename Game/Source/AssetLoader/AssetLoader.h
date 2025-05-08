#pragma once

#include "Dependancies/libs.h"

class AssetLoader {
public:
    AssetLoader() {}
    ~AssetLoader() {}

    GLuint loadBMP_custom(const char* imagepath);
    
private:
};