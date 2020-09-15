/**
 *  Arduino C++ Linux designed by かつらぎ.
 */

#include <libserial/SerialPort.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>

constexpr const char* const SERIAL_PORT_2 = "/dev/ttyACM0" ;

/**
 * @brief This is a file designed by かつらぎ, which controls basic serial communication
 * with Arduino Uno and C++, all rights reserved to the respective owner of libserial.
 */
int main(int argc, char** argv)
{   
    using namespace LibSerial ;

    // Instantiate a SerialPort object.
    SerialPort serial_port ;

    try
    {
        // Open the Serial Port at the desired hardware port.
        serial_port.Open(SERIAL_PORT_2) ;
    }
    catch (const OpenFailed&)
    {
        std::cerr << "The serial port did not open correctly." << std::endl ;
        return EXIT_FAILURE ;
    }

    // Set the baud rate of the serial port.
    serial_port.SetBaudRate(BaudRate::BAUD_115200) ;

    // Set the number of data bits.
    serial_port.SetCharacterSize(CharacterSize::CHAR_SIZE_8) ;

    // Turn off hardware flow control.
    serial_port.SetFlowControl(FlowControl::FLOW_CONTROL_NONE) ;

    // Disable parity.
    serial_port.SetParity(Parity::PARITY_NONE) ;
    
    // Set the number of stop bits.
    serial_port.SetStopBits(StopBits::STOP_BITS_1) ;

    std::cout << "Program developed by かつらぎ. Running version 1.0, developed for Arduino Uno. \n ";
while (true)
{
    //Set the switch structure for operation selection.
    std::cout << "Select your operation.[1][Write], [2][Read], [3][Exit]   " << std::flush;
    std::string operation;
    std::cin >> operation;
    int op4 = std::stoi(operation);

    switch(op4) {
        case 1 : {
            std::cout << "Please select your character [5 char max]. <<   " << std::flush;
            std::string data_control;
            std::cin >> data_control;

            for (int i = 0; i < 250; i++) 
                {
                    // Create a variable to store data from the input file and write to the
                    // serial port.
                    char data_byte ;
                    usleep(1000) ;
      
                    std::string my_string = (data_control);
                    serial_port.Write( my_string );

                    //usleep(1000) ; //1s Cambio de letra en misma pos.
                    //std::string my_string1 = ("B");
                    //serial_port.Write( my_string1 );

                    usleep(1000) ;
                    // Write the data to the serial port.
                    //serial_port.WriteByte(data_byte) ;

                    // Wait until the data has actually been transmitted.
                    serial_port.DrainWriteBuffer() ;

                    // Print to the terminal what is being written to the serial port.
                    //std::cout << data_byte ;
                }

                // Successful program completion.
                std::cout << "Done. " << std::endl ;
                
                    break;          
                }
        
            case 2 : {
                // Wait for data to be available at the serial port.
            std::cout << "Select Pin to Read [EX. A0]  << " << std::flush;
            std::string data_controlUSER;
            std::cin >> data_controlUSER;
            
            //Command R is declared as asking for a READ in the specified input.
            std::string data_control;
            std::string data_controlCOMMAND = ("R");
            data_control = data_controlCOMMAND + data_controlUSER;
            for (int i = 0; i < 250; i++) 
                {
                    // Create a variable to store data from the input file and write to the
                    // serial port.
                    char data_byte ;
                    usleep(1000) ;
      
                    std::string my_string = (data_control);
                    serial_port.Write( my_string );

                    usleep(1000) ;

                    // Wait until the data has actually been transmitted.
                    serial_port.DrainWriteBuffer() ;

                }

                // Successful program completion.
                std::cout << "[...]Contacting Arduino" << std::endl ;

            //RX Receiver.
            while(!serial_port.IsDataAvailable()) 
            {
                usleep(10000) ;
                break;
            }

            // Specify a timeout value (in milliseconds).
            size_t ms_timeout = 1000;

            // Char variable to store data coming from the serial port.
            char data_byteRead ;

            // Read one byte from the serial port and print it to the terminal.
            try
            {
                // Read a single byte of data from the serial port.
                serial_port.ReadByte(data_byteRead, ms_timeout) ;

                // Show the user what is being read from the serial port.
                std::cout << data_byteRead << std::flush ;
            }
            catch (const ReadTimeout&)
            {
                std::cerr << "   [...]Waiting response" << std::endl ;
            }

            // Wait a brief period for more data to arrive.
            usleep(1000) ;

            DataBuffer read_buffer ;

            try
            {
                // Read as many bytes as are available during the timeout period.
                serial_port.Read(read_buffer, 0, ms_timeout) ;
            }
            catch (const ReadTimeout&)
            {
                for (size_t i = 0 ; i < read_buffer.size() ; i++)
                {
                    std::cout << read_buffer.at(i) << std::flush ;
                }

                std::cerr << "   ...Data received." << std::endl ;
            }

            // Successful program completion.
            std::cout << "Done" << std::endl ;
              
                break;
            }

            case 3 : {
                return EXIT_SUCCESS ;
            }     
       }
    }       
}
