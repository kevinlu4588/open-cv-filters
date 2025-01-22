import cv2

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
    is_grayscale = False

    while True:
        # Capture a frame from the camera
        ret, frame = cap.read()
        if not ret:
            print("Frame capture failed or stream ended.")
            break

        # Convert frame to grayscale if 'g' was pressed
        if is_grayscale:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Display the frame in the window
        cv2.imshow("Video", frame)

        # Wait for a keypress for 10ms
        key = cv2.waitKey(10) & 0xFF  # Mask to handle 64-bit systems

        if key == ord('q'):  # Quit on 'q'
            print("Quitting...")
            break
        elif key == ord('g'):  # Switch to grayscale on 'g'
            is_grayscale = True
            print("Switched to grayscale mode.")
        elif key != 255:  # Switch back to color for any other key (excluding no keypress)
            is_grayscale = False
            print("Switched to color mode.")

    # Release resources
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
