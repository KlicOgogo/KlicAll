#ifndef REMOVE_COPY_IF_H
#define REMOVE_COPY_IF_H

namespace mystd {
template <typename It, typename Out, typename Pred>
Out remove_copy_if(It first, It last, Out out, Pred f) {
    while (first != last) {
        if (!f(*first)) {
            *out = *first;
            out++;
        }
        first++;
    }
    return out;
}

template <typename It, typename Pred>
bool any_of(It first, It last, Pred f) {
    while (first != last) {
        if (f(*first)) {
            return true;
        }
        first++;
    }
    return false;
}

template <typename It>
It unique(It first, It last) {
    if (first == last) {
        return last;
    }
    It temp = first;
    first++;
    while (first != last) {
        if (*first != *temp) {
          temp++;
          *temp = std::move(*first);
        }
        first++;
    }
    return ++temp;
}

template <typename It, typename Out>
Out reverse_copy(It first, It last, Out out) {
    last--;
    while (first != last) {
        *out = *last;
        last--;
        out++;
    }
    *out = *first;
    out++;
    return out;
}

template <typename It1, typename It2, typename Out>
Out set_difference(It1 first1, It1 last1, It2 first2, It2 last2, Out out) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 > *first2) {
            first2++;
        } else if (*first1 < *first2) {
            *out = *first1;
            first1++;
            out++;
        } else {
            first1++;
            first2++;
        }
    }
    while (first1 != last1) {
        *out = *first1;
        *out++;
        *first1++;
    }
    return out;
}

}

#endif

