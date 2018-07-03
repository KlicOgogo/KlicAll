#include "widget.h"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <climits>

const double PARAM_PERC = 0.9;
const double TEST_PERC = 0.05;

typedef std::vector<double> Object;

Object read_object(const std::string &line) {
    Object obj;
    std::stringstream in(line);
    double a;
    while (in >> a) {
        obj.emplace_back(a);
    }
    return obj;
}

std::vector<std::string> read_test_data(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> data;
    while(std::getline(file, line)) {
        data.emplace_back(line);
    }
    std::vector<std::string> test_data;
    for (int i = data.size() * (1. - TEST_PERC); i < data.size(); ++i) {
        test_data.emplace_back(data[i]);
    }
    return test_data;
}

std::vector<Object> read_data(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Object> data;
    while (std::getline(file, line)) {
        data.emplace_back(read_object(line));
    }
    return data;
}

std::vector<Object> get_train(const std::vector<Object> &data) {
    std::vector<Object> train;
    for (int i = data.size() * PARAM_PERC; i < data.size() * (1. - TEST_PERC); ++i) {
        train.emplace_back(data[i]);
    }
    return train;
}

std::vector<Object> get_param(const std::vector<Object> &data) {
    std::vector<Object> param;
    for (int i = 0; i < data.size() * PARAM_PERC; ++i) {
        param.emplace_back(data[i]);
    }
    return param;
}

double distance(Object a, Object b) {
    assert(a.size() == b.size());
    double dist = 0;
    for (int i = 0; i < a.size() - 1; ++i) {
        dist += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(dist);
}

std::vector<double> get_dist_vector(const Object &obj, const std::vector<Object> &param) {
    std::vector<double> dist(param.size());
    for (int i = 0; i < param.size(); ++i) {
        dist[i] = distance(obj, param[i]);
    }
    return dist;
}

std::vector<std::vector<double>> get_dist_matrix(const std::vector<Object> &train,
                                                 const std::vector<Object> &param) {
    std::vector<std::vector<double>> dist_matrix(train.size());
    for (int i = 0; i < train.size(); ++i) {
        dist_matrix[i] = get_dist_vector(train[i], param);
    }
    return dist_matrix;
}

std::unordered_map<double, int> get_indices(const std::vector<Object> &data) {
    size_t n_features = data[0].size() - 1;
    std::unordered_map<double, int> indices;
    int index = 0;
    for (const auto &i : data) {
        if (indices.find(i[n_features]) == indices.end()) {
            indices[i[n_features]] = index++;
        }
    }
    return indices;
}
/*
std::vector<double> get_class_dist_vector(const std::vector<double> &dist_vector,
                                          const std::vector<Object> &param,
                                          std::unordered_map<double, int> indices) {
    size_t n_features = param[0].size() - 1;
    std::vector<double> class_dist_vector(indices.size());
    std::vector<int> counts(indices.size());
    for (int i = 0; i < dist_vector.size(); ++i) {
        int index = indices[param[i][n_features]];
        class_dist_vector[index] += dist_vector[i];
        ++counts[index];
    }
    for (int i = 0; i < counts.size(); ++i) {
        class_dist_vector[i] /= counts[i];
    }
    return class_dist_vector;
}
*/
std::vector<double> get_class_dist_vector(const std::vector<double> &dist_vector,
                                          const std::vector<Object> &param,
                                          std::unordered_map<double, int> indices) {
    size_t n_features = param[0].size() - 1;
    std::vector<double> class_dist_vector(indices.size(), std::numeric_limits<double>::max());
    for (int i = 0; i < dist_vector.size(); ++i) {
        int index = indices[param[i][n_features]];
        class_dist_vector[index] = std::min(dist_vector[i], class_dist_vector[index]);
    }
    return class_dist_vector;
}

std::vector<std::vector<double>> get_class_dist_matrix(const std::vector<std::vector<double> > &dist_matrix,
                                                       const std::vector<Object> &param,
                                                       const std::unordered_map<double, int> &indices) {
    std::vector<std::vector<double> > class_dist_matrix(dist_matrix.size());
    for (int i = 0; i < dist_matrix.size(); ++i) {
        class_dist_matrix[i] = get_class_dist_vector(dist_matrix[i], param, indices);
    }
    return class_dist_matrix;
}

std::unordered_map<int, double> get_classes(std::unordered_map<double, int> classes_indices) {
    std::unordered_map<int, double> classes;
    for (auto &classes_index : classes_indices) {
        classes[classes_index.second] = classes_index.first;
    }
    return classes;
}

double predict(const std::vector<double> &class_dist_vector,
                            std::unordered_map<int, double> classes) {
    double min_dist = class_dist_vector[0];
    int min_dist_index = 0;
    for (int i = 1; i < class_dist_vector.size(); ++i) {
        if (min_dist > class_dist_vector[i]) {
            min_dist = class_dist_vector[i];
            min_dist_index = i;
        }
    }
    return classes[min_dist_index];
}

std::vector<double> train_predict(const std::vector<std::vector<double> > &class_dist_matrix,
                                  const std::unordered_map<int, double> &classes) {
    std::vector<double> predictions(class_dist_matrix.size());
    for (int i = 0; i < class_dist_matrix.size(); ++i) {
        predictions[i] = predict(class_dist_matrix[i], classes);
    }
    return predictions;
}

double get_true_label(const Object &obj) {
    return obj[obj.size() - 1];
}

std::vector<double> get_true_labels(const std::vector<Object> &data) {
    std::vector<double> true_labels(data.size());
    for (int i = 0; i < data.size(); ++i) {
        true_labels[i] = get_true_label(data[i]);
    }
    return true_labels;
}

double count_accuracy(const std::vector<double> &y_true, const std::vector<double> &y_pred) {
    assert(y_true.size() == y_pred.size());
    double count = 0;
    for (int i = 0; i < y_true.size(); ++i) {
        if (y_true[i] == y_pred[i]) {
            ++count;
        }
    }
    return count / y_true.size();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    std::string filename = "glass2.txt";
    auto data = read_data(filename);
    auto train = get_train(data);
    auto param = get_param(data);
    auto dist_matrix = get_dist_matrix(train, param);
    auto indices = get_indices(data);
    auto class_dist_matrix = get_class_dist_matrix(dist_matrix, param, indices);
    auto y_pred = train_predict(class_dist_matrix, get_classes(indices));
    auto y_true = get_true_labels(train);
    auto train_score =  count_accuracy(y_true, y_pred);
    std::cout << train_score << std::endl;
    auto test_data = read_test_data(filename);
    QStringList items;
    for (auto it = test_data.begin(); it != test_data.end(); ++it) {
        items << QString((*it).c_str());
    }
    std::string quit_string = "Quit";
    items << QString(quit_string.c_str());
    bool ok;
    while(true) {
        QString item = QInputDialog::getItem(&w, "Choosing an object",
                                                "Choose a test object or quit:", items, 0, false, &ok);
        std::string object;
        if (ok && !item.isEmpty())
               object = item.toStdString();
        if (object == "Quit") {
            break;
        }
        Object obj = read_object(object);
        auto dist_vector = get_dist_vector(obj, param);
        auto class_dist_vector = get_class_dist_vector(dist_vector, param, indices);
        double pred = predict(class_dist_vector, get_classes(indices));
        QMessageBox box;
        box.setText(("Predicted class of chosen object: " + std::to_string((int)pred)).c_str());
        box.exec();
    }
    w.close();
    return a.exec();
}
