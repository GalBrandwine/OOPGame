#pragma once
#include <memory>
#include <opencv2/opencv.hpp>

#ifdef ShowDebugMap
#include <opencv2/highgui.hpp>
#endif

class IMap
{
public:
        virtual ~IMap(){};
};
