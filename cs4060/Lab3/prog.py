import cv2
import os
import matplotlib.pyplot as plt



if __name__ == "__main__":
    img = cv2.imread('travelbook.png')

    assert img is not None

    qr_detector = cv2.QRCodeDetector()
    decoded_text, points, _ = qr_detector.detectAndDecode(img) 
        
    if points is not None:
        pts = points[0].astype(int)
        cv2.line(img, tuple(pts[0]), tuple(pts[1]), (255, 0, 0), 3)
        cv2.line(img, tuple(pts[1]), tuple(pts[2]), (255, 0, 0), 3)
        cv2.line(img, tuple(pts[2]), tuple(pts[3]), (255, 0, 0), 3)
        cv2.line(img, tuple(pts[3]), tuple(pts[0]), (255, 0, 0), 3)
        print(f'->{decoded_text}<-')
    else:
        print("No QR Code detected")
    
    # cv2.imwrite('QRCode-output.png', img)

    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    plt.show()