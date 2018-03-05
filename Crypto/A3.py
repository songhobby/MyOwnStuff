lst="1011001011"
mult = 17
result = 1
for st in reversed(lst):
    if (st=='1'):
        result = (result * mult) % 1073
    print(result)
    mult=mult**2 % 1073
    print(mult)
print (result)
