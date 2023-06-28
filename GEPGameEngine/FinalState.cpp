#include "FinalState.h"
#include <iostream>
#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"

using namespace std;

// G?i làm enter khi tr?ng thái ?c thêm vào state machine 
void FinalState::Enter()
{
	// Font ch? load t? t?p "game_over.ttf" kích th??c ch? 100 
	gFont = TTF_OpenFont("game_over.ttf", 100);

	cout << "Entering FinalState..." << endl;

	// Kh?i t?o 2 button : play và exit 
	// thêm chúng vào vector m_vButtons 
	// new Button ( "???ng d?n ?nh", ph?n hình ?nh mà nút ???c c?t ra( x, y, w, h ), v? trí và kích th??c c?a nút trên màn ( x, y, w, h )
	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 412,300,200,80 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }));
}


// c?p nh?t các tr?ng thái c?a button ( play hay exit ) 
// N?u play -> chuy?n sang state "GameState
// N?u exit -> chuy?n sang state "MainMenuState"
void FinalState::Update()
{
	// C?p nh?t tr?ng thái c?a nút, ktra con chu?t có ?ang di chuy?n trên 1 nút không 
	// Duy?t qua t?t c? buttons trong vector m_vButton 
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	// Ktra nút play có ???c nh?p k ( g?i hàm Clicked c?a Button )
	if (m_vButtons[btn::play]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new GameState());
	}
	// Ktra nút exit có ???c nh?p không ( g?i hàm Clicked) 
	else if (m_vButtons[btn::exit]->Clicked())
	{
		Game::Instance()->GetFSM()->Clean(); // Xóa m?i tr?ng thái, bao g?m c? GameState ? d??i cùng  
		// V? main menu 
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}

}


// V? hcn màu xanh lên màn, v? các button và hi?n th? ?i?m s? cu?i cùng c?a ng??i ch?i 
void FinalState::Render()
{
	// ??t màu thành xanh ??m 
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 64, 64, 128, 128);

	// V? m?t hcn ??i di?n cho ph?n ch?i game 
	SDL_Rect rect = { 256, 128, 512, 512 };
	// v? lên hcn này 
	SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);

	// g?i hàm Render c?a m?i button trong danh sách các nút trên màn hình 
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	// T?o chu?i k?t qu? cu?i cùng ?? hi?n th? ?i?m trên màu hình 
	string pts = "Your final Score: " + to_string(score);

	// V? chu?i ký t? ?i?m c?a ng ch?i lên màn  
	ScreenState::RenderFont(true, pts.c_str(), 400, 150);

	// Hi?n th? m?i ??i t??ng v?a ???c v? lên màn hình 
	ScreenState::Render();

}


// Gi?i phóng các button ???c t?o ra 
void FinalState::Exit()
{

	cout << "Exiting Pause " << endl;

	// gi?i phóng b? nh? m?i ph?n t? c?a vector 
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}

	// Xóa t?t c? ph?n t? c?a vector 
	m_vButtons.clear();

	// Gi?m kích th??c b? nh? c?a vector xu?ng t?i thi?u 
	m_vButtons.shrink_to_fit();
}

