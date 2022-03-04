#ifndef button_hpp
#define button_hpp

#include <string>
#include <opencv2/opencv.hpp>

/**
 * @brief Button
 * 
 * @param label button text
 * @param rect (x,y) and (width, height)
 * @param r color
 * @param g color
 * @param b color
 */
class Button{        

    public:
        cv::Rect rect;
        int r;
        int g;
        int b;
        bool hover;
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
            this->hover = false;
        }
        
        void (*function)(void);

        cv::Scalar getColor() {
            return cv::Scalar((this->hover) ? 255 - this->b : this->b, (this->hover) ? 255 - this->g : this->g, (this->hover) ? 255 - this->r : this->r);
        }

        int getR(){
            return this->hover ? 255 - this-> r : this->r;
        }

        int getG(){
            return this->hover ? 255 - this-> g : this->g;
        }

        int getB(){
            return this->hover ? 255 - this-> b : this->b;
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