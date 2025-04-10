# Software Renderer in C/C++
A basic software rasterizer written in C that renders simple 2D graphics and exports a raw pixel buffer to a .data file. This file can be viewed using tools like GIMP or ImageMagick by interpreting it as raw image data.

## 📚 Topics

- Line drawing 
   - [x] Mathematical Equation
   - [ ] DDA Algorithm
   - [ ] Bresenham Algorithm
   - [ ] Different Thickness
   - [ ] Antialiasing (Xiaolin Wu)
- Circle drawing  
   - [x] Mathematical Equations
   - [ ] Bresenham Approach
- Polygon filling  
   - [ ] Scan Line
   - [ ] Flood Fill
- Text rendering  
   - [ ] Pre-Converting
- Coordinate Transformations  
- Line and Polygon Clipping  
   - [ ] Cohen-Sutherland Algorithm
   - [ ] Cyrus-Beck-Liang-Barsky Algorithm  

More coming soon

## Usage  
### ✅ Prerequisites
- A C compiler (e.g., `gcc` , `clang`, `MSVC`)
- GIMP, ImageMagick, or any image viewer that supports loading raw `.data`

### Build & Run
```bash
gcc main.c -o renderer -lm
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
