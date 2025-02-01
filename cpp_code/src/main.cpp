#include<windows.h>
#include<iostream>

int main()
{

    HANDLE hComm;
    std::string port_name = "COM4";  //change port name
    char write_buffer[] = "Test Data";
    char read_buffer[100];
    DWORD dNoOFBytestoWrite;         // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0;     // No of bytes written to the port
    DWORD bytes_read = 0;

    hComm = CreateFileA(port_name.c_str(),                //port name
        GENERIC_READ | GENERIC_WRITE, //Read/Write
        0,                            // No Sharing
        NULL,                         // No Security
        OPEN_EXISTING,// Open existing port only
        0,            // Non Overlapped I/O
        NULL);        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error in opening serial port”";
        return -1;
    }
    else
        std::cerr << "opening serial port successful";

    DCB dcbSerialParams = { 0 }; // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hComm, &dcbSerialParams);

    dcbSerialParams.BaudRate = CBR_115200;  // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;  // Setting Parity = None
    SetCommState(hComm, &dcbSerialParams);

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 20; // in milliseconds
    timeouts.ReadTotalTimeoutConstant = 100; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier = 10; // in milliseconds
    timeouts.WriteTotalTimeoutConstant = 100; // in milliseconds
    timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds 


    dNoOFBytestoWrite = sizeof(write_buffer);

    WriteFile(hComm,        // Handle to the Serial port
        write_buffer,     // Data to be written to the port
        dNoOFBytestoWrite,  //No of bytes to write
        &dNoOfBytesWritten, //Bytes written
        NULL);
    do
    {
        ReadFile(hComm,      //Handle of the Serial port
            &read_buffer,       //Temporary character
            100,//Size of TempChar
            &bytes_read,    //Number of bytes read
            NULL);

    } while (bytes_read <= 0);

    std::cout << "Read Data : " << read_buffer << std::endl;
    CloseHandle(hComm);//Closing the Serial Port

    return 0;
}