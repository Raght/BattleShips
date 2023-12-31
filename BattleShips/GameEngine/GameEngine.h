#pragma once
#include "olcPixelGameEngine.h"
#include "GameObject.h"
#include "GameEngineGlobals.h"
#include "BaseScriptComponent.h"
#include "Collision.h"
#include "Color.h"
#include "Draw.h"
#include "Math.h"
#include "Mesh.h"


struct GraphicsMode
{
	int32_t resolution_width = 320;
	int32_t resolution_height = 240;
	int32_t pixel_width = 1;
	int32_t pixel_height = 1;
	bool full_screen = false;
	bool vsync = false;
};

class GameEngine : public olc::PixelGameEngine
{
public:
	GameEngine()
	{
		sAppName = "GameEngine";
	}

	olc::vi2d ToScreenSpace(olc::vf2d world_position)
	{
		return { (int32_t)round(world_position.x), (int32_t)round(ScreenHeight() - world_position.y) };
	}

	olc::vf2d ToWorldSpace(olc::vi2d screen_position)
	{
		return { (float)screen_position.x, (float)(ScreenHeight() - screen_position.y) };
	}

	uint64_t frameCounter = 0;

	const uint32_t GAME_OBJECTS_MAX_SIZE = 65536;
	std::vector<GameObject> gameObjects;

	uint32_t UIScale() { return m_UI_scale; }
	uint32_t UICharacterSize() { return m_UI_character_size; }
	void SetUIScale(uint32_t new_ui_scale) { m_UI_scale = new_ui_scale; m_UI_character_size = 8 * m_UI_scale; }


	void DrawShapeOutline(const Shape& polygon)
	{
		if (polygon.points.size() == 0)
		{
			return;
		}
		else if (polygon.points.size() == 1)
		{
			FillCircle(ToScreenSpace(polygon.points[0]), 1, polygon.color);
			return;
		}

		for (int i = 0; i < polygon.points.size() - 1; i++)
		{
			olc::vf2d position1 = polygon.points[i];
			olc::vf2d position2 = polygon.points[i + 1];
			DrawLine(ToScreenSpace(position1), ToScreenSpace(position2), polygon.color);
		}
		olc::vf2d position1 = polygon.points[polygon.points.size() - 1];
		olc::vf2d position2 = polygon.points[0];
		DrawLine(ToScreenSpace(position1), ToScreenSpace(position2), polygon.color);
	}

	void DrawConvexShapeFill(const Shape& polygon)
	{
		for (int i = 1; i < polygon.points.size() - 1; i++)
		{
			FillTriangle(ToScreenSpace(polygon.points[0]), ToScreenSpace(polygon.points[i]), ToScreenSpace(polygon.points[i + 1]), polygon.color);
		}
	}

	// For now uses DrawShapeOutline(const Shape&)
	void DrawNonConvexShapeFill(const Shape& polygon)
	{
		DrawShapeOutline(polygon);
	}

	void DrawShape(const Shape& polygon)
	{
		if (polygon.drawingMode == DrawingMode::OUTLINE)
		{
			DrawShapeOutline(polygon);
		}
		else if (polygon.drawingMode == DrawingMode::FILL)
		{
			if (polygon.isConvex)
				DrawConvexShapeFill(polygon);
			else
				DrawNonConvexShapeFill(polygon);
		}
	}

	void DrawMesh(const Mesh& mesh)
	{
		for (const Shape& polygon : mesh.polygons)
		{
			DrawShape(polygon);
		}
	}

	void DrawGameObject(GameObject& game_object)
	{
		for (int i = 0; i <= game_object.childrenGameObjects.size(); i++)
		{
			GameObject* p_game_object_to_draw = &game_object;
			if (i != game_object.childrenGameObjects.size())
				p_game_object_to_draw = game_object.childrenGameObjects[i];


			DrawMesh(p_game_object_to_draw->mesh);
		}
	}


	GameObject* AddGameObject(const GameObject& game_object)
	{
		if (gameObjects.size() >= GAME_OBJECTS_MAX_SIZE)
		{
			std::cout << "WARNING: Maximum game objects limit has been exceeded. The game object will not be added." << '\n';
		}
		else
		{
			gameObjects.push_back(game_object);
		}

		return &gameObjects[gameObjects.size() - 1];
	}
	

	bool OnUserCreate() override
	{
		gameObjects.reserve(GAME_OBJECTS_MAX_SIZE);

		for (GameObject& game_object : gameObjects)
		{
			game_object.script->OnStart();
		}

		OnGameLoopCreate();

		frameCounter++;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (GameObject& game_object : gameObjects)
		{
			game_object.lifetime += fElapsedTime;
		}
			

		{
			int game_objects_removed = 0;
			int i = 0;
			while (i < gameObjects.size() - game_objects_removed)
			{
				if (gameObjects[i].LifetimeExceeded())
					gameObjects.erase(gameObjects.begin() + i);
				else
					i++;
			}
		}

		for (GameObject& game_object : gameObjects)
		{
			if (game_object.script != nullptr)
			{
				game_object.script->CoreUpdate(fElapsedTime);
				game_object.script->OnUpdate(fElapsedTime);
			}
			
			if (game_object.rigidbody != nullptr)
			{
				game_object.rigidbody->CoreUpdate(fElapsedTime);
				game_object.rigidbody->OnUpdate(fElapsedTime);
			}

			DrawGameObject(game_object);
		}

		OnGameLoopUpdate(fElapsedTime);

		frameCounter++;

		return true;
	}


public:
	virtual bool OnGameLoopCreate() = 0;
	virtual bool OnGameLoopUpdate(float fElapsedTime) = 0;


private:
	uint32_t m_UI_scale = 2;
	uint32_t m_UI_character_size = 8 * m_UI_scale;
};


inline GameEngine* p_game_engine = nullptr;