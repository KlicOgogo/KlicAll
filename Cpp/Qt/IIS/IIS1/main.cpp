#include <QInputDialog>
#include <QMessageBox>
#include "widget.h"
#include <QApplication>
#include <QString>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <stack>

std::vector<std::string> read_data(const std::string &filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

std::vector<std::vector<std::string>> get_rule_lines(const std::vector<std::string> &lines) {
    std::vector<std::vector<std::string>> all_rules;
    int i = 0;
    std::vector<std::string> temp;
    while (!lines[i].empty()) {
        if (lines[i] != "----------") {
            temp.emplace_back(lines[i]);

        } else {
            all_rules.emplace_back(temp);
            temp.clear();
        }
        ++i;
    }
    return all_rules;
}

std::unordered_map<std::string, std::string> get_questions(const std::vector<std::string> &lines) {
    int i = 0;
    while (!lines[i].empty()) {
        ++i;
    }
    std::unordered_map<std::string, std::string> questions;
    for (int j = i+1; j < lines.size(); j += 2) {
        questions[lines[j]] = lines[j+1];
    }
    return questions;
}

class Feature {
public:
    Feature() = default;
    Feature(std::string name,
            std::string value): name_(std::move(name)),
                                        value_(std::move(value)) {}
    std::string get_name() const {
        return name_;
    }
    std::string get_value() const {
        return value_;
    }
private:
    std::string name_;
    std::string value_;
};

class Rule {
public:
    Rule() = default;

    explicit Rule(const std::vector<std::string> &rule_lines) {
        for (int i = 0; i < rule_lines.size(); i += 2) {
            if (rule_lines[i] != "-----") {
                features.emplace_back(Feature(rule_lines[i], rule_lines[i+1]));
            } else {
                purpose = Feature(rule_lines[i+1], rule_lines[i+2]);
                break;
            }
        }

    }
    std::string get_name() const {
        return purpose.get_name();
    }
    std::string get_value() const {
        return purpose.get_value();
    }
    std::vector<Feature>& get_features() {
        return features;
    }
private:
    Feature purpose;
    std::vector<Feature> features;
};

std::vector<Rule> get_rules(const std::vector<std::vector<std::string>> &all_rules) {
    std::vector<Rule> rules(all_rules.size());
    for (int i = 0; i < all_rules.size(); ++i) {
        rules[i] = Rule(all_rules[i]);
    }
    return rules;
}

int analyse_rule(Rule rule, std::unordered_map<std::string, std::string> answers, size_t &index) {
    size_t j = 0;
    for (auto &i : rule.get_features()) {
        if (answers.find(i.get_name()) == answers.end()) {
            index = j;
            return -1;
        } else {
            if (answers[i.get_name()] != i.get_value()) {
                return 0;
            }
        }
        ++j;
    }
    return 1;
}

void data_analyser(const std::string &filename, Widget *w) {
    auto lines = read_data(filename);
    auto ques = get_questions(lines);
    auto rules = get_rules(get_rule_lines(lines));
    std::unordered_map<std::string, std::unordered_set<std::string> > probable_answers;
    std::unordered_set<std::string> purposes;
    for (auto &rule : rules) {
        purposes.insert(rule.get_name());
        for (auto &j : rule.get_features()) {
            if (ques.find(j.get_name()) != ques.end()) {
                probable_answers[j.get_name()].insert(
                        j.get_value());
            }
        }
    }
    QStringList items;
    for (auto it = purposes.begin(); it != purposes.end(); ++it) {
        items << QString((*it).c_str());
    }
    bool ok;
    QString item = QInputDialog::getItem(w, "QInputDialog::getItem()",
                                            "Purpose:", items, 0, false, &ok);
    std::string purpose;
    if (ok && !item.isEmpty())
           purpose = item.toStdString();
    std::unordered_map<std::string, std::string> answers;
    std::unordered_set<int> non_false_indices;
    for (int i = 0; i < rules.size(); ++i) {
        non_false_indices.insert(i);
    }
    std::stack<std::string> purpose_stack;
    purpose_stack.push(purpose);
    bool bool_feature = false;
    while (!bool_feature) {
        int rule_num = -1;
        size_t index;
        std::vector<int> to_erase;
        for (auto it = non_false_indices.begin(); it != non_false_indices.end(); ++it) {
            if (rules[*it].get_name() == purpose_stack.top()) {
                int val = analyse_rule(rules[*it], answers, index);
                if (val == 1) {
                    answers[rules[*it].get_name()] = rules[*it].get_value();
                    purpose_stack.pop();
                    if (purpose_stack.empty()) {
                        bool_feature = true;
                    }
                    rule_num = *it;
                    break;
                } else if (val == -1) {
                    purpose_stack.push(rules[*it].get_features()[index].get_name());
                    rule_num = *it;
                    break;
                } else {
                    if (non_false_indices.find(*it) != non_false_indices.end()) {
                        to_erase.push_back(*it);
                    }
                }
            }
        }
        for (int i : to_erase) {
            non_false_indices.erase(i);
        }
        if (rule_num == -1) {
            if (ques.find(purpose_stack.top()) != ques.end()) {
                QStringList items;
                for (auto it = probable_answers[purpose_stack.top()].begin(); it != probable_answers[purpose_stack.top()].end(); ++it) {
                    items << QString((*it).c_str());
                }
                QString item = QInputDialog::getItem(w, "QInputDialog::getItem()",
                                                        ques[purpose_stack.top()].c_str(), items, 0, false, &ok);
                std::string answer;
                if (ok && !item.isEmpty())
                       answer = item.toStdString();
                answers[purpose_stack.top()] = answer;
                purpose_stack.pop();
            } else {
                bool_feature = true;
            }
        }
    }
    std::string result;
    if (answers.find(purpose) != answers.end()) {
        result = answers[purpose];
    } else {
        result = "Purpose can not be reached";
    }
    QMessageBox box;
    box.setText(result.c_str());
    box.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    data_analyser("data2.txt", &w);
    w.show();
    return a.exec();
}
