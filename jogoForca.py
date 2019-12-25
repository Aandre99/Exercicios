import socket

words_Server = {"Frutas":['uva','maçã','laranja','banana','pera','mamão','abacate'],
                "Animais":['macaco','gato','cachorro','galinha','cobra','tartaruga'],
                "Cores":['azul','verde','vermelho','preto','amarelo','rosa','marrom'],
                "Países":['brasil','italia','alemanha','inglaterra','venezuela','espanha']}

address = ("localhost",20000)
server = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server.bind(address)

print("Servidor escutando...Aguardando Usuarios")
try:
    while True:
        message, connection = server.recvfrom(1024)
        #server.send((words_Server["message"]))
        
        print("MSG RECBIDA: " + message.decode("ascii"))
except:
    server.close()
