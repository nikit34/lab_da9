from random import randint
import sys


if __name__ == '__main__':
    start = 1
    end = int(sys.argv[1][4:])
    from_vertex = 1
    to_vertex = 1
    max_weight = 20

    with open(sys.argv[1], "w+") as file:
        file.write(f'{end} {end * end}\n')
        for i in range(1, end * end):
            from_vertex = randint(start, end)
            to_vertex = randint(start, end)
            w = randint(1, max_weight)
            while from_vertex >= to_vertex:
                from_vertex = randint(start, end)
                to_vertex = randint(start, end)
            file.write(f'{from_vertex} {to_vertex} {w}\n')
