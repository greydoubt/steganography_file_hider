#include <iostream>
#include <fstream>
#include <cstring>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int HEADER_SIZE = 32;
const int MAX_MESSAGE_SIZE = 16777216; // 16 MB

void writeHeader(Mat& image, int fileSize) {
    // Write the header information into the image
    int rows = image.rows;
    int cols = image.cols;

    // Write the size of the file into the first 32 pixels of the first row
    int* fileSizePtr = reinterpret_cast<int*>(image.ptr(0));
    *fileSizePtr = fileSize;

    // Write the size of the header into the next 32 pixels
    int* headerSizePtr = reinterpret_cast<int*>(image.ptr(0) + HEADER_SIZE);
    *headerSizePtr = HEADER_SIZE;

    // Write the size of the image into the next 32 pixels
    int* imageSizePtr = reinterpret_cast<int*>(image.ptr(0) + HEADER_SIZE * 2);
    *imageSizePtr = rows * cols * image.channels();
}

void embedFile(Mat& image, const char* filename) {
    // Open the file to be embedded
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: Failed to open file " << filename << endl;
        exit(1);
    }

    // Get the size of the file
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Check if the file can fit into the image
    int imageSize = image.rows * image.cols * image.channels();
    if (fileSize + HEADER_SIZE > imageSize) {
        cerr << "Error: File is too big to embed into image." << endl;
        exit(1);
    }

    // Write the header information into the image
    writeHeader(image, fileSize);

    // Embed the file data into the image
    uchar* imageDataPtr = image.ptr(0) + HEADER_SIZE * 3;
    uchar byte;
    for (int i = 0; i < fileSize; i++) {
        file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        for (int j = 0; j < 8; j++) {
            if (byte & (1 << j)) {
                // Set the least significant bit to 1
                *imageDataPtr |= 1;
            } else {
                // Set the least significant bit to 0
                *imageDataPtr &= ~1;
            }
            imageDataPtr++;
        }
    }
}

void extractFile(Mat& image, const char* filename) {
    // Read the header information from the image
    int* fileSizePtr = reinterpret_cast<int*>(image.ptr(0));
    int fileSize = *fileSizePtr;
    int* headerSizePtr = reinterpret_cast<int*>(image.ptr(0) + HEADER_SIZE);
    int headerSize = *headerSizePtr;

    // Extract the file data from the image
    ofstream file(filename, ios::binary);
    uchar* imageDataPtr = image.ptr(0) + HEADER_SIZE * 3;
    uchar byte = 0;
    for (int i = 0; i < fileSize; i++) {
        for (int j = 0; j < 8; j++) {
            byte |= (*imageDataPtr & 1) << j;
            imageDataPtr++;
        }
        file.write(reinterpret_cast<char*>(&byte), sizeof(byte));
}
}

int main() {
// Load the image
Mat image = imread("image.jpg", IMREAD_UNCHANGED);
if (image.empty()) {
    cerr << "Error: Failed to load image." << endl;
return 1;
}

// Embed the file into the image
embedFile(image, "file.bin");

// Save the modified image
imwrite("image_embedded.jpg", image);

// Extract the file from the image
Mat embeddedImage = imread("image_embedded.jpg", IMREAD_UNCHANGED);
extractFile(embeddedImage, "file_extracted.bin");

return 0;
}



