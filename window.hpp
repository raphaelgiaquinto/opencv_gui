#ifndef window_hpp
#define window_hpp

#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include "button.hpp"
/**
 * @brief Window
 * 
 * @param name window name
 * @param size (width, height)
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
         * @brief Draws the image and all of the buttons attached to the window
         * Buttons with border and color
         */
        void draw() {
            for(auto& b: this->buttons) {
                cv::Size rect = cv::getTextSize(b.label, cv::FONT_HERSHEY_SIMPLEX, 1.0, 1, 0);

                cv::Rect border(b.rect);
                cv::Rect container(b.rect);

                cv::Point2i tl( container.tl());
                tl.x += border.width / 20;
                tl.y += border.height / 20;
                cv::Point2i br( container.br());
                br.x -= border.width / 20;
                br.y -= border.height / 20;
                container = cv::Rect(tl, br);

                double scalex = (double) container.width / (double)rect.width;
                double scaley = (double) container.height / (double)rect.height;
                double scale = std::min(scalex, scaley);

                int marginx = scale == scalex ? 0 : (int)((double) container.width * (scalex - scale) / scalex * 0.5);
                int marginy = scale == scaley ? 0 : (int)((double) container.height * (scaley - scale) / scaley * 0.5);
                
                
                cv::Scalar borderColor(b.getB()/2, b.getG()/2, b.getR()/2);

                cv::rectangle(this->image, border, borderColor, cv::FILLED);
                cv::rectangle(this->image, container, b.getColor(), cv::FILLED);

                cv::putText(this->image, b.label, cv::Point(container.x + marginx, container.y + container.height - marginy), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(255 - b.getB(), 255 - b.getG(), 255 - b.getR()), 1, 8, false);
            }
            cv::imshow(this->name, this->image);
        }

        /**
         * @brief Display the window in a while loop by calling draw method
         * 
        */
        void show() {
    
            while(this->exitCode != (int) cv::waitKey(25)) {
                this->draw();
            }
        }

        void exitOnKey(int code) {
            this->exitCode = code;
        }
};


std::vector<Window> windows;

static void callback(int event, int x, int y, int flags, void* img) {
    if(event == cv::EVENT_LBUTTONDOWN){
        for(auto &win: windows){
            for(auto& button: win.buttons) {
                if(button.rect.contains(cv::Point2i(x, y))){
                    button.function();
                }
            }
        }
    }

    if(event == cv::EVENT_MOUSEMOVE) {
        for(auto &win: windows){
            for(auto& button: win.buttons) {
                button.hover = button.rect.contains(cv::Point2i(x, y));
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
    windows.push_back(window);
    cv::setMouseCallback(window.name, callback, 0);
}

#endif