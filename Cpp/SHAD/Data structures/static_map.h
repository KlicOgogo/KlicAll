#include <algorithm>
#include <vector>
#include <string>
#include <utility>

#ifndef STATIC_MAP_H
#define STATIC_MAP_H

bool pred_equal(std::pair<std::string, std::string> p1,
           std::pair<std::string, std::string> p2) {
    return (p1.first == p2.first);
}

bool pred_less(std::pair<std::string, std::string> p1,
           std::pair<std::string, std::string> p2) {
    return (p1.first < p2.first);
}

class StaticMap {
 public:
    explicit StaticMap(const std::vector<std::pair<std::string,
                       std::string> >& items);

    bool Find(const std::string& key, std::string* value) const;

 private:
    std::vector<std::pair<std::string, std::string>> items_;
};

StaticMap::StaticMap(const std::vector<std::pair<std::string,
                     std::string> >& items) {
    items_.clear();
    for (auto it = items.begin(); it != items.end(); it++) {
        items_.push_back(*it);
    }
    std::sort(items_.begin(), items_.end());
    std::unique(items_.begin(), items_.end(), pred_equal);
}

bool StaticMap::Find(const std::string &key,
                     std::string *value) const {
    auto it = std::lower_bound(items_.begin(),
items_.end(), make_pair(key, ""), pred_less);
    if (it == items_.end())
        return false;
    if (it->first == key) {
        *value = it->second;
        return true;
    } else {
        return false;
    }
}

#endif
