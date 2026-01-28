import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import os

def upscale_image(image, target_height, target_width):
    # uses nearest neighbor interpolation
    # idea is to src = output_pos * (original_pos / new_size)
    # aka for each pixel it just gets duplicated n times where n is the new scale
    
    h, w = image.shape[:2]
    new_image = np.zeros((target_height, target_width, image.shape[2]), dtype=image.dtype)

    for y in range(target_height):
        for x in range(target_width):
            src_y = int(y * (h / target_height))
            src_x = int(x * (w / target_width))
            new_image[y, x] = image[src_y, src_x]

    return new_image

if __name__ == '__main__':
    dir = os.path.dirname(os.path.abspath(__file__))
    fg = cv.imread(os.path.join(dir, 'panther.png'), cv.IMREAD_UNCHANGED)
    bg = cv.imread(os.path.join(dir, 'savanna.jpg'))
    
    assert fg is not None and bg is not None # keep pylance happy

    print(f'foreground shape: {fg.shape}')
    print(f'background shape: {bg.shape}')

    # upscale background to keep foreground precision 
    Cbg = upscale_image(bg, fg.shape[0], fg.shape[1])

    # np newasix to increase the dimension back to 3d after normalization
    alpha = (fg[:, :, 3] / 255.0)[:, :, np.newaxis]
    Cfg = fg[:, :, :3]

    composite = (alpha * Cfg + (1 - alpha) * Cbg).astype(np.uint8)

    plt.imshow(cv.cvtColor(composite, cv.COLOR_BGR2RGB))
    plt.show()
