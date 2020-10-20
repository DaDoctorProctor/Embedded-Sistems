#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkAxesActor.h>
#include <vtkTransform.h>

#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
//OpenCV 4
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sstream>


//Others
#include <thread>
#include <mutex>

int global01 = 0;
int global02 = 0;
int globalEnd = 0;

std::mutex m;

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
     int iSliderValue2 = 0;
     createTrackbar("Contrast", "戦闘妖精雪風", &iSliderValue2, 100);

    //Trackbar 01
     int iSlider01 = 0;
     createTrackbar("Sein", "戦闘妖精雪風", &iSlider01, 360);
    
    //Trackbar 02
     int iSlider02 = 0;
     createTrackbar("Rotate X", "戦闘妖精雪風", &iSlider02, 360);

    //Trackbar End
     int iSliderEnd = 0;
     createTrackbar("End", "戦闘妖精雪風", &iSliderEnd, 1); 
       
       
    while (true) {
          Mat dst;        
          int iBrightness  = iSliderValue1 - 50;
          double dContrast = iSliderValue2 / 50.0;
          src.convertTo(dst, -1, dContrast, iBrightness); 
          
          m.lock();
          global01 = iSlider01;
          global02 = iSlider02;
          globalEnd = iSliderEnd;
          m.unlock();
          
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


int main ( int argc, char *argv[] )
{

  argc = 2;
  
  std::thread first (second_runner);

  std::string inputFilename01 = "01BaseMain.STL";
  std::string inputFilename02 = "02BaseGiratory.STL";
  std::string inputFilename03 = "03ArmO1.STL";
  std::string inputFilename04 = "04ArmO2.STL";
  //"01BaseMain.STL"
  //"02BaseGiratory.STL"
  //"03ArmO1.STL"
  //"04ArmO2.STL"

  vtkSmartPointer<vtkSTLReader> reader =
    vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(inputFilename01.c_str());
  reader->Update();
  

  if ( argc != 2 )
    {
    cout << "Required parameters: Filename" << endl;
    return EXIT_FAILURE;
    }

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);


  //Object 2
  vtkSmartPointer<vtkSTLReader> reader02 =
    vtkSmartPointer<vtkSTLReader>::New();
  reader02->SetFileName(inputFilename02.c_str());
  reader02->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper02 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper02->SetInputConnection(reader02->GetOutputPort());

  vtkSmartPointer<vtkActor> actor02 =
    vtkSmartPointer<vtkActor>::New();
  actor02->SetMapper(mapper02);

  actor02->SetOrigin(25,25,0);
  actor02->SetPosition(6,0,10);
  actor02->RotateZ(0);

  //Object 3
  vtkSmartPointer<vtkSTLReader> reader03 =
    vtkSmartPointer<vtkSTLReader>::New();
  reader03->SetFileName(inputFilename03.c_str());
  reader03->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper03 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper03->SetInputConnection(reader03->GetOutputPort());

  vtkSmartPointer<vtkActor> actor03 =
    vtkSmartPointer<vtkActor>::New();
  actor03->SetMapper(mapper03);

  //actor03->SetPosition(7.5,29,54); //parado a 90 en x
  actor03->SetPosition(7.5,21,54); //parado a 0 en x
  
  //actor03->SetOrigin(1,1,0);
  //actor03->RotateX(0);
  //actor03->RotateY(0);
  //actor03->SetOrigin(0,0,0);

  //Object 4
  vtkSmartPointer<vtkSTLReader> reader04 =
    vtkSmartPointer<vtkSTLReader>::New();
  reader04->SetFileName(inputFilename04.c_str());
  reader04->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper04 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper04->SetInputConnection(reader04->GetOutputPort());

  vtkSmartPointer<vtkActor> actor04 =
    vtkSmartPointer<vtkActor>::New();
  actor04->SetMapper(mapper04);

  //actor04->RotateWXYZ(0,0,0,0);
  actor04->SetPosition(8.5,22,132);
  actor04->RotateX(90);
  actor04->RotateY(90);

  //Render
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  //dvi

  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(75.0, 0.0, 0.0);

  vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
  
  // The axes are positioned with a user transform
  axes->SetUserTransform(transform);
  
  //Rendering initial conditions.
  renderer->AddActor(axes);
  renderer->AddActor(actor);
  renderer->AddActor(actor02);
  renderer->AddActor(actor03);
  renderer->AddActor(actor04);
  renderer->SetBackground(.627, .1725,.819 ); // Background color green
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  while (true)
  {
    
    if (globalEnd >= 1){

      renderWindow->Finalize();
      renderWindowInteractor->TerminateApp();
      first.detach();
      return EXIT_SUCCESS;
      break;

    } else if (globalEnd <= 0) {

      actor03->SetOrigin(3.9,3.9,3.9);
      actor03->RotateX(global02);
      renderer->AddActor(actor03);
      renderWindow->Render();
      renderWindowInteractor->Start();
      usleep(100000);
      
    }
    usleep(10000);
    
    
  }
  //return EXIT_SUCCESS;
}
