from csv import reader, DictReader
from sys import argv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py DATABASE SEQUENCE")
        exit()

    STR = []
    database = []

    with open(argv[1], 'r') as dbFile:
        rows  = reader(dbFile)
        for row in rows:
            STR = row
            STR.pop(0)
            break

    with open(argv[1], 'r') as dbFile:
        rows = DictReader(dbFile)
        for row in rows:
            database.append(row)

    seq = ''
    with open(argv[2], 'r') as seqFile:
        rows = reader(seqFile)
        for row in rows:
            seq = row[0]
            break

    counts = {}
    for key in STR:
        maxTimes = countSTRMax(seq, key)
        counts[key] = maxTimes

    for person in database:
        flag = True
        for key in STR:
            if int(person[key]) != counts[key]:
                flag = False

        if flag:
            print(person['name'])
            break

    print("No match")

def countSTRMax(seq, key):

    maxTimes = 0
    times = 0

    for i in range(len(seq)):
        times = 0
        j = i
        while seq[j:j+len(key)] == key:
            times += 1
            if times > maxTimes:
                maxTimes = times
            j += len(key)

    return maxTimes

main()



