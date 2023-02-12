"""
Name: 임준상 Lin Chenxiang
Student Number: 2017320215
"""

def sam(a, b, n):                           # square-and-multiply algo.
    exp = bin(b)
    value = a

    for i in range(3, len(exp)):
        value = (value * value) % n
        if (exp[i:i + 1] == '1'):
            value = (value * a) % n
    return value

def ex_euc(m, b):                           # extended euclidean algo.
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
    return A1



if __name__=="__main__":
    c1 = 2909170161
    c2 = 2565161545
    q = 2934201397
    a = 37
    YA = 2174919958


    for XA in range(1, q-1):
        if sam(a, XA, q) == YA:
            break

    for k in range(1, q - 1):
        if sam(a, k, q) == c1:
            break

    K = sam(c1, XA, q)
    #K = sam(YA, k, q)

    Z = ex_euc(K, q)                    # Z is inverse of K
    print('Plaintext:', (c2*Z) % q)     # Plaintext of problem 2

    c2 = int(input('Input c2: '))
    print('Plaintext:', (c2*Z) % q)     # you can check more (c1 is same)
    c2 = int(input('Input c2: '))
    print('Plaintext:', (c2*Z) % q)