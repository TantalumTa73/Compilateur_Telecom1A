x = 0

if x > 0:
    if x > 5:
        if x > 6:
            if x == 7:
                print("X is exactly 7!")  # This should be printed
            else:
                print("X is greater than 6 but not 7")
        else:
            print("X is greater than 5 but not 6")
    else:
        print("X is positive but less than or equal to 5")
else:
    print("X is non-positive")
