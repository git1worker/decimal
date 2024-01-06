
def splitBin(s):
    cnt = 0
    for i in range(len(s) - 1, -1, -1):
        if (cnt % 33) == 0:
            s = s[:len(s) - cnt] + '|' + s[len(s) - cnt:]
        cnt += 1
    return s

def transformToAppropriate(s):
    s = splitBin(s)
    s = s.replace("-", '')
    l = s.split("|")
    cnt = 0
    l.pop()
    for i in range(len(l) - 1, -1, -1):
        l[i] = "0b" + l[i]
        cnt += 1
    while (cnt < 3) :
        l.insert(0, "0b")
        cnt += 1
    return l

    
s1 = '11010101010010110011110110011001000101010101011000110101010'
s2 = '1010010101000101010101010010101010111111111101010110101011111111101010'

s = "{0:b}".format(
 -int(s1,
 2) - int(s2,
2))
print(transformToAppropriate(s1))
print(transformToAppropriate(s2))

print(s)

print(transformToAppropriate(s))
