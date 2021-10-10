#pragma once

struct ANIM_DATA {
	int imgIdx = 0;
	float elapsedTime = 0;
	float interval = 0.1f;
	void reset() { imgIdx = 0; elapsedTime = 0; }
};

class ANIM
{
private:
	int NumImgs = 0;
	int* Imgs = 0;
	bool LoopFlag = true;
public:
	ANIM();
	ANIM(const char* pathName);
	~ANIM();
	void load(const char* path);
	void divideRow(int imgIdx, int row, int cols, int w, int h);
	void divide(const char* fileName, int cols, int rows, int w, int h);
	void draw(ANIM_DATA* ad, float px, float py, float angle = 0, float scale = 1);
	void noLoop() { LoopFlag = false; }
	bool end(const ANIM_DATA& data) { return data.imgIdx >= NumImgs; }
};