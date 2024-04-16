#include "sdk/sdk.hpp"

void(*PlayerUpdate_o)(Component*);
void PlayerUpdateHk(Component* obj) {
    PlayerUpdate_o(obj);

    Transform* trans = obj->GetTransform();
    Vector3 pos = trans->GetPosition();

    std::cout << "X: " << pos.x << " Y: " << pos.y << " Z: " << pos.z << "\n";
}

DWORD MainThread(LPVOID lpReserved) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);

    Mono::Initialize();

    Method::Resolve("Assembly-CSharp", "", "Player", "Update", 0)->Hook(PlayerUpdateHk, &PlayerUpdate_o);

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

