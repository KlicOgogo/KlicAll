from collections import defaultdict


class Req:
    def __init__(self):
        self.type = 'REQUEST'
        pass


class Appoint(Req):
    def __init__(self, attr_list):
        super().__init__()
        self.type = 'APPOINT'
        self.day = int(attr_list[1])
        start_time = attr_list[2].split(':')
        self.start_time = int(start_time[0]) * 60 + int(start_time[1])
        self.duration = int(attr_list[3])
        self.names = attr_list[5:5 + int(attr_list[4])]
        self.time = attr_list[2]

    def __str__(self):
        result = [self.time, str(self.duration)]
        for name in self.names:
            result.append(name)
        return ' '.join(result)


class Print(Req):
    def __init__(self, attr_list):
        super().__init__()
        self.type = 'PRINT'
        self.day = int(attr_list[1])
        self.name = attr_list[2]


def main():
    file = open('input.txt', 'r')
    file.readline()
    data = [line.strip().split(' ') for line in file]
    file.close()
    reqs = []
    for attr_list in data:
        if attr_list[0] == 'APPOINT':
            reqs.append(Appoint(attr_list))
        elif attr_list[0] == 'PRINT':
            reqs.append(Print(attr_list))
    out = open('output.txt', 'w')
    name_dict = defaultdict()
    for req in reqs:
        if req.type == 'APPOINT':
            for name in req.names:
                name_dict[name] = defaultdict(list)
    for req in reqs:
        if req.type == 'PRINT':
            if req.day in name_dict[req.name]:
                app_list = list(sorted(name_dict[req.name][req.day], key=lambda ap: ap.start_time))
                for app in app_list:
                    out.write(str(app) + '\n')
        elif req.type == 'APPOINT':
            approve = [True for _ in range(len(req.names))]
            for i in range(len(req.names)):
                cur_apps = name_dict[req.names[i]][req.day]
                for app in cur_apps:
                    left = app.start_time
                    right = left + app.duration
                    if req.start_time < right and req.start_time + req.duration > left:
                        approve[i] = False

            to_appr = 0
            for val in approve:
                if not val:
                    to_appr += 1
            if to_appr == 0:
                out.write('OK' + '\n')
                for name in req.names:
                    name_dict[name][req.day].append(req)
            else:
                out.write('FAIL\n')
                to_write = []
                for i in range(len(req.names)):
                    if not approve[i]:
                        to_write.append(req.names[i])
                out.write(' '.join(to_write) + '\n')
    out.close()

if __name__ == '__main__':
    main()
