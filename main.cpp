#include "window.hpp"
#include <iostream>

void clickA() {
    std::cout << "click A !" << std::endl;
}

void clickB() {
    std::cout << "click B !" << std::endl;
}

int main(){

    Window window("window", cv::Size(720, 480));

    Button buttonA("button A", cv::Rect(50, 50, 150, 50), 255, 0, 0);
    
    buttonA.setFunction(clickA);

    Button buttonB("button B", cv::Rect(250, 50, 150, 50), 0, 255, 0);
    
    buttonB.setFunction(clickB);

    window.addButton(buttonA);
    window.addButton(buttonB);

    initMouseCallback(window);
    
    window.show();

    return EXIT_SUCCESS;
}

