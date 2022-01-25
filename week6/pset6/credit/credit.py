from cs50 import get_string
from math import floor

# Get credit card number as string
number = get_string("Number: ")

# TODO: Controll for non numerals

# Initialize verification bools
ver1 = False
ver2 = False

######################################
##  VERIFICATION 1                  ##
##  ACCEPTED CARD COMPANIES:        ##
##  AMEX, VISA, MASTERCARD          ##
######################################

# Initialize company name
name = ""
# Initialize starting decimals to verify
first = int(number[0])
second = int(number[1])

if (first in [3, 4, 5]):

    # AMEX
    if (first in [3]):
        if(second in [4, 7]):
            name = "AMEX"
            ver1 = True
    # VISA
    if (first in [4]):
        name = "VISA"
        ver1 = True
    # MASTERCARD
    if (first in [5]):
        if (second in [1, 2, 3, 4, 5]):
            name = "MASTERCARD"
            ver1 = True

######################################
##  VERIFICATION 2                  ##
##  LUHN ALGORITHM                  ##
######################################

# Prepare traversion of number string
numofdecs = len(number)
simple_sum = 0
product_sum = 0
step = True

# VERIFIY IF CORRECT UNDER LUHN
if (ver1):
    for i in range(numofdecs-1, -1, -1):
        decimal = int(number[i])
        if (step):
            simple_sum += decimal
            step = False
        else:
            product_sum += ((decimal * 2) % 10) + floor((decimal * 2) / 10)
            step = True
    if ((simple_sum + product_sum) % 10 == 0):
        ver2 = True

##########################
## RESULT:              ##
if (ver1 and ver2):     ##
    print(name)         ##
else:                   ##
    print("INVALID")    ##
##                      ##
##########################
