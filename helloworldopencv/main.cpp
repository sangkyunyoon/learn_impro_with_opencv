#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat ssread(int flags) {
    return imread("ss.jpeg", flags);
}

void helloworld() {
    Mat mtx(3, 3, CV_32F); // make a 3 x 3 floating-point matrix
    Mat cmtx(10, 1, CV_64FC2); //make a 10 x 1 2-channel floating-point

    Mat img(Size(5,3), CV_8UC3); // make a 3-channel (color) image of 1920 columns and 1080 rows
    // matrix 4 x 3 -> image/video width 3, height 4

    //Created after the declaration
    Mat mtx2 = Mat(3, 3, CV_32F);
    Mat cmtx2 = Mat(10, 1, CV_64FC1); //CV_64FC1 = CV_64F

    //Create a point
    Mat* mtx3 = new Mat(3, 3, CV_32F);
    delete mtx3;

    //value set an print
    mtx.setTo(10);
    cout << mtx << endl;

    cmtx2.setTo(11);
    cout << cmtx2 << endl;
}

void firstMatUse() {
    Mat m = Mat(3, 3, CV_64F);
    m = m * 3;
    cout << m << endl;

    double dm[3][3] = {
            {1, 2, 1},
            {0, 1, 1},
            {1, 0, 0}
    };
    Mat m2 = Mat(3, 3, CV_64F, dm);
    cout << m2 << endl;

    cout << m + m2 << endl << endl;
    cout << m - m2 << endl << endl;
    cout << m * m2 << endl << endl;
    cout << m.mul(m2) << endl << endl; //multiple
    cout << m / m2 << endl << endl;
    cout << m2.inv() << endl << endl; //행과 열의 크기가 같아야한다.
    cout << m2.t() << endl << endl; //전치행렬

    m2 = m + m2;
    cout << m2 << endl << endl;

    dm[2][2] = 1000;
    cout << m2 << endl << endl;
}

void FirstMatUse2() {
    namedWindow("img", 0);

    Mat img = ssread(1);
    imshow("img", img); //show image

    Mat img2;
    Sobel(img, img2, img.depth(), 1, 0);
    imshow("img2", img2); //show image

    Mat img3;
    flip(img, img3, 1);
    imshow("img3", img3);

    waitKey(0);
    destroyAllWindows();
}

void MatAndImageVideo() {
    Mat img = ssread(1);
    namedWindow("image", 0); //resizable 0, fixed 1
    imshow("image", img);

    waitKey(0);
    destroyAllWindows();
}

void MatAndImageVideo2() {
    Mat img = ssread(0);

    namedWindow("imageWindow", 1); //resizable 0, fixed 1
    imshow("imageWindow", img);

    while(1) {
        int keyValue = waitKey(0);
        cout << keyValue << endl;

        if(keyValue == 'c') {
            break;
        }
    }
    destroyAllWindows();
}

void MatAndImageVideo3() {

    VideoCapture capture("small.avi");
    Mat frame;

    if(!capture.isOpened()) {
        cout << "AVI file can not open." << endl;
        return;
    }
    namedWindow("w");
    while(1) {
        capture >> frame;
        if(frame.empty()) {
            break;
        }

        Sobel(frame,frame,frame.depth(),1,0);

        imshow("w", frame);
        if(waitKey(10) == 27 )
            break;
    }
    destroyAllWindows();
}

void MatAndImageVideo4() {
    namedWindow("img", 0);

    Mat img = ssread(1);
    bitwise_not(img, img);
    imshow("img", img);

    Mat img_s = img;
    bitwise_not(img, img);
    imshow("img_s", img_s);

    waitKey(0);
    destroyAllWindows();
}

void MatAndImageVideo5() {
    namedWindow("img", 0);

    Mat img = ssread(1);
    bitwise_not(img, img);
    imshow("img", img);

    Mat img2 = img.clone();
    bitwise_not(img, img);
    imshow("img2", img2);

    Rect r(img.cols / 4, img.rows / 4, img.cols / 4 * 2, img.rows / 4 * 2);
    cout << r << endl;

    //clone
    Mat img5 = img(r).clone();
    imshow("img5", img5);

    //copyTo #1
    Mat cimg;
    img.copyTo(cimg);
    imshow("cimg", cimg);

    //copyTo #2
    Mat cimg2;
    img(r).copyTo(cimg2);
    imshow("cimg2", cimg2);

    Mat cimg3(Size(img.cols * 2, img.rows), img.type());
    cimg3.setTo(255);
    img.copyTo(cimg3(Range::all(), Range(0, img.cols)));
    img2.copyTo(cimg3(Range::all(), Range(img2.cols, img2.cols * 2)));
    imshow("cimg3", cimg3);

    Mat roi(img, r);
    bitwise_not(roi, roi);
    imshow("roi", roi);

    waitKey(0);
    destroyAllWindows();
}
void ImageReadingAndPixelAccessInMat() {
    namedWindow("img", 1);
    Mat img = ssread(1);

    cout << img.elemSize() << endl; //픽셀의 바이트 사이즈
    cout << img.channels() << endl; //채널 수
    cout << img.rows << endl; //행의 수
    cout << img.cols << endl; //렬의 수
    cout << img.step << endl; //가로의 실제 바이트 사이즈
    cout << img.step / img.rows << endl;

    if (img.depth() == CV_8U)
        cout << "8bit unsigend" << endl;

    //using data
    //for (int y = 0; y < img.rows; y++) {
    for (int y = img.rows / 10 * 7; y <  img.rows / 10 * 8; y++) {
        for (int x = 0; x < img.cols; x++) {

            uchar r, g, b;
            b = img.data[y * img.step + x * img.elemSize() + 0]; //(x,y)의 위치는 y * img.step: y의 위치로 몇 번째 행을 가리키는지 높이 값, x * img.elemSize:
            g = img.data[y * img.step + x * img.elemSize() + 1];
            r = img.data[y * img.step + x * img.elemSize() + 2];

            img.data[y * img.step + x * img.elemSize() + 0] = uchar(255 - b);
            img.data[y * img.step + x * img.elemSize() + 1] = uchar(255 - g);
            img.data[y * img.step + x * img.elemSize() + 2] = uchar(255 - r);
        }
    }

    //using at
    for (int y = img.rows / 10 * 2; y <  img.rows / 10 * 3; y++) {
        for (int x = 0; x < img.cols; x++) {

            uchar r, g, b;
            b = img.at<Vec3b>(y, x)[0];
            g = img.at<Vec3b>(y, x)[1];
            r = img.at<Vec3b>(y, x)[2];

            img.at<Vec3b>(y, x)[0] = uchar(255 - b);
            img.at<Vec3b>(y, x)[1] = uchar(255 - g);
            img.at<Vec3b>(y, x)[2] = uchar(255 - r);
        }
    }

    //using pointer
    for (int y = img.rows / 10 * 5; y <  img.rows / 10 * 6; y++) {

        Vec3b* ptr = img.ptr<Vec3b>(y);

        for (int x = 0; x < img.cols; x++) {
            //1번 방식
            uchar b1, g1, r1;
            b1 = ptr[x][0];
            g1 = ptr[x][1];
            r1 = ptr[x][2];

            //2번 방식 - 추천
            Vec3b brg = ptr[x];
            uchar b2, g2, r2;
            b2 = brg[0];
            g2 = brg[1];
            r2 = brg[2];

            ptr[x] = Vec3b(255 - b2, 255 - g2, 255 - r2);
        }
    }

    //using iteration
    MatIterator_<Vec3b> itd = img.begin<Vec3b>(), itd_end = img.end<Vec3b>();
    for (int i = 0; itd != itd_end; ++itd, ++i) {
        Vec3b bgr = (*itd);
        (*itd)[0] = 255 - bgr[0];
        (*itd)[1] = 255 - bgr[1];
        (*itd)[2] = 255 - bgr[2];
    }

    imshow("img", img);
    waitKey(0);
    destroyAllWindows();
}

int MatAndImageVideoWrite()
{
    namedWindow("img", 1);
    Mat img = ssread(1);
    imshow("img", img);
    waitKey(0);

//    imwrite("new_img.jpg", img);
//    imwrite("new_img.bmp", img);
//    imwrite("new_img.tif", img);
//    imwrite("new_img.png", img);

    Mat img2;
    Sobel(img, img2, CV_8U, 1, 0);
    imwrite("sobel_img.png", img2);

    vector<Mat> bgrMat(3);
    split(img, bgrMat);

    imwrite("b.jpg", bgrMat[0]);
    imwrite("g.bmp", bgrMat[1]);
    imwrite("r.tif", bgrMat[2]);

    cout << img.channels() << endl;
    cout << bgrMat[0].channels() << endl;

    //video
    VideoCapture capture("small.avi");
    Mat frame;

    //set properties
    int askFileTypeBox = 0; //-1 is show box of codec
    int color = 1;
    Size s = Size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));

    VideoWriter outVideo;
    outVideo.open("small_out.avi", askFileTypeBox, capture.get(CAP_PROP_FPS), s, color);

    if(!capture.isOpened())
    {
        cout << "AVI file can not open" << endl;
        return 0;
    }

    namedWindow("w");

    while(1)
    {
        capture >> frame;
        if(frame.empty())
        {
            break;
        }
        Sobel(frame, frame, frame.depth(), 1, 0);
        //1번
        outVideo.write(frame);
        //2번
        //outVideo << frame;

        //display and delay
        imshow("w", frame);
        if(waitKey(10) > 0)
        {
            break;
        }
    }
    destroyAllWindows();

    return 0;
}

void MatAndMatrix()
{
    //namedWindow("img", 1);
    Mat Ma = Mat::eye(3, 3, CV_64FC1);
    cout << "Ma " << endl << Ma << endl;
    double dm[3][3] = {{1,2,3}, {4,5,6,}, {7,8,9}};
    Mat Mb = Mat(3, 3, CV_64F, dm);
    cout << "Mb " << endl << Mb << endl << endl;

    Mat Mc;
    Mc = Ma * Mb;
    cout << "Mc " << endl << Mc << endl << endl;

    //Ma.*Mb
    cv::multiply(Ma, Mb, Mc);
    cout << "multiply Mc" << endl << Mc << endl << endl;

    Mc = Ma.mul(Mb);
    cout << "mul Mc " << endl <<  Mc << endl << endl;

    //Ma./Mb
    cout << Ma / Mb << endl << endl;

    cv::divide(Ma, Mb, Mc);
    cout << "divide Mc" << endl <<  Mc << endl << endl;

    double va[] = {1, 2, 3};
    double vb[] = {0, 0, 1};
    double vc[3];

    Mat Va(3,1,CV_64FC1, va);
    Mat Vb(3,1,CV_64FC1, vb);
    Mat Vc(3,1,CV_64FC1, vc);

    //dot product(Va . Vb), 내적 = 두 벡터간의 각도 구하기
    double res = Va.dot(Vb);
    //cross product(Va x Vb), 외적 =두 벡터간의 직교하는 새로운 벡터 구하기
    Vc = Va.cross(Vb);
    cout << "dot product " << res << endl <<  "cross product" << endl << Vc << endl;

    //Single Operation
    //전치, transpose(Ma) -> Mb (cannot transpose onto self)
    Mc = Mb.t();
    cout << "transpose Mc" << endl << Mc << endl;

    //trace 대각선의 값을 모두 더하기, trace(Ma) -> t.val[0]
    cv::Scalar t = trace(Ma);
    cout << "trace Ma" << endl <<  t.val[0] << endl;

    double d = determinant(Ma);
    cout << "determinant Ma" << endl << d << endl;

    double dm2[3][3] = { {1,3,1}, {3,1,2}, {1,2,3}};
    Mat Mb2 = Mat(3, 3, CV_64F, dm2);
    cout << Mb2 << endl << endl;

    //역행렬
    Mc = Mb2.inv();
    cout << "inv Mb2" << endl << Mc << endl;
    invert(Mb2, Mc);
    cout << "invert Mb2" << endl << Mc << endl;

    //destroyAllWindows();
}

int main() {
    //MatAndMatrix();
    //ImageReadingAndPixelAccessInMat();
    //MatAndImageVideo5();
    //MatAndImageVideo();
    MatAndImageVideo3();
    return 0;
}
