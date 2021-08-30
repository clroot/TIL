while True:
    line = input()

    if line == "0":
        break

    if line == line[::-1]:
        print("yes")
    else:
        print("no")
