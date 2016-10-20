#ifndef V2VA_V2VA_H
#define V2VA_V2VA_H
/**
 * @brief
 * @authors Alex Stoliar (alexstolr@gmail.com); Mohammad Najjar (najjar@post.bgu.ac.il)
 * @date 16/09/16
 */

#include "alpr.h"                           /* http://doc.openalpr.com/index.html */
#include "opencv2/opencv.hpp"               /* http://docs.opencv.org/2.4/index.html */
#include <string>
#define MAX_PLATE_NUMBER 50
#define OPENALPRCONF "/home/alex/Workspace/OpenALPR/openalpr/src/config/openalpr.conf"


class v2va {

public:
    void runCamera();
    void streamALPR();

    void runOpenALPR();
    void imgALPR(std::string imgPath);
private:
    void init();
    int findPlate(cv::Mat frame);
    alpr::AlprResults findPlatesInFrame(alpr::Alpr openalpr, cv::Mat frame);
    void runCamera(alpr::Alpr openalpr);


    int getPlateFromImg(std::string imgPath);
};


#endif //V2VA_V2VA_H
