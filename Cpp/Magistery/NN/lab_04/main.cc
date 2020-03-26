#include <cassert>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>


using Matrix = std::vector<std::vector<float>>;
using Vector = std::vector<float>;

Matrix transpose(const Matrix& m) {
	Matrix result(m[0].size(), Vector(m.size()));
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[0].size(); ++j) {
			result[j][i] = m[i][j];
		}
	}
	return result;
}

float scalar_product(const Vector& v1, const Vector& v2) {
	assert(v1.size() == v2.size());
	float sum = 0;
	for (int i = 0; i < v1.size(); ++i) {
		sum += v1[i] * v2[i];
	}
	return sum;
}

Vector dot_product(const Matrix& a, const Vector& b) {
	assert(a[0].size() == b.size());
	Vector result(a.size());
	for (int i = 0; i < a.size(); ++i) {
		result[i] = scalar_product(a[i], b);
	}
	return result;
}

Vector vector_sum(const Vector& a, const Vector& b) {
	assert(a.size() == b.size());
	Vector result(a.size());
	for (int i = 0; i < a.size(); ++i) {
		result[i] = a[i] + b[i];
	}
	return result;
}

void normalize(Matrix& m) {
	for (int j = 0; j < m[0].size(); ++j) {
		float sq_sum = 0;
		for (int i = 0; i < m.size(); ++i) {
			sq_sum += m[i][j] * m[i][j];
		}
		sq_sum = std::sqrt(sq_sum);
		for (int i = 0; i < m.size(); ++i) {
			m[i][j] /= sq_sum;
		}
	}
}

void normalize(Vector& v) {
	float sq_sum = 0;
	for (int i = 0; i < v.size(); ++i) {
		sq_sum += v[i] * v[i];
	}
	sq_sum = std::sqrt(sq_sum);
	for (int i = 0; i < v.size(); ++i) {
		v[i] /= sq_sum;
	}
}


int argmax(const Vector& v) {
	float max = v[0];
	float arg_max = 0;
	for (int i = 1; i < v.size(); ++i) {
		if (v[i] > max) {
			arg_max = i;
			max = v[i];
		}
	}
	return arg_max;
}

float euclidean_distance(const Vector& v1, const Vector& v2) {
	assert(v1.size() == v2.size());
	float dist = 0;
	for (int i = 0; i < v1.size(); ++i) {
		dist += (v1[i] - v2[i]) * (v1[i] - v2[i]);
	}
	return std::sqrt(dist);
}


struct SelfOrganizingNN {
	SelfOrganizingNN(int input_len, int output_len): win_counts(output_len, 1) {
		weights.resize(input_len);
		std::random_device device;
    	std::default_random_engine generator(device());
		std::uniform_real_distribution<double> distribution(-1.0, 1.0);
		for (int i = 0; i < input_len; ++i) {
			weights[i].resize(output_len);
			for (int j = 0; j < output_len; ++j) {
				weights[i][j] = distribution(generator);
			}
		}
		normalize(weights);
	}

	Vector forward(const Vector& x) {
		return dot_product(transpose(weights), x);
	}

	float backward(float beta, const Vector& x, const Vector& y_pred) {
		Vector metrics(y_pred.size());
		auto weights_t = transpose(weights);
		for (int i = 0; i < weights_t.size(); ++i) {
			metrics[i] = - static_cast<float>(win_counts[i]) * euclidean_distance(weights_t[i], x);
		}
		const auto best_neuron = argmax(metrics);
		++win_counts[best_neuron];

		for (int i = 0; i < weights.size(); ++i) {
			weights[i][best_neuron] += beta * (x[i] - weights[i][best_neuron]);
		}
		normalize(weights);

		weights_t = transpose(weights);
		const auto dist = euclidean_distance(x, weights_t[best_neuron]);
		return dist;
	}

	float train_iteration(float beta, const Vector& x) {
		const auto y_pred = forward(x);
		const auto error = backward(beta, x, y_pred);
		return error;
	}

	Matrix weights;
	std::vector<uint32_t> win_counts;
};



std::vector<Matrix> read_images() {
	const char* const images_path_list[5] = {"1.txt", "2.txt", "3.txt", "4.txt", "5.txt"};
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

Vector image_with_noise(const Vector& source_image, float noize_percentage) {
	Vector result = source_image;
	std::random_device device;
    std::default_random_engine generator(device());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	for (int i = 0; i < result.size(); ++i) {
		if (distribution(generator) < noize_percentage) {
			result[i] = 1 - result[i];
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
	// std::cout << images.size() << ' ' << images[0].size() << ' ' << images[0][0].size() << '\n';
	for (const auto& image : images) {
		for (int i = 0; i < image[0].size(); ++i) {
			std::cout << '_';
		}
		std::cout << '\n';
		for (int i = 0; i < image.size(); ++i) {

			for (int j = 0; j < image[i].size(); ++j) {
				if (image[i][j] == 0) {
					std::cout << ' ';
				} else if (image[i][j] == 1) {
					std::cout << image[i][j];
				} else {
					std::cout << 0;
				}
			}
			std::cout << "|\n";
		}
		// std::cout << '\n';
	}
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
	const Matrix true_outputs = {
		{1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 
		{0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, 
		{0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f, 1.0f}
	};

	SelfOrganizingNN nn(flatten_images[0].size(), flatten_images.size());
	// float sq_sum = 0;
	// for (int i = 0; i < nn.weights.size(); ++i) {
	// 	for (int j = 0; j < nn.weights[i].size(); ++j) {
	// 		sq_sum += nn.weights[i][j] * nn.weights[i][j];
	// 		std::cout << nn.weights[i][j] << ' ';
	// 	}
	// 	std::cout << '\n';
	// }

	auto train_set = flatten_images;
	for (int i = 0; i < train_set.size(); ++i) {
		normalize(train_set[i]);
	}

	const float error_limit = 0.005;
	const float beta = 0.01;
	float err = 0;
	auto indexes = random_index_permutation(train_set.size());
	for (int index : indexes) {
		const auto step_err = nn.train_iteration(beta, train_set[index]);
		err = std::max(err, step_err);
	}
	int n_iter = 1;
	while (err > error_limit) {
		auto indexes = random_index_permutation(train_set.size());
		err = 0;
		for (int index : indexes) {
			const auto step_err = nn.train_iteration(beta, train_set[index]);
			err = std::max(step_err, err);
		}
		++n_iter;
		if (n_iter % 1000 == 0) {
			std::cout << err << '\n';
			// if (n_iter % 10000 == 0) {
			// 	float sq_sum = 0;
			// 	for (int i = 0; i < nn.weights.size(); ++i) {
			// 		for (int j = 0; j < nn.weights[i].size(); ++j) {
			// 			sq_sum += nn.weights[i][j] * nn.weights[i][j];
			// 			std::cout << nn.weights[i][j] << ' ';
			// 		}
			// 		std::cout << '\n';
			// 	}
			// }
		}
	}

	std::cout << "Train iterations mumber: " << n_iter << '\n'; 

	std::vector<Vector> test_set(3 * flatten_images.size());
	for (int i = 0; i < flatten_images.size(); ++i) {
		test_set[i * 3 + 0] = image_with_noise(flatten_images[i], 0.0);
		normalize(test_set[i * 3 + 0]);
		test_set[i * 3 + 1] = image_with_noise(flatten_images[i], 0.2);
		normalize(test_set[i * 3 + 1]);
		test_set[i * 3 + 2] = image_with_noise(flatten_images[i], 0.4);
		normalize(test_set[i * 3 + 2]);
	}

	const auto test_set_unflatten = unflatten(test_set, 6, 6);
	for (int i = 0; i < test_set.size(); ++i) {
		std::vector<Matrix> imgs(1);
		imgs[0] = test_set_unflatten[i];
		print(imgs);
		std::cout << "Probabilities: ";
		const auto res = nn.forward(test_set[i]);
		for (int i = 0; i < res.size(); ++i) {
			std::cout << res[i] << ' ';
		}
		std::cout << "\n";
	}
	return 0;
}