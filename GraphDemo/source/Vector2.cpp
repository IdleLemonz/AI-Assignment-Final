#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	m_x = 0.0f;
	m_y = 0.0f;
}
Vector2::Vector2(float x1, float y1)
{
	m_x = x1;
	m_y = y1;
}

Vector2::~Vector2() {}

void Vector2::SetX(float x1)
{
	m_x = x1;
}

void Vector2::SetY(float y1)
{
	m_y = y1;
}

void Vector2::Set(float x1, float y1)
{
	m_x = x1;
	m_y = y1;
}

float Vector2::GetX()
{
	return m_x;
}

float Vector2::GetY()
{
	return m_y;
}

float Vector2::Dot(const Vector2& other)
{
	float temp = ((m_x*other.m_x) + (m_y*other.m_y));
	return temp;
}

float Vector2::Length()
{
	float length = sqrt((m_x*m_x) + (m_y*m_y));
	return length;
}

Vector2 Vector2::Normalise()
{
	Vector2 temp;
	if (Length() > 0)
	{
		float len = Length();
		temp.m_x = m_x / len;
		temp.m_y = m_y / len;
	}
	return temp;
}

Vector2 Vector2::Normalise(Vector2 val)
{
	Vector2 temp;
	if (val.Length() > 0)
	{
		float len = val.Length();
		temp.m_x = val.m_x / len;
		temp.m_y = val.m_y / len;
	}
	return temp;
}

float Vector2::Magnitude()
{
	return sqrt(m_x*m_x + m_y*m_y);
}

float Vector2::Distance(Vector2 other)
{
	return(*this - other).Magnitude();
}

Vector2 Vector2::operator + (const Vector2& other)
{
	Vector2 newVec;
	newVec.m_x = m_x + other.m_x;
	newVec.m_y = m_y + other.m_y;
	return newVec;
}

Vector2 Vector2::operator - (const Vector2& other)
{
	Vector2 newVec;
	newVec.m_x = m_x - other.m_x;
	newVec.m_y = m_y - other.m_y;
	return newVec;
}

Vector2 Vector2::operator / (const Vector2& other)
{
	Vector2 newVec;
	newVec.m_x = m_x / other.m_x;
	newVec.m_y = m_y / other.m_y;
	return newVec;
}

Vector2 Vector2::operator / (const float& other)
{
	Vector2 newVec;
	newVec.m_x = m_x / other;
	newVec.m_y = m_y / other;
	return newVec;
}

Vector2 Vector2::operator * (const Vector2& other)
{
	Vector2 newVec;
	newVec.m_x = m_x * other.m_x;
	newVec.m_y = m_y * other.m_y;
	return newVec;
}

Vector2 Vector2::operator * (const float& other)
{
	Vector2 newVec;
	newVec.m_x = m_x * other;
	newVec.m_y = m_y * other;
	return newVec;
}

Vector2& Vector2::operator = (const Vector2& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	return *this;
}

Vector2::operator float*()
{
	return (float*)this;
}

Vector2 operator * (const float& lhs, const Vector2& rhs)
{
	Vector2 newVec;
	newVec.m_x = lhs * rhs.m_x;
	newVec.m_y = lhs * rhs.m_y;
	return newVec;
}