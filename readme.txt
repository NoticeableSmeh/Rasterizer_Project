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

Example Output:
---------------
https://media2.dev.to/dynamic/image/width=800%2Cheight=%2Cfit=scale-down%2Cgravity=auto%2Cformat=auto/https%3A%2F%2Fdev-to-uploads.s3.amazonaws.com%2Fuploads%2Farticles%2Fkmoz7fmp5hzbukouwz22.png

Build Instructions
------------------
Compile and run using any C++17 compiler:
I put the zip onto my dekstop 
C:\Users\yourName\Desktop\Rasterizer_Project-main

so CD C:\Users\yourName\Desktop\Rasterizer_Project-main

then I run 

g++ main.cpp model.cpp -o rasterizer -std=c++17

Double click .exe that is now in folder and it should run.

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

For a more indepth review of the code: A step by step walkthrough on creating it.

https://dev.to/noticeablesmeh/rasterizer-project-part-1-getting-started-jph 



