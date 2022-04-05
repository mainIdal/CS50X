from cs50 import get_float

money = 0.0
while(True):
    money = get_float("Change owed: ")
    if (money > 0.0):
        break

ans = 0
peni = money * 100
while(peni != 0):

    if peni >= 25:
        peni -= 25
        ans += 1
    elif peni >= 10:
        peni -= 10
        ans += 1
    elif peni >= 5:
        peni -= 5
        ans += 1
    else:
        peni -= 1
        ans += 1


print(ans)
