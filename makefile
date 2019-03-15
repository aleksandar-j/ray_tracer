objects = ray_tracer/main.o ray_tracer/main_trace.o \
	ray_tracer/math_extension.o ray_tracer/vector.o \
	ray_tracer/objects_list.o ray_tracer/shape.o ray_tracer/texture.o \
	ray_tracer/atmosphere.o ray_tracer/camera.o ray_tracer/light.o \
	ray_tracer/render_settings.o

build_out = build_ray_tracer

build : $(objects)
	g++ $(objects) -pthread -lSDL2

clean :
	-rm ray_tracer/*.o
	-rm a.out
