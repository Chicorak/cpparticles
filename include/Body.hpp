#ifndef body_hpp
#define body_hpp
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <algorithm>


struct Vector2
{
    float x, y;
};
Vector2 operator+(Vector2 const& v1, Vector2 const& v2);

class Body{
public:
    Body(float x, float y, std::vector<Vector2> vertices, float speed, float rotation, float drag, float mass, bool ridgid);
    float getRotation() { return rotation; }
	float getSpeed() { return speed; }
	float getX() { return x; }
	float getY() { return y; }
    std::vector<Vector2> getVertices() { return vertices; }
    bool getRidgidity() { return ridgid; }
    void accelerate(Vector2 vector);
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
    float drag;
    float rotation;
    float speed; 
    std::vector<Vector2> vertices;
	float x;
	float y;
};

#endif