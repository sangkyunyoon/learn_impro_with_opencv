##[Mat point access method, get pixel](http://study.marearts.com/2014/04/opencv-study-mat-point-access-method.html) 
1. At approach

Mat image (ROW, COL, CV_TYPE);
image.at (WANT_ROW, WANT_COL);

- ROW: Row
- COL: Column
- CV_TYPE: data type ( for example : CV_8UC3 = 8 bit 3 channels)
- DATA_TYPE: Mat creation data type ( for example : float, usigned char)
- WANT_ROW: access to the desired row
- WANT_COL: access to the desired column

[Advantage]: Access after validation progress , so safe and accurate approach .
[Disadvantage]:  most slow in 3 ways.

2. Ptr approach
Mat image (ROW, COL, CV_TYPE);
image.ptr (WANT_ROW, WANT_COL); (This access is changed to the Point)

- ROW: Row
- COL: Column- CV_TYPE: data type ( for example : CV_8UC3 = 8 bit 3 channels)
- DATA_TYPE: Mat creation data type ( for example : float, usigned char)
- WANT_ROW: access to the desired row
- WANT_COL: access to the desired column

[Advantage]: Access is faster than first way.
[Disadvantage]: direct access to the data , but way slower than third way .



3. Data approach
Mat image (ROW, COL, CV_TYPE);
DATA_TYPE * data = (DATA_TYPE *) image.data;data [WANT_ROW * image.cols + WANT_COL]

- ROW: Row
- COL: Column
- CV_TYPE: data type ( for example : CV_8UC3 = 8 bit 3 channels)
- DATA_TYPE: Mat creation data type ( for example : float, usigned char)
- WANT_ROW: access to the desired row
- WANT_COL: access to the desired column

[Advantage]: very fast.
[Disadvantage]: not check validation ,  it is hard to know inadequate access.

##[OpenCV Pixel Access, at, ptr, data, iteration (example)](http://study.marearts.com/2016/06/opencv-pixel-access-at-ptr-data.html)
~~~
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
    namedWindow("img", 1);
    Mat img = imread("anapji.jpg");
    
    if (img.depth() == CV_8U)
        printf("8bit unsigend\n");

    img.

    /*
    cout << img.elemSize() << endl;
    cout << img.channels() << endl;
    cout << img.rows << endl;
    cout << img.step << endl;
    */

    //using data
    //for (int i = img.rows / 10 * 7; i < img.rows / 10 * 8; i++) {

    //for (int i = 0; i < img.rows ; i++) {

    for (int i = img.rows / 10 * 7; i < img.rows / 10 * 8; i++) {
        for (int j = 0; j < img.cols; j++) {


            unsigned char r, g, b;

            b = img.data[i * img.step + j * img.elemSize() + 0];
            g = img.data[i * img.step + j * img.elemSize() + 1];
            r = img.data[i * img.step + j * img.elemSize() + 2];

            img.data[i * img.step + j * img.elemSize() + 0] = unsigned char(255 - b);
            img.data[i * img.step + j * img.elemSize() + 1] = unsigned char(255 - g);
            img.data[i * img.step + j * img.elemSize() + 2] = unsigned char(255 - r);

        }
    }

    //using at
    for (int i = img.rows / 10 * 2; i < img.rows / 10 * 3; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            //Vec3b means 'uchar 3ch'
            unsigned char b = img.at< cv::Vec3b>(i, j)[0];
            unsigned char g = img.at< cv::Vec3b>(i, j)[1];
            unsigned char r = img.at< cv::Vec3b>(i, j)[2];

            //printf("%d %d %d\n", b, g, r);

            img.at< cv::Vec3b>(i, j)[0] = unsigned char(255 - b); //b
            img.at< cv::Vec3b>(i, j)[1] = unsigned char(255 - g); //g
            img.at< cv::Vec3b>(i, j)[2] = unsigned char(255 - r); //r
        }
    }

    //using ptr
    for (int i = img.rows / 10 * 5; i < img.rows / 10 * 6; i++) {

        cv::Vec3b* ptr = img.ptr< cv::Vec3b >(i);

        for (int j = 0; j < img.cols; j++) {

            unsigned char b1 = (ptr[j][0]);
            unsigned char g1 = (ptr[j][1]); //note!!
            unsigned char r1 = (ptr[j][2]);


            cv::Vec3b bgr = ptr[j];
            unsigned char b2 = (bgr[0]);
            unsigned char g2 = (bgr[1]); //note!!
            unsigned char r2 = (bgr[2]);

            

            ptr[j] = cv::Vec3b(255 - b1, 255 - g1, 255 - r1);

        }
    }

    //using iteration
    cv::MatIterator_< cv::Vec3b> itd = img.begin< cv::Vec3b>(), itd_end = img.end< cv::Vec3b>();

    for (int i = 0; itd != itd_end; ++itd, ++i) {

        cv::Vec3b bgr = (*itd);

        (*itd)[0] = 255 - bgr[0];
        (*itd)[1] = 255 - bgr[1];
        (*itd)[2] = 255 - bgr[2];
    }

    

    imshow("img", img); //show
    waitKey(0);

    destroyAllWindows();

    return 0;
}
~~~

##(OpenCV, data type change, copy) vector to Mat, Mat to vector

This post is about how to copy Mat data to vector and copy vector data to Mat.
Reference this example source code.

~~~
printf("/////////////////////////////////////////////////////////////\n");
 printf("//vector to Mat\n");
 int r=3;
 int c=4;

 vector< float> Vf;

 //insert value
 int cnt=0;
 for(int i=0; i< c; ++i) 
  for(int j=0; j< r; ++j)  
   Vf.push_back(cnt++);
  
 //create Mat
 Mat M=Mat(r,c,CV_32FC1);
 //copy vector to mat
 memcpy(M.data,Vf.data(),Vf.size()*sizeof(float));

 //print Mat
 cout < <  M < <  endl;


 printf("/////////////////////////////////////////////////////////////\n");
 printf("//Mat to vector\n");
 vector< float> Vf2;
 //copy mat to vector
 Vf2.assign((float*)M.datastart, (float*)M.dataend);
 
 //confirm
 cnt=0;
 for(int i=0; i< c; ++i)
 {
  for(int j=0; j< r; ++j)  
   printf("%lf ", Vf2[cnt++]);
  printf("\n");
}
~~~

##(OpenCV, Mat class) Image buffer(point) copy to Mat
when you want to copy "unsigned char * pData" image buffer to Mat class in OpenCV.

This source is simple example code.
~~~
 Mat InImg(height, width, CV_8UC1);
 memcpy(InImg.data, pData, sizeof(unsigned char)*width*height);
~~~

##OpenCV Mat copyTo, Clone, ROI example code
~~~
Mat img = imread("ss.jpg");
 
 Rect r(img.cols / 4, img.rows / 4, img.cols / 4 * 2, img.rows / 4 * 2);

 //clone #1
 Mat img2 = img.clone();
 bitwise_not(img2, img2);

 //clone #2
 Mat img5 = img(r).clone();


 //copyTo #1
 Mat cimg;
 img.copyTo(cimg);

 //copyTo #2
 Mat cimg2;
 img(r).copyTo(cimg2);

 //copyTo #3
 Mat cimg3( Size(img.cols*2, img.rows), img.type() );
 cimg3.setTo(255);
 img.copyTo(cimg3(Range::all(), Range(0, img.cols)));
 img2.copyTo(cimg3(Range::all(), Range(img2.cols, img2.cols * 2)));

 //set roi
 Mat roi(img, r);
 //invert color
 bitwise_not(roi, roi);


 namedWindow("img2", 0); //make window
 imshow("img2", cimg); //show
 namedWindow("img3", 0); //make window
 imshow("img3", cimg2); //show
 namedWindow("img4", 0); //make window
 imshow("img4", cimg3); //show
 namedWindow("img5", 0); //make window
 imshow("img5", img5); //show
 namedWindow("img", 0); //make window
 imshow("img", img); //show
 
 waitKey(0);
~~~

##Keycode and ascii code

http://study.marearts.com/2016/11/keycode-and-ascii-code.html

