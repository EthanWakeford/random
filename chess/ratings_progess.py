#!/usr/bin/python3
import requests
from sys import argv
from matplotlib import pyplot as plt
from datetime import datetime

variant = 'Rapid' if not len(argv) > 1 else argv[1]
username = 'off_fast' if not len(argv) > 2 else argv[2]
all_ratings = requests.get(f'https://lichess.org/api/user/{username}/rating-history').json()

#retrives ratings of variant from list of all ratings across all variants
for i in all_ratings:
    if i.get('name') == variant:
        rating_history = i.get('points')

#lichess API counts months from zero, fixes conflict with datetime objects
for i in rating_history:
    i[1] += 1

#retrieves data from [year, month, day, rating] format
dates = [datetime(*i[:3]) for i in rating_history]
ratings = [i[3] for i in rating_history]

plt.plot(dates, ratings)
plt.title(f'{username}\'s {variant} Rating')
plt.ylabel(f'{variant} Rating')
plt.show()
