##OpenCV, Video file load and display example source code (using VideoCapture function)
~~~
//file load
 VideoCapture capture(".\\video.avi");
 Mat frame;

 //check
 if( !capture.isOpened() )
 {
  printf("AVI file can not open.\n");
  return;
 }
 
 //create window
 namedWindow("w");
 
 while(1)
 {
  //grab frame from file & throw to Mat
  capture >> frame;
  if(frame.empty() ) //Is video end?
   break;
  
  //processing example
  Sobel(frame,frame,frame.depth(),1,0);
  ////////////////////

  //display and delay
  imshow("w", frame);
  if(waitKey(10) > 0)
   break;
 }
~~~
