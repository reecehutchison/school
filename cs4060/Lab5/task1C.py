import matplotlib.pyplot as plt
import numpy as np
import os
import cv2


if __name__ == "__main__":
  path = os.path.dirname(os.path.abspath(__file__)) + "/boy.jpg"
  img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

  assert img is not None
  
  bit_depths = []
  bit_depths.append(0b10000000)  
  bit_depths.append(0b01000000)  
  bit_depths.append(0b00100000)  
  bit_depths.append(0b00010000)  
  bit_depths.append(0b00001000)  
  bit_depths.append(0b00000100)  
  bit_depths.append(0b00000010)  
  bit_depths.append(0b00000001)  

  fig, axes = plt.subplots(2, 4)

  for i, depth in enumerate(bit_depths):
    row = i // 4
    col = i % 4

    bit_plane = (img & depth).flatten()

    axes[row][col].hist(bit_plane)
    axes[row][col].set_title(f"bit plane : {7 - i}")
  
  plt.show()
  
