#include "../../includes/math_tool.h"
#include <stdio.h>

// Helper to print vectors cleanly
void	print_vec(char *name, t_vec3 v)
{
	printf("%s: [%.2f, %.2f, %.2f]\n", name, v.x, v.y, v.z);
}

int	main(void)
{
	printf("=== TESTING VECTOR MATH ===\n");

	// 1. Initialization
	t_vec3 v1 = vec_init(1, 0, 0); // X-axis
	t_vec3 v2 = vec_init(0, 1, 0); // Y-axis
	t_vec3 v3 = vec_init(0, 0, 5); // Z-axis (long)
	print_vec("v1", v1);
	print_vec("v2", v2);
	print_vec("v3", v3);

	// 2. Addition & Subtraction
	printf("\n-- Add / Sub --\n");
	print_vec("v1 + v2", vec_add(v1, v2)); // Exp: [1.00, 1.00, 0.00]
	print_vec("v1 - v2", vec_sub(v1, v2)); // Exp: [1.00, -1.00, 0.00]

	// 3. Scaling & Length
	printf("\n-- Scale & Length --\n");
	print_vec("v3 * 0.5", vec_scale(v3, 0.5)); // Exp: [0.00, 0.00, 2.50]
	printf("Len(v3): %.2f (Expected: 5.00)\n", vec_len(v3));

	// 4. Normalization
	printf("\n-- Normalization --\n");
	t_vec3 norm_v3 = vec_normalize(v3);
	print_vec("Normalized v3", norm_v3); // Exp: [0.00, 0.00, 1.00]
	printf("Len(Norm_v3): %.2f (Expected: 1.00)\n", vec_len(norm_v3));

	// 5. Dot Product
	printf("\n-- Dot Product --\n");
	double d1 = vec_dot(v1, v2); // Perpendicular
	double d2 = vec_dot(v1, v1); // Parallel
	printf("Dot(v1, v2): %.2f (Expected: 0.00)\n", d1);
	printf("Dot(v1, v1): %.2f (Expected: 1.00)\n", d2);

	// 6. Cross Product (The Standard Check)
	printf("\n-- Cross Product --\n");
	// Cross(X-axis, Y-axis) should be Z-axis
	t_vec3 cross = vec_cross(v1, v2);
	print_vec("Cross(v1, v2)", cross); // Exp: [0.00, 0.00, 1.00]

	// Check order (Y x X should be -Z)
	t_vec3 cross_neg = vec_cross(v2, v1);
	print_vec("Cross(v2, v1)", cross_neg); // Exp: [0.00, 0.00, -1.00]

	printf("\n=== TESTING COLOR OPS ===\n");

	// 7. Color Creation (Int -> Double)
	t_color c1 = color_init(255, 0, 0);     // Red
	t_color c2 = color_init(128, 128, 128); // Grey
	print_vec("Red (0-1)", c1);            // Exp: [1.00, 0.00, 0.00]
	print_vec("Grey (0-1)", c2);           // Exp: [0.50, 0.50, 0.50]

	// 8. Color Multiplication
	t_color mix = color_mult(c1, c2); // Red * Grey
	print_vec("Red * Grey", mix);     // Exp: [0.50, 0.00, 0.00] (Dark Red)

	// 9. Color to Int (Hex) and Clamping
	printf("\n-- Hex Conversion --\n");
	int hex_red = color_to_int(c1);
	printf("Red Hex: %X (Expected: FF0000)\n", hex_red);

	// Test Over-exposure clamping
	t_color bright = vec_init(2.5, -0.5, 10.0); // Crazy values
	int hex_clamp = color_to_int(bright);
	printf("Clamped Hex: %X (Expected: FF00FF)\n", hex_clamp); // R=255, G=0, B=255

	return (0);
}
