#include <stdio.h>  
#include <windows.h>  
int main(void)  
{  
    FILE *fp;  
    HANDLE uart ;
    char temp,rec_cnt;  
    char buf[100];  
    char wbuf[10] = "text2send" ;
    unsigned int length ;
    COMMTIMEOUTS T_out ;
    DCB b_set ;
    
    uart = CreateFile("COM3",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    
    if(uart != INVALID_HANDLE_VALUE) puts("UART OPEN SUCCESS \n");
    else puts("UART OPEN FAIL ! \n");
    
    T_out.ReadIntervalTimeout = 1000 ;
    T_out.ReadTotalTimeoutMultiplier = 500 ;
    T_out.ReadTotalTimeoutConstant = 5000 ;
    T_out.WriteTotalTimeoutMultiplier = 0 ;
    T_out.WriteTotalTimeoutConstant = 2000 ;
    
    SetCommTimeouts(uart,&T_out);
    SetupComm(uart,500,500);
    
    GetCommState(uart, &b_set);
    b_set.BaudRate = CBR_9600 ;
    b_set.ByteSize = 8 ;
    b_set.Parity = NOPARITY ;
    b_set.StopBits = ONESTOPBIT ;
    
    if(SetCommState(uart,&b_set)) puts("UART SET SUCCESS \n");
    
	while(1)  
    {  
        temp=0;  
        rec_cnt ++ ;
        
		if(ReadFile(uart,buf,100,&length,NULL)) puts("Rx fail \n");
		printf("%d time cyc , read %d bytes , %d \n",rec_cnt,length,buf[0]);  
		 
    }  
    return 0;  
}  
