#pragma once

// defines rgba color
struct Color32
{
public:
    Color32() = default;
    Color32(unsigned int rgba): mRGBA(rgba) {}
    Color32(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca)
        : mR(cr)
        , mG(cg)
        , mB(cb)
        , mA(ca)
    {
    }
    // @param rgba: Source 32bits color
    inline Color32& operator = (Color32 rgba)
    {
        mRGBA = rgba.mRGBA;
        return *this;
    }
    // set color components
    // @param cr, cg, cb, ca: Color components
    inline void Setup(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca)
    {
        mA = cr;
        mR = cg;
        mG = cg;
        mB = cb;
    }

    // combine rgba channels into single unsigned int value
    static unsigned int MakeRGBA(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca)
    {
        return ((unsigned int)(cr)) | (((unsigned int)(cg)) << 8U) | (((unsigned int)(cb)) << 16U) | (((unsigned int)(ca)) << 24U);
    }

    // implicit conversion to int
    inline operator unsigned int () const { return mRGBA; }

    inline unsigned char operator [] (int index) const
    {
        debug_assert(index > -1 && index < 4);
        return mChannels[index];
    }

    inline unsigned char& operator [] (int index)
    {
        debug_assert(index > -1 && index < 4);
        return mChannels[index];
    }

public:
    union
    {
        struct
        {
            unsigned char mChannels[4];
        };
        struct
        {
            unsigned char mR;
            unsigned char mG;
            unsigned char mB;
            unsigned char mA;
        };
        unsigned int mRGBA;
    };
};

const unsigned int Sizeof_Color32 = sizeof(Color32);

inline bool operator == (Color32 lhs, Color32 rhs) { return lhs.mRGBA == rhs.mRGBA; }
inline bool operator != (Color32 lhs, Color32 rhs) { return lhs.mRGBA != rhs.mRGBA; }

// standard colors
extern const Color32 Color32_Red;
extern const Color32 Color32_Green;
extern const Color32 Color32_DarkGreen;
extern const Color32 Color32_Orange;
extern const Color32 Color32_Blue;
extern const Color32 Color32_Brown;
extern const Color32 Color32_SkyBlue;
extern const Color32 Color32_DarkBlue;
extern const Color32 Color32_White;
extern const Color32 Color32_DarkGray;
extern const Color32 Color32_GrimGray;
extern const Color32 Color32_Gray;
extern const Color32 Color32_Black;
extern const Color32 Color32_Cyan;
extern const Color32 Color32_Yellow;
extern const Color32 Color32_NULL;

// defines array of bytes
using ByteArray = std::vector<unsigned char>;

// defines coordinate or size in 2d
using Point = glm::ivec2;

// defines rectangle in 2d
struct Rectangle
{
public:
    Rectangle() = default;
    Rectangle(int posx, int posy, int sizex, int sizey)
        : x(posx)
        , y(posy)
        , w(sizex)
        , h(sizey)
    {
    }
    inline void Set(int posx, int posy, int sizex, int sizey)
    {
        x = posx;
        y = posy;
        w = sizex;
        h = sizey;
    }
    inline void SetNull()
    {
        x = 0;
        y = 0;
        w = 0;
        h = 0;
    }
    // test whether point is within rect
    inline bool PointWithin(const Point& point) const
    {
        return point.x >= x && point.y >= y &&
            point.x < (x + w - 1) &&
            point.y < (y + h - 1);
    }
    // get union area of two rectangles
    inline Rectangle GetUnion(const Rectangle& rc) const
    {
        Rectangle rcOutput;

        int maxx = glm::max(x + w, rc.x + rc.w);
        int maxy = glm::max(y + h, rc.y + rc.h);

        rcOutput.x = glm::min(x, rc.x);
        rcOutput.y = glm::min(y, rc.y);
        rcOutput.w = glm::max(maxx - rcOutput.x, 0);
        rcOutput.h = glm::max(maxy - rcOutput.y, 0);

        return rcOutput;
    }
    // get intersection area of two rectangles
    inline Rectangle GetIntersection(const Rectangle& rc) const
    {        
        Rectangle rcOutput;

        int minx = glm::min(x + w, rc.x + rc.w);
        int miny = glm::min(y + h, rc.y + rc.h);

        rcOutput.x = glm::max(x, rc.x);
        rcOutput.y = glm::max(y, rc.y);
        rcOutput.w = glm::max(minx - rcOutput.x, 0);
        rcOutput.h = glm::max(miny - rcOutput.y, 0);

        return rcOutput;
    }
public:
    int x, y;
    int w, h;
};

inline bool operator == (const Rectangle& lhs, const Rectangle& rhs) 
{ 
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && 
        (lhs.w == rhs.w) && 
        (lhs.h == rhs.h);
}

inline bool operator != (const Rectangle& lhs, const Rectangle& rhs)
{
    return (lhs.x != rhs.x) || (lhs.y != rhs.y) || 
        (lhs.w != rhs.w) ||
        (lhs.h != rhs.h);
}

// console log message category
enum eLogMessage
{
    eLogMessage_Debug,
    eLogMessage_Info,
    eLogMessage_Warning,
    eLogMessage_Error,
    eLogMessage_COUNT
};

decl_enum_strings(eLogMessage);

// 