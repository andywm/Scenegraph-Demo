#pragma once
#include "window_archtype.h"
#include "d3d_context.h"
#include <SDL2/SDL_syswm.h>

class D3DWindow : public WindowArchtype
{
private:
	std::shared_ptr<Render::d3d11::D3DContext> mContext;
	//D3DContext mContext;
	HWND getWin32Handle() const;

public:
	// HWND * window, ID3D11Device * device);
	D3DWindow(
		const std::string & title,
		const uint w, const uint h,
		const uint flags
		);
	virtual ~D3DWindow() = default;

	std::shared_ptr<Render::d3d11::D3DContext> context() const;
	virtual void resized() override;
};
