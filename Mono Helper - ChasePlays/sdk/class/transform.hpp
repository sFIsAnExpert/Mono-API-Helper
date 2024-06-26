#pragma once

class Transform : public Object {
public:
	int ChildCount() {
		return Method::Call<int(*)(Transform*)>("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_childCount", 0)(this);
	}

	Vector3 GetPosition() {
		return Method::CallVT<Vector3>("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_position", 0, this);
	}
};
