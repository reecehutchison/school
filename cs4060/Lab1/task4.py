import matplotlib.pyplot as plt
import numpy as np
import os

if __name__ == '__main__':
    originalImage = plt.imread(os.path.join(os.path.dirname(__file__), './boy.jpg'))
    posterizedImage = np.array((originalImage // 64) * 64)
    
    fig, (ax1, ax2) = plt.subplots(1, 2)
    ax1.imshow(originalImage)
    ax1.set_title('Original')
    ax2.imshow(posterizedImage)
    ax2.set_title('Posterized')
    
    plt.show()