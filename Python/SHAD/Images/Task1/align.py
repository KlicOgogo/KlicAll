from PIL import Image
from scipy import misc
import numpy as np
from sklearn.metrics import mean_squared_error


def horizontally_split(image, n_channels):
    channels = []
    new_height = int(image.shape[0] / n_channels)
    for i in range(n_channels):
        channels.append(np.array(image[i * new_height: (i + 1) * new_height, :]))
    return channels


def delete_borders(image, border_percentage):
    b_width = int(image.shape[1] * border_percentage)
    b_height = int(image.shape[0] * border_percentage)
    return np.array(image[b_height: image.shape[0] - b_height, b_width: image.shape[1] - b_width])


def cross_correlation(image1, image2):
    if image1.shape != image2.shape:
        raise ValueError('Sizes of images must be equal!')
    sc_prod = np.sum(image1 * image2)
    sq_sum1 = np.sum(image1 * image1)
    sq_sum2 = np.sum(image2 * image2)
    return sc_prod / np.sqrt(1. * sq_sum1 * sq_sum2)


def best_shift_mse(image1, image2, shift_limit):
    best_mse = 10 ** 50
    best_shift = ()
    for i in range(-shift_limit[0], 1):
        for j in range(-shift_limit[1], 1):
            mse = mean_squared_error(image1[:image1.shape[0] + i, :image1.shape[1] + j], image2[-i:, -j:])
            if best_mse > mse:
                best_mse = mse
                best_shift = (i, j)
        for j in range(1, shift_limit[1] + 1):
            mse = mean_squared_error(image1[:image1.shape[0] + i, j:], image2[-i:, :image2.shape[1]-j])
            if best_mse > mse:
                best_mse = mse
                best_shift = (i, j)
    for i in range(1, shift_limit[0] + 1):
        for j in range(-shift_limit[1], 1):
            mse = mean_squared_error(image1[i:, :image1.shape[1] + j], image2[:image2.shape[0] - i, -j:])
            if best_mse > mse:
                best_mse = mse
                best_shift = (i, j)
        for j in range(1, shift_limit[1] + 1):
            mse = mean_squared_error(image1[i:, j:], image2[:image2.shape[0] - i, :image2.shape[1] - j])
            if best_mse > mse:
                best_mse = mse
                best_shift = (i, j)
    return best_shift


def best_shift_cc(image1, image2, shift_limit):
    best_cc = -10 * 49
    best_shift = ()
    for i in range(-shift_limit[0], 1):
        for j in range(-shift_limit[1], 1):
            cc = cross_correlation(image1[:image1.shape[0] + i, :image1.shape[1] + j], image2[-i:, -j:])
            if best_cc < cc:
                best_cc = cc
                best_shift = (i, j)
        for j in range(1, shift_limit[1] + 1):
            cc = cross_correlation(image1[:image1.shape[0] + i, j:], image2[-i:, :image2.shape[1]-j])
            if best_cc < cc:
                best_cc = cc
                best_shift = (i, j)
    for i in range(1, shift_limit[0] + 1):
        for j in range(-shift_limit[1], 1):
            cc = cross_correlation(image1[i:, :image1.shape[1] + j], image2[:image2.shape[0] - i, -j:])
            if best_cc < cc:
                best_cc = cc
                best_shift = (i, j)
        for j in range(1, shift_limit[1] + 1):
            cc = cross_correlation(image1[i:, j:], image2[:image2.shape[0] - i, :image2.shape[1] - j])
            if best_cc < cc:
                best_cc = cc
                best_shift = (i, j)
    return best_shift


def align_by_height(channels, red_shift, blue_shift):
    height = channels[0].shape[0]
    cropped_channels = []
    if red_shift > 0:
        if blue_shift <= 0:
            cropped_channels.append(channels[2][0: height + blue_shift - red_shift, :])
            cropped_channels.append(channels[1][red_shift: height + blue_shift, :])
            cropped_channels.append(channels[0][red_shift - blue_shift: height, :])
        elif red_shift > blue_shift:
            cropped_channels.append(channels[2][0: height - red_shift, :])
            cropped_channels.append(channels[1][red_shift: height, :])
            cropped_channels.append(channels[0][red_shift - blue_shift: height - blue_shift, :])
        else:
            cropped_channels.append(channels[2][-red_shift + blue_shift: height - red_shift, :])
            cropped_channels.append(channels[1][blue_shift: height, :])
            cropped_channels.append(channels[0][0: height - blue_shift, :])
    else:
        if blue_shift >= 0:
            cropped_channels.append(channels[2][blue_shift - red_shift: height, :])
            cropped_channels.append(channels[1][blue_shift: height + red_shift, :])
            cropped_channels.append(channels[0][0: height - blue_shift + red_shift, :])
        elif red_shift > blue_shift:
            cropped_channels.append(channels[2][-red_shift: height - red_shift + blue_shift, :])
            cropped_channels.append(channels[1][0: height + blue_shift, :])
            cropped_channels.append(channels[0][-blue_shift: height, :])
        else:
            cropped_channels.append(channels[2][-red_shift: height, :])
            cropped_channels.append(channels[1][0: height + red_shift, :])
            cropped_channels.append(channels[0][-blue_shift: height - blue_shift + red_shift, :])
    return cropped_channels


def align_by_width(channels, blue_shift, red_shift):
    width = channels[0].shape[1]
    cropped_channels = []
    if red_shift > 0:
        if blue_shift <= 0:
            cropped_channels.append(channels[2][:, 0: width + blue_shift - red_shift])
            cropped_channels.append(channels[1][:, red_shift: width + blue_shift])
            cropped_channels.append(channels[0][:, red_shift - blue_shift: width])
        elif red_shift > blue_shift:
            cropped_channels.append(channels[2][:, 0: width - red_shift])
            cropped_channels.append(channels[1][:, red_shift: width])
            cropped_channels.append(channels[0][:, red_shift - blue_shift: width - blue_shift])
        else:
            cropped_channels.append(channels[2][:, -red_shift + blue_shift: width - red_shift])
            cropped_channels.append(channels[1][:, blue_shift: width])
            cropped_channels.append(channels[0][:, 0: width - blue_shift])
    else:
        if blue_shift >= 0:
            cropped_channels.append(channels[2][:, blue_shift - red_shift: width])
            cropped_channels.append(channels[1][:, blue_shift: width + red_shift])
            cropped_channels.append(channels[0][:, 0: width - blue_shift + red_shift])
        elif red_shift > blue_shift:
            cropped_channels.append(channels[2][:, -red_shift: width - red_shift + blue_shift])
            cropped_channels.append(channels[1][:, 0: width + blue_shift])
            cropped_channels.append(channels[0][:, -blue_shift: width])
        else:
            cropped_channels.append(channels[2][:, -red_shift: width])
            cropped_channels.append(channels[1][:, 0: width + red_shift])
            cropped_channels.append(channels[0][:, -blue_shift: width - blue_shift + red_shift])
    return cropped_channels


def align_mse(image, green_coord):
    channels = horizontally_split(image, 3)
    for i in range(3):
        channels[i] = delete_borders(channels[i], 0.05)
    red_shift = best_shift_mse(channels[1], channels[2], (15, 3))
    blue_shift = best_shift_mse(channels[1], channels[0], (15, 3))
    red_coord = (green_coord[0] - red_shift[0] + int(image.shape[0] / 3), green_coord[1] - red_shift[1])
    blue_coord = (green_coord[0] - blue_shift[0] - int(image.shape[0] / 3), green_coord[1] - blue_shift[1])
    cropped_channels = align_by_height(channels, red_shift[0], blue_shift[0])
    cropped_channels = align_by_width(channels, red_shift[1], blue_shift[1])
    return np.stack(cropped_channels, axis=2), blue_coord, red_coord


def align_cc(image, green_coord):
    channels = horizontally_split(image, 3)
    for i in range(3):
        channels[i] = delete_borders(channels[i], 0.05)
    red_shift = best_shift_cc(channels[1], channels[2], (15, 3))
    blue_shift = best_shift_cc(channels[1], channels[0], (15, 3))
    red_coord = (green_coord[0] - red_shift[0] + int(image.shape[0] / 3), green_coord[1] - red_shift[1])
    blue_coord = (green_coord[0] - blue_shift[0] - int(image.shape[0] / 3), green_coord[1] - blue_shift[1])
    cropped_channels = align_by_height(channels, red_shift[0], blue_shift[0])
    cropped_channels = align_by_width(channels, red_shift[1], blue_shift[1])
    return np.stack(cropped_channels, axis=2), blue_coord, red_coord


def best_shift_pyramid_cc(image1, image2, shift_limit):
    if image1.shape[0] < 501 and image1.shape[1] < 501:
        return best_shift_cc(image1, image2, (15, 3))
    else:
        best_shift = best_shift_pyramid_cc(image1[::2, ::2], image2[::2, ::2], shift_limit)
        best_cc = -10 ** 49
        best_shift = (2 * best_shift[0], 2 * best_shift[1])
        for i in range(best_shift[0] - shift_limit[0], best_shift[0] + shift_limit[0] + 1):
            for j in range(best_shift[1] - shift_limit[1], best_shift[1] + shift_limit[1] + 1):
                if i < 0 and j < 0:
                    cc = cross_correlation(image1[:image1.shape[0] + i, :image1.shape[1] + j], image2[-i:, -j:])
                elif i < 0:
                    cc = cross_correlation(image1[:image1.shape[0] + i, j:], image2[-i:, :image2.shape[1] - j])
                elif j < 0:
                    cc = cross_correlation(image1[i:, :image1.shape[1] + j], image2[:image2.shape[0] - i, -j:])
                else:
                    cc = cross_correlation(image1[i:, j:], image2[:image2.shape[0] - i, :image2.shape[1] - j])
                if best_cc < cc:
                    best_cc = cc
                    best_shift = (i, j)
        return best_shift


def best_shift_pyramid_mse(image1, image2, shift_limit):
    if image1.shape[0] < 501 and image1.shape[1] < 501:
        return best_shift_mse(image1, image2, (15, 3))
    else:
        best_shift = best_shift_pyramid_mse(image1[::2, ::2], image2[::2, ::2], shift_limit)
        best_mse = 10 ** 49
        best_shift = (2 * best_shift[0], 2 * best_shift[1])
        for i in range(best_shift[0] - shift_limit[0], best_shift[0] + shift_limit[0] + 1):
            for j in range(best_shift[1] - shift_limit[1], best_shift[1] + shift_limit[1] + 1):
                if i < 0 and j < 0:
                    mse = mean_squared_error(image1[:image1.shape[0] + i, :image1.shape[1] + j], image2[-i:, -j:])
                elif i < 0:
                    mse = mean_squared_error(image1[:image1.shape[0] + i, j:], image2[-i:, :image2.shape[1] - j])
                elif j < 0:
                    mse = mean_squared_error(image1[i:, :image1.shape[1] + j], image2[:image2.shape[0] - i, -j:])
                else:
                    mse = mean_squared_error(image1[i:, j:], image2[:image2.shape[0] - i, :image2.shape[1] - j])
                if best_mse > mse:
                    best_mse = mse
                    best_shift = (i, j)
        return best_shift


def align_pyramid_cc(image, green_coord):
    channels = horizontally_split(image, 3)
    for i in range(3):
        channels[i] = delete_borders(channels[i], 0.05)
    red_shift = best_shift_pyramid_cc(channels[1], channels[2], (2, 2))
    blue_shift = best_shift_pyramid_cc(channels[1], channels[0], (2, 2))
    red_coord = (green_coord[0] - red_shift[0] + int(image.shape[0] / 3), green_coord[1] - red_shift[1])
    blue_coord = (green_coord[0] - blue_shift[0] - int(image.shape[0] / 3), green_coord[1] - blue_shift[1])
    cropped_channels = align_by_height(channels, red_shift[0], blue_shift[0])
    cropped_channels = align_by_width(channels, red_shift[1], blue_shift[1])
    return np.stack(cropped_channels, axis=2), blue_coord, red_coord


def align_pyramid_mse(image, green_coord):
    channels = horizontally_split(image, 3)
    for i in range(3):
        channels[i] = delete_borders(channels[i], 0.05)
    red_shift = best_shift_pyramid_mse(channels[1], channels[2], (2, 2))
    blue_shift = best_shift_pyramid_mse(channels[1], channels[0], (2, 2))
    red_coord = (green_coord[0] - red_shift[0] + int(image.shape[0] / 3), green_coord[1] - red_shift[1])
    blue_coord = (green_coord[0] - blue_shift[0] - int(image.shape[0] / 3), green_coord[1] - blue_shift[1])
    cropped_channels = align_by_height(channels, red_shift[0], blue_shift[0])
    cropped_channels = align_by_width(channels, red_shift[1], blue_shift[1])
    return np.stack(cropped_channels, axis=2), blue_coord, red_coord


def align(image, green_coord):
    if image.shape[0] <= 1665 and image.shape[1] <= 555:
        return align_mse(image, green_coord)
    else:
        return align_pyramid_mse(image, green_coord)

"""
correct_small = 0
for i in range(10):
    im = misc.imread(r'public_data/0' + str(i) + '_input/img.png', mode='P')
    print(im.shape)
    parts = open(r'public_data/0' + str(i) + '_input/g_coord.csv').read().rstrip('\n').split(',')
    g_coord = (int(parts[0]), int(parts[1]))
    xx, yy, zz = align(im, g_coord)
    with open(r'public_data/0' + str(i) + '_gt/gt.csv') as fhandle:
        parts = fhandle.read().rstrip('\n').split(',')
        coords = map(int, parts[1:])
        gt_b_row, gt_b_col, _, _, gt_r_row, gt_r_col, diff_max = coords
    metric = abs(gt_b_row - yy[0]) + abs(gt_b_col - yy[1]) + \
             abs(gt_r_row - zz[0]) + abs(gt_r_col - zz[1])
    if metric <= diff_max:
        correct_small += 1
    misc.imsave('public_data/0' + str(i) + '_input/image' + str(i) + '.png', xx)
print('Small image correct answers = {}'.format(correct_small))


correct = 0
for i in range(10, 20):
    im = misc.imread(r'public_data/' + str(i) + '_input/img.png', mode='P')
    print(im.shape)
    parts = open(r'public_data/' + str(i) + '_input/g_coord.csv').read().rstrip('\n').split(',')
    g_coord = (int(parts[0]), int(parts[1]))
    xx, yy, zz = align(im, g_coord)
    with open(r'public_data/' + str(i) + '_gt/gt.csv') as fhandle:
        parts = fhandle.read().rstrip('\n').split(',')
        coords = map(int, parts[1:])
        gt_b_row, gt_b_col, _, _, gt_r_row, gt_r_col, diff_max = coords
    metric = abs(gt_b_row - yy[0]) + abs(gt_b_col - yy[1]) + \
                abs(gt_r_row - zz[0]) + abs(gt_r_col - zz[1])
    if metric <= diff_max:
        correct += 1
    misc.imsave('public_data/' + str(i) + '_input/image' + str(i) + '.png', xx)
print('Large image correct answers = {}'.format(correct))
"""
