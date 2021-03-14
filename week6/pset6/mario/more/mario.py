def main():
    h = 0
    while h < 1 or h > 8:
        tmp = input('Height: ')
        if str.isdigit(tmp):
            h = int(tmp)
        else:
            continue
        
    for i in range(1, h+1):
        print(" " * (h-i), end="")
        print("#" * i, end="  ")
        print("#" * i)

main()