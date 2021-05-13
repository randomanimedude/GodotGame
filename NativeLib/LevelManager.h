#pragma once
#include "CommonLib.h"
#include "DataLoader.h"
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

    void CompleteLevel(int completed, int opened);
    void LoadLevel(int id);

private:
    ResourceLoader* resourceLoader;

    String mainMenuPath = "res://Scenes/Menu.tscn";
    String levelPath[11] = { "res://Scenes/LVL1.tscn","res://Scenes/LVL2.tscn","res://Scenes/LVL3.tscn","res://Scenes/LVL4.tscn", "res://Scenes/LVL5.tscn","res://Scenes/LVL6.tscn","res://Scenes/LVL7.tscn","res://Scenes/LVL8a.tscn", "res://Scenes/LVL8b.tscn", "res://Scenes/LVL9.tscn" , "res://Scenes/LVL10.tscn" };

public:
    Node* currentScene;
};

