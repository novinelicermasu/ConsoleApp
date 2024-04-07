
#include "MenuScene.hpp"
#include "Csv_Parser.hpp"

#include <vector>

class Application
{
public:
    Application();
    void Update();

private:
    MenuScene *menuScene;
    MenuScene *adminScene;
    MenuScene *sortScene;
    HANDLE console;
    CSV_Parser *parser;

    void AddAllScenesElements();
    void ShowCinemaList();

    void AddCinema();
    void DeleteCinema();

    void SortById(bool reverse);
    void SortByTitle(bool reverse);

    void CheckPassword();

    std::string password = "admin";

    bool isProtected;
    bool isAccessGranted = false;
};
