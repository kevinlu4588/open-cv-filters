import cv2 
import numpy as np

def custom_greyscale(src):
    """
    Custom grayscale transformation using weighted contributions of color channels.

    Args:
        src (np.ndarray): The source image in BGR format.
    
    Returns:
        np.ndarray: The transformed grayscale image in 3 channels.
    """
    # Split channels
    b, g, r = cv2.split(src)
    
    # Calculate grayscale intensities using weighted sum
    bgr_average = (b * 0.2 + g * 0.5 + r * 0.4)

    gray = np.clip(255 - bgr_average, 0, 255)

    # Convert the single-channel grayscale to a 3-channel grayscale image
    dst = cv2.merge([gray, gray, gray])
    
    return dst.astype(np.uint8)



def apply_sepia(src):
    """
    Applies a sepia tone filter to an image.
    
    Args:
        src (np.ndarray): The source image in BGR format.
    
    Returns:
        np.ndarray: The image with the sepia tone applied.
    """
    # Define the sepia transformation matrix
    sepia_matrix = np.array([[0.272, 0.534, 0.131],
                             [0.349, 0.686, 0.168],
                             [0.393, 0.769, 0.189]])
    
    # Apply the sepia matrix transformation
    sepia_image = cv2.transform(src, sepia_matrix)
    
    # Ensure pixel values are within the valid range [0, 255]
    sepia_image = np.clip(sepia_image, 0, 255).astype(np.uint8)
    
    return sepia_image


def apply_vignette(src, intensity=0.5):
    """
    Applies a vignette effect to an image.
    
    Args:
        src (np.ndarray): The source image in BGR format.
        intensity (float): Intensity of the vignette effect (0 to 1).
    
    Returns:
        np.ndarray: The image with the vignette effect applied.
    """
    rows, cols = src.shape[:2]
    
    # Create Gaussian kernels for x and y axes
    kernel_x = cv2.getGaussianKernel(cols, cols * intensity)
    kernel_y = cv2.getGaussianKernel(rows, rows * intensity)
    
    # Create the 2D vignette mask by multiplying the kernels
    vignette_mask = kernel_y @ kernel_x.T
    
    # Normalize the vignette mask to range [0, 1]
    vignette_mask = vignette_mask / vignette_mask.max()
    
    # Apply the vignette effect to each channel
    output = np.zeros_like(src)
    for i in range(3):  # Loop over B, G, R channels
        output[:, :, i] = src[:, :, i] * vignette_mask
    
    return output.astype(np.uint8)



def blur5x5(src):
    """
    Applies a 5x5 Gaussian blur filter to the image.
    
    Args:
        src (np.ndarray): The source image in BGR format.
    
    Returns:
        np.ndarray: The blurred image with the same size as the source image.
    """
    # Gaussian kernel (5x5)
    kernel = np.array([
        [1, 2, 4, 2, 1],
        [2, 4, 8, 4, 2],
        [4, 8, 16, 8, 4],
        [2, 4, 8, 4, 2],
        [1, 2, 4, 2, 1]
    ])
    kernel = kernel / np.sum(kernel)  # Normalize the kernel

    # Create a copy of the source image to store the blurred result
    dst = np.copy(src)

    # Get the image dimensions
    rows, cols, channels = src.shape

    # Apply the filter (skip the first two and last two rows/columns)
    for i in range(2, rows - 2):
        for j in range(2, cols - 2):
            for c in range(channels):  # Process each color channel separately
                # Extract a 5x5 region around the current pixel
                region = src[i - 2:i + 3, j - 2:j + 3, c]
                # Apply the Gaussian kernel to the region
                dst[i, j, c] = np.sum(region * kernel)

    return dst.astype(np.uint8)


def blur5x5_separable(src):
    """
    Applies a faster 5x5 Gaussian blur filter using separable horizontal and vertical filters.
    
    Args:
        src (np.ndarray): The source image in BGR format.
    
    Returns:
        np.ndarray: The blurred image with the same size as the source image.
    """
    # Define the 1x5 Gaussian kernel
    kernel = np.array([1, 2, 4, 2, 1], dtype=np.float32)
    kernel = kernel / kernel.sum()  # Normalize the kernel

    # Create a copy of the source image to store the intermediate and final results
    intermediate = np.zeros_like(src, dtype=np.float32)  # Temporary buffer
    dst = np.zeros_like(src, dtype=np.float32)

    # Image dimensions
    rows, cols, channels = src.shape

    # Apply the horizontal filter
    for i in range(rows):
        for j in range(2, cols - 2):  # Skip the first and last two columns
            for c in range(channels):
                intermediate[i, j, c] = np.dot(kernel, src[i, j - 2:j + 3, c])  # 1x5 horizontal filter

    # Apply the vertical filter
    for i in range(2, rows - 2):  # Skip the first and last two rows
        for j in range(cols):
            for c in range(channels):
                dst[i, j, c] = np.dot(kernel, intermediate[i - 2:i + 3, j, c])  # 5x1 vertical filter

    # Clip the values to [0, 255] and return as uint8
    return np.clip(dst, 0, 255).astype(np.uint8)