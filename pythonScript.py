#EXACTLY PROTOCOL
import threading
import socket,time
import random as r
import sys
import sys

if len(sys.argv[1])==0:
    print("Please provide a port number\n")
    exit()
port = int(sys.argv[1])

#port = 7891
nameLock = threading.Lock()
adminLock = threading.Lock()
playersCount = r.randint(1,8)
playerNames = ["Georgiy","Mona","Martin","Mark","Ben",
               "Aigerim","Michael","Ainur","Shirailym"]
#https://stackoverflow.com/questions/5998245/get-current-time-in-milliseconds-in-python
current_milli_time = lambda: int(round(time.time() * 1000))


possibleAnswers = ["NOANS", "A","B","C","D","E","F","G"]
adminString = "QS|ADMIN\r\n"
waitString = "WAIT\r\n"
joinString = "QS|JOIN\r\n"
fullString = "QS|FULL\r\n"
global gameAdmin
gameAdmin="None"

def clientPrints(playerName,messageString):
     print(str(current_milli_time())+": "+ "Thread " + playerName+" sends to server "+
           messageString)

def clientGets(playerName,messageString):
     print(str(current_milli_time())+": "+"Thread " + playerName+
           " received from server " + messageString)
        
def makeGroup(playerName):
    if playersCount==1:
        groupSize=1
    else:
        groupSize = r.randint(1,playersCount-1)
    if groupSize<1:
        groupSize=1
    
    resultString = "GROUP|"+playerName+"|"+str(groupSize)+"\r\n"
    return resultString

def makeAnswer(questionLimit):
    selectedAnswer = possibleAnswers[r.randint(0,questionLimit-1)]
    
    resultString = "ANS|"+selectedAnswer + "\r\n"
    return resultString

def joinGroup(playerName):
    resultString = "JOIN|"+playerName+"\r\n"
    return resultString

def player(playerName):
    global gameAdmin
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(('localhost', port))
    
    while True:
        data = client.recv(4096)
        dataString = data.decode()
        if len(dataString) == 0:
            print("Server sent an empty string")
            break;
        clientGets(playerName,dataString)
        if dataString==adminString:
           # adminLock.acquire()
           # if gameAdmin=="None":
            groupString=makeGroup(playerName)
            gameAdmin=playerName
            clientPrints(playerName,groupString)
            client.sendall(groupString.encode('utf-8'))
           #     adminLock.release()
            #else:
             #   adminLock.release()

        if dataString==fullString:
            break;
            
        if dataString==joinString:
            playerJoinString=joinGroup(playerName)
            clientPrints(playerName,playerJoinString)
            client.sendall(playerJoinString.encode('utf-8'))
        
        if dataString.startswith("QUES"):
            numberOfAnswers = dataString.count('\n')
            clientsAnswer = makeAnswer(numberOfAnswers)
            clientPrints(playerName,clientsAnswer)
            client.sendall(clientsAnswer.encode('utf-8'))
            
        if dataString.startswith("RESULT"):
            break;
    client.close()
    return

threads = []
print("hello from main, players count will be: "+ str(playersCount))
for i in range(0,playersCount):
    threadName = r.choice(playerNames)
    playerNames.remove(threadName)
    t = threading.Thread(target=player, args=(threadName,))
    print("thread " +threadName + " spawned")
    threads.append(t)
for t in threads:
    t.start()
for t in threads:
    t.join()
print("bye from main")
