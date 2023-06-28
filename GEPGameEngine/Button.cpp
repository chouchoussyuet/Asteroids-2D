#include "Button.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"


// Hàm tạo 
/* s : đường dẫn tới tập tin hình ảnh của Button
* src : vị trí, kích thước của hình ảnh trong tập tin
dst : vị trí và kích thước của Button trên màn
*/
Button::Button(const char* s, SDL_Rect src, SDL_Rect dst)
{
	// Tải hình ảnh kiểu SDL_Surface
	m_pSurf = IMG_Load(s);

	// Tạo đối tượng kiểu SDL_Texture ( tạo kết cấu pixel từ bề mặt ) 
	m_pText = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), m_pSurf);

	// Giải phóng về mặt cũ 
	SDL_FreeSurface(m_pSurf);

	// Kiểm tra trạng thái của nút chuột đã được nhấn hay chưa (Khi người dùng kick vào Button ) 
	// biến bool bReleased = true là nút đã được thả ra và trạng thái không được nhấn 
	m_bReleased = true;

	// Gán vị trí và kích thước của hình ảnh trong tập tin 
	m_rSrc = src;
	// gán vị trí, kích thước của Button trên màn hình 
	m_rDst = dst;
}



// Hàm hủy 
Button::~Button()
{
	SDL_DestroyTexture(m_pText);
}


// Hàm update cập nhật trạng thái của nút và chuyển đổi khung nhìn của nút tương ứng với trạng thái 
void Button::Update()
{
	// Lấy tọa độ của chuột trên màn hình 
	int mx = Game::Instance()->GetMouseX();
	int my = Game::Instance()->GetMouseY();

	// Kiểm tra xem tọa độ chuột có nằm trong vùng giới hạn của nút không 
	// so sánh với rDst
	// m_iFrame lưu khung
	if (mx < (m_rDst.x + m_rDst.w) && mx > m_rDst.x && my < (m_rDst.y + m_rDst.h) && my > m_rDst.y)
	{ // Nếu tọa độ chuọt nằm trong vùng giới hạn của nút 

		/* Kiểm tra nút được nhấn hay k
		phương thức GetLeftMouse của lớp Game ?
		* biến m_bReleased đã được thiết lập thành true chưa */
		if (Game::Instance()->GetLeftMouse() && m_bReleased)
		{ // chuột được nhấn + trước đó chưa có hoạt động nhấn nút nào 
			m_iFrame = MOUSE_DOWN; // nút đang được nhấn 
			m_bReleased = false; // ngăn người dùng nhấn nút nhiều lần 
		}
		else if (!Game::Instance()->GetLeftMouse())
		{ // Chuột di chuyển qua nút + không nhấn 
			m_bReleased = true;
			m_iFrame = MOUSE_OVER; // nút đang được rê chuột 
		}
	}
	else // tọa độ chuột không nằm trong giới hạn nút 
		m_iFrame = MOUSE_UP; // nút không được nhấn 
}

// Vẽ h.a lên màn tại vị trí x, y 
void Button::Render()
{
	m_rSrc.x = m_rSrc.w * m_iFrame;
	SDL_RenderCopy(Game::Instance()->GetRenderer(), m_pText, &m_rSrc, &m_rDst);
}