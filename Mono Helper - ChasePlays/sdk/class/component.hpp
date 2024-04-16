#pragma once

class Component : public Object {
public:
	Transform* GetTransform() {
		return Method::Call<Transform * (*)(Component*)>("UnityEngine.CoreModule", "UnityEngine", "Component", "get_transform", 0)(this);
	}
};
