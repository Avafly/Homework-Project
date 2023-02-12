"""
Name: 임준상 Lin Chenxiang
Student Number: 2017320215
"""

def find_pq():                          # find prime number p and q
    for p in range(2, n):               # mod为0则可以整除 半素数只能被p q整除
        if n%p == 0:
            return p, n//p

def sam(a, b):                          # square-and-multiply algorithm
    exp = bin(b)
    value = a

    for i in range(3, len(exp)):
        value = (value * value) % n
        if (exp[i:i + 1] == '1'):
            value = (value * a) % n
    return value

def ex_euc(m, b):                       # extended euclidean algorithm
    A1, A2, A3 = 1, 0, m
    B1, B2, B3 = 0, 1, b

    if b == 0:
        return 1, 0, m
    else:
        while (B3 != 0):
            Q = A3 // B3
            T1, T2, T3 = A1 - Q*B1, A2 - Q*B2, A3 - Q*B3
            A1, A2, A3 = B1, B2, B3
            B1, B2, B3 = T1, T2, T3
    return A1, A2, A3
    


if __name__=="__main__":
    C = int(input('C: '))
    #C = 1220703125
    #C = 528567365900595529
    #C = 8792215503885098117
    n = 9943237852845877651
    e = 13

    # The results of find_pq(): p = 2701212721, q = 3681027331
    p = 2701212721
    q = 3681027331
    nn = (p-1) * (q-1)                  # Φ(n)

    x, y, gcd = ex_euc(e, nn)           # ax + by = d = gcd(a, b)
    d = x % nn                          # d = 9178373396735665477

    print('M:', sam(C, d))              #result