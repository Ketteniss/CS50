import sys
import csv
import random

def main():
    teams = []
    # Read teams into memory from file
    print(sys.argv)
    prevCup = sys.argv[1]
    with open("data.csv", "r") as file:

        reader = csv.DictReader(file)
        next(reader)
        for data in reader:
            print(data)
    
main()