objects = ray_tracer/main.o ray_tracer/main_trace.o \
	ray_tracer/math_extension.o ray_tracer/vector.o \
	ray_tracer/atmosphere.o ray_tracer/camera.o ray_tracer/light.o \
	ray_tracer/render_settings.o

build_out = build_ray_tracer

build : $(objects)
	g++ -o $(build_out) $(objects) -pthread -lSDL2

main_trace.o : camera.hpp objects_list.hpp render_settings.hpp

clean :
	-rm ray_tracer/*.o
