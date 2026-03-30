import matplotlib.pyplot as plt
import numpy as np
import os
import cv2

if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/team.jpeg"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

  assert img is not None

  print(img.shape)
  shading = cv2.GaussianBlur(img, (301, 301), sigmaX=100)

  img_float = img.astype(np.float64) # convert so divisino works smoothly
  shading_float = shading.astype(np.float64)

  for x in range(len(shading_float)):
    for y in range(len(shading_float[0])):
      if shading_float[x][y] == 0:
        shading_float[x][y] = 1

  total = 0 # get mean to re multiply back so it looks normal 
  for x in range(len(shading_float)):
    for y in range(len(shading_float[0])):
      total += shading_float[x][y]
  mean = total / (len(shading_float) * len(shading_float[0]))

  corrected = (img_float / shading_float)
  corrected = np.clip(corrected, 0, 255).astype(np.uint8)

  fig, axes = plt.subplots(1, 3, figsize=(12, 8))

  axes[0].imshow(img, cmap='gray')
  axes[0].set_title('Original')
  axes[0].axis('off')

  axes[1].imshow(shading, cmap='gray')
  axes[1].set_title('Shading Pattern')
  axes[1].axis('off')

  axes[2].imshow(corrected, cmap='gray')
  axes[2].set_title('Corrected')
  axes[2].axis('off')

  plt.show()
