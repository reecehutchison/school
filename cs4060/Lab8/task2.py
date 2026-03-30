import matplotlib.pyplot as plt
import numpy as np
import os
import cv2
import random


if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/boy.png"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

  assert img is not None

  img_float = img.astype(np.float64)

  noisy = np.zeros(img.shape, dtype=np.int16)
  for x in range(len(img)):
    for y in range(len(img[0])):
      noisy[x][y] = int(img[x][y]) + random.randint(-50, 50)
  noisy = np.clip(noisy, 0, 255).astype(np.uint8)
  noisy_float = noisy.astype(np.float64)

  denoised = cv2.GaussianBlur(noisy, (5, 5), sigmaX=1.5)

  # unsharp mask to sharpen
  blurred = cv2.GaussianBlur(denoised.astype(np.float64), (5, 5), sigmaX=1.5)
  sharpened = np.clip(2.0 * denoised - blurred, 0, 255).astype(np.uint8)

  fig, axes = plt.subplots(1, 4, figsize=(18, 4))
  axes[0].imshow(img, cmap='gray')
  axes[0].set_title('Original')
  axes[0].axis('off')
  axes[1].imshow(noisy, cmap='gray')
  axes[1].set_title('Noisy')
  axes[1].axis('off')
  axes[2].imshow(denoised, cmap='gray')
  axes[2].set_title('Denoised (Gaussian Blur)')
  axes[2].axis('off')
  axes[3].imshow(sharpened, cmap='gray')
  axes[3].set_title('Sharpened')
  axes[3].axis('off')
  plt.suptitle('1) & 2) Denoise + Sharpen')
  plt.show()

  median = cv2.medianBlur(noisy, 5)

  geometric = np.zeros(noisy.shape, dtype=np.float64)
  padded = np.pad(noisy_float, 2, mode='reflect')
  for i in range(len(noisy)):
    for j in range(len(noisy[0])):
      region = padded[i:i + 5, j:j + 5]
      region = np.clip(region, 1, 255)
      geometric[i][j] = np.exp(np.mean(np.log(region)))
  geometric = np.clip(geometric, 0, 255).astype(np.uint8)

  harmonic = np.zeros(noisy.shape, dtype=np.float64)
  for i in range(len(noisy)):
    for j in range(len(noisy[0])):
      region = padded[i:i + 5, j:j + 5]
      region = np.clip(region, 1, 255)
      harmonic[i][j] = 25 / np.sum(1.0 / region)
  harmonic = np.clip(harmonic, 0, 255).astype(np.uint8)

  fig, axes = plt.subplots(1, 4, figsize=(18, 4))
  axes[0].imshow(noisy, cmap='gray')
  axes[0].set_title('Noisy')
  axes[0].axis('off')
  axes[1].imshow(median, cmap='gray')
  axes[1].set_title('Median')
  axes[1].axis('off')
  axes[2].imshow(geometric, cmap='gray')
  axes[2].set_title('Geometric Mean')
  axes[2].axis('off')
  axes[3].imshow(harmonic, cmap='gray')
  axes[3].set_title('Harmonic Mean')
  axes[3].axis('off')
  plt.suptitle('3) Median, Geometric, and Harmonic Filters')
  plt.show()

  fig, axes = plt.subplots(2, 3, figsize=(15, 8))

  axes[0][0].hist(img.flatten(), bins=256)
  axes[0][0].set_title('Original')

  axes[0][1].hist(noisy.flatten(), bins=256)
  axes[0][1].set_title('Noisy')

  axes[0][2].hist(denoised.flatten(), bins=256)
  axes[0][2].set_title('Denoised')

  axes[1][0].hist(median.flatten(), bins=256)
  axes[1][0].set_title('Median')

  axes[1][1].hist(geometric.flatten(), bins=256)
  axes[1][1].set_title('Geometric Mean')

  axes[1][2].hist(harmonic.flatten(), bins=256)
  axes[1][2].set_title('Harmonic Mean')

  plt.suptitle('4) Histograms')
  plt.show()
