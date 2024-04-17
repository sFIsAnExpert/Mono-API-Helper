#pragma once

template <class T>
class List : public Object {
public:
	int Count() {
		return this->GetField("_size")->GetValue<int>(this);
	}

	Array<T>* GetValues() {
		return this->GetField("_items")->GetValue<Array<T>*>(this);
	}
};