# -*- coding: utf-8


def bootstrap(X, Y, corpus, context_size=3):
    def common_back(list1, list2):
        result = []
        for i in range(min(len(list1), len(list2))):
            if list1[-1 - i] != list2[-1 - i]:
                break
            else:
                result.append(list1[-1 - i])
        return list(reversed(result))

    def common_front(list1, list2):
        result = []
        for i in range(min(len(list1), len(list2))):
            if list1[i] != list2[i]:
                break
            else:
                result.append(list1[i])
        return result

    result = set()
    indices = dict()

    def part(X, Y):
        result.add((X, Y))
        xy_left = dict()
        xy_right = dict()
        sents = []
        for l in range(len(corpus)):
            words = corpus[l].split(' ')
            sents.append(words)
            x_ind = []
            y_ind = []
            for i in range(len(words)):
                if words[i] == X:
                    x_ind.append(i)
                if words[i] == Y:
                    y_ind.append(i)
            if len(x_ind) > 0 and len(y_ind) > 0:
                if y_ind[-1] >= x_ind[-1] and x_ind[0] >= y_ind[0]:
                    xs = y_ind[0]
                    ys = y_ind[-1]
                    key = tuple(words[xs + 1:ys])
                    if key not in xy_left:
                        xy_left[key] = words[max(0, xs - context_size):xs]
                    else:
                        xy_left[key] = common_back(xy_left[key], words[max(0, xs - context_size):xs])
                    if key not in xy_right:
                        xy_right[key] = words[ys + 1:min(len(words), ys + context_size + 1)]
                    else:
                        xy_right[key] = common_front(xy_right[key],
                                                     words[ys + 1:min(len(words), 1 + ys + context_size)])
                    key = tuple(reversed(words[xs + 1:ys]))
                    if key not in xy_right:
                        xy_right[key] = list(reversed(words[max(0, ys - context_size):ys]))
                    else:
                        xy_right[key] = common_front(xy_right[key],
                                                     list(reversed(words[max(0, ys - context_size):ys])))
                    if key not in xy_left:
                        xy_left[key] = list(reversed(words[1 + xs:min(len(words), 1 + xs + context_size)]))
                    else:
                        xy_left[key] = common_back(xy_left[key],
                                                   list(reversed(words[1 + xs:min(len(words), 1 + xs + context_size)])))
                elif  y_ind[-1] >= x_ind[-1] and x_ind[0] < y_ind[0]:
                    xs = x_ind[0]
                    ys = y_ind[-1]
                    key = tuple(words[xs + 1:ys])
                    if key not in xy_left:
                        xy_left[key] = words[max(0, xs - context_size):xs]
                    else:
                        xy_left[key] = common_back(xy_left[key], words[max(0, xs - context_size):xs])
                    if key not in xy_right:
                        xy_right[key] = words[ys + 1:min(len(words), ys + context_size + 1)]
                    else:
                        xy_right[key] = common_front(xy_right[key],
                                                     words[ys + 1:min(len(words), 1 + ys + context_size)])
                elif x_ind[0] < y_ind[0]:
                    xs = x_ind[0]
                    ys = x_ind[-1]
                    key = tuple(words[xs + 1:ys])
                    if key not in xy_left:
                        xy_left[key] = words[max(0, xs - context_size):xs]
                    else:
                        xy_left[key] = common_back(xy_left[key], words[max(0, xs - context_size):xs])
                    if key not in xy_right:
                        xy_right[key] = words[ys + 1:min(len(words), ys + context_size + 1)]
                    else:
                        xy_right[key] = common_front(xy_right[key],
                                                     words[ys + 1:min(len(words), 1 + ys + context_size)])
                    key = tuple(reversed(words[xs + 1:ys]))
                    if key not in xy_right:
                        xy_right[key] = list(reversed(words[max(0, ys - context_size):ys]))
                    else:
                        xy_right[key] = common_front(xy_right[key],
                                                     list(reversed(words[max(0, ys - context_size):ys])))
                    if key not in xy_left:
                        xy_left[key] = list(reversed(words[1 + xs:min(len(words), 1 + xs + context_size)]))
                    else:
                        xy_left[key] = common_back(xy_left[key],
                                                   list(reversed(words[1 + xs:min(len(words), 1 + xs + context_size)])))
                else:
                    xs = y_ind[0]
                    ys = x_ind[-1]
                    key = tuple(reversed(words[xs + 1:xs]))
                    if key not in xy_right:
                        xy_right[key] = list(reversed(words[max(0, ys - context_size):ys]))
                    else:
                        xy_right[key] = common_front(xy_right[key],
                                                     list(reversed(words[max(0, ys - context_size):ys])))
                    if key not in xy_left:
                        xy_left[key] = list(reversed(words[1 + xs:min(len(words), 1 + xs + context_size)]))
                    else:
                        xy_left[key] = common_back(xy_left[key],
                                                   list(reversed(words[1 + xs:min(len(words), 1 + xs + context_size)])))
            for key in xy_left.keys():
                key_len = len(key)
                for i in range(len(sents)):
                    for j in range(0, len(sents[i]) - key_len+1):
                        if tuple(sents[i][j:j+key_len]) == key or tuple(sents[i][j:j+key_len]) == tuple(reversed(key)):
                            if key not in indices:
                                indices[key] = {(i, j)}
                            else:
                                indices[key].add((i, j))
        for key in xy_left.keys():
            for ind in indices[key]:
                if list(key) == sents[ind[0]][ind[1]:ind[1] + len(key)] and \
                                xy_left[key] == sents[ind[0]][ind[1]-1 - len(xy_left[key]):ind[1]-1] and \
                                xy_right[key] == sents[ind[0]][ind[1] + len(key) + 1:ind[1] + len(key) + 1 + len(xy_right[key])]:
                    if (sents[ind[0]][ind[1]-1], sents[ind[0]][ind[1] + len(key)]) not in result and \
                                    (sents[ind[0]][ind[1] + len(key)], sents[ind[0]][ind[1] - 1]) not in result:
                        part(sents[ind[0]][ind[1]-1], sents[ind[0]][ind[1] + len(key)])
                if list(key) == list(reversed(sents[ind[0]][ind[1]:ind[1] + len(key)])) and \
                                xy_right[key] == list(reversed(sents[ind[0]][ind[1]-1 - len(xy_left[key]):ind[1]-1])) and \
                                xy_left[key] == list(reversed(sents[ind[0]][ind[1] + len(key) + 1:ind[1] + len(key) + 1 + len(xy_right[key])])):
                    if (sents[ind[0]][ind[1] + len(key)], sents[ind[0]][ind[1]-1]) not in result and \
                            (sents[ind[0]][ind[1] - 1], sents[ind[0]][ind[1] + len(key)]) not in result:
                        part(sents[ind[0]][ind[1] + len(key)], sents[ind[0]][ind[1]-1])

    part(X, Y)
    return result

def main():
    kek = (1,2,3)
    print(tuple(reversed(kek)))



print(bootstrap(X = "Пушкин",
            Y = "поэт",
            corpus = [
                "Александр Сергеевич Пушкин - великий русский поэт - родился в 1799 году",
                "В 1799 году здесь родился Александр Сергеевич Пушкин - великий русский поэт XIX века",
                "Александр Сергеевич Грибоедов - великий русский драматург и дипломат",
                "Михаил Юрьевич Лермонтов - великий русский поэт - родился в 1814 году",
            ]))