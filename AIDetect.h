#pragma once
#define OBJECTDETECT_LIBRARY
#if defined(OBJECTDETECT_LIBRARY)
#  define OBJECTDETECTSHARED_EXPORT __declspec(dllexport)
#else
#  define OBJECTDETECTSHARED_EXPORT __declspec(dllimport)
#endif

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;

/*******************************************
*    目标信息结构体
* *****************************************/
typedef struct tagTargetInfo {
	unsigned int x;                 // 目标矩形框左上角X坐标
	unsigned int y;                 // 目标矩形框左上角Y坐标
	unsigned int w;                 // 目标矩形框宽度
	unsigned int h;                 // 目标矩形框高度
	float prob;                     // 目标置信度（0-1）
	float obj_id;            // 目标id（0：坦克 1：战车 2：卡车）
}TargetInfo;


class OBJECTDETECTSHARED_EXPORT yolov5_det
{
private:
	void* det_demo = NULL;
	
public:
	yolov5_det(std::string yolov5_path, float conf, float nms);
	void detect(uchar* buf, int imgW, int imgH, std::vector<TargetInfo>& det);
	~yolov5_det();
};


//extern "C" OBJECTDETECTSHARED_EXPORT bool  init_AI(char* path, float zt, float st);
//
//
//extern "C" OBJECTDETECTSHARED_EXPORT void  fireDetect_AI(char* buf, int imgW, int imgH, int imgDeep, std::vector<TargetInfo>& det);
//
//
//extern "C" OBJECTDETECTSHARED_EXPORT void   uninit_AI();

//extern "C" OBJECTDETECTSHARED_EXPORT class runtime_yolov5
//{
//	void init_AI(std::string m_yolov5_trt, float m_conf_thresh, float m_nms_thresh, int m_crop_size, int m_infer_size);
//	void Detect_AI(char* buf, int imgW, int imgH, int imgDeep, std::vector<TargetInfo>& det);
//};
