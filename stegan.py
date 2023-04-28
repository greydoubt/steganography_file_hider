import cv2
import numpy as np

HEADER_SIZE = 32
MAX_MESSAGE_SIZE = 16777216 # 16 MB

def write_header(image, file_size):
    # Write the header information into the image
    rows, cols, channels = image.shape

    # Write the size of the file into the first 32 pixels of the first row
    file_size_ptr = np.array([file_size], dtype=np.int32)
    image[0, :HEADER_SIZE] = np.unpackbits(file_size_ptr.view(dtype=np.uint8))

    # Write the size of the header into the next 32 pixels
    header_size_ptr = np.array([HEADER_SIZE], dtype=np.int32)
    image[0, HEADER_SIZE:HEADER_SIZE*2] = np.unpackbits(header_size_ptr.view(dtype=np.uint8))

    # Write the size of the image into the next 32 pixels
    image_size_ptr = np.array([rows * cols * channels], dtype=np.int32)
    image[0, HEADER_SIZE*2:HEADER_SIZE*3] = np.unpackbits(image_size_ptr.view(dtype=np.uint8))

def embed_file(image, filename):
    # Open the file to be embedded
    with open(filename, "rb") as file:
        file_data = file.read()

    # Get the size of the file
    file_size = len(file_data)

    # Check if the file can fit into the image
    rows, cols, channels = image.shape
    image_size = rows * cols * channels
    if file_size + HEADER_SIZE > image_size:
        print("Error: File is too big to embed into image.")
        return

    # Write the header information into the image
    write_header(image, file_size)

    # Embed the file data into the image
    image_data_ptr = image.flatten()[HEADER_SIZE*3:]
    for byte in file_data:
        for bit in range(8):
            if byte & (1 << bit):
                # Set the least significant bit to 1
                image_data_ptr[0] |= 1
            else:
                # Set the least significant bit to 0
                image_data_ptr[0] &= ~1
            image_data_ptr = image_data_ptr[1:]

def extract_file(image, filename):
    # Read the header information from the image
    file_size_ptr = np.unpackbits(image[0, :HEADER_SIZE]).view(dtype=np.int32)
    file_size = file_size_ptr[0]
    header_size_ptr = np.unpackbits(image[0, HEADER_SIZE:HEADER_SIZE*2]).view(dtype=np.int32)
    header_size = header_size_ptr[0]

    # Extract the file data from the image
    file_data = bytearray()
    image_data_ptr = image.flatten()[HEADER_SIZE*3:]
    for i in range(file_size):
        byte = 0
        for j in range(8):
            if image_data_ptr[0] & 1:
                byte |= (1 << j)
            image_data_ptr = image_data_ptr[1:]
        file_data.append(byte)

    # Write the extracted file data to disk
    with open(filename, "wb") as file:
        file.write(file_data)

if __name__ == "__main__":
    # Load the image
    image = cv2.imread("image.jpg", cv2.IMREAD_UNCHANGED)
    if image is None:
        print("Error: Failed to load image.")
        exit(1)

    # Embed the file into the image
    embed_file(image, "file.bin")

    # Save the modified image
    cv2.imwrite("image_embedded.jpg", image)

    # Extract the file
    # Load the embedded image
    image_embedded = cv2.imread("image_embedded.jpg", cv2.IMREAD_UNCHANGED)
    if image_embedded is None:
        print("Error: Failed to load embedded image.")
        exit(1)
    
    # Extract the file from the image
    extract_file(image_embedded, "file_extracted.bin")
    
    print("Done.")  