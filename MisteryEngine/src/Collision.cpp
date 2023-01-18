#include "../include/Rect.hpp"
#include "../include/Vec2.hpp"

#include <algorithm>
#include <cmath>

class Collision {

	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
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
				v =  (v - a.get_center()).rotate(angleOfA) + a.get_center();
			}

			for (auto& v : B) {
				v = (v - b.get_center()).rotate(angleOfB) + b.get_center();
			}

			Vec2 axes[] = { (A[0] - A[1]).normalise() , (A[1] - A[2]).normalise(), (B[0] - B[1]).normalise(), (B[1] - B[2]).normalise() };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}
};
