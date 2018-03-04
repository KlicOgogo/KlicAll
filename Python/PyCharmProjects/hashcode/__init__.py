import numpy as np

BONUS = 0


def distance(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


class Ride(object):

    def __init__(self, id, start_from, ride_to, earliest_start, latest_finish):
        self.id = id
        self.start_from = start_from
        self.ride_to = ride_to
        self.earliest_start = earliest_start
        self.latest_finish = latest_finish

    def __lt__(self, other):
        if self.latest_finish < other.latest_finish:
            return True
        if self.latest_finish == other.latest_finish:
            return self.latest_finish - self.earliest_start < other.latest_finish - other.earliest_start
        return False


class Car(object):

    def __init__(self):
        self.queue = []
        self.release_time = 0

    @property
    def current_pos(self):
        return self.queue[-1].ride_to if self.queue else (0, 0)

    def check_ride(self, ride):
        time_to_finish = distance(self.current_pos, ride.start_from) + distance(ride.start_from, ride.ride_to) + self.release_time
        return time_to_finish <= ride.latest_finish

    def check_profit(self, ride):
        if not self.check_ride(ride):
            return 0
        res = BONUS if self.release_time + distance(self.current_pos, ride.start_from) <= ride.earliest_start else 0
        res += distance(ride.ride_to, ride.start_from)
        return res

    def assign(self, ride):
        self.queue.append(ride)
        self.release_time = max(
            self.release_time + distance(self.current_pos, ride.start_from), ride.earliest_start
        ) + distance(ride.start_from, ride.ride_to)

    def __lt__(self, other):
        return self.release_time < other.release_time

    def __str__(self):
        return ' '.join([str(ride.id) for ride in self.queue])


def read_data(file):
    with open(file, 'r') as fin:
        data = []
        rows, columns, vehicles, rides, bonus, steps = [int(el) for el in next(fin).split()]
        for i, line in enumerate(fin):
            start_from_x, start_from_y, ride_to_x, ride_to_y, earliest_start, latest_finish = [
                int(el) for el in line.split()
            ]
            data.append(
                Ride(i, (start_from_x, start_from_y), (ride_to_x, ride_to_y), earliest_start, latest_finish)
            )
        return data, (rows, columns, vehicles, rides, bonus, steps)


def main():
    dist_thr = [5000 + 20*i for i in range(100)]

    title = 'd_metropolis'
    queue_rides, (rows, columns, vehicles, rides, bonus, steps) = read_data('.'.join([title, 'in']))
    distances = []
    winds = []
    for ride in queue_rides:
        dist = distance(ride.ride_to, ride.start_from)
        distances.append(dist)
    for d in dist_thr:
        print(np.sum((np.array(distances) >= d).astype(int)), d)


if __name__ == '__main__':
    main()
