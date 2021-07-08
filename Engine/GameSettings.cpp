#include "GameSettings.h"

GameSettings::GameSettings()
{
    std::ifstream in("Teksti//GameSettings.txt");
    if (in.is_open())
    {
        in >> VerticalSpeed;
    }
    else
    {
        VerticalSpeed = deffault;
    }
    
}

void GameSettings::Save()
{
    std::ofstream out("Teksti//GameSettings.txt");
    if (out.is_open())
    {
        out << VerticalSpeed;
    }
    else
    {
        VerticalSpeed = deffault;
    }
}

void GameSettings::Draw(Graphics& gfx) const
{
    Setting.DrawTexts("Vertical Speed: ", Vei2(100, 100), gfx, Colors::White);
    Setting.DrawTexts(std::to_string(VerticalSpeed), Vei2(400, 100), gfx, Colors::White);
}

float GameSettings::TranslateSpeed()
{
    float speed;
    if (VerticalSpeed == 6)
    {
        speed = 0.05f;
    }
    else if (VerticalSpeed == 5)
    {
        speed = 0.06f;
    }
    else if (VerticalSpeed == 4)
    {
        speed = 0.07f;
    }
    else if (VerticalSpeed == 3)
    {
        speed = 0.08f;
    }
    else if (VerticalSpeed == 2)
    {
        speed = 0.09f;
    }
    else if (VerticalSpeed == 1)
    {
        speed = 0.1f;
    }
    return speed;
}

void GameSettings::ProccesKeys(const Keyboard::Event e)
{
    if (e.IsPress() && e.GetCode() == VK_UP && VerticalSpeed < 6)
    {
        VerticalSpeed += 1;
    }
    else if (e.IsPress() && e.GetCode() == VK_DOWN && VerticalSpeed > 1)
    {
        VerticalSpeed -= 1;
    }
}

int GameSettings::GetVerticalSpeed() const
{
    return VerticalSpeed;
}
