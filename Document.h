// document.h
// model
#include <string>
#include <vector>

class Image {}; // Placeholder for image class

class Document {
public:
    std::string text;
    std::vector<Image> images;
    void load(const std::string &filePath);
    void save(const std::string &filePath);
    void addImage(const Image &image);
    std::string getText() const;
};
