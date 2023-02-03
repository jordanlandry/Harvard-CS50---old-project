from sys import argv, exit
import csv


def main():
    # Check correct argument usage
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Initialize
    seq = []
    dat = []

    # Read through the data file
    with open(argv[1], mode="r") as file:
        reader = csv.DictReader(file)
        seq = reader.fieldnames[1:]
        for row in reader:
            dat.append(row)

    # Initialize dictionary
    str_count = dict.fromkeys(seq, 0)

    # Read through the sequence file
    with open(argv[2], mode="r") as file:
        sequence = file.readline()
        for s in seq:
            str_count[s] = get_str_count(sequence, s)

    # Check if person data has same str count
    for d in dat:
        matches = 0

        for s in seq:
            if int(d[s]) == str_count[s]:
                matches += 1

        if matches == len(seq):
            print(d['name'])
            exit(0)

    print("No match")
    exit(1)


def get_str_count(seq, s):
    length = len(s)

    max_repeats = 0
    for i in range(len(seq)):
        count = 0

        if seq[i: i + length] == s:
            count += 1
            while seq[i: i + length] == seq[i + length: i + (2 * length)]:
                count += 1
                i += length

        # Update the max count
        if count > max_repeats:
            max_repeats = count

    return max_repeats


if __name__ == "__main__":
    main()