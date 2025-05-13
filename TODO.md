# MiniRT
Simple C ray tracer.

### basic
- [X] Create Camera and iterate over pixels
- [ ] Create scene and calculate intersections of rays and objects
  - [ ] Sphere
    - [X] basic intersection
	- [ ] only spheres in front of cam
	- [ ] shading
	- [ ] light level
	- [ ] ray rebound
  - [ ] Cylinder
  - [ ] Wall

- [] Parsing
	- [X] handle empty file

- [ ] add double_is_equal() using epsilon
- [ ] add vec3_is_equal() aswell

### end
 - [ ] remove wildcard from Makefile
 - [ ] remove all asserts
 - [ ] remove time.h and timing in main

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
