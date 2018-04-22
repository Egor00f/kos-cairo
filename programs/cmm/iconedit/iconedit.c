/*
 * Icon Editor for KolibriOS
 * Authors: Leency, Nicolas
 * Licence: GPL v2
*/

/*
TODO:
window colors
enhance icon
pipet aside color view
*/

#define MEMSIZE 4096*100

#include "../lib/gui.h"
#include "../lib/random.h"
#include "../lib/mem.h"
#include "../lib/obj/libimg.h"
#include "../lib/patterns/rgb.h"
#include "../lib/patterns/libimg_load_skin.h"

#include "colors_mas.h"

//===================================================//
//                                                   //
//                       DATA                        //
//                                                   //
//===================================================//

#define T_TITLE "Icon Editor 0.46 Alpha"

#define TOOLBAR_H    24+8
#define PANEL_LEFT_W 16+5+5+3+3
#define PALLETE_SIZE 116
#define TB_ICON_PADDING 26

#define PAL_ITEMS_X_COUNT 13
#define COLSIZE 18
#define RIGHT_BAR_W PAL_ITEMS_X_COUNT*COLSIZE

#define TO_CANVAS_X(xval) xval - canvas.x/zoom.value
#define TO_CANVAS_Y(yval) yval - canvas.y/zoom.value

block canvas = { NULL, NULL, NULL, NULL };
block wrapper = { PANEL_LEFT_W, TOOLBAR_H, NULL, NULL };
block right_bar = { NULL, TOOLBAR_H, RIGHT_BAR_W+10, NULL };

block b_color_gradient = {NULL, 30+TOOLBAR_H, RIGHT_BAR_W, 30};
block b_last_colors = {NULL, 70+TOOLBAR_H, RIGHT_BAR_W, COLSIZE*2};
block b_default_palette = {NULL, COLSIZE*2+10+70+TOOLBAR_H, RIGHT_BAR_W, COLSIZE*9};

dword color1 = 0x000000;
dword color2 = 0xFFFfff;
dword tool_color;

enum {
	BTN_NEW = 40,
	BTN_OPEN,
	BTN_SAVE,
	BTN_MOVE_LEFT,
	BTN_MOVE_RIGHT,
	BTN_MOVE_UP,
	BTN_MOVE_DOWN,
	BTN_FLIP_HOR,
	BTN_FLIP_VER,
	BTN_ROTATE_LEFT,
	BTN_ROTATE_RIGHT,
	BTN_PENCIL,
	BTN_PICK,
	BTN_FILL,
	BTN_LINE,
	BTN_RECT,
	BTN_SELECT,
	BTN_ZOOM_IN,
	BTN_ZOOM_OUT,
	BTNS_PALETTE_COLOR_MAS = 100,
	BTNS_LAST_USED_COLORS = 400
};

proc_info Form;

more_less_box zoom = { 11, 1, 40, "Zoom" };

dword default_palette[] = {
0x330000,0x331900,0x333300,0x193300,0x003300,0x003319,0x003333,0x001933,0x000033,0x190033,
0x330033,0x330019,0x000000,0x660000,0x663300,0x666600,0x336600,0x006600,0x006633,0x006666,
0x003366,0x000066,0x330066,0x660066,0x660033,0x202020,0x990000,0x994C00,0x999900,0x4C9900,
0x009900,0x00994C,0x009999,0x004C99,0x000099,0x4C0099,0x990099,0x99004C,0x404040,0xCC0000,
0xCC6600,0xCCCC00,0x66CC00,0x00CC00,0x00CC66,0x00CCCC,0x0066CC,0x0000CC,0x6600CC,0xCC00CC,
0xCC0066,0x606060,0xFF0000,0xFF8000,0xFFFF00,0x80FF00,0x00FF00,0x00FF80,0x00FFFF,0x0080FF,
0x0000FF,0x7F00FF,0xFF00FF,0xFF007F,0x808080,0xFF3333,0xFF9933,0xFFFF33,0x99FF33,0x33FF33,
0x33FF99,0x33FFFF,0x3399FF,0x3333FF,0x9933FF,0xFF33FF,0xFF3399,0xA0A0A0,0xFF6666,0xFFB266,
0xFFFF66,0xB2FF66,0x66FF66,0x66FFB2,0x66FFFF,0x66B2FF,0x6666FF,0xB266FF,0xFF66FF,0xFF66B2,
0xC0C0C0,0xFF9999,0xFFCC99,0xFFFF99,0xCCFF99,0x99FF99,0x99FFCC,0x99FFFF,0x99CCFF,0x9999FF,
0xCC99FF,0xFF99FF,0xFF99CC,0xE0E0E0,0xFFCCCC,0xFFE5CC,0xFFFFCC,0xE5FFCC,0xCCFFCC,0xCCFFE5,
0xCCFFFF,0xCCE5FF,0xCCCCFF,0xE5CCFF,0xFFCCFF,0xFFCCE5,0xFFFFFF	
};
dword last_used_colors[13*2] = {
0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,
0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,
0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF
};

_image image;

#include "actions_history.h"

libimg_image open_image;
_ActionsHistory actionsHistory;

#include "tools.h"

//===================================================//
//                                                   //
//                       CODE                        //
//                                                   //
//===================================================//


void initTools() 
{
	tools[0].id = TOOL_PENCIL;
	tools[0].onMouseEvent = #PencilTool_onMouseEvent;
	tools[0].deactivate = #PencilTool_reset;
	
	tools[1].id = TOOL_PIPETTE;
	tools[1].activate = #PipetteTool_activate;
	tools[1].onMouseEvent = #PipetteTool_onMouseEvent;
	
	tools[2].id = TOOL_FILL;
	tools[2].onMouseEvent = #FillTool_onMouseEvent;
	
	tools[3].id = TOOL_LINE;
	tools[3].activate = #SimpleFigureTool_Reset;
	tools[3].deactivate = #SimpleFigureTool_Reset;
	tools[3].onMouseEvent = #SimpleFigureTool_onMouseEvent;
	tools[3].onCanvasDraw = #SimpleFigureTool_onCanvasDraw;
	
	tools[4].id = TOOL_RECT;
	tools[4].activate = #SimpleFigureTool_Reset;
	tools[4].deactivate = #SimpleFigureTool_Reset;
	tools[4].onMouseEvent = #SimpleFigureTool_onMouseEvent;
	tools[4].onCanvasDraw = #SimpleFigureTool_onCanvasDraw;	

	tools[5].id = TOOL_SELECT;
	tools[5].activate = #SelectTool_activate;
	tools[5].deactivate = #SelectTool_deactivate;
	tools[5].onMouseEvent = #SelectTool_onMouseEvent;
	tools[5].onCanvasDraw = #SelectTool_onCanvasDraw;	
	tools[5].onKeyEvent = #SelectTool_onKeyEvent;	
}

void main()
{
	word btn;

	load_dll(libio,  #libio_init,  1);
	load_dll(libimg, #libimg_init, 1);
	Libimg_LoadImage(#skin, "/sys/icons16.png");
	//system.color.get();
	//Libimg_ReplaceColor(tools_img.image, tools_img.w, tools_img.h, 0xFFF8C0D0, system.color.work);

	if (!param[0]) {
		image.create(32, 32);
	}
	else
	{
		Libimg_LoadImage(#open_image, #param);

		if (open_image.w*open_image.h>MAX_CELL_SIZE*MAX_CELL_SIZE) {
			notify("'Hey, this is just an icon editor,\nselected image is too big to open!' -E");
			ExitProcess();
		}
		else {
			image.create(open_image.w, open_image.h);
			image.set_image(open_image.imgsrc);
		}
	}

	actionsHistory.init();

	initTools();
	setCurrentTool(TOOL_PENCIL);
	
	SetEventMask(EVM_REDRAW+EVM_KEY+EVM_BUTTON+EVM_MOUSE+EVM_MOUSE_FILTER);

	loop() switch(WaitEvent())
	{
		case evMouse:
			mouse.get();
			
			if (mouse.lkm) tool_color = color1;
			if (mouse.pkm) tool_color = color2;
			if (mouse.mkm) break;

			if (currentTool != TOOL_NONE)
				tools[currentTool].onMouseEvent(mouse.x, mouse.y, mouse.lkm, mouse.pkm);

			if (mouse.vert) {
				if (mouse.vert==65535) zoom.inc();
				if (mouse.vert==1) zoom.dec();
				DrawEditArea();
			}

			if (mouse.down) {
				if (b_color_gradient.hovered()) 
				|| (b_last_colors.hovered())
				|| (b_default_palette.hovered()) {
					if (mouse.key&MOUSE_LEFT) EventSetActiveColor(1, GetPixelUnderMouse());
					if (mouse.key&MOUSE_RIGHT) EventSetActiveColor(2, GetPixelUnderMouse());
				}	
			}

			break;

		case evButton:
			btn = GetButtonID();

			switch(btn)
			{
				case BTN_NEW:
					image.create(32, 32);
					DrawCanvas();
					break;
				case BTN_OPEN:
					RunProgram("/sys/lod", sprintf(#param, "*png* %s",#program_path));
					break;
				case BTN_SAVE:
					EventSave();
					break;
				case BTN_MOVE_LEFT:
					image.move(MOVE_LEFT);
					DrawCanvas();
					break;
				case BTN_MOVE_RIGHT:
					image.move(MOVE_RIGHT);
					DrawCanvas();
					break;
				case BTN_MOVE_UP:
					image.move(MOVE_UP);
					DrawCanvas();
					break;
				case BTN_MOVE_DOWN:
					image.move(MOVE_DOWN);
					DrawCanvas();
					break;
				case BTN_FLIP_VER:
					image.move(FLIP_VER);
					DrawCanvas();
					break;
				case BTN_FLIP_HOR:
					image.move(FLIP_HOR);
					DrawCanvas();
					break;
				case BTN_PENCIL:
					setCurrentTool(TOOL_PENCIL);
					break;
				case BTN_PICK:
					setCurrentTool(TOOL_PIPETTE);
					//EventPickActivate();
					break;
				case BTN_FILL:
					setCurrentTool(TOOL_FILL);
					//EventFillActivate();
					break;
				case BTN_LINE:
					setCurrentTool(TOOL_LINE);
					break;
				case BTN_RECT:
					setCurrentTool(TOOL_RECT);
					break;
				case BTN_SELECT:
					setCurrentTool(TOOL_SELECT);
					break;
				case BTN_ZOOM_IN:
					zoom.inc();
					DrawEditArea();
					break;
				case BTN_ZOOM_OUT:
					zoom.dec();
					DrawEditArea();
					break;
				case CLOSE_BTN:
					ExitProcess();
					break;
			}
			break;
	  
		case evKey:
			GetKeys();

			if (currentTool != TOOL_NONE) && (tools[currentTool].onKeyEvent != 0)
				tools[currentTool].onKeyEvent(key_scancode);

			if (key_scancode == SCAN_CODE_ESC) setCurrentTool(TOOL_PENCIL);
			if (key_scancode == SCAN_CODE_KEY_P) setCurrentTool(TOOL_PENCIL);
			if (key_scancode == SCAN_CODE_KEY_I) setCurrentTool(TOOL_PIPETTE);
			if (key_scancode == SCAN_CODE_KEY_F) setCurrentTool(TOOL_FILL);
			if (key_scancode == SCAN_CODE_KEY_L) setCurrentTool(TOOL_LINE);
			if (key_scancode == SCAN_CODE_KEY_R) setCurrentTool(TOOL_RECT);

			if (key_scancode == SCAN_CODE_KEY_Z) && (key_modifier&KEY_LCTRL) actionsHistory.undoLastAction();
			if (key_scancode == SCAN_CODE_KEY_Y) && (key_modifier&KEY_LCTRL) actionsHistory.redoLastAction();

			if (key_scancode == SCAN_CODE_MINUS) {zoom.dec(); DrawEditArea();}
			if (key_scancode == SCAN_CODE_PLUS)  {zoom.inc();  DrawEditArea();}

			break;
		 
		case evReDraw:
			draw_window();
			break;
	}
}

void DrawToolbarButton(dword _id, _x, _icon_n)
{
	DrawWideRectangle(_x, 4, 22, 22, 3, 0xFFFfff);
	DefineHiddenButton(_x, 4, 21, 21, _id);
	img_draw stdcall(skin.image, _x+3, 7, 16, 16, 0, _icon_n*16);
}

void DrawLeftPanelButton(dword _id, _y, _icon_n)
{
	int x = 5;
	DrawWideRectangle(x, _y, 22, 22, 3, 0xFFFfff);
	DefineHiddenButton(x, _y, 21, 21, _id);
	img_draw stdcall(skin.image, x+3, _y+3, 16, 16, 0, _icon_n*16);
}

void DrawStatusBar()
{
	zoom.draw(wrapper.x, wrapper.y + wrapper.h + 6);

	sprintf(#param,"Canvas: %ix%i", image.rows, image.columns);
	WriteText(wrapper.x+wrapper.w-calc(strlen(#param)*8), zoom.y+2, 0x90, system.color.work_text, #param);
}

void draw_window()
{
	incn tx;
	system.color.get();
	DefineAndDrawWindow(115+random(100), 50+random(100), 700, 540, 0x33, system.color.work, T_TITLE, 0);
	GetProcessInfo(#Form, SelfInfo);
	if (Form.status_window>2) return;
	if (Form.width  < 560) { MoveSize(OLD,OLD,560,OLD); return; }
	if (Form.height < 430) { MoveSize(OLD,OLD,OLD,430); return; }

	right_bar.x = Form.cwidth - right_bar.w;
	b_color_gradient.x = b_last_colors.x = b_default_palette.x = right_bar.x;

	tx.n = 10-TB_ICON_PADDING;
	DrawToolbarButton(BTN_NEW,    tx.inc(TB_ICON_PADDING), 2); //not implemented
	DrawToolbarButton(BTN_OPEN,   tx.inc(TB_ICON_PADDING), 0); //not implemented
	DrawToolbarButton(BTN_SAVE,   tx.inc(TB_ICON_PADDING), 5);
	DrawToolbarButton(BTN_MOVE_LEFT,  tx.inc(TB_ICON_PADDING+8), 30);
	DrawToolbarButton(BTN_MOVE_RIGHT, tx.inc(TB_ICON_PADDING),   31);
	DrawToolbarButton(BTN_MOVE_UP,    tx.inc(TB_ICON_PADDING),   32);
	DrawToolbarButton(BTN_MOVE_DOWN,  tx.inc(TB_ICON_PADDING),   33);
	
	DrawToolbarButton(BTN_FLIP_HOR,   tx.inc(TB_ICON_PADDING+8), 34);
	DrawToolbarButton(BTN_FLIP_VER,   tx.inc(TB_ICON_PADDING),   35);
	// DrawToolbarButton(BTN_ROTATE_LEFT,   tx.inc(TB_ICON_PADDING), 36); //not implemented
	// DrawToolbarButton(BTN_ROTATE_RIGHT,  tx.inc(TB_ICON_PADDING), 37); //not implemented

	DrawLeftPanel();
	
	DrawEditArea();

	DrawActiveColor(right_bar.y);
	DrawColorPallets();

	DrawStatusBar();
}

void DrawLeftPanel()
{
	incn ty;
	ty.n = TOOLBAR_H-TB_ICON_PADDING;
	DrawLeftPanelButton(BTN_PENCIL, ty.inc(TB_ICON_PADDING), 38);
	DrawLeftPanelButton(BTN_PICK,   ty.inc(TB_ICON_PADDING), 39);
	DrawLeftPanelButton(BTN_FILL,   ty.inc(TB_ICON_PADDING), 40);
	DrawLeftPanelButton(BTN_LINE,   ty.inc(TB_ICON_PADDING), 41);
	DrawLeftPanelButton(BTN_RECT,   ty.inc(TB_ICON_PADDING), 42);
	DrawLeftPanelButton(BTN_SELECT,   ty.inc(TB_ICON_PADDING), 43);
	DrawRectangle3D(5, currentTool*TB_ICON_PADDING+TOOLBAR_H, 16+3+2, 16+3+2, 0x333333, 0x777777);
}

void DrawEditArea()
{
	dword color1=0xC0C0C0;
	int top_side;
	int left_side;

	wrapper.w = Form.cwidth - right_bar.w - 10 - wrapper.x;
	wrapper.h = Form.cheight - TOOLBAR_H - 35;

	//canvas{
	canvas.w = image.columns * zoom.value;
	canvas.h = image.rows * zoom.value;
	if (canvas.w+2 > wrapper.w) || (canvas.h+2 > wrapper.h) { 
		zoom.value--;
		DrawEditArea();
		return;
	}
	canvas.x = -zoom.value*image.columns+wrapper.w/2 + wrapper.x;
	canvas.y = -zoom.value*image.rows+wrapper.h/2 + wrapper.y;
	DrawCanvas();
	//}

	left_side = canvas.x-wrapper.x-1;
	top_side = canvas.y-wrapper.y-1;

	DrawRectangle(wrapper.x-1, wrapper.y-1, wrapper.w, wrapper.h, system.color.work_graph);

	if (left_side>0)
	{
		DrawBar(wrapper.x, wrapper.y, wrapper.w-1, top_side, color1); //top
		DrawBar(wrapper.x, wrapper.y+wrapper.h-top_side-1, wrapper.w-1, top_side, color1); //bottom
	}
	if (top_side>0)
	{
		//left
		DrawBar(wrapper.x, wrapper.y+top_side, left_side, 
			wrapper.h-top_side-top_side, color1); 
		//right
		DrawBar(wrapper.x+wrapper.w-left_side-1, wrapper.y+top_side, left_side, 
			wrapper.h-top_side-top_side, color1);
	}
	DrawRectangle(canvas.x-1, canvas.y-1, canvas.w+1, canvas.h+1, 0x808080);
}

void DrawActiveColor(dword iny)
{
	static dword outy;
	if (iny != NULL) outy = iny;
	DrawBar(right_bar.x, outy, 20, 20, color1);
	sprintf(#param, "%A", color1);
	EDI = system.color.work;
	WriteText(right_bar.x + 30, outy + 3, 0xD0, system.color.work_text, #param+4);

	DrawBar(right_bar.x+110, outy, 20, 20, color2);
	sprintf(#param, "%A", color2);
	EDI = system.color.work;
	WriteText(right_bar.x+110 + 30, outy + 3, 0xD0, system.color.work_text, #param+4);	
	DrawCurrentColorGradientByLightness();
}

void DrawCurrentColorGradientByLightness()
{
	int i;
	int w = right_bar.w-10/2;
	for (i=0; i<w; i++)
		DrawBar(b_color_gradient.x+i, b_color_gradient.y, 
			1, b_color_gradient.h, MixColors(color1,0xFFFfff,255*i/w));
	for (i=0 ; i<=w; i++)
		DrawBar(b_color_gradient.x+w+w-i, b_color_gradient.y, 
			1, b_color_gradient.h, MixColors(color1,0x000000,255*i/w));
}

void DrawColorPallets()
{
	int r, c, i=0;
	//Last used colors
	for (r = 0; r < 2; r++)
	{
		for (c = 0; c < PAL_ITEMS_X_COUNT; c++, i++)
		{
			DrawBar(c*COLSIZE + b_last_colors.x, r*COLSIZE + b_last_colors.y, 
				COLSIZE, COLSIZE, last_used_colors[i]);
		}
	}
	i=0;
	//Default colors
	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < PAL_ITEMS_X_COUNT; c++, i++)
		{
			DrawBar(c*COLSIZE + b_default_palette.x, r*COLSIZE + b_default_palette.y, 
				COLSIZE, COLSIZE, default_palette[PALLETE_SIZE-i]);
		}
	}
}

void DrawCanvas()
{
	int r, c;
	for (r = 0; r < image.rows; r++)
	{
		for (c = 0; c < image.columns; c++)
		{
			DrawBar(c*zoom.value + canvas.x, r*zoom.value + canvas.y, 
				zoom.value, zoom.value, image.get_pixel(r, c));
		}
	}
	
	if ((currentTool != TOOL_NONE) && (tools[currentTool].onCanvasDraw != 0))
		tools[currentTool].onCanvasDraw();

	DrawPreview();
}

void DrawPreview()
{
	int x = right_bar.x;
	int y = wrapper.y + wrapper.h - image.rows-2;
	DrawRectangle(x, y, image.columns+1, image.rows+1, system.color.work_graph);
	_PutImage(x+1,y+1, image.columns, image.rows, image.get_image());
}

dword GetPixelUnderMouse()
{
	return GetPixelColorFromScreen(mouse.x + Form.left + 5, mouse.y + Form.top + skin_height);
}

//===================================================//
//                                                   //
//                      EVENTS                       //
//                                                   //
//===================================================//

void EventSave()
{
	save_image(image.get_image(), image.columns, image.rows, "/rd/1/saved_image.png");
}

void EventSetActiveColor(int _number, _color)
{
	int i;
	for (i=13*2-1; i>0; i--) {
		last_used_colors[i] = last_used_colors[i-1];
	}
	last_used_colors[0] = _color;

	if (_number == 1) color1 = _color;
	if (_number == 2) color2 = _color;

	DrawActiveColor(NULL);
	DrawColorPallets();
}
