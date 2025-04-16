# Software Renderer in C/C++
A basic software rasterizer written in C that renders simple 2D graphics and exports a raw pixel buffer to a .data file. This file can be viewed using tools like GIMP or ImageMagick by interpreting it as raw image data.

## 🎯 Project Goals

The primary objectives of this project are to:

1. __Implement Core Rendering Algorithms__: Develop and optimize key 2D graphics algorithms, such as line drawing, circle drawing, and polygon filling, which are fundamental to rendering in computer graphics.

2. __Explore Efficient Rendering Techniques__: Optimize and implement algorithms for better performance and visual quality, including anti-aliasing and handling different line thicknesses.

3. __Learn Computer Graphics Theory__: Gain a deeper understanding of geometric transformations, coordinate systems, clipping algorithms, and rasterization techniques.

4. __Generate Visual Outputs__: Produce visual outputs that can be viewed in image editors (GIMP, ImageMagick) by exporting raw pixel data.

5. __Expand the Algorithm Library__: Gradually add more graphics algorithms, such as texture mapping, shading models, and 3D object rendering, to create a comprehensive library of algorithms.

## 📚 Topics

- [Line drawing](docs/line-drawing.md) 
   - [x] Mathematical Equation
   - [x] DDA Algorithm
   - [x] Bresenham Algorithm
   - [ ] Different Thickness
   - [ ] Antialiasing (Xiaolin Wu)
- [Circle drawing](docs/circle-drawing.md)
   - [x] Mathematical Equations
   - [ ] Bresenham Approach
- [Polygon drawing & filling](docs/polygon-drawing-filling.md)
   - [ ] Connecting Vertices
   - [ ] Scan Line
   - [ ] Flood Fill
- Text rendering  
   - [ ] Naive Rendering
   - [ ] Pre-Converting
- Line and Polygon Clipping  
   - [ ] Cohen-Sutherland Algorithm
   - [ ] Cyrus-Beck-Liang-Barsky Algorithm  

More coming soon

## Usage  
### ✅ Prerequisites
- A C compiler (e.g., `gcc` , `clang`, `MSVC`)
- CMake
- GIMP, ImageMagick, or any image viewer that supports loading raw `.data`

### Build & Run
```bash
mkdir build
cd build
cmake ../
make
./renderer
```
This will generate a file called pixmap.data in the current directory.

### 🖼️ Viewing the output (e.g. GIMP)
1. Open Gimp.
2. Go to File > Open.
3. Choose pixmap.data.
4. In the Raw Image Data import dialog:  
   - Image Type: RGBA
   - Width: width of the pixmap itself (e.g. 800)
   - Height: height of the pixmap itself (e.g. 600)
   - Offset: 0
5. Click import to view the image.


## License
This project is licensed under the MIT License. Feel free to use, modify, and distribute it as you wish.
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
