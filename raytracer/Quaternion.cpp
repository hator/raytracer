#include "stdafx.h"
#include "Quaternion.h"

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), v(x, y, z) {}
Quaternion::Quaternion(float w, vec3 v) : w(w), v(v) {}
Quaternion::Quaternion(vec3 axis, float angle) {
	w = cos(angle/2.f);
	v = axis*sin(angle/2.f);
}

Quaternion Quaternion::fromTwoVectors(vec3::i u, vec3::i v) {
	float m = sqrt( 2.f * (1.f + u.dot(v)) );
	vec3 w = u.cross(v) * (1.f / m);
	return Quaternion(0.5f * m, w);
}

Quaternion Quaternion::inverse() const {
	return Quaternion(w, -v);
}
	
Quaternion Quaternion::operator*(const Quaternion q) const {
	const float w1 = w;
	const float w2 = q.w;
	const vec3 v1 = v;
	const vec3 v2 = q.v;
	return Quaternion(
		w1*w2 - v1.dot(v2),
		v2*w1 + v1*w2 + v1.cross(v2)
	);
}


vec3 Quaternion::rotate(vec3::i p) const {
	const vec3 vxp = v.cross(p);
	return p + vxp*2.f*w + v.cross(vxp)*2.f;
}

vec3 rotate(vec3::i v, const Quaternion q) {
	return q.rotate(v);
}