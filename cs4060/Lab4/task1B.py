# --> gamma value 1.5 looks the best with the lena image. 
# lower gamma values make it look to bright
# higher gamma values make the details too dark

import cv2
import matplotlib.pyplot as plt
import numpy as np
import os

if __name__ == "__main__":
  img_path = os.path.dirname(os.path.abspath(__file__)) + "/lena.tif"
  img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
  
  assert img is not None
  
  rows = 2
  cols = 4
  fig, axes = plt.subplots(rows, cols)
  
  gammas = [0.1, 0.3, 0.5, 0.7, 1.5, 2.5, 4.0, 6.0]
  
  # normalize, then raise to power of gamma, Y < 1 gets brighter, Y > 1 gets darker
  for i, gamma in enumerate(gammas):
    row = i // 4
    col = i % 4
    normalized = img / 255.0 
    transformed = np.uint8(np.power(normalized, gamma) * 255)
    axes[row][col].imshow(transformed, cmap='gray')
    axes[row][col].set_title(f"Y = {gamma}")
    axes[row][col].axis('off')

  plt.show()