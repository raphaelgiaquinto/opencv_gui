#ifndef button_hpp
#define button_hpp

#include <string>
#include <opencv2/opencv.hpp>

/**
 * @brief Button
 * 
 */
class Button{        

    public:
        cv::Rect rect;
        int r;
        int g;
        int b;
        cv::Scalar color;
        std::string label;
        /**
         * @brief Construct a new Button object
         * 
         * @param label button text
         * @param rect (x,y) and (width, height)
         * @param r color
         * @param g color
         * @param b color
         */
        Button(std::string label, cv::Rect rect, int r, int g, int b) {
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

        /**
         * @brief Set the Function object
         * 
         * @param f callback function triggered on click
         */
        void setFunction(void (*f)(void)){
            this->function = f;
        }

};
#endif