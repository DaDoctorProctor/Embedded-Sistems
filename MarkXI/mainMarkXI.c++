/**
 *  Arduino C++ Linux designed by かつらぎ. Version Mark Elf XI
 */

//Libserial
#include <libserial/SerialPort.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sstream>
constexpr const char* const SERIAL_PORT_2 = "/dev/ttyACM0" ;


//OpenCV 4
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

//Others
#include <thread>


/**
 * @brief This is a file designed by かつらぎ, which controls basic serial communication
 * with Arduino Uno and C++, all rights reserved to the respective owner of libserial.
 */

//Global variable pool
int global1 = 0;
int globalPWM6 = 0;
int globalD13 = 0;
int globalA0 = 0;
//
int globalA0_B[4] = {0, 0, 0, 0};
//
int last_sent_value_globalD13 = 0;
int last_sent_value_globalPWM6 = 0;
//Bools
int ON = 1;

void second_runner() {

    // Read original image 

     Mat src = imread("white.png");
     

     //if fail to read the image
     if (!src.data) 
     { 
          cout << "Error loading the image" << endl;
          
     }

     // Create a window
     namedWindow("戦闘妖精雪風", 1);
     // Set size
     cv::resizeWindow("戦闘妖精雪風", 300, 700);
     //Create trackbar to change brightness
     int iSliderValue1 = 100;
     createTrackbar("Brightness", "戦闘妖精雪風", &iSliderValue1, 100);

     //Create trackbar to change contrast
     int iSliderValue2 = 100;
     createTrackbar("Contrast", "戦闘妖精雪風", &iSliderValue2, 100);

    //Trackbar Mark Sein
     int iSliderMarkSein = 30;
     createTrackbar("Sein", "戦闘妖精雪風", &iSliderMarkSein, 255);
    
    //Trackbar D13
     int iSliderD13 = 0;
     createTrackbar("D13", "戦闘妖精雪風", &iSliderD13, 1);
       
       
    while (true) {
          Mat dst;        
          int iBrightness  = iSliderValue1 - 50;
          double dContrast = iSliderValue2 / 50.0;
          src.convertTo(dst, -1, dContrast, iBrightness); 

          globalPWM6 = iSliderMarkSein;
          globalD13 = iSliderD13;
          
          char dataA0_ichi = static_cast<char>(globalA0_B[0]);
          char dataA0_ni = static_cast<char>(globalA0_B[1]);
          char dataA0_san = static_cast<char>(globalA0_B[2]);
          char dataA0_yon = static_cast<char>(globalA0_B[3]);
         
            std::string dataA0_ichi_str;
	        std::stringstream s0;
	        s0 << dataA0_ichi;
	        s0 >> dataA0_ichi_str;

            std::string dataA0_ni_str;
	        std::stringstream s1;
	        s1 << dataA0_ni;
	        s1 >> dataA0_ni_str;
            
            std::string dataA0_san_str;
	        std::stringstream s2;
	        s2 << dataA0_san;
	        s2 >> dataA0_san_str;
            
            std::string dataA0_yon_str;
	        std::stringstream s3;
	        s3 << dataA0_yon;
	        s3 >> dataA0_yon_str;

            string str = "A0x" + dataA0_ichi_str + dataA0_ni_str + dataA0_san_str + dataA0_yon_str;
            
            cv::putText(
                dst,
                str, //STRING NAME
                cv::Point(25,75),
                cv::FONT_HERSHEY_SIMPLEX,
                1, // STRING SIZE
                cv::Scalar(0,0,0),
                3
            );
           
          //show the brightness and contrast adjusted image
          imshow("戦闘妖精雪風", dst);

          // Wait until user press some key for 50ms
          int iKey = waitKey(50);

          //if user press 'ESC' key
          if (iKey == 9)
          {
               break;
          }
      
    }
    
}

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

    std::cout << "Program developed by かつらぎ. Running version Mark Elf XI, developed for Arduino Uno. \n ";
    
    std::thread first (second_runner);

    while (true)
    {  
                            
            std::string KamiString = std::to_string (globalPWM6);
            string KamiString2 = "SV";
            std::string StringDataControl;   

            //Command filter
            if (globalPWM6 >= 100){
                StringDataControl = KamiString2 + KamiString;}
            else if (globalPWM6 < 100 && globalPWM6 >= 10){
                StringDataControl = KamiString2 + "0" + KamiString;    
            }else{
                StringDataControl = KamiString2 + "00" + KamiString;
            }   
            int current_value_globalPWM6 = globalPWM6;
            if (current_value_globalPWM6 != last_sent_value_globalPWM6) {                     
                last_sent_value_globalPWM6 = current_value_globalPWM6;
            for (int i = 0; i < 1; i++) 
                {
                    usleep(1000) ;
      
                    std::string my_string = (StringDataControl);
                    serial_port.Write( my_string );

                    usleep(10000) ;

                    // Wait until the data has actually been transmitted.
                    serial_port.DrainWriteBuffer() ;   
                }
                usleep(1000000);
            }
            //Command filter D13
            std::string D13_str = std::to_string (globalD13);
            string DigitalCommand = "W";
            std::string D13_str_control;
            
            if (globalD13 == 1){
                D13_str_control = DigitalCommand + "131";}
            else if (globalD13 == 0){
                D13_str_control = DigitalCommand + "130";  
            }
            
            int current_value_globalD13 = globalD13;

            if (current_value_globalD13 != last_sent_value_globalD13) {                     
                last_sent_value_globalD13 = current_value_globalD13;
                for (int i = 0; i < 1; i++) 
                {
                    usleep(1000) ;
                    //std::string my_string = (data_control);
                    std::string my_string = (D13_str_control);
                    serial_port.Write( my_string );
                    usleep(10000) ;

                    // Wait until the data has actually been transmitted.
                    serial_port.DrainWriteBuffer() ;     
                }
                usleep(1000000);
            }
            
                // Wait for data to be available at the serial port.
            std::cout << "Select Pin to Read [EX. A0]  << " << std::flush;
            std::string data_controlUSER;
            data_controlUSER = "A0";
            
            //Command R is declared as asking for a READ in the specified input.
            std::string data_control;
            std::string data_controlCOMMAND = ("R");
            data_control = data_controlCOMMAND + data_controlUSER;
            for (int i = 0; i < 1; i++) 
                {
                    // Create a variable to store data from the input file and write to the
                    // serial port.
                    char data_byte ;
                    usleep(1000) ;
      
                    std::string my_string = (data_control);
                    serial_port.Write( my_string );

                    usleep(10000) ;

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
            //Clear Buffer
            
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
                globalA0_B[0] = 48;globalA0_B[1] = 48; globalA0_B[2] = 48; globalA0_B[3] = 48;
                for (size_t i = 0 ; i < read_buffer.size() ; i++)
                {
                    usleep(100);
                    globalA0_B[0] = data_byteRead;
                    globalA0_B[i+1] = read_buffer.at(i);
                    std::cout << read_buffer.at(i) << std::flush ;
                      
                }
                std::cerr << "   ...Data received." << std::endl ;
            }

            int iKeyx = waitKey(50);

            if (iKeyx == 9)
            {
               first.detach();
               return EXIT_SUCCESS ;
               break;
            }   
    }       
}
