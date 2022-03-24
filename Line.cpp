#include "../include/Line.hpp"

Line::Line(float StartX, float StartY, float EndX, float EndY, float LineWidth):
StartX(StartX), StartY(StartY), EndX(EndX), EndY(EndY), width(LineWidth){
}

void Line::checkCollide(Joint *P){
    float LineX1 = EndX - StartX;
	float LineY1 = EndY - StartY;

	float LineX2 = P->getX() - StartX;
	float LineY2 = P->getY() - StartY;

    float EdgeLength = LineX1 * LineX1 + LineY1 * LineY1;

    float t = std::max(0.0f, std::min(EdgeLength, (LineX1 * LineX2 + LineY1 * LineY2))) / EdgeLength;

    float ClosestPointX = StartX + t * LineX1;
	float ClosestPointY = StartY + t * LineY1;

    if (ClosestPointX+width+P->getSize() > P->getX()&&ClosestPointX<P->getX()+width+P->getSize()&&ClosestPointY+width+P->getSize()>P->getY()&&ClosestPointY<P->getY()+width+P->getSize()){
        float Distance = sqrtf((P->getX() - ClosestPointX) * (P->getX() - ClosestPointX) + (P->getY() - ClosestPointY) * (P->getY() - ClosestPointY));

        if (Distance <= (P->getSize() + width)){
            //COLLISION
            //float Overlap = 1.0f * (Distance - P->getSize() - width);
            
            // Displace Current Ball away from collision
            float dx = ClosestPointX - P->getX();
            float dy = ClosestPointY - P->getY();
            float distance = hypot(dx, dy);
            float tangent = atan2(dy, dx);
            float newAngle = 0.5f * M_PI + tangent;
            float Overlap = 1.0f * (width + P->getSize() - distance + 1);
            P->setAngle(newAngle - M_PI);
            P->setSpeed(P->getSpeed() * P->getElasticity());

            P->setX(P->getX() - sin(newAngle) * Overlap);
            P->setY(P->getY() + cos(newAngle) * Overlap);

            
            //P->setX( P->getX() - Overlap * (P->getX() - ClosestPointX) / Distance);
            //P->setY( P->getY() - Overlap * (P->getY() - ClosestPointY) / Distance);
        }
    }
}