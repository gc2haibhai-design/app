#include "screenshot.h"
#include "lodepng.h"
#include <GLES3/gl3.h>
#include <vector>
#include <cstring>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <sys/stat.h>
#include <unistd.h>

// Get package name from /proc/self/cmdline (NDK-only)
std::string GetPackageName() {
    char buffer[256] = {0};
    FILE* fp = fopen("/proc/self/cmdline", "r");
    if (fp) {
        fread(buffer, sizeof(char), sizeof(buffer) - 1, fp);
        fclose(fp);
        return std::string(buffer);
    }
    return "";
}

// Screenshot function
std::string TakeScreenshot(int width, int height) {
    // Read pixels from GL
    std::vector<unsigned char> pixels(width * height * 4);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    // Flip image vertically
    std::vector<unsigned char> flipped(width * height * 4);
    for (int y = 0; y < height; ++y) {
        memcpy(
            &flipped[y * width * 4],
            &pixels[(height - 1 - y) * width * 4],
            width * 4
        );
    }

    // Get time
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    localtime_r(&now, &tstruct);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);

    // Get package name
    std::string packageName = GetPackageName();
    if (packageName.empty()) {
        printf("Failed to detect package name.\n");
        return "";
    }

    // Build file path
    std::ostringstream pathStream;
    pathStream << "/data/data/" << packageName << "/files/";
    std::string basePath = pathStream.str();
    std::ostringstream fileStream;
    fileStream << basePath << "screenshot_" << buf << ".png";
    std::string filePath = fileStream.str();

    // Encode image
    std::vector<unsigned char> png;
    unsigned error = lodepng::encode(png, flipped, width, height);
    if (!error) {
        std::ofstream file(filePath, std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<const char*>(png.data()), png.size());
        file.close();
        printf("Saved to: %s\n", filePath.c_str());
        return filePath;
    } else {
        printf("LodePNG error: %s\n", lodepng_error_text(error));
        return "";
    }
}
