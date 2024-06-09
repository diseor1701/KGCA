#include "T_Math.h"
namespace T_Math
{
    FVector2 FVector2::ZeroVector2(0.0f, 0.0f);
    FVector2 T_Math::FVector2::operator+(const FVector2& v) const
    {
        return FVector2(X + v.X, Y + v.Y);
    }

    FVector2 T_Math::FVector2::operator-(const FVector2& v) const
    {
        return FVector2(X - v.X, Y - v.Y);
    }

    FVector2 T_Math::FVector2::operator*(const float s) const
    {
        return FVector2(X * s, Y * s);
    }

    FVector2 T_Math::FVector2::operator/(const float s) const
    {
        return FVector2(X / s, Y / s);
    }

    float T_Math::FVector2::Length()
    {
        return sqrt(X * X + Y * Y);
    }

    FVector2 FVector2::Normarlize()
    {
        float fLength = 0.0f;
        if (IsZero(fLength)) return ZeroVector2;
        return FVector2(X / fLength, Y / fLength);
    }

    bool T_Math::FVector2::IsZero()
    {
        float fLength = Length();
        if (fLength <= 0.00001f)
        {
            return true;
        }
        return false;
    }

    bool T_Math::FVector2::IsZero(float& fLength)
    {
        fLength = Length();
        if (fLength <= 0.00001f)
        {
            return true;
        }
        return false;
    }
}