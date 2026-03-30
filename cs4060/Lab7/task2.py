import matplotlib.pyplot as plt
import numpy as np
import os
import cv2
from collections import defaultdict

if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/dog.jpeg"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
  
  assert img is not None
  
  gauss_img = cv2.GaussianBlur(img, (5, 5), sigmaX=3)
  box_img = cv2.boxFilter(img, -1, (5, 5))

  counts = defaultdict(int)

  for x in range(len(gauss_img)):
    for y in range(len(gauss_img[0])):
      counts[(gauss_img[x][y] // 4)] += 1

  roi = [0]
  max_count = counts[0]
  for key, value in counts.items():
    if value > max_count:
      roi = [key]
      max_count = value
    elif value == max_count:
      roi.append(key)

  mask = np.zeros(gauss_img.shape, dtype=np.uint8)
  for x in range(len(gauss_img)):
    for y in range(len(gauss_img[0])):
      if (gauss_img[x][y] // 4) in roi:
        mask[x][y] = 255

  quantized = gauss_img // 16

  fig, axes = plt.subplots(1, 5, figsize=(16, 8))

  axes[0].imshow(img, cmap='gray')
  axes[0].set_title('Original')
  axes[0].axis('off')

  axes[1].imshow(box_img, cmap='gray')
  axes[1].set_title('Box Filter')
  axes[1].axis('off')

  axes[2].imshow(gauss_img, cmap='gray')
  axes[2].set_title('Gaussian')
  axes[2].axis('off')

  axes[3].imshow(quantized, cmap='tab20', vmin=0, vmax=15)
  axes[3].set_title('16 Segments')
  axes[3].axis('off')

  axes[4].imshow(mask, cmap='gray')
  axes[4].set_title('ROI Mask')
  axes[4].axis('off')

  plt.show()
