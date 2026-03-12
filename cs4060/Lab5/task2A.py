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
  
  fig, (ax1, ax2, ax3,) = plt.subplots(1, 3) 

  ax1.hist(unnormalized, bins=256)
  ax1.set_title("UnNormalized")
  ax2.set_title("Normalized")
  ax2.bar(range(256), normalized, width=1)
  ax3.bar(range(256), cum_sum, width=1)
  ax3.set_title("Cum Sum")

  plt.show()
  
