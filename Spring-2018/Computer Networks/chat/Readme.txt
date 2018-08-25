
I implement the server/client chat system using multithreaded programming.
 
Actually there are a lot of resources and video tutorials about socket programming using threads and synchronized methods and data structures on the web. I constructed my Server, Client, ServerThread and ClientThread classes with the help from the website:

http://pirate.shu.edu/~wachsmut/Teaching/CSAS2214/Virtual/Lectures/chat-client-server.html.

Another useful source that I've learned a lot from is the set of video tutorials:
https://www.youtube.com/watch?v=cRfsUrU3RjE

After enabling to exchange basic messages between server and client I added the rest of the functionality of the server inside the handleClients() method in the Server class and also created some additional classes when needed. 

To store the information about the clients an array of socket was created in the main thread, and when the new client connected a new element to the array was added and in the same manner when disconnected the element from the array is removed. 