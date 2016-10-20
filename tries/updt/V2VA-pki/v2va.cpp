/**
 * @brief
 * @authors Alex Stoliar (alexstolr@gmail.com); Mohammad Najjar (najjar@post.bgu.ac.il)
 * @date 16/09/16
 */
#include "v2va.h"




/**
 * @brief
 * @return
 */
int v2va::findPlate(cv::Mat frame)
{

    return 0;
}

/**
 * @brief
 */
void v2va::init() {
    alpr::Alpr openalpr("eu", OPENALPRCONF);
    openalpr.setTopN(1);
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
    }
}
/**
 * @brief turns on and show video from usb camera
 */
void v2va::runCamera() {
    cv::VideoCapture cap(1); // open usb camera
    if(!cap.isOpened())  // check if we succeeded
    {
        std::cerr << "Error Opening Video Camera" << std::endl;
    }

    cv::Mat edges;
    cv::namedWindow("edges",1);
    while(true)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(cv::waitKey(30) >= 0) break;
    }
}
alpr::AlprResults v2va::findPlatesInFrame(alpr::Alpr openalpr, cv::Mat mat)
{
//    std::vector<char> vec;
//    if (mat.isContinuous()) {
//        vec.assign(mat.datastart, mat.dataend);
//    } else {
//        for (int i = 0; i < mat.rows; ++i) {
//            vec.insert(vec.end(), mat.ptr<char>(i), mat.ptr<char>(i)+mat.cols);
//        }
//    }
    return openalpr.recognize(mat);

}


void v2va::runCamera(alpr::Alpr openalpr)
{
    cv::VideoCapture cap(1); // open usb camera
    if(!cap.isOpened())  // check if we succeeded
    {
        std::cerr << "Error Opening Video Camera" << std::endl;
    }

    cv::Mat frame;
    cv::namedWindow("frame",1);

    //for(int i = 0; i <10 ; i++)
    //while(true)
    //{
        //cv::Mat frame;
        cap >> frame; // get a new frame from camera
        std::cout << "debug1" <<std::endl;
        alpr::AlprResults results = findPlatesInFrame(openalpr, frame);
        std::cout << "debug2" <<std::endl;
        //printf("results.plates.size(): %lu",results.plates.size());
        //for (int i = 0; i < results.plates.size(); i++)
        //{
        //    alpr::AlprPlateResult plate = results.plates[i];
        //    std::cout << plate.topNPlates[0].characters << std::endl;
        //}
        //cvtColor(frame, edges, CV_BGR2GRAY);
        //GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        //imshow("Video Capture", frame);
        //if(cv::waitKey(2000) >= 0);
    //}
}

void v2va::runOpenALPR() {
    // Initialize the library using United States style license plates.
    // You can use other countries/regions as well (for example: "eu", "au", or "kr")
    alpr::Alpr openalpr("us", OPENALPRCONF);

    // Optionally specify the top N possible plates to return (with confidences).  Default is 10
    openalpr.setTopN(1);

    // Optionally, provide the library with a region for pattern matching.  This improves accuracy by
    // comparing the plate text with the regional pattern.
    openalpr.setDefaultRegion("md");

    // Make sure the library loaded before continuing.
    // For example, it could fail if the config/runtime_data is not found
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
    }

    // Recognize an image file.  You could alternatively provide the image bytes in-memory.
    alpr::AlprResults results = openalpr.recognize("/home/alex/Workspace/V2VA/include/Images/lp.jpg");

    // Iterate through the results.  There may be multiple plates in an image,
    // and each plate return sthe top N candidates.
    for (int i = 0; i < results.plates.size(); i++)
    {
        alpr::AlprPlateResult plate = results.plates[i];
        //std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;
        std::cout << plate.topNPlates[0].characters << std::endl;

        //for (int k = 0; k < plate.topNPlates.size(); k++)
        //{
            //alpr::AlprPlate candidate = plate.topNPlates[k];
            //std::cout << candidate.characters << std::endl;
            //std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
            //std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
        //}
    }
}

void v2va::streamALPR()
{
    alpr::Alpr openalpr("eu", OPENALPRCONF);
    openalpr.setTopN(1);
    openalpr.setDefaultRegion("md");
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
    }
    runCamera(openalpr);
}

void v2va::imgALPR(std::string imgPath)
{
    alpr::Alpr openalpr("eu", OPENALPRCONF);
    openalpr.setTopN(MAX_PLATE_NUMBER);
    openalpr.setDefaultRegion("md");
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
    }
    alpr::AlprResults results = openalpr.recognize(imgPath);
    /*
    for (int i = 0; i < results.plates.size(); i++)
    {
        alpr::AlprPlateResult plate = results.plates[i];
        //std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;
        std::cout << plate.topNPlates[0].characters << std::endl;

        //for (int k = 0; k < plate.topNPlates.size(); k++)
        //{
        //alpr::AlprPlate candidate = plate.topNPlates[k];
        //std::cout << candidate.characters << std::endl;
        //std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
        //std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
        //}
    }
     */
    for (int i = 0; i < results.plates.size(); i++)
    {
        alpr::AlprPlateResult plate = results.plates[i];
        std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;

        for (int k = 0; k < plate.topNPlates.size(); k++)
        {
            alpr::AlprPlate candidate = plate.topNPlates[k];
            std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
            std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
        }
    }
}

int v2va::getPlateFromImg(std::string imgPath)
{
    alpr::Alpr openalpr("eu", OPENALPRCONF);
    openalpr.setTopN(MAX_PLATE_NUMBER);
    openalpr.setDefaultRegion("md");
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
    }
    alpr::AlprResults results = openalpr.recognize(imgPath);
    for (int i = 0; i < results.plates.size(); i++)
    {
        alpr::AlprPlateResult plate = results.plates[i];
        std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;

        for (int k = 0; k < plate.topNPlates.size(); k++)
        {
            alpr::AlprPlate candidate = plate.topNPlates[k];
            std::cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence;
            std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
        }
    }
}
