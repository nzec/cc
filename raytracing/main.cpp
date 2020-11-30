#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"

#include <iostream>

using std::cout;
using std::cerr;

double hit_sphere(const point3& center, const double& radius, const ray& r) {
	vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2 * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1.0;
	} else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

color ray_color(const ray& r) {
	auto center = point3(0, 0, -1);
	auto t = hit_sphere(center, 0.5, r);
	if (t > 0.0) {
		vec3 N = unit_vector(r.at(t) - center);
		return 0.5 * (N + 1);
	}

	// Make the gradient more circular'ish from the top center
	// because unit_direction.y() is maximized at top center
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);

	// A simpler gradient from top to bottom
	// auto t = r.direction().y() + 1.0;

	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio); 

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * aspect_ratio;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin -
		horizontal / 2 -
		vertical / 2 -
		vec3(0, 0, focal_length);

	cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	
	for (int j = image_height - 1; j >= 0; j--) {
		cerr << "\rLines remaining: " << j << " " << std::flush;

		for (int i = 0; i < image_width; i++) {
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);

			// tail = origin,
			// direction = (0, 0, 0) -> pixel on viewport
			ray r(origin, lower_left_corner +
					u * horizontal +
					v * vertical
					- origin);

			color pixel_color = ray_color(r);
			write_color(cout, pixel_color);
		}
	}
	cerr << "\nDone.\n";
}
