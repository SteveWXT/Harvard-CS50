from cs50 import get_string

def checkBrand(number):
    
    length = len(number)
    
    brand = "INVALID"
    
    if length == 13:
        if number[0] == "4":
            brand = "VISA"

    elif length == 15:
        if number[:2] == "34" or number[:2] == "37":
            brand = "AMEX"

    elif length == 16:
        if number[0] == "4":
            brand = "VISA"
        elif number[:2] == "51" or number[:2] == "52" or number[:2] == "53" or number[:2] == "54" or number[:2] == "55":
            brand = "MASTERCARD"

    return brand


def checkLuhn(number):
    number = int(number)
    
    #sum of every other from second-to-last digit, multplied by 2
    sum1 = 0
    #sum of the rest
    sum2 = 0
    
    while number > 0:
        sum2 += number % 10
        
        number = number // 10
        
        if number > 0:
            tmp = number % 10 * 2
            if tmp < 10:
                sum1 += tmp
            else:
                tmp1 = tmp % 10
                tmp2 = tmp // 10
                sum1 += tmp1 + tmp2
            number = number // 10
        
    total = sum1 + sum2
    if total % 10 == 0:
        return True
    else:
        return False
        
        
def main():
    number = get_string("Number: ")
    
    brand = checkBrand(number)
    if brand != "INVALID":
        flag = checkLuhn(number)
        if flag:
            print(brand)
        else:
            print("INVALID")
    
    else:
        print(brand)

main()
