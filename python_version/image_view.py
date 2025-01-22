import cv2

def main():
    # Read an image file
    image_path = "/Users/KevinLu/open-cv-filters-1/python_version/Screenshot 2025-01-21 at 2.25.18 PM.png"  # Replace with your image file path
    image = cv2.imread(image_path)
    
    if image is None:
        print("Error: Unable to load image.")
        return
    
    # Display the image in a window
    cv2.imshow("Image Viewer", image)
    
    print("Press 'q' to quit the program.")
    
    while True:
        # Wait for a key press (10 ms delay)
        key = cv2.waitKey(10) & 0xFF  # Mask to handle 64-bit machines
        
        if key == ord('q'):  # Quit on 'q'
            print("Quitting program.")
            break
        elif key == ord('s'):  # Example: Save image when 's' is pressed
            save_path = "saved_image.jpg"
            cv2.imwrite(save_path, image)
            print(f"Image saved to {save_path}.")
    
    # Close all OpenCV windows
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
