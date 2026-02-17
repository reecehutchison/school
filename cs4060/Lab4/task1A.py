import cv2
import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
  img_path = os.path.dirname(os.path.abspath(__file__)) + "/lena.tif"
  img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
  
  assert img is not None
  
  negative = 255 - img
  
  fig, (ax1, ax2) = plt.subplots(1, 2)
  
  ax1.imshow(img, cmap='gray')
  ax1.set_title("Original")
  ax2.set_title("Negative")
  ax2.imshow(negative, cmap='gray')
  plt.show()