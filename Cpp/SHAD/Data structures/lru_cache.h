#include <string>
#include <list>
#include <unordered_map>

#ifndef LRU_CACHE_H
#define LRU_CACHE_H

class LruCache {
 public:
    LruCache(size_t max_size): max_size_(max_size) {}

    void Set(const std::string& key, const std::string& value) {
        if (map.size() < max_size_) {
            map[key] = value;
            if (iters.find(key) != iters.end()) {
                list.erase(iters[key]);
            }
            list.push_back(key);
            iters[key] = --list.end();
        } else {
            std::string str = list.front();
            map.erase(str);
            list.pop_front();
            iters.erase(str);
            Set(key, value);
        }
    }

    bool Get(const std::string& key, std::string* value) {
        if (map.find(key) != map.end()) {
            *value = map[key];
            list.erase(iters[key]);
            list.push_back(key);
            iters[key] = --list.end();
            return true;
        } else {
        return false;
        }
    }

 private:
    std::unordered_map<std::string, std::string> map;
    std::unordered_map<std::string, std::list<std::string>::iterator> iters;
    std::list<std::string> list;
    size_t max_size_;
};

#endif

