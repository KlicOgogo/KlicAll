#include <string>
#include <stack>
#include <set>
#include "./dungeon.h"
#ifndef ROGUE_H
#define ROGUE_H

#endif

#pragma once

Room* FindFinalRoom(Room* r) {
    std::stack<Room*> rooms;
    std::set<Room*> visited;
    std::set<Door*> closed;
    std::set<std::string> keys;
    rooms.push(r);
    while (true) {
        if (rooms.empty()) {
            for (auto it = closed.begin();
                 it != closed.end(); it++) {
                for (auto itt = keys.begin();
                     itt != keys.end(); itt++) {
                    if ((*it)->TryOpen(*itt)) {
                        if (visited.find((*it)->GoThrough())
                                == visited.end()) {
                            rooms.push((*it)->GoThrough());
                        }
                        break;
                    }
                }
                if (!rooms.empty()) {
                    break;
                }
            }
        }
        if (rooms.empty()) {
            break;
        }
        Room* last = rooms.top();
        if (last->IsFinal()) {
            return last;
        }
        visited.insert(last);
        for (size_t i = 0; i < last->NumKeys(); i++) {
            keys.insert(last->GetKey(i));
        }
        for (size_t i = 0; i < last->NumDoors(); i++) {
            if (last->GetDoor(i)->IsOpen()) {
                if (visited.find(last->GetDoor(i)->GoThrough())
                        == visited.end()) {
                    rooms.push(last->GetDoor(i)->GoThrough());
                    break;
                }
            } else {
                for (auto it = keys.begin(); it != keys.end(); it++) {
                    if (last->GetDoor(i)->TryOpen(*it)) {
                        if (visited.find(last->GetDoor(i)->GoThrough())
                                == visited.end()) {
                            rooms.push(last->GetDoor(i)->GoThrough());
                        }
                        break;
                    }
                }
            }
            if (!last->GetDoor(i)->IsOpen())
                closed.insert(last->GetDoor(i));
        }
        if (rooms.top() == last) {
            rooms.pop();
        }
    }
    return nullptr;
}

