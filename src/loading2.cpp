#include "DxLib.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

//Window size
#define MIN_X 0
#define MIN_Y 0
#define MAX_X 720
#define MAX_Y 480

#define BALL_SIZE 2

#define OMEGA(t) (t * M_PI / 180)

int t=0;
unsigned int white = GetColor(255,255,255);
unsigned int black = GetColor(0,0,0);
int mouse_x,mouse_y;

struct V{
	double x,y;
	V(){}
	V(double x, double y){
		this->x = x;
		this->y = y;
	}
};

struct BALL{
	double x,y;	//�{�[���̍��W
	int r;		//�{�[���̔��a
	unsigned int color;
	V v;

	BALL(){
		color = white;
	}
	//���W�Ƒ������w��
	BALL(double x,double y,V v){
		this->x = x;
		this->y = y;
		this->v = v;
		r = -1;
		color = white;
	}
	//���W�ƃ{�[���̔��a�Ƒ������w��
	BALL(double x,double y, int r, V v){
		this->x = x;
		this->y = y;
		this->r = r;
		this->v = v;
		color = white;
	}

	void setPosition(double x,double y){
		this->x = x;
		this->y = y;
	}
	void setV(V v){
		this->v = v;
	}
	void update(){
		x+=v.x;
		y+=v.y;
		int radius = r;
		if(r < 0){
			radius = 1;
		}
		if(x-radius <= MIN_X || x+radius >= MAX_X){
			v.x *= -1;
		}
		if(y-radius <= MIN_Y || y+radius >= MAX_Y){
			v.y *= -1;
		}
		V vm;
		vm.x = mouse_x - x;
		vm.y = mouse_y - y;
		int crossZ = v.x*vm.y - v.y*vm.x;
		double rad = OMEGA(1.0 * crossZ);
		V rot;
		rot.x = cos(rad)*v.x - sin(rad)*v.y;
		rot.y = sin(rad)*v.x + cos(rad)*v.y;
		v = rot;
	}
	void draw(){
		if(r < 1){
			DrawPixel(x, y,color);
		}else{
			DrawCircle(x,y,r,color,true);
			//DrawCircle(x, y, r/3 ,black, true);
		}
	}

};





// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	SetGraphMode(MAX_X, MAX_Y, 32);
	if( DxLib_Init() == -1 )		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}
	// Drawing destination screen is on the back

	int sign_x, sign_y;
	unsigned int color;

	std::vector<BALL> balls;

	sign_x = GetRand(1)==0?1:-1;
	sign_y = GetRand(1)==0?1:-1;

	BALL ball(MAX_X/2.0, MAX_Y/2.0, BALL_SIZE, V((GetRand(5)+1)*sign_x, (GetRand(5)+1)*sign_y));
	
	balls.push_back(ball);

	while(!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)){

		ClearDrawScreen();
		GetMousePoint(&mouse_x,&mouse_y);

		//ball.setPosition(mouse_x, mouse_y);
		for(int i=0;i<balls.size();i++){
			balls[i].update();
			balls[i].draw();
		}
		
		if(CheckHitKey(KEY_INPUT_SPACE)){
			for(int i=0;i<balls.size();i++){
				sign_x = GetRand(1)==0?1:-1;
				sign_y = GetRand(1)==0?1:-1;
				balls[i].setV(V((GetRand(5)+1)*sign_x, (GetRand(5)+1)*sign_y));
			}
		}

		if(CheckHitKey(KEY_INPUT_A)){
			sign_x = GetRand(1)==0?1:-1;
			sign_y = GetRand(1)==0?1:-1;

			BALL ball(MAX_X/2.0, MAX_Y/2.0, BALL_SIZE, V((GetRand(5)+1)*sign_x, (GetRand(5)+1)*sign_y));
			
			color = GetColor(GetRand(255),GetRand(255),GetRand(255));
			ball.color = color;

			balls.push_back(ball);
		}

		ScreenFlip();

		t++;
	}

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}