#ifndef window_hpp
#define window_hpp

#include <string>
#include <opencv2/opencv.hpp>
#include "button.hpp"
/**
 * @brief Window, 
 * 
 * One per session
 */
class Window{

    public:
        std::string name;
        cv::Size size;
        cv::Mat image;
        std::vector<Button> buttons;
        int exitCode;
        
        Window(){}
        /**
         * @brief Construct a new Window object
         * 
         * @param name window name
         * @param size (width, height)
         */
        Window(std::string name, cv::Size size){
            this->name = name;
            this->size = size;
            this->image =  cv::Mat::zeros(this->size, CV_8UC3);
            this->exitCode = 27;
            cv::namedWindow(this->name);
        }

        void setImage(cv::Mat image) { 
            this->image = image;
            cv::resize(this->image, this->image, this->size);
        }
        
        void addButton(Button button) {
            this->buttons.push_back(button);
        }

        /**
         * @brief Display the window
         * 
         * Draws the image and all of the buttons attached to the window
         */
        void show() {
    
            while(this->exitCode != (int) cv::waitKey(25)) {
                
                for(auto& b: this->buttons) {
                    cv::rectangle(this->image, b.rect, b.getColor(), cv::FILLED);
                    cv::putText(this->image, b.label, cv::Point2i(b.rect.x * 1.05, b.rect.y * 1.15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255 - b.b, 255 - b.g, 255 - b.r), 2);  
                }
                cv::imshow(this->name, this->image);
            }
        }

        void exitOnKey(int code) {
            this->exitCode = code;
        }
};


Window globalWindow;

static void callback(int event, int x, int y, int flags, void* img) {
    if(event == cv::EVENT_LBUTTONDOWN){
        for(auto& button: globalWindow.buttons) {
            if(button.rect.contains(cv::Point2i(x, y))){
                button.function();
            }
        }
    }
}

/**
 * @brief Initializes mouse callback
 * 
 * Activates buttons callbacks
 * 
 * @param window 
 */
static void initMouseCallback(Window window) {
    globalWindow = window;
    cv::setMouseCallback(window.name, callback, 0);
}

#endif