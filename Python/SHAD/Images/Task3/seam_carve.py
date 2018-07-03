import numpy as np


def brightness(image):
    return image[:, :, 0] * 0.299 + \
           image[:, :, 1] * 0.587 + \
           image[:, :, 2] * 0.114


def derivative_x(im_bness):
    return np.concatenate((im_bness[:1, :], im_bness[:-1, :]), axis=0) - \
           np.concatenate((im_bness[1:, :], im_bness[-1:, :]), axis=0)


def derivative_y(im_bness):
    return np.concatenate((im_bness[:, :1], im_bness[:, :-1]), axis=1) - \
           np.concatenate((im_bness[:, 1:], im_bness[:, -1:]), axis=1)


def count_energy(im_bness):
    der_x = derivative_x(im_bness)
    der_y = derivative_y(im_bness)
    return np.array(np.sqrt(der_x * der_x + der_y * der_y), dtype='float64')


def mins_horizontal(energy):
    height = energy.shape[0]
    width = energy.shape[1]
    mins = np.zeros((height, width), dtype='float64')
    mins[0] = energy[0]
    for i in range(1, height):
        for j in range(width):
            mins[i][j] = energy[i][j] + \
                         np.min(mins[i - 1, max(0, j - 1):min(j + 2, width)])
    return mins


def mins_vertical(energy):
    height = energy.shape[0]
    width = energy.shape[1]
    mins = np.zeros((height, width), dtype='float64')
    mins[:, 0] = energy[:, 0]
    for j in range(1, width):
        for i in range(height):
            mins[i][j] = energy[i][j] + \
                         np.min(mins[max(0, i - 1):min(i + 2, height), j - 1])
    return mins

"""
def horizontal_shrink(image, mask):
    height = image.shape[0]
    width = image.shape[1]
    energy = count_energy(brightness(image))
    if mask is not None:
        energy += mask * 25600# * height * width
    mins = mins_horizontal(energy)
    ind = np.argmin(mins[height - 1])
    new_image = np.zeros((height, width - 1, image.shape[2]), dtype=int)
    new_mask = None
    if mask is not None:
        new_mask = np.zeros((height, width - 1), dtype=int)
    carve_mask = np.zeros((height, width), dtype=int)
    for i in range(height - 2, -1, -1):
        new_image[i + 1] = np.delete(image[i + 1], ind, axis=0)
        if mask is not None:
            new_mask[i + 1] = np.delete(mask[i + 1], ind)
        carve_mask[i + 1, ind] = 1
        if ind > 0:
            ind += np.argmin(mins[i, max(0, ind - 1): min(width, ind + 2)]) - 1
        else:
            ind += np.argmin(mins[i, max(0, ind - 1): min(width, ind + 2)])
    new_image[0] = np.delete(image[0], ind, axis=0)
    if mask is not None:
        new_mask[0] = np.delete(mask[0], ind)
    carve_mask[0, ind] = 1
    return new_image, new_mask, carve_mask


def horizontal_expand(image, mask):
    height = image.shape[0]
    width = image.shape[1]
    energy = count_energy(brightness(image))
    if mask is not None:
        energy += mask * 25600# * height * width
    mins = mins_horizontal(energy)
    ind = np.argmin(mins[height - 1])
    new_image = np.zeros((height, width + 1, image.shape[2]), dtype=int)
    new_mask = None
    if mask is not None:
        new_mask = np.zeros((height, width + 1), dtype=int)
    carve_mask = np.zeros((height, width), dtype=int)
    for i in range(height - 2, -1, -1):
        if ind < width - 1:
            val = (image[i + 1, ind] + image[i + 1, ind + 1]) / 2
        else:
            val = image[i + 1, ind]
        new_image[i + 1] = np.insert(image[i + 1], ind + 1, [val], axis=0)
        if mask is not None:
            new_mask[i + 1] = np.insert(mask[i + 1], ind + 1, [0])
        carve_mask[i + 1, ind] = 1
        if ind > 0:
            ind += np.argmin(mins[i, max(0, ind - 1): min(width, ind + 2)]) - 1
        else:
            ind += np.argmin(mins[i, max(0, ind - 1): min(width, ind + 2)])
    if ind < width - 1:
        val = (image[0, ind] + image[0, ind + 1]) / 2
    else:
        val = image[0, ind]
    new_image[0] = np.insert(image[0], ind + 1, [val], axis=0)
    if mask is not None:
        new_mask[0] = np.insert(mask[0], ind + 1, [0])
    carve_mask[0, ind] = 1
    return new_image, new_mask, carve_mask



def vertical_shrink(image, mask):
    if mask is not None:
        im, msk, carve_msk = horizontal_shrink(np.transpose(image, (1, 0, 2)), mask.transpose())
        return np.transpose(im, (1, 0, 2)), msk.transpose(), carve_msk.transpose()
    else:
        im, msk, carve_msk = horizontal_shrink(np.transpose(image, (1, 0, 2)), mask)
        return np.transpose(im, (1, 0, 2)), None, carve_msk.transpose()


def vertical_expand(image, mask):
    if mask is not None:
        im, msk, carve_msk = horizontal_expand(np.transpose(image, (1, 0, 2)), mask.transpose())
        return np.transpose(im, (1, 0, 2)), msk.transpose(), carve_msk.transpose()
    else:
        im, msk, carve_msk = horizontal_expand(np.transpose(image, (1, 0, 2)), mask)
        return np.transpose(im, (1, 0, 2)), None, carve_msk.transpose()
"""


def vertical_shrink(image, mask):
    height = image.shape[0]
    width = image.shape[1]
    energy = count_energy(brightness(image))
    if mask is not None:
        energy += mask * 25600# * height * width
    mins = mins_vertical(energy)
    ind = np.argmin(mins[:, width - 1])
    new_image = np.zeros((height - 1, width, image.shape[2]), dtype=int)
    new_mask = None
    if mask is not None:
        new_mask = np.zeros((height - 1, width), dtype=int)
    carve_mask = np.zeros((height, width), dtype=int)
    for i in range(width - 2, -1, -1):
        new_image[:, i + 1] = np.delete(image[:, i + 1], ind, axis=0)
        if mask is not None:
            new_mask[:, i + 1] = np.delete(mask[:, i + 1], ind)
        carve_mask[ind, i + 1] = 1
        if ind > 0:
            ind += np.argmin(mins[max(0, ind - 1): min(height, ind + 2), i]) - 1
        else:
            ind += np.argmin(mins[max(0, ind - 1): min(height, ind + 2), i])
    new_image[:, 0] = np.delete(image[:, 0], ind, axis=0)
    if mask is not None:
        new_mask[:, 0] = np.delete(mask[:, 0], ind)
    carve_mask[ind, 0] = 1
    return new_image, new_mask, carve_mask


def vertical_expand(image, mask):
    height = image.shape[0]
    width = image.shape[1]
    energy = count_energy(brightness(image))
    if mask is not None:
        energy += mask * 25600# * height * width
    mins = mins_vertical(energy)
    ind = np.argmin(mins[:, width - 1])
    new_image = np.zeros((height + 1, width, image.shape[2]), dtype=int)
    new_mask = None
    if mask is not None:
        new_mask = np.zeros((height + 1, width), dtype=int)
    carve_mask = np.zeros((height, width), dtype=int)
    for i in range(width - 2, -1, -1):
        if ind < height - 1:
            val = (image[ind, i + 1] + image[ind + 1, i + 1]) / 2
        else:
            val = image[ind, i + 1]
        new_image[:, i + 1] = np.insert(image[:, i + 1], ind + 1, [val], axis=0)
        if mask is not None:
            new_mask[:, i + 1] = np.insert(mask[:, i + 1], ind + 1, [0])
        carve_mask[ind, i + 1] = 1
        if ind > 0:
            ind += np.argmin(mins[max(0, ind - 1): min(height, ind + 2), i]) - 1
        else:
            ind += np.argmin(mins[max(0, ind - 1): min(height, ind + 2), i])
    if ind < height - 1:
        val = (image[ind, 0] + image[ind + 1, 0]) / 2
    else:
        val = image[ind, 0]
    new_image[:, 0] = np.insert(image[:, 0], ind + 1, [val], axis=0)
    if mask is not None:
        new_mask[:, 0] = np.insert(mask[:, 0], ind + 1, [0])
    carve_mask[ind, 0] = 1
    return new_image, new_mask, carve_mask


def horizontal_shrink(image, mask):
    if mask is not None:
        im, msk, carve_msk = vertical_shrink(np.transpose(image, (1, 0, 2)), mask.transpose())
        return np.transpose(im, (1, 0, 2)), msk.transpose(), carve_msk.transpose()
    else:
        im, msk, carve_msk = vertical_shrink(np.transpose(image, (1, 0, 2)), mask)
        return np.transpose(im, (1, 0, 2)), None, carve_msk.transpose()


def horizontal_expand(image, mask):
    if mask is not None:
        im, msk, carve_msk = vertical_expand(np.transpose(image, (1, 0, 2)), mask.transpose())
        return np.transpose(im, (1, 0, 2)), msk.transpose(), carve_msk.transpose()
    else:
        im, msk, carve_msk = vertical_expand(np.transpose(image, (1, 0, 2)), mask)
        return np.transpose(im, (1, 0, 2)), None, carve_msk.transpose()


def seam_carve(image, mode, mask=None):
    if mode == 'horizontal shrink':
        return horizontal_shrink(image, mask)
    if mode == 'vertical shrink':
        return vertical_shrink(image, mask)
    if mode == 'horizontal expand':
        return horizontal_expand(image, mask)
    if mode == 'vertical expand':
        return vertical_expand(image, mask)


