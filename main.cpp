// For a more detailed walkthrough of the entire process of creating this code
// https://dev.to/noticeablesmeh/rasterizer-project-part-1-getting-started-jph

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "geometry.h"
#include "model.h"
#include "stb_image_write.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 800;
using namespace std;

// Simple RGBA color struct
struct Color {
    uint8_t r, g, b, a;
};

// Some basic colors
Color red { 255, 0, 0, 255 };
Color green { 0, 255, 0, 255 };
Color blue { 0, 0, 255, 255 };
Color white { 255, 255, 255, 255 };
Color yellow { 0, 200, 255, 255 };
Color black { 0, 0, 0, 255 };

// Framebuffer stores all our pixels
struct Framebuffer {
    int w, h;
    std::vector<uint8_t> data; // 4 bytes per pixel (RGBA)

    Framebuffer(int SCREEN_WIDTH, int SCREEN_HEIGHT)
        : w(SCREEN_WIDTH)
        , h(SCREEN_HEIGHT)
        , data(SCREEN_WIDTH * SCREEN_HEIGHT * 4, 0)
    {
    }

    // Fills the entire framebuffer with one color
    inline void clear(Color c)
    {
        for (int i = 0; i < w * h; i++) {
            int k = i * 4;
            data[k + 0] = c.r;
            data[k + 1] = c.g;
            data[k + 2] = c.b;
            data[k + 3] = c.a;
        }
    }

    // Sets a single pixel at (x, y)
    inline void set(int x, int y, Color c)
    {
        if (x < 0 || y < 0 || x >= w || y >= h)
            return;
        int i = (y * w + x) * 4;
        data[i + 0] = c.r;
        data[i + 1] = c.g;
        data[i + 2] = c.b;
        data[i + 3] = c.a;
    }

    // Saves the framebuffer to a .bmp file
    bool save_bmp(const char* path)
    {
        stbi_flip_vertically_on_write(1);
        return stbi_write_bmp(path, w, h, 4, data.data());
    }
};

// Basic line drawing using a Bresenham-like approach
void line(int ax, int ay, int bx, int by, Framebuffer& framebuffer, Color color)
{
    bool steep = abs(ax - bx) < abs(ay - by);
    if (steep) {
        swap(ax, ay);
        swap(bx, by);
    }
    if (ax > bx) {
        swap(ax, bx);
        swap(ay, by);
    }
    int y = ay;
    int ierror = 0;
    for (int x = ax; x <= bx; x++) {
        if (steep)
            framebuffer.set(y, x, color);
        else
            framebuffer.set(x, y, color);
        ierror += 2 * abs(by - ay);
        if (ierror > bx - ax) {
            y += (by > ay ? 1 : -1);
            ierror -= 2 * (bx - ax);
        }
    }
}

// Draws a wireframe triangle (3 lines)
void triangle(int ax, int ay, int bx, int by, int cx, int cy, Framebuffer& framebuffer, Color color)
{
    line(ax, ay, bx, by, framebuffer, color);
    line(bx, by, cx, cy, framebuffer, color);
    line(cx, cy, ax, ay, framebuffer, color);
}

// Converts a 3D vertex into 2D screen space
pair<int, int> project(const vec3& vertex, int width, int height)
{
    double normalizedX = (vertex.x + 1.0) / 2.0;
    double normalizedY = (vertex.y + 1.0) / 2.0;

    int screenX = static_cast<int>(normalizedX * (width - 1));
    int screenY = static_cast<int>(normalizedY * (height - 1));

    return { screenX, screenY };
}

// Fills a triangle using barycentric coordinates
void triangle_fill(int ax, int ay, int bx, int by, int cx, int cy, Framebuffer& fb, Color color)
{
    // Bounding box for the triangle
    int minx = std::max(0, std::min(ax, std::min(bx, cx)));
    int maxx = std::min(fb.w - 1, std::max(ax, std::max(bx, cx)));
    int miny = std::max(0, std::min(ay, std::min(by, cy)));
    int maxy = std::min(fb.h - 1, std::max(ay, std::max(by, cy)));

    // Used to normalize barycentric weights (based on triangle area)
    double denom = double(by - cy) * double(ax - cx) + double(cx - bx) * double(ay - cy);
    if (denom == 0.0)
        return;

    // Check each pixel inside bounding box
    for (int y = miny; y <= maxy; ++y) {
        for (int x = minx; x <= maxx; ++x) {
            // Compute barycentric coordinates
            double w1 = (double(by - cy) * double(x - cx) + double(cx - bx) * double(y - cy)) / denom;
            double w2 = (double(cy - ay) * double(x - cx) + double(ax - cx) * double(y - cy)) / denom;
            double w0 = 1.0 - w1 - w2;

            // If all weights are positive, the pixel is inside the triangle!
            if (w0 >= 0.0 && w1 >= 0.0 && w2 >= 0.0)
                fb.set(x, y, color);
        }
    }
}

// Checks if the triangle is facing away from the camera via 2D Cross Product
bool backface_culled(int ax, int ay, int bx, int by, int cx, int cy)
{
    int abx = bx - ax, aby = by - ay;
    int acx = cx - ax, acy = cy - ay;
    int area2 = abx * acy - aby * acx;
    return area2 >= 0; // Cull if facing away
}

// Loops through all faces in the model and fills them
void draw_model_filled(Model& model, Framebuffer& fb)
{
    for (int i = 0; i < model.getFaceCount(); ++i) {
        auto [ax, ay] = project(model.getVertexFromFace(i, 0), fb.w, fb.h);
        auto [bx, by] = project(model.getVertexFromFace(i, 1), fb.w, fb.h);
        auto [cx, cy] = project(model.getVertexFromFace(i, 2), fb.w, fb.h);

        // Skip triangles facing away
        if (backface_culled(ax, ay, bx, by, cx, cy))
            continue;

        // Give each triangle a unique color % fun
        Color c {
            uint8_t(50 + (i * 97) % 206),
            uint8_t(50 + (i * 57) % 206),
            uint8_t(50 + (i * 23) % 206),
            255
        };

        triangle_fill(ax, ay, bx, by, cx, cy, fb, c);
    }
}

// Main loop
int main(int, char**)
{
    Framebuffer fb(SCREEN_WIDTH, SCREEN_HEIGHT);
    fb.clear(black);

    Model model("spot_triangulated.obj"); // Load the model

    // test triangles
    // triangle_fill(7, 45, 35, 100, 45, 60, fb, red);

    draw_model_filled(model, fb); // Render model to framebuffer

    fb.save_bmp("framebuffer.bmp"); // Save output image
    return 0;
}
