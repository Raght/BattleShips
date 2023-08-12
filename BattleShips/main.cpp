#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <random>
#include "Bar.h"
#include "Ship.h"
#include "Missile.h"
#include "Player.h"
#include "Team.h"
#include "GameSettings.h"
#include "GlobalsMechanics.h"
#include "GlobalsContent.h"



std::uniform_real_distribution<float> distribution_field_width(0, (float)SCREEN_WIDTH);
std::uniform_real_distribution<float> distribution_field_height(0, (float)SCREEN_HEIGHT);
std::uniform_real_distribution<float> distribution_angles(0, 2 * PI);
std::uniform_real_distribution<float> distribution_velocities(0, 40);


class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "BattleShips";
	}

	olc::vi2d ToScreenSpace(olc::vf2d world_position)
	{
		return { (int32_t)round(world_position.x), (int32_t)round(ScreenHeight() - world_position.y) };
	}
	
	olc::vf2d ToWorldSpace(olc::vi2d screen_position)
	{
		return { (float)screen_position.x, (float)(ScreenHeight() - screen_position.y) };
	}

	std::vector<Ship> ships;
	std::vector<Missile> missiles;
	std::vector<Player> players;
	
	int32_t UI_scale = 2;
	int32_t UI_character_size = 8 * UI_scale;
	olc::vi2d UI_bar_size = { 80, 6 };

	void DrawBar(Bar& bar, const olc::Pixel& color_full, const olc::Pixel& color_empty)
	{
		olc::vi2d position_full = bar.position - bar.size / 2;
		double part_full = ((double)bar.value - (double)bar.minValue) / ((double)bar.maxValue - (double)bar.minValue);
		part_full = max(0, part_full);
		olc::vi2d size_full = { (int32_t)round(bar.size.x * part_full), bar.size.y };
		olc::vi2d size_empty = { bar.size.x - size_full.x, bar.size.y };
		olc::vi2d position_empty = { position_full.x + size_full.x, position_full.y };
		
		FillRect(position_full, size_full, color_full);
		FillRect(position_empty, size_empty, color_empty);
	}

	void DrawHealthBar(Bar& bar)
	{
		DrawBar(bar, olc::GREEN, olc::RED);
	}
	
	void DrawAmmoBar(Bar& bar)
	{
		DrawBar(bar, olc::WHITE, olc::DARK_GREY);
	}

	
	
	bool AllKeyStatesPositive(KeyStatesForAction& key_state_action)
	{
		bool all_states_positive = true;
		for (KeyStatePair& key_state_pair : key_state_action.keyStatesToAct)
		{
			olc::Key key = key_state_pair.key;
			KeyState key_state_to_act = key_state_pair.state;
			bool state = false;
			if (key_state_to_act == KeyState::PRESSED)
				state = GetKey(key).bPressed;
			else if (key_state_to_act == KeyState::HELD)
				state = GetKey(key).bHeld;
			else if (key_state_to_act == KeyState::RELEASED)
				state = GetKey(key).bReleased;

			all_states_positive = all_states_positive && state;
		}
		
		return all_states_positive;
	}

	void AddMissiles(std::vector<Missile>& missiles_to_add)
	{
		for (Missile& missile : missiles_to_add)
			missiles.push_back(missile);
	}

	void ControlShip(Player& player, float fElapsedTime)
	{
		Ship& ship = *player.controlled_ship;

		ship.StopAccelerating();

		for (KeyStatesForAction& key_state_action : player.control_scheme.keyStateActions)
		{
			Action action = key_state_action.action;
			
			if (AllKeyStatesPositive(key_state_action))
			{
				if (action == Action::TURN_LEFT)
					ship.TurnLeft(player.control_scheme.turningSpeedDegreesPerSecond * fElapsedTime);
				else if (action == Action::TURN_RIGHT)
					ship.TurnRight(player.control_scheme.turningSpeedDegreesPerSecond * fElapsedTime);
				else if (action == Action::MOVE_FORWARD)
					ship.AccelerateForward();
				else if (action == Action::STOP)
					ship.Brake();
				else if (action == Action::SHOOT)
					ship.TryShoot(missiles);
			}
			else
			{
				
			}
		}
	}

	void DrawGameObject(GameObject& game_object)
	{
		for (int i = 0; i <= game_object.childrenGameObjects.size(); i++)
		{
			GameObject* p_game_object_to_draw = &game_object;
			if (i != game_object.childrenGameObjects.size())
				p_game_object_to_draw = &game_object.childrenGameObjects[i];

			GameObject& game_object_to_draw = *p_game_object_to_draw;

			for (const Shape& polygon : game_object_to_draw.mesh.polygons)
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
		}
	}

	
	bool OnUserCreate() override
	{
		std::uniform_int_distribution<int> available_hulls_distribution(0, available_hulls.size() - 1);
		std::uniform_int_distribution<int> available_weapons_distribution(0, available_weapons.size() - 1);

		for (int i = 0; i < available_hulls.size(); i++)
		{
			Hull& hull_prototype = available_hulls[available_hulls_distribution(rng)];
			Weapon& weapon_prototype = available_weapons[available_weapons_distribution(rng)];
			//weapon_prototype = assault_cannon;
			//weapon_prototype = smg_cannon;
			//weapon_prototype = laser_cannon;
			std::string name;
			Team team;
			if (i == 0)
			{
				name = "Player 1";
				team = TEAM_GREEN;
			}
			else if (i == 1)
			{
				name = "Player 2";
				team = TEAM_RED;
			}
			else
			{
				name = "Ship " + std::to_string(i);
				team = TEAM_BLUE;
			}

			olc::vf2d initial_position = { distribution_field_width(rng), distribution_field_height(rng) };
			float angle = distribution_angles(rng);
			//float angle = 0;
			olc::vf2d initial_direction = { cosf(angle), sinf(angle) };
			float initial_velocity = distribution_velocities(rng);

			ships.push_back(Ship(hull_prototype, weapon_prototype, initial_position, initial_direction, name, team, initial_velocity));
			ships[i].sizeBoundingBox = { UI_character_size, UI_character_size };
		}
		players.push_back(Player(control_scheme_player_first, &ships[0]));
		players.push_back(Player(control_scheme_player_second, &ships[1]));


		return true;
	}

	

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		// Game logic

		for (Player& player : players)
		{
			ControlShip(player, fElapsedTime);
		}


		for (Ship& ship : ships)
		{
			ship.UpdatePosition(fElapsedTime);
			olc::vf2d position_mod = { Mod(ship.position.x, SCREEN_WIDTH), Mod(ship.position.y, SCREEN_HEIGHT) };
			ship.SetPosition(position_mod);

			//DrawCircle(ToScreenSpace(ship.weapon.mesh.missile_origins[0].position), 10);
		}


		std::vector<std::vector<Missile>::iterator> missiles_to_remove;
		for (int i = 0; i < missiles.size(); i++)
		{
			Missile& missile = missiles[i];
			missile.lifetime += fElapsedTime;
			if (missile.LifetimeExceeded())
				missiles_to_remove.push_back(missiles.begin() + i);
		}
		for (auto iterator : missiles_to_remove)
		{
			missiles.erase(iterator);
		}

		for (Missile& missile : missiles)
		{
			missile.UpdatePosition(fElapsedTime);
		}


		for (Ship& ship : ships)
		{
			DrawGameObject(ship.hull);
			DrawGameObject(ship.weapon);
		}

		for (Missile& missile : missiles)
		{
			DrawGameObject(missile);
		}

		//std::cout << missiles.size() << ' ' << '\n';

		for (Ship& ship : ships)
		{
			//FillCircle(ToScreenSpace(ship.position), 6, ship.team.color);
			//FillCircle(ToScreenSpace(ship.position), 3, olc::BLACK);
			//DrawLine(ToScreenSpace(ship.position), ToScreenSpace(ship.position + 100.0f * ship.direction), ship.team.color);
			//DrawLine(ToScreenSpace(ship.position), ToScreenSpace(ship.position + ship.velocity), olc::MAGENTA);

			float max_size = max(ship.sizeBoundingBox.x, ship.sizeBoundingBox.y);

			DrawStringCenter(ToScreenSpace(ship.position - olc::vf2d(0, max_size) - olc::vf2d(0, UI_character_size / 2)), ship.name, ship.team.color, UI_scale);

			olc::vi2d health_bar_position = ToScreenSpace(ship.position + olc::vf2d(0, max_size) + olc::vf2d(0, UI_bar_size.y));
			Bar health_bar = Bar(health_bar_position, UI_bar_size, ship.hull.health, ship.hull.maxHealth);
			DrawHealthBar(health_bar);

			olc::vi2d ammo_bar_position = ToScreenSpace(ship.position + olc::vf2d(0, max_size) + 3 * olc::vf2d(0, UI_bar_size.y));
			Bar ammo_bar = Bar(ammo_bar_position, UI_bar_size, ship.weapon.ammo, ship.weapon.maxAmmo);
			DrawAmmoBar(ammo_bar);
		}

		return true;
	}
};

int main()
{
	olc::GraphicsMode graphics_mode = { SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1 };

	Game game;
	if (game.Construct(graphics_mode))
		game.Start();
	else
		return 1;
}