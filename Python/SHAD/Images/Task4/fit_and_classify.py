import numpy as np
from skimage.transform import resize
from skimage.io import imread
from sklearn.svm import LinearSVC
#from sklearn.model_selection import RandomizedSearchCV
#from os.path import join
#from numpy import zeros


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


def gradient_abs_and_dir(im_bness):
    der_x = derivative_x(im_bness)
    der_y = derivative_y(im_bness)
    return np.array(np.sqrt(der_x * der_x + der_y * der_y), dtype='float64'), \
           (np.arctan2(der_y, der_x) * 180 / np.pi) % 180


def basket_number(pos_angle, bin_count):
    result = np.zeros(pos_angle.shape, dtype=int)
    basket_size = 180 / bin_count
    left_border = 0
    for j in range(bin_count):
        right_border = left_border + basket_size
        result[np.logical_and(pos_angle >= left_border, pos_angle < right_border)] = j
        left_border += basket_size
    return result


def cell_histogram(basket_num, cell_abs, bin_count):
    sums = np.zeros(bin_count)
    for i in range(bin_count):
        sums[i] += np.sum(cell_abs[basket_num == i])
    return sums


def full_histogram(basket_num, grad_abs, bin_count):
    n_cells = 14
    cell_rows = int(basket_num.shape[0] / n_cells)
    cell_cols = int(basket_num.shape[1] / n_cells)
    height = basket_num.shape[0]
    width = basket_num.shape[1]
    result = np.zeros((n_cells, n_cells, bin_count))
    u_border = 0
    for i in range(n_cells):
        d_border = u_border + cell_rows
        if i == n_cells - 1:
            d_border = height
        l_border = 0
        for j in range(n_cells):
            r_border = l_border + cell_cols
            if j == n_cells - 1:
                r_border = width
            result[i, j] = cell_histogram(basket_num[u_border:d_border, l_border:r_border],
                                                grad_abs[u_border:d_border, l_border:r_border],
                                                bin_count)
            l_border += cell_cols
        u_border += cell_rows
    return result


def block_descriptor(block, eps):
    sub_vectors = np.zeros((block.shape[0], block.shape[1] * block.shape[2]))
    for i in range(block.shape[0]):
        sub_vectors[i] = np.concatenate(block[i, :])
    vector = np.concatenate(sub_vectors[:])
    return vector / np.sqrt(np.sum(vector * vector) + eps)


def descriptor(full_hist, block_shape, eps):
    block_rows = block_shape[0]
    block_cols = block_shape[1]
    b_height = full_hist.shape[0]
    b_width = full_hist.shape[1]
    result = np.zeros((0,))
    for u_border in range(0, b_height-block_rows + 1):
        d_border = u_border + block_rows
        for l_border in range(0, b_width-block_cols + 1):
            r_border = l_border + block_cols
            if u_border % 5 != 0 and l_border % 5 != 0:
                result = np.concatenate((result,
                                         block_descriptor(full_hist[u_border:d_border,
                                                          l_border:r_border], eps)))
    return result


def extract_hog(image):
    opt_size = (24, 24, 3)
    bin_count = 8
    resized = resize(image, opt_size, mode='reflect')
    im_bness = brightness(resized)
    grad_abs, grad_dir = gradient_abs_and_dir(im_bness)
    baskets = basket_number(grad_dir, bin_count)
    histogram = full_histogram(baskets, grad_abs, bin_count)
    return descriptor(histogram, (2, 2), 1e-100)


def fit_and_classify(train_features, train_labels, test_features):
    svc = LinearSVC(dual=False, C=3)
    svc.fit(train_features, train_labels)
    return svc.predict(test_features)

"""
def read_gt(gt_dir):
    fgt = open(join(gt_dir, 'gt.csv'))
    next(fgt)
    lines = fgt.readlines()

    filenames = []
    labels = zeros(len(lines))
    for i, line in enumerate(lines):
        filename, label = line.rstrip('\n').split(',')
        filenames.append(filename)
        labels[i] = int(label)

    return filenames, labels


def extract_features(path, filenames):
    hog_length = len(extract_hog(imread(join(path, filenames[0]))))
    data = zeros((len(filenames), hog_length))
    for i in range(0, len(filenames)):
        filename = join(path, filenames[i])
        data[i, :] = extract_hog(imread(filename))
    return data


def best_params_svm(train_features, train_labels):
    svc = LinearSVC(dual = False)
    params = {'C': [0.5, 1., 1.5, 0.2, 0.8, 2., 3.], 'penalty': ['l1', 'l2']}
    search = RandomizedSearchCV(svc, params, n_iter=4, n_jobs=-1, cv=5, scoring='accuracy')
    search.fit(train_features, train_labels)
    return search.best_params_


def main():
    data_dir = 'test/00_input'
    train_dir = join(data_dir, 'train')
    train_filenames, train_labels = read_gt(train_dir)
    train_features = extract_features(train_dir, train_filenames)
    print(best_params_svm(train_features, train_labels))

"""
def main():
    im = imread('00090.png')
    kek = extract_hog(im)
    print(len(kek))


#main()