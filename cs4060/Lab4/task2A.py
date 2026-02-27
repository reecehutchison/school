import cv2
import matplotlib.pyplot as plt
import os
import numpy as np



if __name__ == "__main__":
  dir = os.path.dirname(os.path.abspath(__file__))
  
  spectrum = cv2.imread(dir + "/FTspectrum.tif", cv2.IMREAD_UNCHANGED)
  assert spectrum is not None

  fig, (ax1, ax2) = plt.subplots(1, 2)
  
  ax1.imshow(spectrum, cmap="gray")
  ax1.set_title("pre log")
  
  log_spectrum = np.log1p(spectrum.astype(np.float64))
  normalized = np.uint8((log_spectrum / log_spectrum.max()) * 128)

  ax2.imshow(normalized, cmap='gray')
  ax2.set_title("post log")

  plt.show()