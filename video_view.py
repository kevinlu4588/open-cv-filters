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

    while True:
        # Capture a frame from the camera
        ret, frame = cap.read()
        if not ret:
            print("Frame capture failed or stream ended.")
            break

        # Display the frame in the window
        cv2.imshow("Video", frame)

        # Wait for a keypress for 10ms
        key = cv2.waitKey(10) & 0xFF  # Mask to handle 64-bit systems

        if key == ord('q'):  # Quit on 'q'
            print("Quitting...")
            break
        elif key == ord('s'):  # Save the frame on 's'
            save_path = "captured_frame.jpg"
            cv2.imwrite(save_path, frame)
            print(f"Frame saved as {save_path}")

    # Release resources
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
