### Q\_StringValue

![image](https://user-images.githubusercontent.com/69573151/212334298-f7c6215c-a80c-491c-ad3e-6ba0e539f0d0.png)

Command Change String Value ( Part 6 - F.24 ) 

ISO 11783-6

This command sends a string to the VT. The length of the string including '' may not be longer than the define ISO\_VTC\_CMD\_STR\_MAX\_LENGTH. Take care that '' is trailed.

Return values

iso\_s16  
•E\_NO\_ERR - transport started  
•E\_OVERFLOW - buffer overflow  
•E\_NOACT - Command not possible in current state  
•E\_NO\_INSTANCE - No VT client available
