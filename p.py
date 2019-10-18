def build(index,left,right):
    
    print(left,right)
    if(left == right):
        segment[index] = vector[left]
        return
    else:
        mid = int((right+left)/2)
        build(index*2,left,mid)
        build(index*2+1,mid+1,right)
        segment[index] = segment[index*2]+segment[index*2+1]

vector = []
segment = []

n = int(input())
values = input()
values = values.split(' ')

for i in range(n):
    vector.append(int(values[i]))

build(1,0,len(vector)-1)
print(segment)

m = int(input())

for i in range(m):
    option = input()
    option = option.split(" ")
    op,a,b = int(option[0]),int(option[1]),int(option[2])
    
   # if(op == 1):
        
        
    