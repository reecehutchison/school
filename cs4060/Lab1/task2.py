import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    x = np.linspace(-5, 10, 20)
    Y = (2 * x ** 2) + 44 * np.cos(x)
    plt.scatter(x, Y, color='red')
    
    # note, assignment says 100 but assume it meant 10, same as (a)
    xInterpolate = np.linspace(-5, 10, 200)
    YInterpolate = (2 * xInterpolate ** 2) + 44 * np.cos(xInterpolate)
    plt.plot(xInterpolate, YInterpolate)
    
    plt.show()
    
    