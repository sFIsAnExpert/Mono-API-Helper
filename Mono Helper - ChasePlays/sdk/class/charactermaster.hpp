#pragma once

class CharacterBody : public Component {
public:
	Vector3 GetPosition() {
		return Method::CallVT<Vector3>("RoR2", "RoR2", "CharacterBody", "get_footPosition", 0, this);
	}
	bool isPlayer() {
		return Method::Call<bool(*)(CharacterBody*)>("RoR2", "RoR2", "CharacterBody", "get_isPlayerControlled", 0)(this);
	}
	static List<CharacterBody*>* GetInstances() {
		return Class::Resolve("RoR2", "RoR2", "CharacterBody")->GetField("instancesList")->GetStaticValue<List<CharacterBody*>*>();
	}
};

class CharacterMaster : public Component {
public:
	static List<CharacterMaster*>* Instances() {
		return Class::Resolve("RoR2", "RoR2", "CharacterMaster")->GetField("instancesList")->GetStaticValue<List<CharacterMaster*>*>();
	}
};

class PlayerCharacterMasterController : public Component {
public:
	CharacterMaster* GetCharacterMaster() {
		return Method::Call<CharacterMaster * (*)(PlayerCharacterMasterController*)>("RoR2", "RoR2", "PlayerCharacterMasterController", "get_master", 0)(this);
	}
};