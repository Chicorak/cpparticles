#define OLC_PGE_APPLICATION
#include "../include/olcPixelGameEngine.h" //https://github.com/OneLoneCoder/olcPixelGameEngine

#include "../include/cpparticles.hpp"

// Override base class with my custom function
class Platformer : public olc::PixelGameEngine{
private:
	int size = 2;
	int mass = 250;
	int speed = 10;
	int angle = 0;
	float elasticity = 0.02;
	int length = 35;
	int strength = 40;

	float ang = 0;
	
	Environment *env = new Environment(600, 600, {M_PI, 0.28});
	
	Joint *selectedJoint = nullptr;
	
	Joint *ps[4] = {	env->addJoint(40, 500, size, mass, speed, angle, elasticity),
						env->addJoint(40 + (length*2), 500, size, mass, speed, angle, elasticity),
						env->addJoint(40 + (length*2), 500 + length, size, mass, speed, angle, elasticity),
						env->addJoint(40, 500 + length, size, mass, speed, angle, elasticity)};
	
	std::vector<Joint* >balls = {env->addJoint(150, 300, 10.0f, 250.0f)};

	Line *cut = env->addLine(200, 400, 400, 400, 12);
	Line *corn = env->addLine(0,0,0,0, 12);
	
	std::unique_ptr<olc::Sprite> sprMar;
	std::unique_ptr<olc::Decal> decMar;
	std::array<olc::vf2d, 4> points;

public:
	Platformer() //class constructor used by libary to name the application
	{
		sAppName = "Platformer";	// Name of app
	}

	//*********************************************
	bool OnUserCreate() override {
			sprMar = std::make_unique<olc::Sprite>("./test.png");
			decMar = std::make_unique<olc::Decal>(sprMar.get());
			//Floor = env->addBody(ScreenHeight()/2, ScreenHeight() - 25, std::vector<Vector2>{{0, ScreenHeight() - 50}, {ScreenWidth(), ScreenHeight()-50}, {ScreenWidth(), ScreenHeight()}, {0, ScreenHeight()}}, speed, angle, mass, true); 
			
			env->addSpring(ps[0], ps[1], length, strength);
			env->addSpring(ps[1], ps[2], length, strength);
			env->addSpring(ps[2], ps[3], length, strength);
			env->addSpring(ps[3], ps[0], length, strength);
			env->addSpring(ps[0], ps[2], length, strength*5);
			env->addSpring(ps[1], ps[3], length, strength*5);

			for (size_t i = 0; i < 250; i++)
			{
				balls.push_back({env->addJoint(rand() % ScreenWidth(), 0, rand() % 15 +2, 150.0f, 0.0f, 0.0f, 1)});
			}
			
			
		return true;
	}

	// ****************** Frame Calculations and Rendering ******************
	bool OnUserUpdate(float fElapsedTime) override{
		if (GetMouse(0).bPressed)
			selectedJoint = env->getJoint(GetMouseX(), GetMouseY());
		if (GetKey(olc::RIGHT).bHeld)
			for (int i = 0; i < 4; i++)
				ps[i]->accelerate({M_PI/2, 0.3f});
		if (GetKey(olc::LEFT).bHeld)
			for (int i = 0; i < 4; i++)
				ps[i]->accelerate({(3*M_PI)/2, 0.3f});
		if (GetKey(olc::UP).bReleased)
			for (int i = 0; i < 4; i++)
				ps[i]->accelerate({0, 7});
		if(GetMouse(0).bReleased)
			selectedJoint = nullptr;
		if (selectedJoint)
			selectedJoint->moveTo(GetMouseX(), GetMouseY());

		env->update();
		
		Clear(olc::BLACK);

		DrawStringDecal({0, 20}, std::to_string(env->getJoints()[0]->getSpeed()));
		DrawStringDecal({80, 20}, std::to_string(env->getJoints()[1]->getSpeed()));
		DrawStringDecal({160, 20}, std::to_string(env->getJoints()[2]->getSpeed()));
		DrawStringDecal({240, 20}, std::to_string(env->getJoints()[3]->getSpeed()));

		for (int i=0; i<env->getSprings().size(); i++) {
			Spring *spring = env->getSprings()[i];
			
			DrawCircle({spring->getP1()->getX(), spring->getP1()->getY()}, size);
			//DrawStringDecal({spring->getP1()->getX()-20, spring->getP1()->getY()-20}, std::to_string(i));

			DrawLineDecal({spring->getP1()->getX(), spring->getP1()->getY()}, {spring->getP2()->getX(), spring->getP2()->getY()}, olc::Pixel{0, 0, 255, 255});
		}

		FillCircle(cut->getStartX(), cut->getStartY(), cut->getWidth(), olc::Pixel(255,255,255));
		FillCircle(cut->getEndX(), cut->getEndY(), cut->getWidth(), olc::Pixel(128, 128, 128));
		float nx = -(cut->getEndY() - cut->getStartY());
		float ny = (cut->getEndX() - cut->getStartX());
		float d = sqrt(nx*nx + ny * ny);
		nx /= d;
		ny /= d;
		DrawLine((cut->getStartX() + nx * cut->getWidth()), (cut->getStartY() + ny * cut->getWidth()), (cut->getEndX() + nx * cut->getWidth()), (cut->getEndY() + ny * cut->getWidth()), olc::Pixel(255, 255, 255));
		DrawLine((cut->getStartX() - nx * cut->getWidth()), (cut->getStartY() - ny * cut->getWidth()), (cut->getEndX() - nx * cut->getWidth()), (cut->getEndY() - ny * cut->getWidth()), olc::Pixel(255, 255, 255));
		
		DrawLineDecal({corn->getStartX(), corn->getStartY()}, {corn->getEndX(), corn->getEndY()});
		

		ang+=0.01f;
		cut->setEndX(-cos(ang) * 150 + 400);
		//ang+=0.05f;
		cut->setEndY(sin(ang) * 150 + 400);
		cut->setStartX(-cos(ang) * 150 + 200);
		
		cut->setStartY(-sin(ang) * 150 + 400);
		
		points[0] = {env->getSprings()[0]->getP1()->getX(), env->getSprings()[0]->getP1()->getY()};
		points[1] = {env->getSprings()[1]->getP1()->getX(), env->getSprings()[1]->getP1()->getY()};
		points[2] = {env->getSprings()[2]->getP1()->getX(), env->getSprings()[2]->getP1()->getY()};
		points[3] = {env->getSprings()[3]->getP1()->getX(), env->getSprings()[3]->getP1()->getY()};
		for (auto &b : balls)
			DrawCircle({b->getX(), b->getY()}, b->getSize());
		
		DrawWarpedDecal(decMar.get(), points);
		
		return true;
	}
};

int main(){
	Platformer app;
	if (app.Construct(600, 600, 1, 1, false, true))
		app.Start();
	return 0;
}