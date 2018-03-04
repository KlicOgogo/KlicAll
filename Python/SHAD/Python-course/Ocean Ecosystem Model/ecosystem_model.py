import random


class Animal:
    def __init__(self, pregnancy_term):
        self._pregnancy_time = 0
        self._pregnancy_term = pregnancy_term

    def just_live(self):
        self._pregnancy_time += 1
        return

    def reproduce(self):
        self._pregnancy_time = 0
        return

    def ready_to_reproduce(self):
        return self._pregnancy_time >= self._pregnancy_term

    def __str__(self):
        return 'A'


class Victim(Animal):
    def __str__(self):
        return 'V'


class Predator(Animal):
    def __init__(self, pregnancy_term, hungriness_limit):
        super().__init__(pregnancy_term)
        self._hungriness_limit = hungriness_limit
        self._hungriness_count = 0

    def reproduce(self):
        self._hungriness_count += 1
        super().reproduce()

    def eat(self):
        self._hungriness_count = 0
        self.just_live()

    def just_live(self):
        self._hungriness_count += 1
        super().just_live()

    def will_die(self):
        return self._hungriness_count - 1 == self._hungriness_limit

    def __str__(self):
        return 'P'


class OceanEcosystemModel:
    def __init__(self, ocean_size, pregnancy_term_victim,
                 pregnancy_term_predator, hungriness_limit_predator):
        self._ocean = []
        self._is_made_move = []
        self._predators_count = 0
        self._victims_count = 0
        types_dict = {'_': '_',
                      '|': '|',
                      'V': Victim(pregnancy_term_victim),
                      'P': Predator(pregnancy_term_predator, hungriness_limit_predator)}
        for i in range(ocean_size):
            false_row = []
            ocean_row = []
            for j in range(ocean_size):
                false_row.append(False)
                type_of_cell = random.sample(['_', '_', '_', '_', '_',
                                              '_', '_', '_', '_', '_',
                                              '_', '|', 'V', 'V', 'V',
                                              'V', 'V', 'P', 'P', 'P'], 1)
                ocean_row.append(types_dict[type_of_cell[0]])
                if type_of_cell[0] == 'V':
                    self._victims_count += 1
                elif type_of_cell[0] == 'P':
                    self._predators_count += 1
            self._ocean.append(ocean_row)
            self._is_made_move.append(false_row)
        self._pregnancy_term_victim = pregnancy_term_victim
        self._pregnancy_term_predator = pregnancy_term_predator
        self._hungriness_limit_predator = hungriness_limit_predator

    def find_water(self, i, j):
        neighbors = []
        if j < len(self._ocean) - 1 and str(self._ocean[i][j + 1]) == '_':
            neighbors.append('right')
        if j > 0 and str(self._ocean[i][j - 1]) == '_':
            neighbors.append('left')
        if i > 0 and str(self._ocean[i - 1][j]) == '_':
            neighbors.append('up')
        if i < len(self._ocean) - 1 and str(self._ocean[i + 1][j]) == '_':
            neighbors.append('down')
        return neighbors

    def find_victims(self, i, j):
        neighbors = []
        if j < len(self._ocean) - 1 and str(self._ocean[i][j + 1]) == 'V':
            neighbors.append('right')
        if j > 0 and str(self._ocean[i][j - 1]) == 'V':
            neighbors.append('left')
        if i > 0 and str(self._ocean[i - 1][j]) == 'V':
            neighbors.append('up')
        if i < len(self._ocean) - 1 and str(self._ocean[i + 1][j]) == 'V':
            neighbors.append('down')
        return neighbors

    def predator_go(self, directions, i, j):
        self._is_made_move[i][j] = True
        if self._ocean[i][j].will_die():
            self._ocean[i][j] = '_'
            self._predators_count -= 1
            return
        self.victim_go(directions, i, j)

    def predator_eat(self, directions, i, j):
        self._is_made_move[i][j] = True
        self._ocean[i][j].eat()
        self._victims_count -= 1
        eat_dir = random.sample(directions, 1)
        dir_dict = {'right': [i, j + 1], 'left': [i, j - 1], 'up': [i - 1, j],
                    'down': [i + 1, j]}
        self._ocean[i][j], \
            self._ocean[dir_dict[eat_dir[0]][0]][dir_dict[eat_dir[0]][1]] = \
            self._ocean[dir_dict[eat_dir[0]][0]][dir_dict[eat_dir[0]][1]], \
            self._ocean[i][j]
        self._is_made_move[dir_dict[eat_dir[0]][0]][dir_dict[eat_dir[0]][1]] = True
        self._ocean[i][j] = '_'

    def predator_reproduce(self, directions, i, j):
        self._is_made_move[i][j] = True
        if self._ocean[i][j].will_die():
            self._ocean[i][j] = '_'
            self._predators_count -= 1
        else:
            self._ocean[i][j].reproduce()
        repr_dir = random.sample(directions, 1)
        dir_dict = {'right': [i, j + 1], 'left': [i, j - 1], 'up': [i - 1, j],
                    'down': [i + 1, j]}
        self._predators_count += 1
        self._ocean[dir_dict[repr_dir[0]][0]][dir_dict[repr_dir[0]][1]] = \
            Predator(self._pregnancy_term_predator,
                     self._hungriness_limit_predator)
        self._is_made_move[dir_dict[repr_dir[0]][0]][dir_dict[repr_dir[0]][1]] = True

    def victim_go(self, directions, i, j):
        self._is_made_move[i][j] = True
        self._ocean[i][j].just_live()
        directions.append('stay')
        go_dir = random.sample(directions, 1)
        dir_dict = {'right': [i, j + 1], 'left': [i, j - 1], 'up': [i - 1, j],
                    'down': [i + 1, j], 'stay': [i, j]}
        self._ocean[i][j], \
            self._ocean[dir_dict[go_dir[0]][0]][dir_dict[go_dir[0]][1]] = \
            self._ocean[dir_dict[go_dir[0]][0]][dir_dict[go_dir[0]][1]], \
            self._ocean[i][j]
        self._is_made_move[dir_dict[go_dir[0]][0]][dir_dict[go_dir[0]][1]] = True

    def victim_reproduce(self, directions, i, j):
        self._is_made_move[i][j] = True
        self._ocean[i][j].reproduce()
        repr_dir = random.sample(directions, 1)
        dir_dict = {'right': [i, j + 1], 'left': [i, j - 1], 'up': [i - 1, j],
                    'down': [i + 1, j]}
        self._victims_count += 1
        self._ocean[dir_dict[repr_dir[0]][0]][dir_dict[repr_dir[0]][1]] = \
            Victim(self._pregnancy_term_victim)
        self._is_made_move[dir_dict[repr_dir[0]][0]][dir_dict[repr_dir[0]][1]] = True

    def make_move_victim(self, i, j):
        water_neighbors = self.find_water(i, j)
        if len(water_neighbors) > 0:
            if self._ocean[i][j].ready_to_reproduce():
                self.victim_reproduce(water_neighbors, i, j)
            else:
                self.victim_go(water_neighbors, i, j)

    def make_move_predator(self, i, j):
        victims_neighbors = self.find_victims(i, j)
        if len(victims_neighbors) > 0:
            self.predator_eat(victims_neighbors, i, j)
        else:
            water_neighbors = self.find_water(i, j)
            if len(water_neighbors) > 0:
                if self._ocean[i][j].ready_to_reproduce():
                    self.predator_reproduce(water_neighbors, i, j)
                else:
                    self.predator_go(water_neighbors, i, j)

    def move_predators(self):
        for i in range(len(self._ocean)):
            for j in range(len(self._ocean)):
                if str(self._ocean[i][j]) == 'P' and not self._is_made_move[i][j]:
                    self.make_move_predator(i, j)

    def move_victims(self):
        for i in range(len(self._ocean)):
            for j in range(len(self._ocean)):
                if str(self._ocean[i][j]) == 'V' and not self._is_made_move[i][j]:
                    self.make_move_victim(i, j)

    def has_victims(self):
        return self._victims_count > 0

    def has_predators(self):
        return self._predators_count > 0

    def prepare_new_move(self):
        for i in range(len(self._is_made_move)):
            for j in range(len(self._is_made_move)):
                self._is_made_move[i][j] = False

    def simulate(self, move_limit):
        predators_counts = [self._predators_count]
        victim_counts = [self._victims_count]
        if len(self._ocean) <= SIZE_TO_VIEW:
            print(self)
        counter = 0
        while counter < move_limit and self.has_predators() and self.has_victims():
            self.move_predators()
            self.move_victims()
            victim_counts.append(self._victims_count)
            predators_counts.append(self._predators_count)
            if len(self._ocean) <= SIZE_TO_VIEW:
                print(self)
            self.prepare_new_move()
            counter += 1
        return predators_counts, victim_counts

    def __str__(self):
        result = []
        for i in self._ocean:
            for j in i:
                result.append(str(j))
            result.append('\n')
        return ''.join(result)


SIZE_TO_VIEW = 10


def main():
    ocean_size = 20
    pregnancy_term_victim = 5
    pregnancy_term_predator = 5
    hungriness_limit = 3
    iterations_limit = 10
    model = OceanEcosystemModel(ocean_size, pregnancy_term_victim,
                                pregnancy_term_predator, hungriness_limit)
    predator_counts, victim_counts = model.simulate(iterations_limit)
    predator_file = open('predators.txt', 'w')
    for i in predator_counts:
        predator_file.write(str(i) + ' ')
    predator_file.close()
    victim_file = open('victims.txt', 'w')
    for i in victim_counts:
        victim_file.write(str(i) + ' ')
    victim_file.close()
    return


main()
