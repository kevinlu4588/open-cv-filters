import cv2
import time
from filters import blur5x5_separable

def main():
    # Load a sample image
    src = cv2.imread("/Users/KevinLu/open-cv-filters-1/Screenshot 2025-01-21 at 2.25.18 PM.png")
    if src is None:
        print("Error loading image.")
        return

    # Measure the time taken by the blur function
    start_time = time.time()
    blurred_image = blur5x5_separable(src)
    end_time = time.time()

    print(f"Execution time: {end_time - start_time:.6f} seconds")

    # Display the original and blurred images
    cv2.imshow("Original", src)
    cv2.imshow("Blurred", blurred_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
