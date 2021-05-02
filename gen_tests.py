from random import randint
import sys


if __name__ == '__main__':
    start = 1
    end = 1000
    from_vertex = 1
    to_vertex = 1
    max_weight = 20

    with open(sys.argv[1], "w+") as file:
        file.write(f'{end} {end + 1}\n')
        for i in range(1, end + 1):
            from_vertex = randint(start, end)
            to_vertex = randint(start, end)
            w = randint(1, max_weight)
            while from_vertex >= to_vertex:
                from_vertex = randint(start, end)
                to_vertex = randint(start, end)
            file.write(f'{from_vertex} {to_vertex} {w}\n')
