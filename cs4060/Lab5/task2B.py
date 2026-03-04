import matplotlib.pyplot as plt
import numpy as np
import os
import cv2
from collections import defaultdict

if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/lena.tif"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

  assert img is not None
  
  unnormalized = img.flatten()
  
  counts = defaultdict(float)
  for e in unnormalized:
    counts[e] += 1
  
  pixelCount = len(unnormalized)
  for e in counts:
    counts[e] /= pixelCount
    
  normalized = []
  for _ in range(0, 256):
    normalized.append(0)
  
  for e in counts:
    normalized[e] = counts[e]
    
  cum_sum = []
  for _ in range(0, 256):
    cum_sum.append(0)
  
  cum_sum[0] = normalized[0]
  for i in range(1, 256):
    cum_sum[i] = cum_sum[i - 1] + normalized[i]
    
  lut = dict()
  for i, e in enumerate(cum_sum):
    lut[i] = e * 255
  
  equalized_img = img.copy()
  for i in range(len(img)):
    for j in range(len(img[0])):
      equalized_img[i][j] = round(lut[img[i][j]])
  
  fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2) 

  ax1.imshow(img, cmap="gray")
  ax1.set_title("Normal Image")
  ax2.hist(unnormalized)
  
  ax3.imshow(equalized_img, cmap="gray")
  ax3.set_title("Equalized Image")
  ax4.hist(equalized_img.flatten())

  plt.show()
  
