#pragma once

struct Vector3 {
	float x, y, z;

	void Scale(Vector3 scale) {
		return Method::Call<void(*)(Vector3*, Vector3)>("UnityEngine.CoreModule", "UnityEngine", "Vector3", "Scale", 1)(this, scale);
	}
	static Vector3 Cross(Vector3 lhs, Vector3 rhs) {
		return Method::Call<Vector3(*)(Vector3, Vector3)>("UnityEngine.CoreModule", "UnityEngine", "Vector3", "Scale", 2)(lhs, rhs);
	}
};