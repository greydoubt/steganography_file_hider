# steganography_file_hider

This application allows you to embed a binary or text file into an image file using the least significant bit of each pixel. The embedded file can be extracted from the modified image file.
Requirements

    OpenCV 4.0 or later
    Python 3.6 or later

Usage

To embed a file into an image, run the following command:

python embed.py image_file file_to_embed

This will create a modified image file with the embedded data.

To extract a file from the modified image, run the following command:

python extract.py embedded_image_file extracted_file

This will extract the embedded file and save it to a new file.

**Limitations**

The maximum file size that can be embedded depends on the size of the image. The application checks if the file can fit into the image before embedding it. If the file is too big to embed, an error message will be displayed.


**Example**

Here's an example of how to use the application:

    Create an image file called image.jpg.

    Create a binary file called file.bin.

    Run the following command to embed the binary file into the image:

*python embed.py image.jpg file.bin*

This will create a new image file called image_embedded.jpg with the embedded data.

Run the following command to extract the binary file from the modified image:

*python extract.py image_embedded.jpg file_extracted.bin*

This will extract the binary file and save it to a new file called file_extracted.bin.


C++ version of the steganography application:
Steganography Application

This application allows you to embed a binary or text file into an image file using the least significant bit of each pixel. The embedded file can be extracted from the modified image file.
Requirements

    OpenCV 4.0 or later
    C++17 or later
    CMake 3.10 or later

Usage
Python Version

To embed a file into an image using the Python version, run the following command:

*python embed.py image_file file_to_embed*

This will create a modified image file with the embedded data.

To extract a file from the modified image using the Python version, run the following command:

*python extract.py embedded_image_file extracted_file*

This will extract the embedded file and save it to a new file.
C++ Version

To build the C++ version of the steganography application, follow these steps:

    Clone the repository:

*clone https://github.com/username/steganography.git*

Create a build directory and navigate into it:

*mkdir build && cd build

Generate the Makefile using CMake:

*cmake ..*

Build the application using Make:

*make*

To embed a file into an image using the C++ version, run the following command:

*./embed image_file file_to_embed*

This will create a modified image file with the embedded data.

To extract a file from the modified image using the C++ version, run the following command:

*./extract embedded_image_file extracted_file*

This will extract the embedded file and save it to a new file.

**Limitations**

The maximum file size that can be embedded depends on the size of the image. The application checks if the file can fit into the image before embedding it. If the file is too big to embed, an error message will be displayed.
Example

Here's an example of how to use the application:

    Create an image file called image.jpg.

    Create a binary file called file.bin.

    Run the following command to embed the binary file into the image using the Python version:

*python embed.py image.jpg file.bin*

This will create a new image file called image_embedded.jpg with the embedded data.

Run the following command to extract the binary file from the modified image using the Python version:

*python extract.py image_embedded.jpg file_extracted.bin*

This will extract the binary file and save it to a new file called file_extracted.bin.

Build the C++ version of the application and repeat steps 3 and 4 to verify that the C++ version produces the same results.
