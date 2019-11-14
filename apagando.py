stack = []

while(True):

    n,m = input().split();
    n = int(n)
    m = int(m)

    if(n == 0 and m == 0):
        break
    i = 1
    cont = 0
    numero = input()
    stack.append(numero[0])

    while(cont <= m):
        
        if(i < n):
            break
        if(numero[i] > stack[-1]):
            stack.pop()
            cont += 1
            stack.append(numero[i])
            i += 1
        if(numero[i] < stack[-1]):
            stack.append(numero[i])
            i += 1
    else:
        stack.append(numero[i])
        i += 1
    print(stack.reverse())
