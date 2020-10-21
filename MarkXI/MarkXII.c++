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
#include <vtkProp3D.h>

/*#include <vtkJPEGReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkImageCheckerboard.h>*/

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
std::mutex m;

//$Global integers$
//Second runner
int global01 = 0;
int global02 = 0;
int global03 = 0;
int global04 = 0;
int global05 = 0;
int global06 = 0;
//Class VTK
int last_sent_value_time = 0;
int last_pos_act4 = 0;
int last_pos_act3 = 0;
int last_pos_act2 = 0;
double RX [3];
double RZ [3];
void second_runner() { //Second runner for OpenCV

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
     createTrackbar("Brightness Test Type", "戦闘妖精雪風", &iSliderValue1, 100);

     //Create trackbar to change contrast
     int iSliderValue2 = 0;
     createTrackbar("Contrast Test Type", "戦闘妖精雪風", &iSliderValue2, 100);

    //Trackbar 01
     int iSlider01 = 0;
     createTrackbar("Sein Test Type", "戦闘妖精雪風", &iSlider01, 180);
    
    //Trackbar 02
     int iSlider02 = 0;
     createTrackbar("Rotate X", "戦闘妖精雪風", &iSlider02, 90);
    
    //Trackbar 03
     int iSlider03 = 0;
     createTrackbar("Move X", "戦闘妖精雪風", &iSlider03, 90);

    //Trackbar 04
     int iSlider04 = 0;
     createTrackbar("Move Y", "戦闘妖精雪風", &iSlider04, 90);
    
    //Trackbar 05
     int iSlider05 = 0;
     createTrackbar("Move Z", "戦闘妖精雪風", &iSlider05, 90);

    //Trackbar 06
     int iSlider06 = 0;
     createTrackbar("Rotate Z", "戦闘妖精雪風", &iSlider06, 180); 

    while (true) {
          Mat dst;        
          int iBrightness  = iSliderValue1 - 50;
          double dContrast = iSliderValue2 / 50.0;
          src.convertTo(dst, -1, dContrast, iBrightness); 
          
          m.lock();
          global01 = iSlider01;
          global02 = iSlider02;
          global03 = iSlider03;
          global04 = iSlider04;
          global05 = iSlider05;
          global06 = iSlider06;
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

class vtkTimerCallback2 : public vtkCommand //Class for VTK timer
{
public:
  vtkTimerCallback2() = default;

  static vtkTimerCallback2* New()
  {
    vtkTimerCallback2* cb = new vtkTimerCallback2;
    cb->TimerCount = 0;
    return cb;
  }

  virtual void Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData))
  {
    if (vtkCommand::TimerEvent == eventId) //Stop counter when equal to eventId
    {
      ++this->TimerCount;
    }
    //Timer in console output.
    //std::cout << this->TimerCount << std::endl; 

    //actor->SetPosition(this->TimerCount, this->TimerCount, 0); //Actor position
    
    //Run events that will happen when the time starts ticking.
    int current_value_time = this->TimerCount;
    if (current_value_time != last_sent_value_time) {
      actor03->GetOrientation(RX);
      int RXint = int(RX[0]);
      int current_pos_act3 = global02;
      actor03->SetOrigin(25,4,4);
      if (current_pos_act3 != last_pos_act3){
        int xi = RXint;
        int xf = global02;
        //actor03->SetOrigin(0,4,4);
        //actor03->SetOrigin(0,4,500);
        //ゼロと九十は止めるです。
        if(xf == 90){
          xf = 89;
        }else if(xf == 1){
          xf = 0;
        }
        
        if(xi > xf){
          actor03->RotateX(-1);
        }else if(xf == RXint){
          actor03->RotateX(0);
        }else if(xf > xi){
          actor03->RotateX(1);
        }
        current_pos_act3 == last_pos_act3; 
      }
      std::cout << RXint << std::endl;

      //Actor 2 - Action!
      int current_pos_act2 = global06;
      actor02->GetOrientation(RZ);
      int RZint = int(RZ[2]);
      //actor02->RotateZ(POSZ);   
      if (current_pos_act2 != last_pos_act2){
        int xi = RZint;
        int xf = global06;
        //ゼロと九十は止めるです。
        if(xf == 1){
          xf = 0;
        }else if(xf == 180){
          xf = 189;
        }
        
        if(xi > xf){
          actor02->RotateZ(-1);
          actor03->RotateZ(-1);
        }else if(xf == RXint){
          actor02->RotateZ(0);
          actor03->RotateZ(0);
        }else if(xf > xi){
          actor02->RotateZ(1);
          actor03->RotateZ(1);
        }
        current_pos_act2 == last_pos_act2; 
      }

      //std::cout << orentation[0] << std::endl;
      last_sent_value_time = current_value_time;
    }

    if (this->TimerCount < this->maxCount)
    {
      vtkRenderWindowInteractor* iren =
          dynamic_cast<vtkRenderWindowInteractor*>(caller);
      iren->GetRenderWindow()->Render();
    }
    else
    {
      vtkRenderWindowInteractor* iren =
          dynamic_cast<vtkRenderWindowInteractor*>(caller);
      if (this->timerId > -1)
      {
        iren->DestroyTimer(this->timerId);
      }
    }
  }

private:
  int TimerCount = 0;

public:
  vtkActor* actor03 = nullptr;
  vtkActor* actor02 = nullptr;
  int timerId = 0;
  int maxCount = -1;
};


int main ( int argc, char *argv[] )
{

  argc = 2;
  
  std::thread first (second_runner);

  std::string inputFilename01 = "01BaseMain.STL"; //"01BaseMain.STL"
  std::string inputFilename02 = "02BaseGiratory.STL"; //"02BaseGiratory.STL"
  std::string inputFilename03 = "03ArmO1.STL"; //"03ArmO1.STL"
  std::string inputFilename04 = "04ArmO2.STL"; //"04ArmO2.STL"

  if ( argc != 2 )
    {
    cout << "Required parameters: Filename" << endl;
    return EXIT_FAILURE;
    }

  // Visualize
  // Object 1
  vtkSmartPointer<vtkSTLReader> reader =
    vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(inputFilename01.c_str());
  reader->Update();

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

  actor03->SetPosition(7.5,21,54); //parado a 0 en x
  
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
  
  //Setting the clock to start the process.
  auto cb = vtkSmartPointer<vtkTimerCallback2>::New();
  cb->actor03 = actor03;
  cb->actor02 = actor02;
  renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, cb);

  int timerId = renderWindowInteractor->CreateRepeatingTimer(30);
  std::cout << "timerId: " << timerId << std::endl;
  cb->maxCount = 60000; // Destroy the timer when maxCount is reached.
  cb->timerId = timerId;
  
  renderWindowInteractor->Start(); // Start the interaction and timer


  /*while (true)
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
    }
  }*/

  return EXIT_SUCCESS;
}
