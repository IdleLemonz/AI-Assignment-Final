#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	void SetX(float x);
	void SetY(float y);
	void Set(float x, float y);
	float GetX();
	float GetY();
	float Dot(const Vector2& other);
	float Length();
	Vector2 Normalise();
	static Vector2 Normalise(Vector2 val);
	float Magnitude();
	float Distance(Vector2 other);

	Vector2 operator + (const Vector2& other);
	Vector2 operator - (const Vector2& other);
	Vector2 operator / (const Vector2& other);
	Vector2 operator / (const float& other);
	Vector2 operator * (const Vector2& other);
	Vector2 operator * (const float& other);
	Vector2& operator = (const Vector2& other);

	operator float*();

	friend Vector2 operator * (const float& lhs, const Vector2& rhs);

	//private:
	float m_x = 0.0f;
	float m_y = 0.0f;
};

Vector2 operator * (const float& lhs, const Vector2& rhs);