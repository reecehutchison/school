import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    # ax 1
    x = np.linspace(-5, 10)
    fig, ax1 = plt.subplots()
    ax1.plot(x, 
            (2*x**2) + (44 * np.cos(x)), 
            linestyle='dashed',
            color='red',
            label='f(x)')
    ax1.set_xlabel('x')
    ax1.set_ylabel('f(x)')
    
    # ax 2
    ax2 = ax1.twinx()
    ax2.set_ylim(ax1.get_ylim()) # this line matches the y axis
    ax2.plot(x,                  
             3*x**2,
             label='g(x)')
    ax2.set_ylabel('g(x)')
    
    # legend
    handles1, labels1 = ax1.get_legend_handles_labels()
    handles2, labels2 = ax2.get_legend_handles_labels()
    all_handles = handles1 + handles2
    all_labels = labels1 + labels2
    ax1.legend(all_handles, all_labels, loc='upper left')

    plt.show()
    