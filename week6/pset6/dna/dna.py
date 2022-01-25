# Write a programm that takes in a dna-sequence aswell as a data base for STR's and then controlls for STR matches

#   $ python dna.py databases/large.csv sequences/5.txt
#   Lavender
import sys
import csv

def main():

    if (len(sys.argv) != 3):
        print("Usage: python dna.py database.csv sequence.txt")
        return 1

    database_csv = sys.argv[1]
    dna_txt = sys.argv[2]
    database = []

    # Load database into memory
    with open(database_csv, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Generate STR list
    STRs = list(database[0].keys())
    STRs = STRs[1:]

    # Initialize dict to count STRs found within input sequence
    count = {}
    for STR in STRs:
        count[STR] = 0

    # Load dna sequence into memory
    with open(dna_txt, "r") as file:
         dna = file.read()

    # Traverse input dna sequence and count CONSECUTIVE STRs
    for STR in STRs:
        cnsq = 0
        i = 0;
        while (i < len(dna) - len(STR)):
            if (dna[i:len(STR)+i] == STR):
                cnsq += 1
                i += len(STR)
                if (cnsq > count[STR]): count[STR] = cnsq
            else:
                cnsq = 0
                i += 1
        count[STR] = str(count[STR])

    # Compare database with generated counts of STRs for a match
    for entry in database:
        match = True
        for STR in STRs:
            if (count[STR] != entry[STR]):
                match = False
        if (match):
            print(entry["name"])
            return
    # Else
    print("No match")

if __name__ == "__main__":
    main()