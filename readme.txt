Rasterizer Project
========================

A simple CPU-based 3D rasterizer written in C++.
It loads .obj models, projects them to 2D, fills triangles using barycentric coordinates,
and saves the result to a .bmp image 


Features
--------
- Basic .obj model loader
- Triangle rasterization with barycentric coordinates
- Backface culling
- Framebuffer output saved as .bmp
- Completely self-contained (no external dependencies)


Build Instructions
------------------
Compile and run using any C++17 compiler:

    g++ main.cpp model.cpp -o rasterizer -std=c++17
    ./rasterizer

The program will generate a file called framebuffer.bmp in your project folder.


3D Models Used
--------------
Cow:
https://www.cs.cmu.edu/~kmcrane/Projects/ModelRepository/

Reference:
Crane, Keenan; Pinkall, Ulrich; Schröder, Peter.
"Robust Fairing via Conformal Curvature Flow"
ACM Transactions on Graphics (TOG), 32(4), 1–10, 2013.
Publisher: ACM New York, NY, USA.

Triceratops:
https://3d.si.edu/object/3d/triceratops-horridus-marsh-1889:d8c623be-4ebc-11ea-b77f-2e728ce88125


External Dependencies
---------------------
STB Image Write (used for saving .bmp output)
https://github.com/nothings/stb


Based On
--------
TinyRenderer - https://haqr.eu/tinyrenderer/



