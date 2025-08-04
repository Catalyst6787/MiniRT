# MiniRT
Simple C ray tracer.

### basic

- [ ] problem with cone normals


- [ ] euler ?
- [ ] fix a little problem in the tests (commented for now)
- [ ] if he time allow it, be able to move light (event)

### optional

- [ ] add a ratio to move object faster
- [ ] add height mode to pav num
- [ ] display last key pressed


- [X] parsing problem if more than one zero after the coma (try also with 2 dots)
- [X] vec3_basic op use pointers (actually a mess because of the functions calls as parameters)
- [X] this shouldnt work : co 1,0,    0,0,-0.4   2 1 210,95,210
- [X] cone
- [X] ./dev.sh 16 not working
- [X] add size mode to pav num
- [X] start to think how to bonus
- [X] parsing case : pl 0,0,5 1 0,1,0 255,255,255 (count number of numbers)
- [X] parsing need to work with tabs (or parse out the tabs) (add in in move cursor)
- [X] prepare the project to merge it on main
- [X] option to display the commands
- [X] option to activate cone cap
- [X] cylider caps
- [X] change rays to pointers
- [X] why does dir.y cylinder doesnt do shit ?
- [X] add the selected object feature (different from light ?)
- [X] Inter should take *ray instead of ray
- [X] parsing : filter number of coma




- [X] Create Camera and iterate over pixels
- [X] Create scene and calculate intersections of rays
and objects
  - [X] Sphere
    - [X] basic intersection
	- [X] only spheres in front of cam
	- [X] shading
	- [X] light level
	- [X] ray rebound
  - [X] Cylinder
  - [X] Wall

- [] Parsing
	- [X] handle empty file


### bonuses list

 - [X] phong
 - [X] colored and multi spot lighs
 - [X] cube / cone
 - [ ] (diffusion)
 - [X] reflections
 - [ ] refraction
 - [X] multithreading

Other ideas :
 - [ ] Patterns (perlin)

### end

 - [ ] remove all asserts
 - [ ] remove time.h and timing in render.c
 - [ ] remove PRINT_DEBUG
 - [ ] do we need to check mlx init ?


### Completed Column ✓
- [X] Add error handling to init functions


---
With malloc in render_pixel():
	total 2,560,584 allocs.
	runs in ~ 0.1s
Without malloc in render_pixel():
	total 587 allocs.
	runs in ~ 0.05s

(this test was with about 5 mallocs per pixel at the start.)

without malloc, render logic is 2x faster so we'll make sure to use only stack allocation inside the render logic as much as possible.
