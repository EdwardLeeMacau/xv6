from random import randint
from numpy.random import binomial, lognormal, geometric
from typing import Tuple

def random_tuple() -> Tuple:
    period = int(lognormal(2.5, .1))
    processing_time = binomial(period, 0.25, size=None)
    cycles = randint(1, 10)

    arrival_time = randint(0, 10)

    return (processing_time, period, cycles, arrival_time)

SIZE = 16
def main():
    num_threads = (geometric(p=0.25, size=SIZE) == 1).sum()

    print(f"\t__attribute__((unused)) int num_threads = {num_threads};")
    print()

    for n in range(1, num_threads + 1):
        t, p, c, arrival_time = random_tuple()

        print(f"\tstruct thread *t{n} = thread_create(f, NULL, {t}, {p}, {c});")
        print(f"\tthread_add_at(t{n}, {arrival_time});")
        print()

if __name__ == '__main__':
    main()
