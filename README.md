# Keylogger

### Project Description ###
Build as a Milestone project back in 2018 for the Udemy course of Ermin Kreponic "Build an Advanced Keylogger using C++ for Ethical Hacking!".
After building up the base code from the course, I added different encryption algorithms, testing them on their performance and further developing
the keylogger on this end

o Low-resource usage process and generates no windows when ran

o Captures all keystrokes using system hooks

o The custom encryption adds SALTS to the original string

o Afterwards the string is sliced in equal parts, therefore creating a “table” where every slice is a row

o The string is read not row-to-row, but column-to-column, such that Hello World-&gt;Hore llwdlo

o Afterwards the string is encoded using Base64 algorithm

o Automatically log the time and date when a log file is produced

o The log file saves the encoded string containing keystrokes information

o Generates and invokes a powershell script that can attach the encrypted log and email it

o The processes are executed asynchronously using C++11 threads
