import matplotlib.pyplot as plt
import numpy as np
import os
import cv2

if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/boy.png"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

  assert img is not None

  img_float = img.astype(np.float64)

  # lp(x, y)
  lp = cv2.GaussianBlur(img_float, (21, 21), sigmaX=5)

  # hp(x, y) = f(x, y) - lp(x, y)
  hp = img_float - lp

  # br(x, y) = lp1(x, y) + [f(x, y) - lp2(x, y)]
  lp1 = cv2.GaussianBlur(img_float, (11, 11), sigmaX=2)
  lp2 = cv2.GaussianBlur(img_float, (41, 41), sigmaX=10)
  br = lp1 + (img_float - lp2)

  # bp(x, y) = f(x, y) - br(x, y)
  bp = img_float - br

  fig, axes = plt.subplots(2, 3, figsize=(15, 10))

  axes[0, 0].imshow(img, cmap='gray')
  axes[0, 0].set_title('Original')
  axes[0, 0].axis('off')

  axes[0, 1].imshow(lp, cmap='gray')
  axes[0, 1].set_title('Lowpass')
  axes[0, 1].axis('off')

  axes[0, 2].imshow(hp, cmap='gray')
  axes[0, 2].set_title('Highpass')
  axes[0, 2].axis('off')

  axes[1, 0].imshow(br, cmap='gray')
  axes[1, 0].set_title('Bandreject')
  axes[1, 0].axis('off')

  axes[1, 1].imshow(bp, cmap='gray')
  axes[1, 1].set_title('Bandpass')
  axes[1, 1].axis('off')

  axes[1, 2].axis('off')

  plt.suptitle('1) Filtered Images')
  plt.show()

  # hb(x, y) = (K - 1) * f(x, y) + hp(f(x, y))

  # High boost on Lowpass
  lp_lp = cv2.GaussianBlur(lp, (21, 21), sigmaX=5)
  hp_lp = lp - lp_lp

  fig, axes = plt.subplots(1, 5, figsize=(18, 4))
  axes[0].imshow(lp, cmap='gray')
  axes[0].set_title('Original')
  axes[0].axis('off')
  axes[1].imshow((1.0 - 1) * lp + hp_lp, cmap='gray')
  axes[1].set_title('K = 1.0')
  axes[1].axis('off')
  axes[2].imshow((1.5 - 1) * lp + hp_lp, cmap='gray')
  axes[2].set_title('K = 1.5')
  axes[2].axis('off')
  axes[3].imshow((2.0 - 1) * lp + hp_lp, cmap='gray')
  axes[3].set_title('K = 2.0')
  axes[3].axis('off')
  axes[4].imshow((3.0 - 1) * lp + hp_lp, cmap='gray')
  axes[4].set_title('K = 3.0')
  axes[4].axis('off')
  plt.suptitle('2) Lowpass --> High Boost')
  plt.tight_layout()
  plt.show()

  # High boost on Highpass
  lp_hp = cv2.GaussianBlur(hp, (21, 21), sigmaX=5)
  hp_hp = hp - lp_hp

  fig, axes = plt.subplots(1, 5, figsize=(18, 4))
  axes[0].imshow(hp, cmap='gray')
  axes[0].set_title('Original')
  axes[0].axis('off')
  axes[1].imshow((1.0 - 1) * hp + hp_hp, cmap='gray')
  axes[1].set_title('K = 1.0')
  axes[1].axis('off')
  axes[2].imshow((1.5 - 1) * hp + hp_hp, cmap='gray')
  axes[2].set_title('K = 1.5')
  axes[2].axis('off')
  axes[3].imshow((2.0 - 1) * hp + hp_hp, cmap='gray')
  axes[3].set_title('K = 2.0')
  axes[3].axis('off')
  axes[4].imshow((3.0 - 1) * hp + hp_hp, cmap='gray')
  axes[4].set_title('K = 3.0')
  axes[4].axis('off')
  plt.suptitle('2) Highpass --> High Boost')
  plt.tight_layout()
  plt.show()

  # High boost on Bandreject
  lp_br = cv2.GaussianBlur(br, (21, 21), sigmaX=5)
  hp_br = br - lp_br

  fig, axes = plt.subplots(1, 5, figsize=(18, 4))
  axes[0].imshow(br, cmap='gray')
  axes[0].set_title('Original')
  axes[0].axis('off')
  axes[1].imshow((1.0 - 1) * br + hp_br, cmap='gray')
  axes[1].set_title('K = 1.0')
  axes[1].axis('off')
  axes[2].imshow((1.5 - 1) * br + hp_br, cmap='gray')
  axes[2].set_title('K = 1.5')
  axes[2].axis('off')
  axes[3].imshow((2.0 - 1) * br + hp_br, cmap='gray')
  axes[3].set_title('K = 2.0')
  axes[3].axis('off')
  axes[4].imshow((3.0 - 1) * br + hp_br, cmap='gray')
  axes[4].set_title('K = 3.0')
  axes[4].axis('off')
  plt.suptitle('2) Bandreject --> High Boost')
  plt.tight_layout()
  plt.show()

  # High boost on Bandpass
  lp_bp = cv2.GaussianBlur(bp, (21, 21), sigmaX=5)
  hp_bp = bp - lp_bp

  fig, axes = plt.subplots(1, 5, figsize=(18, 4))
  axes[0].imshow(bp, cmap='gray')
  axes[0].set_title('Original')
  axes[0].axis('off')
  axes[1].imshow((1.0 - 1) * bp + hp_bp, cmap='gray')
  axes[1].set_title('K = 1.0')
  axes[1].axis('off')
  axes[2].imshow((1.5 - 1) * bp + hp_bp, cmap='gray')
  axes[2].set_title('K = 1.5')
  axes[2].axis('off')
  axes[3].imshow((2.0 - 1) * bp + hp_bp, cmap='gray')
  axes[3].set_title('K = 2.0')
  axes[3].axis('off')
  axes[4].imshow((3.0 - 1) * bp + hp_bp, cmap='gray')
  axes[4].set_title('K = 3.0')
  axes[4].axis('off')
  plt.suptitle('2) Bandpass --> High Boost')
  plt.tight_layout()
  plt.show()
