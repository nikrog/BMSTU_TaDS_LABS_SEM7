from math import floor

from faker import Faker
from random import randint, random
from random import choice, uniform

from mimesis import Datetime
from numpy import ceil

MAX_N = 89000

datetime = Datetime()
banks = [1, 2, 6, 7, 8]


def generate_products():
    faker = Faker()
    f = open('products2.csv', 'w')
    co_set = set()
    cap_set = set()

    for i in range(MAX_N):
        ptype = randint(0, 1)
        name = faker.name() + str(randint(1, 100000))
        while name in co_set:
            name = faker.name()
        bank_id = choice(banks)
        rate = uniform(0, 25)
        min_time = randint(1, 5000)
        max_time = min_time + randint(1, 5000)
        min_sum = randint(1, 9) * pow(10, randint(1, 5))
        max_sum = min_sum * pow(10, randint(1, 3))
        currency = randint(0, 3)
        avg_rating = 1 + random() * 4
        #print("AVG: ", avg_rating)
        sum_rating = randint(1, 100)
        count_rating = int(ceil(sum_rating / avg_rating))
        if sum_rating/count_rating > 5:
            print(count_rating)
        if sum_rating != 0 and count_rating == 0:
            count_rating = 1
        #print("S/C: ", sum_rating / count_rating)
        line = "{0};{1};{2};{3};{4};{5};{6};{7};{8};{9};{10}\n".format(
            ptype,
            name,
            bank_id,
            rate,
            min_time,
            max_time,
            min_sum,
            max_sum,
            currency,
            sum_rating,
            count_rating)
        f.write(line)
    f.close()

generate_products()