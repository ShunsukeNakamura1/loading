#include "DxLib.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

//Window size
#define MIN_X 0
#define MIN_Y 0
#define MAX_X 720
#define MAX_Y 480
#define LINE 100

#define OMEGA(t) (t * M_PI / 180)

int t=0;
unsigned int white = GetColor(255,255,255);

struct XY{
	double x,y;
	XY(){}
	XY(double x_,double y_){
		x = x_;
		y = y_;
	}
	void set(double x_,double y_){
		x = x_;
		y = y_;
	}
	void draw(){
		DrawPixel(x, y,white);
	}

};



// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	SetGraphMode(MAX_X, MAX_Y, 32);
	if( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}
	// Drawing destination screen is on the back

	int mouse_x,mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	double x,y;

	const int speed = 9;
	const int length = 10;
	const int thicness = 5;
	const int dst = 15;

	XY main = XY((double)mouse_x, (double)mouse_y);

	x = main.x + 20 * cos(OMEGA(t));
	y = main.y + 20 * sin(OMEGA(t));
	XY sub1 = XY(x, y);
	x = main.x + length * cos(OMEGA(t) + OMEGA(180));
	y = main.y + length * sin((OMEGA(t) + OMEGA(180)));
	XY sub2 = XY(x, y);
	while(!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)){

		ClearDrawScreen();

		//mainの更新
		GetMousePoint(&mouse_x, &mouse_y);
		main.set((double)mouse_x, (double)mouse_y);

		//sub1の更新
		x = main.x + length * cos(OMEGA(t) * speed);
		y = main.y + length * sin(OMEGA(t) * speed);
		sub1.set(x, y);

		//sub2の更新
		x = main.x + length * cos((OMEGA(t) + OMEGA(180)) * speed);
		y = main.y + length * sin((OMEGA(t) + OMEGA(180)) * speed);
		sub2.set(x, y);

		//表示
		//main.draw();
		//sub1.draw();
		//sub2.draw();

		DrawLine(sub1.x + length + dst, sub1.y + 10, sub2.x + length + dst, sub2.y + 10,white,thicness);
		
		switch((t%120)/30){
		case 0:
			DrawFormatString(main.x + 2*length + 2*dst, main.y+10, white, "NOW LOADING");
			break;
		case 1:
			DrawFormatString(main.x + 2*length + 2*dst, main.y+10, white, "NOW LOADING.");
			break;
		case 2:
			DrawFormatString(main.x + 2*length + 2*dst, main.y+10, white, "NOW LOADING..");
			break;
		case 3:
			DrawFormatString(main.x + 2*length + 2*dst, main.y+10, white, "NOW LOADING...");
			break;
		}
		//DrawFormatString(main.x + 2*length + 2*dst, main.y+10, white, "NOW LOADING...");
		ScreenFlip();

		t++;
	}

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}