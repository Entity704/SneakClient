#include <engine/shared/config.h>

#include <game/client/components/menus.h>
#include <game/localization.h>

void CMenus::RenderSettingsSneaking(CUIRect MainView)
{
    char aBuf[128 + IO_MAX_PATH_LENGTH];
    CUIRect Button, Left, Right, Label;

    CUIRect Control;
    MainView.HSplitTop(110.0f, &Control, &MainView);
    Control.HSplitTop(30.0f, &Label, &Control);
    Ui()->DoLabel(&Label, Localize("Control"), 20.0f, TEXTALIGN_ML);
    Label.VSplitMid(nullptr, &Label, 20.0f);
    Ui()->DoLabel(&Label, Localize("Sneaking"), 20.0f, TEXTALIGN_ML);

    Control.HSplitTop(5.0f, nullptr, &Control);
    Control.VSplitMid(&Left, &Right, 20.0f);

    Left.HSplitTop(20.0f, &Button, &Left);
    if(DoButton_CheckBox(&g_Config.m_ScSneaking, Localize("Enable sneaking"), g_Config.m_ScSneaking, &Button))
    {
        g_Config.m_ScSneaking ^= 1;
    }
    Ui()->DoToolTip(&g_Config.m_ScSneaking, &Button, Localize("Main switch"));

    CUIRect SettingsButton;
    Left.HSplitBottom(20.0f, &Left, &SettingsButton);
    Left.HSplitBottom(5.0f, &Left, nullptr);
    static CButtonContainer s_SettingsButtonId;
    if(DoButton_Menu(&s_SettingsButtonId, Localize("SneakClient's settings file"), 0, &SettingsButton))
    {
        Storage()->GetCompletePath(IStorage::TYPE_SAVE, SC_CONFIG_FILE, aBuf, sizeof(aBuf));
        if(Storage()->FileExists(SC_CONFIG_FILE, IStorage::TYPE_SAVE))
            Client()->ViewFile(aBuf);
        else
            PopupMessage(Localize("Settings file doesn't exists"), Localize("Maybe all the settings are at their default values"), Localize("Understood"));
    }
    Ui()->DoToolTip(&s_SettingsButtonId, &SettingsButton, Localize("Open SneakClient's settings file"));

    Right.HSplitTop(20.0f, &Button, &Right);
    if(DoButton_CheckBox(&g_Config.m_ScHideTypingStatus, Localize("Hide typing status"), g_Config.m_ScHideTypingStatus, &Button))
    {
        g_Config.m_ScHideTypingStatus ^= 1;
    }
    Ui()->DoToolTip(&g_Config.m_ScHideTypingStatus, &Button, Localize("Don't send your own typing status (no \"...\" bubble)"));
}
