a) Name:  Bhargav Venkataraman

b) USCID: 6658312887
 
c) In Phase 3 of the project, there are 4 entities: Major, Captain 1, Captain 2 and the General. The General behaves as the server to the Major and the Major behaves as the Server to the 2 Captains, which act as Clients. However, the Captains will behave as servers and the General as the client.
   The 2 Captains open their respective input files which contain: 1)Resources and 2)Confidence and send this data to the Major through a socket using the UDP protocol. 
   The Major receives this data and displays the data sent by the respective Captain. The Major uses this data to calculate the Probability of Success for both the Captains. It then sends the calculated values along with the Major's port number and the password, to the General.
   The General receives the password and the port number and validates them. If they are correct, the General displays the Success Rates sent by the Major. If they do not match, it asks the Major to try again and this continues until the Major sends the correct port number and password.
   The General, then decides which Captain has the higher success rate and sends a message to each captain. The message would indicate the captain with the higher success rate to start the mission and the one with the lower success rate to be the backup for the mission.
   The Captains receive their respective commands from the General and display what they will finally do.

d)  Captain: Contains code for both Captain 1 and Captain 2. Creates a child process using the fork() function. There is 1 second delay between each captain to distinguish them. Each captain first opens its respective input files and reads the content. It then creates a socket each and sends the data read from the input files to the Major through the socket that was created using the UDP protocol to the port number 6187 which is known to the captains.
The Captain then creates a socket each, for Captain 1 and Captain 2. Captain 1 has the port number 24087 (21200+2887) and Captain 2 has the port number 24187 (21300+2887). These Captains wait for an incoming TCP connection from the General. Once connected, each Captain will receive a message from the General which reads either "start" or "backup". If the message is "start" it indicates that the Captain is to start the mission and the appropriate message ("Captain X has started the mission!!") is displayed. If the message is "backup", it indicates that the Captain is the backup and so, the appropriate message ("Captain X is the backup for the mission!") is displayed.

    Major:Creates a socket and binds it to port number 6187(3300+2887). Gets its IP address and waits for reception of data. The first two receptions are from Captain 1 and the other is from Captain 2. The data from each captain is parsed and stored in appropriate variables and displayed. The Major then calculates the probablility of success (P(success)) using this data and the formula : ((5*Resources)+(3*Confidence)+(2*Record)). It then opens a UDP connection to the General on port 6287 (3400+2887). It opens the passMj.txt file and sends its contents to the General and the success rates. The Major will have to send the correct port number and password (contents of passMj.txt) again if they were incorrect the previous time.    

    General: Creates a socket and binds it to port number 6587 (3700+2887) and also displays its IP address. It then waits for reception of data from the Major. Major would send its port number and the password. The General would then open the passGn.txt file which contains the Major's port number and the password. If the data sent by the Major matches with the contents of this passGn.txt file, then validation is successful and the data sent by the Major can be trusted. The General would then display the Success Rates of the Captains which were sent by the Major. If validation is not successful, the Major is prompted to send the correct port number and password again.
Now the General compares the success rates of the 2 captains and decides which captain should carry out the mission and which should stay as a backup. It then creates a socket which has the port number 6687 (3800+2887) and opens a TCP connection to each Captain (Captain 1 and Captain 2). Depending on the decision made by the General, it sends a message to each captain, either "start" or "backup". These are the commands sent to the Captains.
   

e) To run the program:
The input files Captain1.txt, Captain2.txt, passMj.txt and passGn.txt must be in the same folder as Captain.c, Major.c, General.c and Makefile.
Need to wait 1 minute between executions to avoid bind and connect issues.

Commands to execute to run the program:
  1)open 3 terminals in all (one for General, one for Major and one for Captain)
  2)type: make (press enter)  (this compiles General.c, Major.c and Captain.c)
  3)on one terminal type:    ./General   (and press enter)
  4)on second terminal type: ./Major     (and press enter)
  5)on third terminal type:  ./Captain   (and press enter)
  6)output will be displayed



