#include "pch.h"
#include "NullGamestate.h"
#include "GameMain.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiPictureBox.h"
#include "GraphicsDevice.h"
#include "GuiPanel.h"

static GuiWidget* gRootWidget = nullptr;

class MyHandler: public GuiEventsHandler
{
public:
    void HandleClickEvent(GuiWidget* sender, GuiEvent* eventData) override
    {
        if (mBox)
        {
            mBox->SetVisible(!mBox->IsVisible());
        }
    }
    void HandleMouseEnter(GuiWidget* sender, GuiEvent* eventData) override
    {
        if (mBox)
        {
            mBox->SetSize(Point(100, 100), eGuiAddressingMode_Relative, eGuiAddressingMode_Relative);
        }
    }
    void HandleMouseLeave(GuiWidget* sender, GuiEvent* eventData) override
    {
        if (mBox)
        {
            mBox->SetSize(Point(20, 20), eGuiAddressingMode_Relative, eGuiAddressingMode_Relative);
        }
    }

public:
    GuiPictureBox* mBox = nullptr;
};

static MyHandler ghandler;

void NullGamestate::HandleGamestateEnter()
{
    gRootWidget = new GuiWidget;
    gRootWidget->SetSize(gGraphicsDevice.mScreenResolution);

    {
        GuiPanel* panel = new GuiPanel;
        panel->SetSize(Point(700, 400));
        panel->SetClipChildren(true);
        gRootWidget->AttachChild(panel);

        {
            GuiButton* button = new GuiButton;
            button->SetPosition(Point(50, 50), eGuiAddressingMode_Relative, eGuiAddressingMode_Relative);
            button->SetSize(Point(60, 60), eGuiAddressingMode_Relative, eGuiAddressingMode_Relative);
            button->SetOrigin(Point(50, 50), eGuiAddressingMode_Relative, eGuiAddressingMode_Relative);
            //button->SetClipChildren(true);

            ghandler.Subscribe(button, eGuiEvent_Click);
            ghandler.Subscribe(button, eGuiEvent_MouseEnter);
            ghandler.Subscribe(button, eGuiEvent_MouseLeave);

            button->mDebugColorDisabled = Color32_GrimGray;
            button->mDebugColorHovered = Color32_Orange;

            {
                GuiPictureBox* picture = new GuiPictureBox;
                {
                    Texture2D_Image texture_image;
                    texture_image.LoadFromFile("D:/Temp/fill.png");
                    texture_image.ResizeToPowerOfTwo();

                    Texture2D* texture = new Texture2D("dummy");
                    texture->CreateTexture(texture_image);

                    picture->SetTexture(texture);
                    ghandler.mBox = picture;
                }
                picture->SetSizeMode(eGuiSizeMode_Tile);
                picture->SetSize(Point(256, 190));
                picture->SetPosition(Point(50, 50), eGuiAddressingMode_Relative, eGuiAddressingMode_Relative);
                button->AttachChild(picture);
            }

            panel->AttachChild(button);
        }
    }


    gGuiManager.AttachWidget(gRootWidget);
}

void NullGamestate::HandleGamestateLeave()
{
}

void NullGamestate::HandleUpdateFrame()
{
    gRootWidget->SetSize(gGraphicsDevice.mScreenResolution);
}

void NullGamestate::HandleInputEvent(MouseButtonInputEvent& inputEvent)
{
}

void NullGamestate::HandleInputEvent(MouseMovedInputEvent& inputEvent)
{
}

void NullGamestate::HandleInputEvent(MouseScrollInputEvent& inputEvent)
{
}

void NullGamestate::HandleInputEvent(KeyInputEvent& inputEvent)
{
}

void NullGamestate::HandleInputEvent(KeyCharEvent& inputEvent)
{
}