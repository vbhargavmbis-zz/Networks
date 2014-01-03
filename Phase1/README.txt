a) Name:  Bhargav Venkataraman

b) USCID: 6658312887
 
c) In Phase 1 of the project, there are 3 entities: Major, Captain 1 and Captain 2. The Major behaves as the Server and the 2 Captains act as Clients. The 2 Captains open their respective input files which contain: 1)Resources and 2)Confidence and send this data to the Major through a socket using the UDP protocol. 
   The Major receives this data and displays the data sent by the respective Captain.

d) Major:Creates a socket and binds it to port number 6187(3300+2887). Gets its IP address and waits for reception of data. The first two receptions are from Captain 1 and the others from Captain 2. The data from each captain is parsed and stored in appropriate variables and displayed.

   Captain: Contains code for both Captain 1 and Captain 2. Creates a child process using the fork() function. There is 1 second delay between each captain to distinguish them. Each captain first opens its respective input files and reads the content. It then creates a socket each and sends the data read from the input files to the Major through the socket that was created using the UDP protocol to the port number 6187 which is known to the captains.

e) To run the program:
The input files Captain1.txt and Captain2.txt must be in the same folder as Captain.c, Major.c and Makefile.
Commands to execute to run the program:
  1)type: make (press enter)  (this compiles Major.c and Captain.c)
  2)open 2 terminals in all (one for Major and one for Captain)
  3)on one terminal type:    ./Major   (and press enter)
  4)on second terminal type: ./Captain (and press enter)
  5)output will be displayed

I have displayed the Resources and Confidence for each Captain instead of the messages shown in the description as we do not calculate the Success Rate in Phase 1 and also the Record is first mentioned in Phase 2.