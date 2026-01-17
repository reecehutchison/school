import matplotlib.pyplot as plt
import os

if __name__ == '__main__':
    
    image = plt.imread(os.path.join(os.path.dirname(__file__), './boy.jpg'))
    
    R = image[:, :, 0]
    G = image[:, :, 1]
    B = image[:, :, 2]
    
    Y = 0.299 * R + 0.587 * G + 0.114 * B
    
    plt.imshow(Y, cmap='gray')
    plt.show()