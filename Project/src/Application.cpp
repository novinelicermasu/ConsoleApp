#include "../include/Application.hpp"

using namespace std;

enum Colors
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

void PrintNameOfProgram()
{
    std::cout << R"(
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
� db   dD db    db db   db  .d88b.  d888888b d88888b  .d8b.  d888888b d8888b.	� 
� 88 ,8P' 88    88 88   88 .8P  Y8. `~~88~~' 88'     d8' `8b `~~88~~' 88  `8D	� 
� 88,8P   88    88 88ooo88 88    88    88    88ooooo 88ooo88    88    88oodD'	� 
� 88`8b   88    88 88~~~88 88    88    88    88~~~~~ 88~~~88    88    88~~~	� 
� 88 `88. 88b  d88 88   88 `8b  d8'    88    88.     88   88    88    88	� 
� YP   YD ~Y8888P' YP   YP  `Y88P'     YP    Y88888P YP   YP    YP    88	� 
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�)"
              << '\n';
}

Application::Application()
{

    console = GetStdHandle(
        STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(console, &info);

    CONSOLE_SCREEN_BUFFER_INFOEX cbi;
    cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(console, &cbi);
    cbi.wAttributes = Colors::WHITE * 16 + Colors::LIGHTGREEN;
    SetConsoleScreenBufferInfoEx(console, &cbi);

    COORD new_size =
        {
            short(info.srWindow.Right - info.srWindow.Left + 1),
            short(info.srWindow.Bottom - info.srWindow.Top + 1)};
    SetConsoleScreenBufferSize(console, new_size);

    SetConsoleCP(866);
    SetConsoleOutputCP(866);

    parser = new CSV_Parser("assets/cinema.csv");

    menuScene = new MenuScene("MainScene", []()
                              { PrintNameOfProgram(); });
    adminScene = new MenuScene("AdminScene", []()
                               { PrintNameOfProgram(); });
    sortScene = new MenuScene("SortScene", [this]()
                              { this->ShowCinemaList(); });

    SceneManager::LoadScene("MainScene", menuScene);
    SceneManager::LoadScene("AdminScene", adminScene);
    SceneManager::LoadScene("SortScene", sortScene);
}

void Application::ShowCinemaList()
{
    
    parser->ReadFromFile();
    
}
void Application::AddCinema()
{
    parser->AddCinema();

    Sleep(500);
    std::cout << "��Μ�皀 Enter, 艪�° �牀ぎ�Θ碎!" << std::endl;
    getchar();
}

void Application::SortById(bool reverse)
{
    parser->SortById(reverse);
    parser->SaveToFile();
}
void Application::SortByTitle(bool reverse)
{
    parser->SortByTitle(reverse);
    parser->SaveToFile();
}

void Application::DeleteCinema()
{
    parser->DeleteCinema();
    std::cout << "��Μ�皀 Enter, 艪�° �牀ぎ�Θ碎!" << std::endl;
    getchar();
}

void Application::CheckPassword()
{
    system("cls");
    std::string pass;
    std::cout << "�▲え皀 ��牀�� か� 皰��, 艪�° ���竍�碎 ぎ痰祚 �が┃�痰��皰��: ";
    cin >> pass;
    if (pass != password)
    {
        cout << "� ぎ痰祚� �皖�����! �▲え皀 ��牀��!" << endl;
        Sleep(300);
    }
    isAccessGranted = (pass == password);
}
void Application::AddAllScenesElements()
{
    menuScene->AddScene(
        new MenuElem("�が┃�痰��罔����� �キ�", [this]()
                     { 
                        if(!isAccessGranted) this->CheckPassword();
                        if(isAccessGranted) SceneManager::ChangeScene("AdminScene"); }));
    menuScene->AddScene(
        new MenuElem("������碎 甎�甌� 筥�讙��", [this]()
                     { SceneManager::ChangeScene("SortScene"); }));
    menuScene->AddScene(
        new MenuElem("�諷�� ├ �牀������", []()
                     { std::cout << "Please stand by.... " << std::endl;
                         exit(EXIT_SUCCESS); }));

    sortScene->AddScene(
        new MenuElem("�� id", [this]()
                     { this->SortById(false); }));
    sortScene->AddScene(
        new MenuElem("�� ��Б���� 筥�讙�", [this]()
                     { this->SortByTitle(false); }));
    sortScene->AddScene(
        new MenuElem("�� id ┃▲珥�牀�����", [this]()
                     { this->SortById(true); }));
    sortScene->AddScene(
        new MenuElem("�� ��Б���� 筥�讙� ┃▲珥�牀�����", [this]()
                     { this->SortByTitle(true); }));
    sortScene->AddScene(
        new MenuElem("�諷�� ├ �牀������", []()
                     { std::cout << "Please stand by.... " << std::endl;
                         exit(EXIT_SUCCESS); }));

    adminScene->AddScene(
        new MenuElem("����※碎 筥�讙 � �牀���", [this]()
                     { this->AddCinema(); }));
    adminScene->AddScene(
        new MenuElem("�����碎 筥�讙 ├ �牀����", [this]()
                     { this->DeleteCinema(); }));

    adminScene->AddScene(
        new MenuElem("�諷�� ├ �牀������", []()
                     { std::cout << "Please stand by.... " << std::endl;
                         exit(EXIT_SUCCESS); }));
}
void Application::Update()
{
    AddAllScenesElements();
    SceneManager::ChangeScene("MainScene");
}
