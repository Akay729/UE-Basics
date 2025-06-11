# 📦 Toon Tanks – Project Module with Unreal Engine 5 and C++

This module walks through the step-by-step development of a basic tank-based game using **Unreal Engine 5** and **C++**. It covers the full game flow—from initial setup to final polish—providing a structured approach to building a functional gameplay loop with responsive controls, visuals, audio, and UI.

---

## 🧱 Project Structure and Setup

The module begins with the creation of a custom `Pawn` class used for the main tank actor. Components such as a **Capsule Collider**, **Static Meshes** for the body and turret, and other key elements are added and configured.  
Blueprint-derived classes are created to enhance visual flexibility and runtime editing.

A distinction is made between **default values** and **instance values**, and variables are exposed to Blueprints where necessary to allow for design-time customization.

---

## 🎮 Input and Movement

This section covers input binding and movement logic. The player-controlled pawn is possessed at runtime, and input is handled to control forward motion and rotation.  
The turret is set up to rotate toward the mouse cursor using world space calculations, allowing for precise targeting independent of tank movement.

---

## 💥 Firing System

A firing system is implemented using a custom `Projectile` class.  
Projectiles are spawned with directional velocity, and Unreal’s built-in `OnComponentHit` delegate is used to handle collision events and trigger impact logic.

Timers are introduced to manage fire rate and cooldown periods.

---

## ❤️ Health System and Actor Destruction

Each actor capable of receiving damage is equipped with a `HealthComponent`.  
This component handles damage application and death detection. When health reaches zero, the actor is destroyed and relevant logic is triggered through the GameMode.

Actor destruction (both `Tank` and `Tower`) is managed centrally by the `GameMode` class to maintain control over game state and progression.

---

## 🧠 Custom GameMode and PlayerController

A custom `GameMode` class is created to control the overall game logic, including:

- Player start and pawn spawning  
- Countdown to game start  
- Win and loss conditions

A `CustomPlayerController` is used to control input flow and interact with UI widgets during different game phases (pre-start, active play, game over).

---

## 🖥️ UI Integration

A simple **UI system** is introduced using `Widget Blueprints`.  
This includes:

- A **start screen**  
- A **countdown timer**  
- A **game over screen** (victory or defeat)  
- An in-game **HUD** to display relevant information

---

## ✨ Visual and Audio Effects

The visual and audio polish phase includes the addition of:

- **Hit particles**  
- **Smoke trails**  
- **Death explosions**  
- **Sound effects**  
- **Camera shake**

These elements provide feedback and immersion, giving the game a more complete and professional feel.

---

## 🧹 Final Polish and Wrap-Up

The final section focuses on general cleanup and polish. Actor setups are reviewed, input logic is refined, UI elements are finalized, and gameplay events are thoroughly tested.

The project is now in a complete and extendable state, suitable for further development or as a foundation for more complex Unreal Engine projects.
