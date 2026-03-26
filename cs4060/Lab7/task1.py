import matplotlib.pyplot as plt
import numpy as np
import os
import cv2
import math
import random


if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/bike.jpeg"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
  
  assert img is not None
  
  # print(img.shape) --> (1024, 768)
  noise = np.zeros(img.shape, dtype=np.int16)
  for x in range(len(img)):
    for y in range(len(img[0])):
      noise[x][y] = random.randint(-50, 50)
      
  noisy_img = np.clip(img.astype(np.int16) + noise, 0, 255).astype(np.uint8)

  gaussian1 = cv2.GaussianBlur(noisy_img, (5, 5), sigmaX=1)
  gaussian2 = cv2.GaussianBlur(noisy_img, (5, 5), sigmaX=3)
  gaussian3 = cv2.GaussianBlur(noisy_img, (5, 5), sigmaX=5)

  gauss_zero = cv2.GaussianBlur(noisy_img, (5, 5), sigmaX=5, borderType=cv2.BORDER_CONSTANT)
  gauss_mirror = cv2.GaussianBlur(noisy_img, (5, 5), sigmaX=5, borderType=cv2.BORDER_REFLECT)
  gauss_replicate = cv2.GaussianBlur(noisy_img, (5, 5), sigmaX=5, borderType=cv2.BORDER_REPLICATE)

  box = cv2.boxFilter(noisy_img, -1, (5, 5))
  box_zero = cv2.boxFilter(noisy_img, -1, (5, 5), borderType=cv2.BORDER_CONSTANT)
  box_mirror = cv2.boxFilter(noisy_img, -1, (5, 5), borderType=cv2.BORDER_REFLECT)
  box_replicate = cv2.boxFilter(noisy_img, -1, (5, 5), borderType=cv2.BORDER_REPLICATE)

  fig, axes = plt.subplots(3, 4, figsize=(12, 8))

  axes[0][0].imshow(img, cmap='gray')
  axes[0][0].set_title('Original')
  axes[0][0].axis('off')

  axes[0][1].imshow(noisy_img, cmap='gray')
  axes[0][1].set_title('Noisy')
  axes[0][1].axis('off')

  axes[0][2].imshow(gaussian1, cmap='gray')
  axes[0][2].set_title('s=1')
  axes[0][2].axis('off')

  axes[0][3].imshow(gaussian2, cmap='gray')
  axes[0][3].set_title('s=3')
  axes[0][3].axis('off')

  axes[1][0].imshow(gaussian3, cmap='gray')
  axes[1][0].set_title('s=5')
  axes[1][0].axis('off')

  axes[1][1].imshow(gauss_zero, cmap='gray')
  axes[1][1].set_title('Zero s=5')
  axes[1][1].axis('off')

  axes[1][2].imshow(gauss_mirror, cmap='gray')
  axes[1][2].set_title('Mirror s=5')
  axes[1][2].axis('off')

  axes[1][3].imshow(gauss_replicate, cmap='gray')
  axes[1][3].set_title('Replicate s=5')
  axes[1][3].axis('off')

  axes[2][0].imshow(box, cmap='gray')
  axes[2][0].set_title('Box')
  axes[2][0].axis('off')

  axes[2][1].imshow(box_zero, cmap='gray')
  axes[2][1].set_title('Box Zero')
  axes[2][1].axis('off')

  axes[2][2].imshow(box_mirror, cmap='gray')
  axes[2][2].set_title('Box Mirror')
  axes[2][2].axis('off')

  axes[2][3].imshow(box_replicate, cmap='gray')
  axes[2][3].set_title('Box Replicate')
  axes[2][3].axis('off')

  plt.show()