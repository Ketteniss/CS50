import sys
import csv

def main():
    teams = []
    # Read teams into memory from file
    prevCup = sys.argv[1]
    with open(prevCup) as file:
        data_set = csv.DictReader(file)
        next(data_set)
        for row in data_set:
            tmp = row
            print(tmp)
    print(teams)

main()