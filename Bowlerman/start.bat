make clean_windows
make alludpServer
make tcpServer
::make tcpServer
make windows
::start tcpServer.exe
start udpServer.exe   
start tcpServer.exe     
:: ^START GÖR ATT DEN GÅR VIDARE TILL NÄSTA "RAD" MEDAN .EXE-FILEN KÖRS
::start main.exe    
start main.exe   
main.exe                
:: ^INGEN START BETYDER ATT DEN VÄNTAR MED NÄSTA RAD TILLS MAN STÄNGT NER .EXE FILEN
::taskkill /im tcpServer.exe 
::taskkill /im udpServer.exe 
:: ^STÄNGER NER SERVERN EFTER MAN STÄNGT SIN CLIENT
taskkill /im main.exe