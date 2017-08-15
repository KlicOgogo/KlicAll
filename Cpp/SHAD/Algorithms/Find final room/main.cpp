#include <iostream>
#include <sstream>
#include <vector>

#include "dungeon.h"
#include "rogue.h"

std::vector<std::unique_ptr<Room>> ReadDungeon(std::istream& in) {
    int num_rooms, num_open_doors, num_closed_doors, num_keys;
    in >> num_rooms;

    std::vector<std::unique_ptr<Room>> dungeon(num_rooms);
    for (int i = 0; i < dungeon.size(); ++i) {
        dungeon[i].reset(new Room(i + 1 == dungeon.size()));
    }

    in >> num_keys;
    for (int i = 0; i < num_keys; ++i) {
        int room;
        std::string key;
        in >> room >> key;
        dungeon[room]->AddKey(key);
    }

    in >> num_open_doors;
    for (int i = 0; i < num_open_doors; ++i) {
        int first_room, second_room, num_keys;
        in >> first_room >> second_room;
        dungeon[first_room]->AddDoor(dungeon[second_room].get());
    }

    in >> num_closed_doors;
    for (int i = 0; i < num_closed_doors; ++i) {
        int first_room, second_room, num_keys;
        std::string key;
        in >> first_room >> second_room >> key;
        dungeon[first_room]->AddDoorWithKey(dungeon[second_room].get(), key);
    }

    return dungeon;
}

void TestSimpleDungeons() {
    std::vector<std::string> test_dungeons = {
R"EOF(
1
0
0
0
)EOF",
R"EOF(
2
0
1
0 1
0
)EOF",
R"EOF(
2
1
0 abc
0
1
0 1 abc
)EOF",
R"EOF(
3
1
1 abc
1
0 1
1
0 2 abc
)EOF",
R"EOF(
3
1
1 abc
1
0 1
1
1 2 abc
)EOF",
R"EOF(
2
0
0
0
)EOF",
R"EOF(
2
1
0 abc
0
1
0 1 bcd
)EOF",
R"EOF(
2
1
1 abc
0
1
0 1 abc
)EOF",
R"EOF(
4
0
3
0 1
1 2
2 1
0
)EOF",
    };

    std::vector<bool> connected = { true, true, true, true, true, false, false, false, false };
    assert(connected.size() == test_dungeons.size());

    for (int i = 0; i < test_dungeons.size(); ++i) {
        std::stringstream dungeon_stream(test_dungeons[i]);
        auto dungeon = ReadDungeon(dungeon_stream);
        Room* exit_room = FindFinalRoom(dungeon[0].get());

        bool ok = connected[i] ? exit_room == dungeon.back().get() : exit_room == nullptr;
        if (!ok) {
            std::cerr << "Wrong answer. ";
            if (connected[i]) {
                std::cerr << "Expected room " << dungeon.size() << ", ";
            } else {
                std::cerr << "Expected nullptr, ";
            }

            for (int i = 0; i < dungeon.size(); ++i) {
                if (dungeon[i].get() == exit_room) {
                    std::cerr << "Got room " << i << std::endl;
                }
            }
            if (exit_room == nullptr) {
                std::cerr << "Got nullptr" << std::endl;
            }

            std::cerr << "Test input:" << test_dungeons[i];

            std::terminate();
        }
    }
}

void TestGeneratedDungeons() {
    srand(42);

    const int NUM_TESTS = 10;
    const int NUM_ROOMS = 100;
    const int NUM_DOORS = 200;
    const int NUM_CLOSED_DOORS = 100;

    for (int k = 0; k < NUM_TESTS; ++k) {
        std::vector<std::unique_ptr<Room>> dungeon(NUM_ROOMS);
        for (int i = 0; i < dungeon.size(); ++i) {
            dungeon[i].reset(new Room(i + 1 == dungeon.size()));
        }

        for (int i = 0; i < NUM_DOORS; ++i) {
            int from = rand() % dungeon.size();
            int to = rand() % dungeon.size();

            dungeon[from]->AddDoor(dungeon[to].get());
        }

        for (int i = 0; i < NUM_CLOSED_DOORS; ++i) {
            int from = rand() % dungeon.size();
            int to = rand() % dungeon.size();
            int key_location = rand() % dungeon.size();
            std::string key = std::to_string(i);

            dungeon[key_location]->AddKey(key);
            dungeon[from]->AddDoorWithKey(dungeon[to].get(), key);
        }

        Room* final_room = FindFinalRoom(dungeon[0].get());
        if (final_room && final_room != dungeon.back().get()) {
            std::cerr << "Wrong answer on generated dungeon" << std::endl;
            std::terminate();
        }
    }
}

int main() {
    TestSimpleDungeons();
    TestGeneratedDungeons();

    return 0;
}
