import matplotlib.pyplot as plt
import numpy as np
import os
import cv2


if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/boy.jpg"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

  assert img is not None
  
  fig, (ax1, ax2) = plt.subplots(1, 2) 
  
  bit_img = (img & 0b10000000) | (img & 0b0100000) | (img & 0b00100000)
  
  ax1.imshow(img, cmap='gray')
  ax1.set_title("Original")
  ax2.set_title("Recovered")
  ax2.imshow(bit_img, cmap='gray')
  
  plt.show()
