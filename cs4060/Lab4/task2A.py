import cv2
import matplotlib.pyplot as plt
import os
import numpy as np

def save_ft_spec(img, out_path):
  """computes the fourier spectrum of img and saves"""
  f = np.fft.fft2(img)
  fshift = np.fft.fftshift(f)
  spectrum = np.abs(fshift)
  cv2.imwrite(out_path, spectrum.astype(np.float32))

if __name__ == "__main__":
  dir = os.path.dirname(os.path.abspath(__file__))
  # img = cv2.imread(dir + "/lena.tif", cv2.IMREAD_GRAYSCALE)
  # assert img is not None
  # # --> this is how i got the spectrum!
  # # save_ft_spec(img, dir + "/FTspectrum.tif")
  
  spectrum = cv2.imread(dir + "/FTspectrum.tif", cv2.IMREAD_UNCHANGED)
  assert spectrum is not None

  fig, (ax1, ax2) = plt.subplots(1, 2)
  
  ax1.imshow(spectrum, cmap="gray")
  ax1.set_title("pre log")
  
  log_spectrum = np.log1p(spectrum.astype(np.float64))
  normalized = np.uint8((log_spectrum / log_spectrum.max()) * 255)

  ax2.imshow(normalized, cmap='gray')
  ax2.set_title("post log")

  plt.show()