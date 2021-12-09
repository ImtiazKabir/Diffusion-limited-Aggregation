# DIFFUSION-LIMITED AGGREGATION
This is an implementation of Diffusion-limited aggregation in [SDL2](https://www.libsdl.org/) and [emscripten](https://emscripten.org/)

> Diffusion-limited aggregation (DLA) is the process whereby particles undergoing a random walk due to Brownian motion cluster together to form aggregates of such particles. This theory, proposed by T.A. Witten Jr. and L.M. Sander in 1981
> [Wikipedia](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation)

![init](https://github.com/ImtiazKabir/Diffusion-limited-Aggregation/blob/main/screenshots/init.PNG)
![final](https://github.com/ImtiazKabir/Diffusion-limited-Aggregation/blob/main/screenshots/final.PNG)
![growing_with_movers](https://github.com/ImtiazKabir/Diffusion-limited-Aggregation/blob/main/screenshots/growing_with_mover.PNG)
![growing_without_movers](https://github.com/ImtiazKabir/Diffusion-limited-Aggregation/blob/main/screenshots/growing_without_movers.PNG)


## Usage as SDL2 project
1. Compile the project with `make sdl`
2. Run the program with `make run`
3. You can move the build folder to any directory after compilation.
4. Press SPACE to toggle the render of moving particles.

## Usage as EMSCRIPTEN project
This is the [deployed site](https://imtiazkabir.github.io/Diffusion-limited-Aggregation/) for DLA. Enjoy! *You can press SPACE to toggle the render of moving particles.*
Emscripten compilation can be done with `make ems`


*This project uses [stb_ds](http://nothings.org/stb_ds/)*
