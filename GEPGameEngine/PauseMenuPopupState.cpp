#include "PauseMenuPopupState.h"
#include <iostream>
#include "Game.h"
#include "MainMenuState.h"
using namespace std;


void PauseMenuPopupState::Enter()
{
	cout << "Entering Pause..." << endl;
	m_vButtons.push_back(new Button("Img/resume.png", { 0,0,200,80 }, { 412,200,200,80 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }));

}

void PauseMenuPopupState::Update()
{
	// Update button
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close 
	if (m_vButtons[btn::resume]->Clicked())
	{
		Game::Instance()->GetFSM()->PopState();
	}

	else if (m_vButtons[btn::exit]->Clicked())
	{
		Game::Instance()->GetFSM()->Clean(); // xóa hết 
		// trở về mainmenu 
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}

}


void PauseMenuPopupState::Render()
{

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 64, 64, 128, 128);

	// vẽ background
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);

	
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();


	ScreenState::Render();

}


void PauseMenuPopupState::Exit()
{

	cout << "Exiting Pause..." << endl;

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

