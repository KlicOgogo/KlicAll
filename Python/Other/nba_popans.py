names = {1: 'Klicunou', 4: 'Dzeikun',
         3: 'Ulasevich', 2: 'Shlyahov', 5: 'real'}

print_names = {1: 'Klicunou', 4: 'Dzeikun',
               3: 'Ulasevich', 2: 'Shlyahov', 5: 'real'}


def count_daily_stats():
    bets = []
    for i in range(1, len(names) + 1):
        bets.append([line.strip().split(' ')[-1][-1] for line in open(names[i] + '.txt', 'r')])
    res = []
    for i in range(len(names) - 1):
        corr = 0
        wr = 0
        for j in range(len(bets[i])):
            if bets[i][j] == bets[-1][j]:
                corr += 1
            else:
                wr += 1
        res.append([corr, wr])
    return res


def print_daily_stats(stats):
    print('Daily stats:')
    for i in range(len(stats)):
        print(print_names[i + 1] + ': ' + str(stats[i][0]) + '+ ' + str(stats[i][1]) + '-')
    print(' ')


def add_daily_to_global(daily_stats):
    global_stats = []
    for i in range(len(daily_stats)):
        file = open(names[i+1] + '_res.txt', 'r')
        global_stats.append(file.read().strip().split(' '))
    updated_res = [[int(global_stats[i][j]) + daily_stats[i][j] for j in range(2)]
                   for i in range(len(global_stats))]
    return updated_res


def print_and_write_global_stats(global_stats):
    print('Overall:')
    for i in range(len(global_stats)):
        print(print_names[i + 1] + ': ' + str(global_stats[i][0]) + '+ ' +
              str(global_stats[i][1]) + '-')
        file = open(names[i+1] + '_res.txt', 'w')
        file.write(str(global_stats[i][0]) + ' ' + str(global_stats[i][1]))


def reset_global_stats():
    for i in range(len(names)-1):
        file = open(names[i + 1] + '_res.txt', 'w')
        file.write('0 0')


def main():
    #reset_global_stats()
    daily_res = count_daily_stats()
    print_daily_stats(daily_res)
    upd_res = add_daily_to_global(daily_res)
    print_and_write_global_stats(upd_res)


main()
