import socket

address = ("localhost",20000)
client = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

print("Cliente ativo, fazendo requisição\n")
try:    
    while True:
        letter = input("Informe a palavra desejada:")
        client.sendto(letter.encode("ascii"),address)
        #data = client.recv(1024)
        #print(data)
        
        print("xixiix")
except:
    client.close()
        