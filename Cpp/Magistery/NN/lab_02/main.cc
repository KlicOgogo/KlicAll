#include <cassert>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>


using Matrix = std::vector<std::vector<float>>;
using Vector = std::vector<float>;

float sigmoid(float x, bool back=false) {
	if (back) {
		return x * (1.0f - x);
	}
	return 1.0f / (1.0f + std::exp(-x));
}

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


struct PerceptroneLayer final {
	PerceptroneLayer(int input_len, int output_len) {
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
		limits.resize(output_len);
		for (int i = 0; i < limits.size(); ++i) {
			limits[i] = distribution(generator);
		}
	}

	Vector forward(const Vector& x) {
		const auto dot_result = dot_product(transpose(weights), x);
		auto result = vector_sum(dot_result, limits);
		for (int i = 0; i < result.size(); ++i) {
			result[i] = sigmoid(result[i]);
		}
		return result;
	}

	Vector backward(float alpha, const Vector& error_deriv, const Vector& curr_layer_out, const Vector& prev_layer_out) {
		assert(error_deriv.size() == curr_layer_out.size());
		Vector limits_delta = curr_layer_out;
		for (int i = 0; i < limits_delta.size(); ++i) {
			limits_delta[i] *= error_deriv[i] * (1.0f - limits_delta[i]);
		}
		const auto next_error_deriv = dot_product(weights, limits_delta);

		for (int i = 0; i < limits_delta.size(); ++i) {
			limits[i] += alpha * limits_delta[i];
			for (int j = 0; j < prev_layer_out.size(); ++j) {
				weights[j][i] += alpha * limits_delta[i] * prev_layer_out[j];
			}
		}
		return next_error_deriv;
	}

	Matrix weights;
	Vector limits;
};

struct TwoLayerPerceptrone final {
	TwoLayerPerceptrone(int input_len, int hidden_len, int output_len)
		: first_layer(input_len, hidden_len), second_layer(hidden_len, output_len) {}

	std::vector<Vector> forward(const Vector& x) {
		std::vector<Vector> result(2);
		result[0] = first_layer.forward(x);
		result[1] = second_layer.forward(result[0]);
		return result;
	}

	Vector backward(float alpha, const std::vector<Vector>& forward_outputs, 
					const Vector& true_output, const Vector& input) {
		Vector error_deriv(true_output.size());
		for (int i = 0; i < true_output.size(); ++i) {
			error_deriv[i] = true_output[i] - forward_outputs[1][i];
		}
		auto first_layer_error_deriv = second_layer.backward(alpha, error_deriv, forward_outputs[1], forward_outputs[0]);
		auto garbage = first_layer.backward(alpha, first_layer_error_deriv, forward_outputs[0], input);
		return error_deriv;
	}

	Vector train_iteration(float alpha, const Vector& true_output, const Vector& input) {
		const auto outputs = forward(input);
		const auto error = backward(alpha, outputs, true_output, input);
		return error;
	}

	PerceptroneLayer first_layer;
	PerceptroneLayer second_layer;
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

float max_abs(const Vector& v) {
	Vector vv(v.size());
	for (int j = 0; j < v.size(); ++j) {
		vv[j] = std::abs(v[j]);
	}
	return *std::max_element(vv.begin(), vv.end());
}

int main() {
	const auto images = read_images();
	print(images);
	const auto flatten_images = flatten(images);
	const Matrix true_outputs = {
		{1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 
		{0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, 
		{0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f, 1.0f}
	};
	TwoLayerPerceptrone nn(flatten_images[0].size(), 300, true_outputs[0].size());
	const float error_limit = 0.005;
	Vector err;
	auto indexes = random_index_permutation(flatten_images.size());
	for (int index : indexes) {
		err = nn.train_iteration(0.01, true_outputs[index], flatten_images[index]);
	}
	int n_iter = 1;
	while (max_abs(err) > error_limit) {
		auto indexes = random_index_permutation(flatten_images.size());
		for (int index : indexes) {
			err = nn.train_iteration(0.01, true_outputs[index], flatten_images[index]);
		}
		++n_iter;
		if (n_iter % 1000 == 0) {
			std::cout << max_abs(err) << '\n';
		}
	}

	std::cout << "Train iterations mumber: " << n_iter << '\n'; 

	std::vector<Vector> test_set(3 * flatten_images.size());
	for (int i = 0; i < flatten_images.size(); ++i) {
		test_set[i * 3 + 0] = image_with_noise(flatten_images[i], 0.0);
		test_set[i * 3 + 1] = image_with_noise(flatten_images[i], 0.2);
		test_set[i * 3 + 2] = image_with_noise(flatten_images[i], 0.4);
	}

	const auto test_set_unflatten = unflatten(test_set, 6, 6);
	for (int i = 0; i < test_set.size(); ++i) {
		std::vector<Matrix> imgs(1);
		imgs[0] = test_set_unflatten[i];
		print(imgs);
		std::cout << "Probabilities: ";
		const auto res = nn.forward(test_set[i]);
		for (int i = 0; i < res[1].size(); ++i) {
			std::cout << res[1][i] << ' ';
		}
		std::cout << "\n";
	}
	return 0;
}