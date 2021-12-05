#include <bangtal>
#include <bangtal.h>
using namespace bangtal;

#include <cstdlib>
#include <ctime>
#include <time.h>

ScenePtr  scene, scene1, scene2, scene3;
ObjectPtr start, end;
ObjectPtr easy, hard;
ObjectPtr start_button1, start_button2, restart_button1, restart_button2;
ObjectPtr square1_red, square1_blue, square1_green;
ObjectPtr square2_red, square2_blue, square2_green;
ObjectPtr red1_button, green1_button, blue1_button;
ObjectPtr red2_button, green2_button, blue2_button;
TimerPtr  timer1, timer2;

int   count = 0, mixCounter1 = 10, mixCounter2 = 20;
float animationTime;
bool  red1_check, red2_check, green1_check, green2_check, blue1_check, blue2_check;


void red1_show()
{
	square1_green->hide();
	square1_blue->hide();
	square1_red->show();	
}
void red2_show()
{
	square2_green->hide();
	square2_blue->hide();
	square2_red->show();
}
void blue1_show()
{
	square1_green->hide();
	square1_red->hide();
	square1_blue->show();
}
void blue2_show()
{
	square2_green->hide();
	square2_red->hide();
	square2_blue->show();
}
void green1_show()
{
	square1_blue->hide();
	square1_red->hide();
	square1_green->show();
}
void green2_show()
{
	square2_blue->hide();
	square2_red->hide();
	square2_green->show();
}

void all_hide()
{
	square1_red->hide();
	square1_green->hide();
	square1_blue->hide();
	square1_red->hide();
	square1_green->hide();
	square1_blue->hide();
}

int random()
{
	int index = rand() % 3;

	return index;
}

void start_game1()
{
	count         = 0;
	mixCounter1   = 10;
	animationTime = 2.0f;

	timer1->set(animationTime);
	timer1->start();
}
void start_game2()
{
	count         = 0;
	mixCounter2   = 20;
	animationTime = 1.0f;

	timer2->set(animationTime);
	timer2->start();
}

void init_game()
{
	scene  = Scene::create("색깔 고르기", "Images/white_scene.png");
	auto background = Object::create("Images/scene.png", scene);
	scene1 = Scene::create("게임 선택", "Images/white_scene.png");
	auto background1 = Object::create("Images/scene2.png", scene1);
	scene2 = Scene::create("EASY", "Images/white_scene.png");
	auto background2 = Object::create("Images/scene2.png", scene2);
	scene3 = Scene::create("HARD", "Images/white_scene.png");
	auto background3 = Object::create("Images/scene1.png", scene3);

	start = Object::create("Images/start.png", scene, 590, 400);
	end   = Object::create("Images/end.png", scene, 590, 320);

	easy = Object::create("Images/easy.png", scene1, 490, 340);
	hard = Object::create("Images/hard.png", scene1, 690, 340);

	start_button1 = Object::create("Images/start.png", scene2, 590, 100);
	start_button1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			start_button1->hide();
			red1_button  ->show();
			green1_button->show();
			blue1_button ->show();

			start_game1();

			return true;
		});
	start_button2 = Object::create("Images/start.png", scene3, 590, 100);
	start_button2->setOnMouseCallback([&](auto, auto, auto, auto)->bool
		{
			start_button2->hide();
			red2_button->show();
			green2_button->show();
			blue2_button->show();

			start_game2();

			return true;
		});
	start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			scene1->enter();

			return true;
		});

	end->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			endGame();

			return true;
		});

	easy->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			scene2->enter();
			start_button1->show();

			return true;
		});

	hard->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			scene3->enter();
			start_button2->show();

			return true;
		});

	square1_red   = Object::create("Images/red.png",   scene2, 490, 260, false);
	square1_blue  = Object::create("Images/blue.png",  scene2, 490, 260, false);
	square1_green = Object::create("Images/green.png", scene2, 490, 260, false);
	square2_red   = Object::create("Images/red.png",   scene3, 490, 260, false);
	square2_blue  = Object::create("Images/blue.png",  scene3, 490, 260, false);
	square2_green = Object::create("Images/green.png", scene3, 490, 260, false);

	red1_button   = Object::create("Images/red_button.png",   scene2, 490, 100, false);
	green1_button = Object::create("Images/green_button.png", scene2, 590, 100, false);
	blue1_button  = Object::create("Images/blue_button.png",  scene2, 690, 100, false);
	red2_button   = Object::create("Images/red_button.png",   scene3, 490, 100, false);
	green2_button = Object::create("Images/green_button.png", scene3, 590, 100, false);
	blue2_button  = Object::create("Images/blue_button.png",  scene3, 690, 100, false);

	red1_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			red1_check   = true;
			green1_check = false;
			blue1_check  = false;

			return true;
		});
	red2_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			red2_check   = true;
			green2_check = false;
			blue2_check  = false;

			return true;
		});

	green1_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			red1_check   = false;
			green1_check = true;
			blue1_check  = false;

			return true;
		});
	green2_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			red2_check   = false;
			green2_check = true;
			blue2_check  = false;

			return true;
		});

	blue1_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			red1_check   = false;
			green1_check = false;
			blue1_check  = true;

			return true;
		});
	blue2_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			red2_check   = false;
			green2_check = false;
			blue2_check  = true;

			return true;
		});

	restart_button1 = Object::create("Images/restart.png", scene2, 590, 100, false);
	restart_button2 = Object::create("Images/restart.png", scene3, 590, 100, false);
	restart_button1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			scene->enter();
			restart_button1->hide();

			return true;
		});
	restart_button2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			scene->enter();
			restart_button2->hide();

			return true;
		});
	
	timer1 = Timer::create(animationTime);
	timer1->setOnTimerCallback([&](auto)->bool	//	timer loop	//
		{
			showTimer(timer1);
			
			int index = random();

			if (index == 0) red1_show();
			else if (index == 1) green1_show();
			else if (index == 2) blue1_show();
			
			if (red1_check && square1_red) count++;
			if (green1_check && square1_green) count++;
			if (blue1_check && square1_blue) count++;

			red1_check   = false;
			green1_check = false;
			blue1_check  = false;

			if (mixCounter1 > 0)
			{
				timer1->set(animationTime);
				timer1->start();

				mixCounter1--;
			}
			else
			{
				if (count == 0) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 0점입니다.");				
				else if (count ==  1) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 1점입니다.");
				else if (count ==  2) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 2점입니다.");
				else if (count ==  3) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 3점입니다.");
				else if (count ==  4) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 4점입니다.");
				else if (count ==  5) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 5점입니다.");
				else if (count ==  6) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 6점입니다.");
				else if (count ==  7) showMessage("성공입니다!!! 7점이에요!");
				else if (count ==  8) showMessage("성공입니다!!! 8점이에요!");
				else if (count ==  9) showMessage("성공입니다!!! 9점이에요!");
				else if (count == 10) showMessage("성공입니다!!! 10점이에요!");
				
				all_hide();

				red1_button->hide();
				green1_button->hide();
				blue1_button->hide();
				restart_button1->show();
			}
			return true;
		});

	timer2 = Timer::create(animationTime);
	timer2->setOnTimerCallback([&](auto)->bool
		{
			showTimer(timer2);

			int index = random();

			if (index == 0) red2_show();
			else if (index == 1) green2_show();
			else if (index == 2) blue2_show();

			if (red2_check && square2_red)     count++;
			if (green2_check && square2_green) count++;
			if (blue2_check && square2_blue)   count++;

			red2_check   = false;
			green2_check = false;
			blue2_check  = false;

			mixCounter2--;

			if (mixCounter2 > 0)
			{
				timer2->set(animationTime);
				timer2->start();
			}
			else
			{
				if (count == 0) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 0점입니다.");
				else if (count ==  1) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 1점입니다.");
				else if (count ==  2) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 2점입니다.");
				else if (count ==  3) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 3점입니다.");
				else if (count ==  4) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 4점입니다.");
				else if (count ==  5) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 5점입니다.");
				else if (count ==  6) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 6점입니다.");
				else if (count ==  7) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 7점입니다.");
				else if (count ==  8) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 8점입니다.");
				else if (count ==  9) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 9점입니다.");
				else if (count == 10) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 10점입니다.");
				else if (count == 11) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 11점입니다.");
				else if (count == 12) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 12점입니다.");
				else if (count == 13) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 13점입니다.");
				else if (count == 14) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 14점입니다.");
				else if (count == 15) showMessage("아쉽네요~~~ 다시 도전해보세요!!! 15점입니다.");
				else if (count == 16) showMessage("성공입니다!!! 16점이에요!");
				else if (count == 17) showMessage("성공입니다!!! 17점이에요!");
				else if (count == 18) showMessage("성공입니다!!! 18점이에요!");
				else if (count == 19) showMessage("성공입니다!!! 19점이에요!");
				else if (count == 20) showMessage("성공입니다!!! 20점이에요!");
				
				all_hide();

				red2_button->hide();
				green2_button->hide();
				blue2_button->hide();
				restart_button2->show();
			}
			return true;
		});

	startGame(scene);
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	init_game();

	return 0;
}