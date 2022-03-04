#ifndef button_hpp
#define button_hpp

#include <string>
#include <opencv2/opencv.hpp>

class Button{        

    public:
        
        cv::Rect rect;
        int r;
        int g;
        int b;
        std::string label;

        Button(std::string label, cv::Rect rect, int r, int g, int b){
            this->label = label;
            this->rect = rect;
            this->r = r;
            this->g = g;
            this->b = b;
        }
        
        void (*function)(void);

        cv::Scalar getColor() {
            return cv::Scalar(this->b, this->g, this->r);
        }

        void setFunction(void (*f)(void)){
            this->function = f;
        }

};
#endif