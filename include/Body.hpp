#ifndef body_hpp
#define body_hpp

#define M_PI 3.14159265359

#include <cmath>
#include <vector>
#include <algorithm>


struct Vector2
{
    float x, y;
};

class Body{
public:
    Body(float x, float y, std::vector<Vector2> vertices, float speed, float rotation, bool ridgid);
    float getRotation() { return rotation; }
	float getSpeed() { return speed; }
    std::vector<Vector2> getVertices() { return vertices; }
	float getX() { return x; }
	float getY() { return y; }
	void move();
	void moveTo(float moveX, float moveY);
	void setAngle(float r) { rotation = r; }
	void setMass(float m) { mass = m; }
	void setSpeed(float s) { speed = s; }
	void setX(float xCoord) { x = xCoord; }
	void setY(float yCoord) { y = yCoord; }
    bool aabbCheck (int x_1, int y_1, int w_1, int h_1, int x_2, int y_2, int w_2, int h_2);
    int dot(const Vector2 &A, const Vector2 &B);
    Vector2 calculate_normalised_projection_axis(const Vector2 &current_point, const Vector2 &next_point);
    void compute_projections(const std::vector<Vector2> &bounds_a, const std::vector<Vector2> &bounds_b, const Vector2 &axis_normalised, std::vector<double> &projections_a, std::vector<double> &projections_b);
    bool is_overlapping(const std::vector<double> &projections_a, const std::vector<double> &projections_b);
    bool separating_axis_intersect(const std::vector<Vector2> &Verts_a, const std::vector<Vector2> &Verts_b);
protected:
    bool ridgid;
    float mass;
    float rotation;
    float speed; 
    std::vector<Vector2> vertices;
	float x;
	float y;
};

#endif