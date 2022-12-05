#!/usr/bin/python3
import requests
from sys import argv

variant = 'rapid' if not len(argv) > 1 else argv[1]
username = 'off_fast' if not len(argv) > 2 else argv[2]
r = requests.get(f'https://lichess.org/api/user/{username}/perf/{variant}').json()

print(r)
