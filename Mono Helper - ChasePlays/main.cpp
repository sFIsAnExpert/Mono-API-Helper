#include "sdk/sdk.hpp"

float nVal = 99999999.f;

void(*Update_o)(CharacterBody*); //STORES ALL PLAYERS
void UpdateHk(CharacterBody* master) {
    Update_o(master);
    auto list = CharacterBody::GetInstances();
    if (!list) return;
    auto arr = list->GetValues();
    if (!arr) return;
    for (size_t i = 0; i < list->Count(); i++) {
        CharacterBody* body = arr->GetValue(i);
        if (!body) continue;
        if (!body->isPlayer()) continue;
        Vector3 pos = body->GetPosition();
        std::cout << "X: " << pos.x << " Y: " << pos.y << " Z: " << pos.z << "\n";
        body->GetField("levelMaxHealth")->SetValue<float>(body, &nVal);
        body->GetField("levelDamage")->SetValue<float>(body, &nVal);
    }
}

DWORD MainThread(LPVOID lpReserved) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);

    Mono::Initialize();

    Method::Resolve("RoR2", "RoR2", "CharacterBody", "Update", 0)->Hook(UpdateHk, &Update_o);

    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

