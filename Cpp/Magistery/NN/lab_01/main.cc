#include <cassert>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
using Vector = std::vector<int>;

std::vector<Matrix> read_images() {
	const char* const images_path_list[3] = {"v.txt", "l.txt", "t.txt"};
	std::vector<Matrix> all_images;
	for (const char* image_path : images_path_list) {
		std::ifstream image_fs(image_path);
		int n, m;
		image_fs >> m >> n;
		Matrix im(m, Vector(n));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				image_fs >> im[i][j];
			}
		}
		all_images.push_back(im);
	}
	return all_images;
}

std::vector<Vector> flatten(const std::vector<Matrix>& images) {
	std::vector<Vector> flatten_images(images.size(), Vector(images[0].size() * images[0][0].size()));
	for (int k = 0; k < images.size(); ++k) {
		for (int i = 0; i < images[k].size(); ++i) {
			for (int j = 0; j < images[k][i].size(); ++j) {
				flatten_images[k][i * images[k][i].size() + j] = images[k][i][j];
			}
		}
	}
	return flatten_images;
}

Matrix leard_nn(const std::vector<Vector>& flatten_images) {
	Matrix result(flatten_images[0].size(), Vector(flatten_images[0].size()));
	for (const auto& im : flatten_images) {
		for (int i = 0; i < im.size(); ++i) {
			for (int j = 0; j < im.size(); ++j) {
				if (i != j) {
					result[i][j] += im[i] * im[j];
				}
			}
		}
	}
	return result;
}

Vector image_with_noise(const Vector& source_image, float noize_percentage) {
	Vector result = source_image;
	std::random_device device;
    std::default_random_engine generator(device());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	for (int i = 0; i < result.size(); ++i) {
		if (distribution(generator) < noize_percentage) {
			result[i] *= -1;
		}
	}
	return result;
}

std::vector<Matrix> unflatten(const std::vector<Vector>& flatten_images, int height, int width) {
	std::vector<Matrix> result(flatten_images.size(), Matrix(height, Vector(width)));
	for (int k = 0; k < flatten_images.size(); ++k) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				result[k][i][j] = flatten_images[k][i * width + j];
			}
		}
	}
	return result;
}


void print(const std::vector<Matrix>& images) {
	std::cout << images.size() << ' ' << images[0].size() << ' ' << images[0][0].size() << '\n';
	for (const auto& image : images) {
		for (int i = 0; i < image.size(); ++i) {
			for (int j = 0; j < image[i].size(); ++j) {
				if (image[i][j] == -1) {
					std::cout << ' ';
				} else if (image[i][j] == 1) {
					std::cout << image[i][j];
				} else {
					std::cout << 0;
				}
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}

int scalar_product(const Vector& v1, const Vector& v2) {
	assert(v1.size() == v2.size());
	int sum = 0;
	for (int i = 0; i < v1.size(); ++i) {
		sum += v1[i] * v2[i];
	}
	return sum;
}

int sgn(int x) {
	return x > 0 ? 1 : -1;
}

std::vector<int> random_index_permutation(int n) {
	std::vector<int> sample(n);
	for (int i = 0; i < n; ++i) {
		sample[i] = i;
	}

	std::random_device device;
    std::default_random_engine generator(device());
	std::vector<int> result(n);
	for (int i = 0; i < n; ++i) {
		std::uniform_int_distribution<> distribution(0, n - 1 - i);
		const auto index = distribution(generator);
		result[i] = sample[index];
		sample.erase(sample.begin() + index);
	}
	return result;
}

int main() {
	const auto images = read_images();
	const auto flatten_images = flatten(images);

	const auto nn = leard_nn(flatten_images);

	constexpr uint32_t kTests = 100;
	std::vector<int> stats(flatten_images.size() * 10);

	for (int test = 0; test < kTests; ++test) {

		std::vector<Vector> test_set(flatten_images.size() * 10);
		for (int i = 0; i < flatten_images.size(); ++i) {
			for (float perc = 0.1; std::abs(perc - 1.1) > 1e-5; perc += 0.1) {
				test_set[i * 10 + static_cast<int>(perc * 10) - 1] = image_with_noise(flatten_images[i], perc);
			}
		}

		if (test == 0) {
			const auto ts_unflatten = unflatten(test_set, 10, 10);
			print(ts_unflatten);
		}

		auto train_prev_state = test_set;
		auto train_next_state = test_set;

		for (int k = 0; k < train_next_state.size(); ++k) {
			auto indexes = random_index_permutation(train_next_state[k].size());
			for (int i : indexes) {
				auto nn_output = scalar_product(nn[i], train_next_state[k]);
				train_next_state[k][i] = sgn(nn_output);
			}
			while (!std::equal(train_prev_state.begin(), train_prev_state.end(), train_next_state.begin())) {
				train_prev_state[k] = train_next_state[k];
				indexes = random_index_permutation(train_next_state[k].size());
				for (int i : indexes) {
					auto nn_output = scalar_product(nn[i], train_next_state[k]);
					train_next_state[k][i] = sgn(nn_output);
				}
			}
			if (std::equal(train_next_state[k].begin(), train_next_state[k].end(), flatten_images[k / 10].begin())) {
				stats[k] += 1;
			}
		}

		if (test == 0) {
			auto result_unflatten = unflatten(train_prev_state, 10, 10);
			// print(result_unflatten);
		}
	}

	for (int i = 0; i < images.size(); ++i) {
		for (int j = 0; j < 10; ++j) {
			std::cout << stats[i * 10 + j] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}