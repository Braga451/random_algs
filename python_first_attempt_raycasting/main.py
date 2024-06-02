#!env/bin/python

import numpy as np
from matplotlib import pyplot as plt
from matplotlib import use
use("gtk3agg")
from pynput import keyboard
from random import randint
from enum import Enum

class MapColors(Enum):
    BLACK = (0, 0, 0)
    RED = (1, 0, 0)
    GREEN = (0, 1, 0)
    BLUE = (0, 0, 1)
    EMPTY = (1, 1, 1)

class Player:
    def __init__(self) -> None:
        self._x , self._y= (1, 1)
        self._visionx, self._visiony = (3, 3)
        self._rot : float = np.pi/4

    def play(self, random_map) -> None:
        while True:
            for i in range(180):
                rot_i : float = self._rot + np.deg2rad(i - 90)
                current_x, current_y = (self._x, self._y)
                sin, cos = (0.02 * np.sin(rot_i) , 0.02 * np.cos(rot_i))
                n : int = 0

                while True:
                    current_x, current_y = (current_x + cos, current_y + sin)
                    n += 1
                    if (random_map[int(current_x)][int(current_y)] != MapColors.EMPTY.value):
                        h : int = np.clip(1 / (0.02 * n), 0, 1)
                        c : np.array = np.asarray(random_map[int(current_x)][int(current_y)]) * (0.3 + 0.7 * (h ** 2))
                        break

                plt.vlines(i, -h, h, lw = 8, colors = c)
            
            plt.axis("off")
            plt.tight_layout()
            plt.axis([0, 180, -1, 1])
            plt.draw()
            plt.pause(0.0001)
            plt.clf()

            current_x, current_y = self._verifyMovement(current_x, current_y)

            if (random_map[int(current_x)][int(current_y)] != MapColors.BLACK.value):
                #if (int(self._x) == len(random_map) and int(self._y) == len(random_map[0])):
                #    break
                self._x, self._y = (current_x, current_y)

        plt.close()
        
    def _verifyMovement(self, x : int, y: int) -> tuple[int, int]:
        print(self._rot)
        with keyboard.Events() as events:
            for event in events:
                match event.key:
                    case keyboard.Key.up:
                        return (x + 0.3 * np.cos(self._rot), y + 0.3 * np.sin(self._rot))
                    
                    case keyboard.Key.down:
                        return (x - 0.3 * np.cos(self._rot), y - 0.3 * np.sin(self._rot))
                    
                    case keyboard.Key.left:
                        self._rot -= np.pi/8
                        break

                    case keyboard.Key.right:
                        self._rot += np.pi/8
                        break

                    case keyboard.Key.esc:
                        exit()

                    case _:
                        break

                break
       	return (x, y)

def randomMap(width: int, heigth: int) -> list[list[list[int]]]:
    random_map : list[list[int]] = [] 
    possible_enums : list[tuple[int]] = list(MapColors)
    
    max_walls : int = int((width * heigth) / 10)

    for i in range(0, width):
        random_map.append([]) 
        for j in range(0, heigth):
            if (i == 0 or i == width - 1 or j == 0 or j == heigth - 1):
                random_map[i].append(MapColors.BLACK.value)
            else:
                if (max_walls > 0):
                    # random_map[i].append(possible_enums[randint(1, 3)].value)
                    random_map[i].append(MapColors.EMPTY.value)
                    max_walls -= 1
                else:
                    random_map[i].append(MapColors.EMPTY.value)

    random_map[1][1] = MapColors.EMPTY.value

    return random_map

def main() -> None:
    random_map : list[list[list[int]]] = randomMap(10, 10)
    player : Player = Player()

    player.play(random_map)

if __name__ == "__main__":
    main()
