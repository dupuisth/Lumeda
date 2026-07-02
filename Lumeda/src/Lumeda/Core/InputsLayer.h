// #pragma once

// #include <Lumeda/Core/Base.h>
// #include <Lumeda/Core/Layer.h>

// namespace Lumeda
// {
// class InputsLayer : public Layer
// {
//   public:
//     void Initialize() override = 0;
//     void Terminate() override = 0;

//     void Update() override;

//     virtual bool IsKeyPressed(LumedaKeys key) = 0;
//     virtual bool IsKeyDown(LumedaKeys key) = 0;
//     virtual bool IsKeyUp(LumedaKeys key) = 0;

//     virtual bool IsMouseButtonPressed(LumedaMouseButtons button) = 0;
//     virtual bool IsMouseButtonDown(LumedaMouseButtons button) = 0;
//     virtual bool IsMouseButtonUp(LumedaMouseButtons button) = 0;

//     static InputsLayer* Create();
// };
// } // namespace Lumeda