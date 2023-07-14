#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <random>
#include "Ship.h"
#include "Missile.h"
#include "Player.h"
#include "Team.h"


int32_t SCREEN_WIDTH = 800;
int32_t SCREEN_HEIGHT = 640;

std::random_device device;
std::default_random_engine rng(device());
std::uniform_real_distribution<float> distribution_field_width(0, (float)SCREEN_WIDTH);
std::uniform_real_distribution<float> distribution_field_height(0, (float)SCREEN_HEIGHT);
std::uniform_real_distribution<float> distribution_angles(0, 2 * PI);
std::uniform_real_distribution<float> distribution_velocities(0, 4);


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

	
	uint32_t UI_scale = 2;
	uint32_t UI_character_size = 8 * UI_scale;

	std::vector<ControlScheme> control_schemes;
	std::vector<ShipPrototype> ship_prototypes;
	
	bool GetKeyState(KeyStateAction& key_state_action)
	{
		olc::Key key = key_state_action.key;
		KeyState key_state_to_act = key_state_action.keyStateToAct;
		if (key_state_to_act == KeyState::PRESSED)
			return GetKey(key).bPressed;
		else if (key_state_to_act == KeyState::HELD)
			return GetKey(key).bHeld;
		else if (key_state_to_act == KeyState::RELEASED)
			return GetKey(key).bReleased;
	}

	void ControlShip(Player& player, float fElapsedTime)
	{
		Ship& ship = *player.controlled_ship;

		ship.StopAccelerating();

		for (KeyStateAction key_state_action : player.control_scheme.keyStateActions)
		{
			Action action = key_state_action.action;
			

			if (GetKeyState(key_state_action))
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
					ship.TryShoot();
			}
			else
			{
				
			}
		}
	}


	bool OnUserCreate() override
	{
		ShipPrototype assault = ShipPrototype(100, 100, 100, 200);
		ShipPrototype scout = ShipPrototype(50, 120, 200, 400);
		ShipPrototype heavy = ShipPrototype(200, 80, 60, 120);

		ship_prototypes.push_back(assault);
		ship_prototypes.push_back(heavy);
		ship_prototypes.push_back(scout);
		for (int i = 0; i < ship_prototypes.size(); i++)
		{
			ShipPrototype& ship_prototype = ship_prototypes[i];
			std::string name;
			Team team;
			if (i == 0)
			{
				name = "Assault";
				team = TEAM_GREEN;
			}
			else if (i == 1)
			{
				name = "Heavy";
				team = TEAM_RED;
			}
			else
			{
				name = "Ship " + std::to_string(i);
				team = TEAM_BLUE;
			}

			olc::vf2d initial_position = { distribution_field_width(rng), distribution_field_height(rng) };
			float angle = distribution_angles(rng);
			olc::vf2d initial_direction = { cosf(angle), sinf(angle) };
			float initial_velocity = distribution_velocities(rng);

			ships.push_back(Ship(ship_prototype, initial_position, initial_direction, name, team, initial_velocity));
		}
		control_schemes.push_back(ControlScheme({
			KeyStateAction(olc::W, KeyState::HELD, Action::MOVE_FORWARD),
			KeyStateAction(olc::S, KeyState::HELD, Action::STOP),
			KeyStateAction(olc::A, KeyState::HELD, Action::TURN_LEFT),
			KeyStateAction(olc::D, KeyState::HELD, Action::TURN_RIGHT),
			KeyStateAction(olc::SPACE, KeyState::PRESSED, Action::SHOOT),
			}));
		control_schemes.push_back(ControlScheme({
			KeyStateAction(olc::NP8, KeyState::HELD, Action::MOVE_FORWARD),
			KeyStateAction(olc::NP5, KeyState::HELD, Action::STOP),
			KeyStateAction(olc::NP4, KeyState::HELD, Action::TURN_LEFT),
			KeyStateAction(olc::NP6, KeyState::HELD, Action::TURN_RIGHT),
			KeyStateAction(olc::RETURN, KeyState::PRESSED, Action::SHOOT),
			}));
		players.push_back(Player(control_schemes[0], &ships[0]));
		players.push_back(Player(control_schemes[1], &ships[1]));


		return true;
	}

	float mod(float a, float b)
	{
		if (a > 0)
			return a - (int)(a / b) * b;
		return a - ((int)(a / b) - 1) * b;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		// Game logic
		
		for (Player& player : players)
		{
			ControlShip(player, fElapsedTime);
		}

		// Draw UI
		for (Ship& ship : ships)
		{
			ship.UpdatePosition(fElapsedTime);
			ship.position.x = mod(ship.position.x, SCREEN_WIDTH);
			ship.position.y = mod(ship.position.y, SCREEN_HEIGHT);

			FillCircle(ToScreenSpace(ship.position), 6, ship.team.color);
			FillCircle(ToScreenSpace(ship.position), 3, olc::BLACK);
			DrawLine(ToScreenSpace(ship.position), ToScreenSpace(ship.position + 100.0f * ship.direction), ship.team.color);
			DrawLine(ToScreenSpace(ship.position), ToScreenSpace(ship.position + ship.velocity), olc::MAGENTA);
			DrawStringCenter(ToScreenSpace(ship.position) - olc::vi2d(0, UI_character_size), ship.name, ship.team.color, UI_scale);
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