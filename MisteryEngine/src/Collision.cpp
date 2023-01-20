#include "../include/Collision.hpp"

#include <algorithm>
#include <cmath>

using namespace std;

// Observação: IsColliding espera ângulos em radianos!
// Para usar graus, forneça a sua própria implementação de Rotate,
// ou transforme os ângulos no corpo de IsColliding.
bool Collision::IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {

	angleOfA = degrees_to_radians(angleOfA);
	angleOfB = degrees_to_radians(angleOfB);

	Vec2 A[] = { Vec2( a.x, a.y + a.h ),
					Vec2( a.x + a.w, a.y + a.h ),
					Vec2( a.x + a.w, a.y ),
					Vec2( a.x, a.y )
				};
	Vec2 B[] = { Vec2( b.x, b.y + b.h ),
					Vec2( b.x + b.w, b.y + b.h ),
					Vec2( b.x + b.w, b.y ),
					Vec2( b.x, b.y )
				};

	for (auto& v : A) {
		v = Vec2::Sum(Vec2::Rot(Vec2::Sub(v, a.get_center()),angleOfA), a.get_center());
	}

	for (auto& v : B) {
		v = Vec2::Sum(Vec2::Rot(Vec2::Sub(v, b.get_center()), angleOfB), b.get_center());
	}

	Vec2 axes[] = { Vec2::Norm(Vec2::Sub(A[0], A[1])) , Vec2::Norm(Vec2::Sub(A[1], A[2])), Vec2::Norm(Vec2::Sub(B[0], B[1])), Vec2::Norm(Vec2::Sub(B[1], B[2])) };

	for (auto& axis : axes) {
		float P[4];

		for (int i = 0; i < 4; ++i) P[i] = Vec2::Dot(A[i], axis);

		float minA = *std::min_element(P, P + 4);
		float maxA = *std::max_element(P, P + 4);

		for (int i = 0; i < 4; ++i) P[i] = Vec2::Dot(B[i], axis);

		float minB = *std::min_element(P, P + 4);
		float maxB = *std::max_element(P, P + 4);

		if (maxA < minB || minA > maxB)
			return false;
	}

	return true;
}
