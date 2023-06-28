#include "FinalState.h"
#include <iostream>
#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"

using namespace std;

// G?i l�m enter khi tr?ng th�i ?c th�m v�o state machine 
void FinalState::Enter()
{
	// Font ch? load t? t?p "game_over.ttf" k�ch th??c ch? 100 
	gFont = TTF_OpenFont("game_over.ttf", 100);

	cout << "Entering FinalState..." << endl;

	// Kh?i t?o 2 button : play v� exit 
	// th�m ch�ng v�o vector m_vButtons 
	// new Button ( "???ng d?n ?nh", ph?n h�nh ?nh m� n�t ???c c?t ra( x, y, w, h ), v? tr� v� k�ch th??c c?a n�t tr�n m�n ( x, y, w, h )
	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 412,300,200,80 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }));
}


// c?p nh?t c�c tr?ng th�i c?a button ( play hay exit ) 
// N?u play -> chuy?n sang state "GameState
// N?u exit -> chuy?n sang state "MainMenuState"
void FinalState::Update()
{
	// C?p nh?t tr?ng th�i c?a n�t, ktra con chu?t c� ?ang di chuy?n tr�n 1 n�t kh�ng 
	// Duy?t qua t?t c? buttons trong vector m_vButton 
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	// Ktra n�t play c� ???c nh?p k ( g?i h�m Clicked c?a Button )
	if (m_vButtons[btn::play]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new GameState());
	}
	// Ktra n�t exit c� ???c nh?p kh�ng ( g?i h�m Clicked) 
	else if (m_vButtons[btn::exit]->Clicked())
	{
		Game::Instance()->GetFSM()->Clean(); // X�a m?i tr?ng th�i, bao g?m c? GameState ? d??i c�ng  
		// V? main menu 
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}

}


// V? hcn m�u xanh l�n m�n, v? c�c button v� hi?n th? ?i?m s? cu?i c�ng c?a ng??i ch?i 
void FinalState::Render()
{
	// ??t m�u th�nh xanh ??m 
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 64, 64, 128, 128);

	// V? m?t hcn ??i di?n cho ph?n ch?i game 
	SDL_Rect rect = { 256, 128, 512, 512 };
	// v? l�n hcn n�y 
	SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);

	// g?i h�m Render c?a m?i button trong danh s�ch c�c n�t tr�n m�n h�nh 
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	// T?o chu?i k?t qu? cu?i c�ng ?? hi?n th? ?i?m tr�n m�u h�nh 
	string pts = "Your final Score: " + to_string(score);

	// V? chu?i k� t? ?i?m c?a ng ch?i l�n m�n  
	ScreenState::RenderFont(true, pts.c_str(), 400, 150);

	// Hi?n th? m?i ??i t??ng v?a ???c v? l�n m�n h�nh 
	ScreenState::Render();

}


// Gi?i ph�ng c�c button ???c t?o ra 
void FinalState::Exit()
{

	cout << "Exiting Pause " << endl;

	// gi?i ph�ng b? nh? m?i ph?n t? c?a vector 
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}

	// X�a t?t c? ph?n t? c?a vector 
	m_vButtons.clear();

	// Gi?m k�ch th??c b? nh? c?a vector xu?ng t?i thi?u 
	m_vButtons.shrink_to_fit();
}

