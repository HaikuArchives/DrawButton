/* This code is written for BeOS R5. To use it under R4 please change the lines, 
where the icon is fetched!!! */

#include <Application.h>
#include <Window.h>
#include <View.h>
#include <PictureButton.h>
#include <Roster.h>
#include <NodeInfo.h>
#include <Bitmap.h>

#include "DrawButton.h"

/* ------------ Declarations of the Window class ------------ */

class Window : public BWindow {
	public:
				Window();
		bool	QuitRequested() { be_app->PostMessage(B_QUIT_REQUESTED); return true; };
};

/* --------------- Main program --------------------------- */

int main() {

	BApplication	myApp("application/x-vnd.pecora-testapp");

	new Window();

	myApp.Run();

	return 0;
}

/* ------------- Window Functions --------- */

Window::Window() :
	BWindow( BRect( 40, 40, 123, 123), "Demo App", B_TITLED_WINDOW, B_NOT_ZOOMABLE|B_NOT_RESIZABLE) {

	BRect	ButtonFrame( 20.0, 20.0, 63.0, 63.0);
	
	// Create a temporary view
	BView	tempView( ButtonFrame, "", 0, 0);
	
	// The view must be added to the windows, otherwise BeginPicture()/EndPicture() crashes!
	AddChild( &tempView );
	
	// Get our programs icon
	app_info	myAppInfo;
	be_app->GetAppInfo(&myAppInfo);
	
	BNode 		myNode = BNode(&myAppInfo.ref);
	BNodeInfo	myNodeInfo(&myNode);

	BBitmap		Icon(BRect(0,0,31,31), B_CMAP8 );
	myNodeInfo.GetTrackerIcon( &Icon );

	// Draw the normal button
	tempView.BeginPicture( new BPicture() );
	
	DrawButton(&tempView, ButtonFrame.OffsetToCopy(0,0) , false);

	tempView.SetDrawingMode(B_OP_OVER);
	tempView.DrawBitmapAsync( &Icon, BPoint(6, 6) );

// uncomment the following lines to receive a disabled look:

//	tempView.SetHighColor(232, 232, 232, 108);
//	tempView.SetDrawingMode(B_OP_ALPHA);
//	tempView.FillRoundRect(ButtonFrame.OffsetToCopy(0,0), 1.5, 1.5);

	BPicture	*off = tempView.EndPicture();
	
	// Draw the pressed button
	tempView.BeginPicture( new BPicture() );

	DrawButton(&tempView, ButtonFrame.OffsetToCopy(0,0), true);

	tempView.SetDrawingMode(B_OP_ALPHA);
    tempView.SetHighColor(0, 0, 0, 200);
    tempView.SetBlendingMode(B_CONSTANT_ALPHA, B_ALPHA_OVERLAY);
                
	tempView.DrawBitmap( &Icon, BPoint(6, 6) );

	BPicture	*on = tempView.EndPicture();

	// Create the picture button
	BPictureButton	*myButton = new BPictureButton( ButtonFrame, "", off, on, NULL );

	// ... and add it!
	AddChild( myButton );
	
	// Remove the temporary view
	RemoveChild( &tempView);
	
	// And open the Window
	Show(); 
}