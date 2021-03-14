from cs50 import get_float

def main():
    
    count = 0
    dollar = -1
    while dollar < 0:
        dollar = get_float("Change owed: ")
        
    cent = dollar * 100
    
    while cent > 0:
        if cent >= 25:
            cent -= 25
            count += 1
        elif cent >= 10:
            cent -= 10
            count += 1
        elif cent >= 5:
            cent -= 5
            count += 1
        else:
            cent -= 1
            count += 1
    
    print(count)
    
main()