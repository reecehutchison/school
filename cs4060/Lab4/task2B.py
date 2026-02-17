# the log transformation just made lena look a lot brighter, it appears to be 
# distorting the image rather then helping it. for an image like lena, it 
# doesn't really make sense because the pixel values are already in a normal
# range so there isn't really a benefit. 

import cv2
import matplotlib.pyplot as plt
import numpy as np
import os

if __name__ == "__main__":
  dir = os.path.dirname(os.path.abspath(__file__))
  img = cv2.imread(dir + "/lena.tif", cv2.IMREAD_GRAYSCALE)
  assert img is not None

  log_img = np.log1p(img.astype(np.float64))
  normalized = np.uint8((log_img / log_img.max()) * 255)

  fig, (ax1, ax2) = plt.subplots(1, 2)

  ax1.imshow(img, cmap='gray')
  ax1.set_title("original")

  ax2.imshow(normalized, cmap='gray')
  ax2.set_title("post log")

  plt.show()
