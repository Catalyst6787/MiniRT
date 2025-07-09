# MiniRT
Simple C ray tracer.

### basic

- [ ] change rays to pointers
- [ ] cone
- [ ] start to think how to bonus
- [ ] prepare the project to merge it on main
- [ ] parsing need to work with tabs (or parse out the tabs) (add in in move cursor)

- [X] why does dir.y cylinder doesnt do shit ?
- [X] add the selected object feature (different from light ?)
- [X] Inter should take *ray instead of ray

- [X] parsing : filter number of coma

- [X] Create Camera and iterate over pixels
- [X] Create scene and calculate intersections of rays and objects
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

### optional

- [ ] add a ratio to move object faster


### cone

- [ ] object_type_to_str
- [ ] set_cone_tranformation
- [ ] create_object_from_cone
- [ ] parsing
- [ ] int	count_intersections


### bonuses list

 - [X] phong
 - [ ] colored and multi spot lighs
 - [ ] cube / cone
 - [ ] diffusion
 - [ ] multithreading

Other ideas :
 - [ ] Patterns (perlin)

### end
 - [ ] remove all asserts
 - [ ] remove time.h and timing in render.c
 - [ ] remove PRINT_DEBUG


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
