#pragma once
#include "CommonLib.h"
#include <Node.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <ResourceLoader.hpp>
#include <PackedScene.hpp>

class LevelManager :
    public Node
{
    GODOT_CLASS(LevelManager, Node);

public:
    static void _register_methods();
    void _init();

    void _ready();

    void CompleteLevel(int id);
    void LoadLevel(int id);

private:
    ResourceLoader* resourceLoader;

    String mainMenuPath = "res://Scenes/Menu.tscn";
    String levelPath[1] = { "res://Scenes/World.tscn"};

public:
    Node* currentScene;
};
