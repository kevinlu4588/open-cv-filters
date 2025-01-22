import cv2
from filters import apply_sepia, apply_vignette, custom_greyscale, blur5x5, blur5x5_separable

def main():
    # Open the video capture (camera)
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("Unable to open video device")
        return

    # Get properties of the video capture
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    print(f"Expected size: {width} x {height}")

    # Create a window for displaying video
    cv2.namedWindow("Video", cv2.WINDOW_AUTOSIZE)

    # Initialize mode (color by default)
    display_mode = "color"

    while True:
        # Capture a frame from the camera
        ret, frame = cap.read()
        if not ret:
            print("Frame capture failed or stream ended.")
            break

        # Apply transformations based on display mode
        if display_mode == "sepia":
            frame = apply_sepia(frame)
        elif display_mode == "vignette":
            frame = apply_vignette(apply_sepia(frame))
        elif display_mode == "gray_scale":
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        elif display_mode == "custom_gray_scale":
            frame = custom_greyscale(frame)
        elif display_mode == "blur":
            frame = blur5x5_separable(frame)
        # Display the frame in the window
        cv2.imshow("Video", frame)

        # Wait for a keypress for 10ms
        key = cv2.waitKey(10) & 0xFF  # Mask to handle 64-bit systems

        if key == ord('q'):  # Quit on 'q'
            print("Quitting...")
            break
        elif key == ord('s'):  # Sepia filter on 's'
            display_mode = "sepia"
            print("Switched to Sepia mode.")
        elif key == ord('v'):  # Vignette effect on 'v'
            display_mode = "vignette"
            print("Switched to Vignette mode.")
        elif key == ord('g'):
            display_mode = "gray_scale"
        elif key == ord('h'):
            display_mode = "custom_gray_scale"
        elif key == ord('b'):
            display_mode = "blur"
        elif key != 255:  # Switch back to color for any other key (excluding no keypress)
            display_mode = "color"
            print("Switched to Color mode.")

    # Release resources
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
