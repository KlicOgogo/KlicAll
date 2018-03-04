from collections import Counter, defaultdict
import numpy as np


def train_hmm(tagged_sents):
    alpha=1e-24
    counter_tag = Counter()
    counter_tag_tag = Counter()
    counter_tag_word = Counter()
    tags = set()
    words = set()
    p_t_t = defaultdict(dict)
    p_w_t = defaultdict(dict)
    pt = dict()
    for tagged_sent in tagged_sents:
        i = 0
        for tagged_word in tagged_sent:
            words.add(tagged_word[0])
            tags.add(tagged_word[1])
            counter_tag_word[tuple(tagged_word)] += 1
            counter_tag[tagged_word[1]] += 1
            if i < len(tagged_sent) - 1:
                counter_tag_tag[(tagged_sent[i][1], tagged_sent[i+1][1])] += 1
            i += 1
    for tag in tags:
        p_t_t[tag] = defaultdict(float)
        p_w_t[tag] = defaultdict(float)
        pt[tag] = 1. / len(tags)
    for (prev, cur), count in counter_tag_tag.items():
        p_t_t[prev][cur] = (count + alpha) / (counter_tag[prev] + alpha * len(tags))
    for (word, tag), count in counter_tag_word.items():
        p_w_t[tag][word] = (count + alpha) / (counter_tag[tag] + alpha * (len(tags) + len(words)))
    return pt, p_w_t, p_t_t


def viterbi_algorithm(test_tokens_list, p_t, p_w_t, p_t_t):
    pos = list(p_t.keys())
    s = np.zeros([len(p_t), len(test_tokens_list)], dtype=np.int)
    delta = np.zeros([len(p_t), len(test_tokens_list)])
    for i in range(len(p_t)):
        delta[i][0] = np.log(max(10 ** (-100), p_t[pos[i]])) + \
                      np.log(max(10 ** (-100), p_w_t[pos[i]][test_tokens_list[0]]))
    for i in range(1, len(test_tokens_list)):
        for j in range(delta.shape[0]):
            delta[j][i] = -10 ** 49
            for k in range(delta.shape[0]):
                cur_proba = delta[k][i-1] + np.log(max(p_t_t[pos[k]][pos[j]], 10 ** (-100))) + \
                            np.log(max(10 ** (-100), p_w_t[pos[j]][test_tokens_list[i]]))
                if delta[j][i] < cur_proba:
                    delta[j][i] = cur_proba
                    s[j][i] = k
    x = np.argmax(delta[:, delta.shape[1] - 1:])
    result = []
    result.append(pos[x])
    for i in range(1, delta.shape[1]):
        x = s[x][s.shape[1] - i]
        result.append(pos[x])
    return list(reversed(result))
