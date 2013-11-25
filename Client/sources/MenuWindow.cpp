#include	<sstream>
#include	<algorithm>
#include	<typeinfo>
#include	"MenuWindow.hh"
#include	"Image.hh"
#include	"TextBlock.hh"
#include	"AWidget.hh"
#include	"CheckBox.hh"
#include	"Text.hh"
#include	"Texture.hh"
#include	"TextArea.hh"
#include	"Button.hh"
#include	"LineServer.hh"
#include	"Sound.hh"
#include	"Font.hh"
#include	"Interface.hh"
#include	"TextureManager.hh"
#include	"FontManager.hh"
#include	"MediaAudioManager.hh"
#include	"InfosUser.hh"
#include	"NetworkManager.hh"
#include	"ChatSendRequest.h"
#include	"ChatRecvRequest.h"
#include	"AuthRequest.hh"
#include	"PartyRequest.hh"
#include	"MD5.hh"
#include	"Protocol.hpp"
#include	"SessionRequest.hh"

MenuWindow::MenuWindow(sf::RenderWindow &window, network::Manager &network):
  AScreen(window, network, START), _objectFocus(0), _objectHover(0)
{
  this->_flag = 0;
  this->_mapCallBack[requestCode::server::OK] = &MenuWindow::receiveOk;
  this->_mapCallBack[requestCode::server::FORBIDDEN] = &MenuWindow::receiveForbidden;
  this->_mapCallBack[requestCode::auth::SESSION] = &MenuWindow::receiveSession;
  this->_mapCallBack[requestCode::party::UPDATE] = &MenuWindow::receiveUpdateParty;
  this->_mapCallBack[requestCode::chat::RECV_MSG] = &MenuWindow::receiveChat;
  this->_mapCallBack[requestCode::party::STOPPED] = &MenuWindow::receiveStopParty;
  this->_mapCallBack[requestCode::party::SERV_START] = &MenuWindow::receiveLaunchGame;
}

bool	MenuWindow::load()
{
  try
    {
      if (!this->_music.openFromFile("./Sounds/Menu/DeepSpace.ogg"))
	throw Exception("Failed to load sprite location: ./Sounds/Menu/DeepSpace.ogg");
      this->_music.setLoop(true);
      TextureManager::getInstance().addTexture("Background1", "./Images/Menu/background1.png");
      TextureManager::getInstance().addTexture("Background2", "Images/Menu/background2.png");
      TextureManager::getInstance().addTexture("Formu", "Images/Menu/form.png");
      TextureManager::getInstance().addTexture("Title", "Images/Menu/title.png");
      TextureManager::getInstance().addTexture("TextArea", "Images/Menu/textArea.png");
      TextureManager::getInstance().addTexture("TextAreaFocus", "Images/Menu/textAreaFocus.png");
      TextureManager::getInstance().addTexture("Exit", "Images/Menu/Exit.png");
      TextureManager::getInstance().addTexture("Enter", "Images/Menu/Enter.png");
      TextureManager::getInstance().addTexture("Settings", "Images/Menu/Settings.png");
      TextureManager::getInstance().addTexture("SettingsHover", "Images/Menu/SettingsHover.png");
      TextureManager::getInstance().addTexture("SettingsFocus", "Images/Menu/SettingsFocus.png");
      TextureManager::getInstance().addTexture("FondSettings", "Images/Menu/FondSettings.png");
      TextureManager::getInstance().addTexture("ExitHover", "Images/Menu/ExitHover.png");
      TextureManager::getInstance().addTexture("EnterHover", "Images/Menu/EnterHover.png");
      TextureManager::getInstance().addTexture("ExitFocus", "Images/Menu/ExitFocus.png");
      TextureManager::getInstance().addTexture("EnterFocus", "Images/Menu/EnterFocus.png");
      TextureManager::getInstance().addTexture("FondWarningMenu", "Images/Menu/fondWarningMenu.png");
      TextureManager::getInstance().addTexture("TextAccessDenied", "Images/Menu/TextAccessDenied.png");
      TextureManager::getInstance().addTexture("Warning", "Images/Lobby/Warning.png");
      TextureManager::getInstance().addTexture("Back", "Images/Lobby/Back.png");
      TextureManager::getInstance().addTexture("BackHover", "Images/Lobby/BackHover.png");
      TextureManager::getInstance().addTexture("BackFocus", "Images/Lobby/BackFocus.png");
      TextureManager::getInstance().addTexture("Create", "Images/Lobby/Create.png");
      TextureManager::getInstance().addTexture("CreateHover", "Images/Lobby/CreateHover.png");
      TextureManager::getInstance().addTexture("CreateFocus", "Images/Lobby/CreateFocus.png");
      TextureManager::getInstance().addTexture("Join", "Images/Lobby/Join.png");
      TextureManager::getInstance().addTexture("JoinHover", "Images/Lobby/JoinHover.png");
      TextureManager::getInstance().addTexture("JoinFocus", "Images/Lobby/JoinFocus.png");
      TextureManager::getInstance().addTexture("Refresh", "Images/Lobby/Refresh.png");
      TextureManager::getInstance().addTexture("RefreshHover", "Images/Lobby/RefreshHover.png");
      TextureManager::getInstance().addTexture("RefreshFocus", "Images/Lobby/RefreshFocus.png");
      TextureManager::getInstance().addTexture("Disconnect", "Images/Lobby/Disconnect.png");
      TextureManager::getInstance().addTexture("DisconnectHover", "Images/Lobby/DisconnectHover.png");
      TextureManager::getInstance().addTexture("DisconnectFocus", "Images/Lobby/DisconnectFocus.png");
      TextureManager::getInstance().addTexture("FondLobby", "Images/Lobby/fondLobby.png");
      TextureManager::getInstance().addTexture("MsgChat", "Images/Lobby/MsgChat.png");
      TextureManager::getInstance().addTexture("ListServer", "Images/Lobby/listServer.png");
      TextureManager::getInstance().addTexture("Submit", "Images/Lobby/SubmitButton.png");
      TextureManager::getInstance().addTexture("SubmitFocus", "Images/Lobby/SubmitButtonFocus.png");
      TextureManager::getInstance().addTexture("SubmitHover", "Images/Lobby/SubmitButtonHover.png");
      TextureManager::getInstance().addTexture("TitleLobby", "Images/Lobby/titleLobby.png");
      TextureManager::getInstance().addTexture("Cancel", "Images/Lobby/CancelButton.png");
      TextureManager::getInstance().addTexture("CancelHover", "Images/Lobby/CancelButtonHover.png");
      TextureManager::getInstance().addTexture("CancelFocus", "Images/Lobby/CancelButtonFocus.png");
      TextureManager::getInstance().addTexture("CancelMenu", "Images/Menu/CancelMenu.png");
      TextureManager::getInstance().addTexture("CancelMenuHover", "Images/Menu/CancelMenuHover.png");
      TextureManager::getInstance().addTexture("CancelMenuFocus", "Images/Menu/CancelMenuFocus.png");
      TextureManager::getInstance().addTexture("Save", "Images/Menu/Save.png");
      TextureManager::getInstance().addTexture("SaveHover", "Images/Menu/SaveHover.png");
      TextureManager::getInstance().addTexture("SaveFocus", "Images/Menu/SaveFocus.png");
      TextureManager::getInstance().addTexture("Valider", "Images/Lobby/ValiderButton.png");
      TextureManager::getInstance().addTexture("ValiderFocus", "Images/Lobby/ValiderButtonFocus.png");
      TextureManager::getInstance().addTexture("ValiderHover", "Images/Lobby/ValiderButtonHover.png");
      TextureManager::getInstance().addTexture("CheckBox", "Images/Lobby/CheckBox.png");
      TextureManager::getInstance().addTexture("CheckBoxFocus", "Images/Lobby/CheckBoxFocus.png");
      TextureManager::getInstance().addTexture("FondCreate", "Images/Lobby/FondCreate.png");
      TextureManager::getInstance().addTexture("JoinOff", "Images/Lobby/JoinButtonOff.png");
      TextureManager::getInstance().addTexture("JoinOffHover", "Images/Lobby/JoinButtonOffHover.png");
      TextureManager::getInstance().addTexture("JoinOffFocus", "Images/Lobby/JoinButtonOffFocus.png");
      TextureManager::getInstance().addTexture("Leave", "Images/Lobby/LeaveButton.png");
      TextureManager::getInstance().addTexture("LeaveHover", "Images/Lobby/LeaveButtonHover.png");
      TextureManager::getInstance().addTexture("LeaveFocus", "Images/Lobby/LeaveButtonFocus.png");
      TextureManager::getInstance().addTexture("PlayerConnected", "Images/Lobby/PlayerConnected.png");
      TextureManager::getInstance().addTexture("PlayerNotConnected", "Images/Lobby/PlayerNotConnected.png");
      TextureManager::getInstance().addTexture("Start", "Images/Lobby/StartButton.png");
      TextureManager::getInstance().addTexture("StartHover", "Images/Lobby/StartButtonHover.png");
      TextureManager::getInstance().addTexture("StartFocus", "Images/Lobby/StartButtonFocus.png");
      TextureManager::getInstance().addTexture("StartOff", "Images/Lobby/StartButtonOff.png");
      TextureManager::getInstance().addTexture("StartOffHover", "Images/Lobby/StartButtonOffHover.png");
      TextureManager::getInstance().addTexture("StartOffFocus", "Images/Lobby/StartButtonOffFocus.png");
      TextureManager::getInstance().addTexture("TextCreate", "Images/Lobby/TextCreate.png");
      TextureManager::getInstance().addTexture("TextWait", "Images/Lobby/TextWait.png");
      TextureManager::getInstance().addTexture("LineServer", "Images/Lobby/LineServer.png");
      TextureManager::getInstance().addTexture("LineServerFocus", "Images/Lobby/LineServerFocus.png");
      TextureManager::getInstance().addTexture("LineServerLock", "Images/Lobby/LineServerLock.png");
      TextureManager::getInstance().addTexture("LineServerLockFocus", "Images/Lobby/LineServerLockFocus.png");
      TextureManager::getInstance().addTexture("FondWarningLobby", "Images/Lobby/fondWarningLobby.png");
      TextureManager::getInstance().addTexture("TextCreationFailed", "Images/Lobby/TextCreationFailed.png");
      TextureManager::getInstance().addTexture("Stop", "Images/Lobby/Stop.png");
      TextureManager::getInstance().addTexture("TextGetPassword", "Images/Lobby/TextGetPassword.png");
      TextureManager::getInstance().addTexture("CreateOff", "Images/Lobby/CreateOff.png");
      TextureManager::getInstance().addTexture("CreateOffHover", "Images/Lobby/CreateOffHover.png");
      TextureManager::getInstance().addTexture("CreateOffFocus", "Images/Lobby/CreateOffFocus.png");
    }
  catch (TextureManager::Exception &e)
    {
      std::cerr << e.what() << std::endl;
      throw AScreen::Exception("MenuWindow can't load all textures");
    }

  try
    {
      MediaAudioManager::getInstance().addSound("SwitchScreen", "Sounds/Menu/SwitchScreen.wav");
    }
  catch (MediaAudioManager::Exception &e)
    {
      std::cerr << e.what() << std::endl;
      throw AScreen::Exception("MenuWindow can't load all textures");
    }

  try
    {
      FontManager::getInstance().addFont("FontMenu", "./Font/NEUROPOL.ttf");
      FontManager::getInstance().addFont("FontLobby", "./Font/verdana.ttf");
    }
  catch (FontManager::Exception &e)
    {
      std::cerr << e.what() << std::endl;
      throw AScreen::Exception("MenuWindow can't load all textures");
    }


  this->_isConnected = 0;
  this->_status = START;
  this->_firstBackground.setTexture(TextureManager::getInstance().getTexture("Background1")->getTexture());
  this->_secondBackground.setTexture(TextureManager::getInstance().getTexture("Background2")->getTexture());
  return (true);
}

MenuWindow::~MenuWindow()
{
  clearWindow();
}

void	MenuWindow::drawMenu()
{
  Text *tmp = 0;
  Text *tmp2 = 0;
  int flag = 0;

  Text *Stocktmp = dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"));
  this->clearWindow();
  this->_currentState = MENU;
  if (Stocktmp != NULL)
    {
      if (Stocktmp->getTmp() != "" && Stocktmp->getTmp() != "Login")
	{
	  tmp = new Text("FontMenu", "LoginText", this->_event, sf::Vector2f(525, 410), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, true, Stocktmp->getTmp());
	  flag = 1;
	}
    }
  if (InfosUser::getInstance().authenticate.login == "Login" && flag == 0)
    tmp = new Text("FontMenu", "LoginText", this->_event, sf::Vector2f(525, 410), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, true, "root");
  else if (flag == 0)
    tmp = new Text("FontMenu", "LoginText", this->_event, sf::Vector2f(525, 410), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, true, InfosUser::getInstance().authenticate.login);

  tmp2 = new Text("FontMenu", "PasswordText", this->_event, sf::Vector2f(525, 515), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, false, "Password");
  this->_listImage.push_back(new Image("Title", sf::Vector2f(370, 60)));
  this->_listImage.push_back(new Image("Formu", sf::Vector2f(370, 175)));
  this->_listWidget.push_back(new TextArea(this->_event, "LoginArea", *tmp, sf::Vector2f(480, 380), sf::Vector2f(520, 415), sf::Vector2f(760, 445)));
  this->_listWidget.push_back(new TextArea(this->_event, "PasswordArea", *tmp2, sf::Vector2f(480, 480), sf::Vector2f(520, 515), sf::Vector2f(765, 545)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new Button(this->_event, "Settings", sf::Vector2f(570, 570), sf::Vector2f(576, 577), sf::Vector2f(706, 611), AScreen::SETTINGS, true));
  this->_listWidget.push_back(new Button(this->_event, "Enter", sf::Vector2f(482, 620), sf::Vector2f(488, 630), sf::Vector2f(619, 663), AScreen::LOGIN, true));
  this->_listWidget.push_back(new Button(this->_event, "Exit", sf::Vector2f(658, 620), sf::Vector2f(663, 630), sf::Vector2f(795, 663), AScreen::EXIT, true));
}

void	MenuWindow::drawMenuWarning(const std::string &Msg)
{
  this->clearWindow();
  this->_status = CONTINUE;
  this->_currentState = MENU_ERROR;
  Text *tmp = new Text("FontLobby", "WarningMessageMenu", this->_event, sf::Vector2f(500, 370), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 10, true, Msg);

  this->_listImage.push_back(new Image("FondWarningMenu", sf::Vector2f(390, 160)));
  this->_listImage.push_back(new Image("TextAccessDenied", sf::Vector2f(410, 320)));
  this->_listImage.push_back(new Image("Warning", sf::Vector2f(570, 175)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(new Button(this->_event, "Back", sf::Vector2f(550, 410), sf::Vector2f(557, 416), sf::Vector2f(745, 464), AScreen::BACK_MENU, true));
}


void	MenuWindow::drawSettings()
{
  Text *textIP;
  Text *textTCP;
  Text *textUDP;

  this->clearWindow();
  this->_status = CONTINUE;
  this->_currentState = SETTINGS;
  if (InfosUser::getInstance().authenticate.addressIp == "Address Ip")
    textIP = new Text("FontLobby", "IPAddress", this->_event, sf::Vector2f(525, 410), sf::Vector2f(519, 410), sf::Vector2f(766, 446), 15, true, "127.0.0.1");
  else
    textIP = new Text("FontLobby", "IPAddress", this->_event, sf::Vector2f(525, 410), sf::Vector2f(519, 410), sf::Vector2f(766, 446), 15, true, InfosUser::getInstance().authenticate.addressIp);

  if (InfosUser::getInstance().authenticate.portTCP == 0)
    textTCP = new Text("FontLobby", "PortTCP", this->_event, sf::Vector2f(525, 500), sf::Vector2f(518, 503), sf::Vector2f(764, 532), 5, true, "44201");
  else
    {
      std::stringstream ss;
      ss << InfosUser::getInstance().authenticate.portTCP;
      textTCP = new Text("FontLobby", "PortTCP", this->_event, sf::Vector2f(525, 500), sf::Vector2f(518, 503), sf::Vector2f(764, 532), 5, true, ss.str());
    }
  if (InfosUser::getInstance().authenticate.portUDP == 0)
    textUDP = new Text("FontLobby", "PortUDP", this->_event, sf::Vector2f(525, 580), sf::Vector2f(517, 580), sf::Vector2f(766, 614), 5, true, "44202");
  else
    {
      std::stringstream ss;
      ss << InfosUser::getInstance().authenticate.portUDP;
      textUDP = new Text("FontLobby", "PortUDP", this->_event, sf::Vector2f(525, 580), sf::Vector2f(517, 580), sf::Vector2f(766, 614), 5, true, ss.str());
    }
  this->_listImage.push_back(new Image("Title", sf::Vector2f(370, 60)));
  this->_listImage.push_back(new Image("FondSettings", sf::Vector2f(370, 175)));
  this->_listWidget.push_back(new TextArea(this->_event, "IPArea", *textIP, sf::Vector2f(480, 375), sf::Vector2f(519, 410), sf::Vector2f(766, 446)));
  this->_listWidget.push_back(new TextArea(this->_event, "PortTCPArea", *textTCP, sf::Vector2f(480, 465), sf::Vector2f(518, 503), sf::Vector2f(764, 532)));
  this->_listWidget.push_back(new TextArea(this->_event, "PortUDPArea", *textUDP, sf::Vector2f(480, 545), sf::Vector2f(517, 580), sf::Vector2f(766, 614)));
  this->_listWidget.push_back(textIP);
  this->_listWidget.push_back(textTCP);
  this->_listWidget.push_back(textUDP);
  this->_listWidget.push_back(new Button(this->_event, "Save", sf::Vector2f(500, 630), sf::Vector2f(505, 638), sf::Vector2f(615, 672), AScreen::SET_CHANGE, true));
  this->_listWidget.push_back(new Button(this->_event, "CancelMenu", sf::Vector2f(650, 630), sf::Vector2f(655, 637), sf::Vector2f(767, 669), AScreen::BACK_SET, true));
}

void	MenuWindow::drawLobbyWarning(const std::string &Msg)
{
  this->clearWindow();
  this->_status = CONTINUE;
  this->_currentState = LOBBY_ERROR;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  Text *tmp2 = new Text("FontLobby", "WarningMessageLobby", this->_event, sf::Vector2f(260, 464), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 10, true, Msg);

  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));

  this->_listImage.push_back(new Image("FondWarningLobby", sf::Vector2f(165, 250)));
  this->_listImage.push_back(new Image("TextCreationFailed", sf::Vector2f(190, 415)));
  this->_listImage.push_back(new Image("Warning", sf::Vector2f(340, 280)));
  this->_listWidget.push_back(new Button(this->_event, "Back", sf::Vector2f(320, 490), sf::Vector2f(326, 496), sf::Vector2f(516, 547), AScreen::BACK_LOBY, true));

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), AScreen::CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), AScreen::JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), AScreen::REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), AScreen::BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), AScreen::SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 40));
}

void	MenuWindow::drawGetPWD()
{
  this->clearWindow();
  this->_status = CONTINUE;
  this->_currentState = VERIF_PWD;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  Text *tmp2 = new Text("FontLobby", "setPWD", this->_event, sf::Vector2f(440, 390), sf::Vector2f(393, 386), sf::Vector2f(641, 419), 10, false);

  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));

  this->_listImage.push_back(new Image("FondWarningLobby", sf::Vector2f(165, 250)));
  this->_listImage.push_back(new Image("TextGetPassword", sf::Vector2f(400, 285)));
  this->_listImage.push_back(new Image("Stop", sf::Vector2f(200, 280)));
  this->_listWidget.push_back(new Button(this->_event, "Valider", sf::Vector2f(200, 490), sf::Vector2f(207, 497), sf::Vector2f(395, 545), AScreen::WAIT, true));
  this->_listWidget.push_back(new Button(this->_event, "Cancel", sf::Vector2f(440, 490), sf::Vector2f(446, 495), sf::Vector2f(635, 546), AScreen::BACK_LOBY, true));

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), AScreen::CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), AScreen::JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), AScreen::REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), AScreen::BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), AScreen::SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(new TextArea(this->_event, "TextPWDArea", *tmp2, sf::Vector2f(355, 350), sf::Vector2f(393, 386), sf::Vector2f(641, 419)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 40));
}


void	MenuWindow::drawLobby()
{
  this->clearWindow();
  this->_status = CONTINUE;
  this->_currentState = LOBBY;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));
  this->_listImage.push_back(new Image("ListServer", sf::Vector2f(50, 195)));
  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), AScreen::CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), AScreen::JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), AScreen::REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), AScreen::BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), AScreen::SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 40));
}

void	MenuWindow::drawLobbyCreate()
{
  this->clearWindow();
  this->_status = CONTINUE;
  this->_currentState = CREATE;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  Text *tmp2 = 0;
  Text *tmp3 = 0;

  if (InfosUser::getInstance().game.partyName == "Party Name")
    tmp2 = new Text("FontLobby", "NameGame", this->_event, sf::Vector2f(200, 300), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 15, true, "Party Name");
  else
    tmp2 = new Text("FontLobby", "NameGame", this->_event, sf::Vector2f(200, 300), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 15, true, InfosUser::getInstance().game.partyName);
  tmp3 = new Text("FontLobby", "PWDGame", this->_event, sf::Vector2f(245, 475), sf::Vector2f(238, 469), sf::Vector2f(487, 502), 10, false, "Party Password");

  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));
  this->_listImage.push_back(new Image("FondCreate", sf::Vector2f(50, 200)));
  this->_listImage.push_back(new Image("TextCreate", sf::Vector2f(80, 220)));

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), AScreen::CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), AScreen::JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), AScreen::REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), AScreen::BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), AScreen::SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(new TextArea(this->_event, "TextPassword", *tmp3, sf::Vector2f(200, 435), sf::Vector2f(238, 469), sf::Vector2f(487, 502)));
  this->_listWidget.push_back(new TextArea(this->_event, "TextName", *tmp2, sf::Vector2f(150, 265), sf::Vector2f(188, 301), sf::Vector2f(437, 332)));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckOnePlayer", sf::Vector2f(110, 390), sf::Vector2f(116, 397), sf::Vector2f(134, 414), 1, true));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckTwoPlayer", sf::Vector2f(250, 390), sf::Vector2f(256, 397), sf::Vector2f(275, 414), 2, false));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckThreePlayer", sf::Vector2f(390, 390), sf::Vector2f(396, 397), sf::Vector2f(414, 414), 3, false));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckFourPlayer", sf::Vector2f(530, 390), sf::Vector2f(536, 397), sf::Vector2f(555, 414), 4, false));
  this->_listWidget.push_back(new Button(this->_event, "Valider", sf::Vector2f(250, 585), sf::Vector2f(254, 592), sf::Vector2f(447, 639), AScreen::VALIDE, true));
  this->_listWidget.push_back(new Button(this->_event, "Cancel", sf::Vector2f(500, 585), sf::Vector2f(505, 590), sf::Vector2f(697, 641), AScreen::BACK_LOBY, true));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(tmp3);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 40));
}

void	MenuWindow::drawLobbyWait(int owner)
{
  Text *tmp2;
  float	posX = 150;
  unsigned int	i = 0;

  this->clearWindow();
  this->_status = CONTINUE;
  this->_currentState = WAIT;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));
  this->_listImage.push_back(new Image("FondCreate", sf::Vector2f(50, 200)));
  this->_listImage.push_back(new Image("TextWait", sf::Vector2f(80, 220)));
  if (owner == 0)
    tmp2 = new Text("FontLobby", "NameGameWait", this->_event, sf::Vector2f(170, 297), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true, this->_serverSelected._name);
  else
    tmp2 = new Text("FontLobby", "NameGameWait", this->_event, sf::Vector2f(170, 297), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true, InfosUser::getInstance().game.partyName);

  for (i = 0; i < InfosUser::getInstance().game.nbPlayer; i++)
    {
      this->_listImage.push_back(new Image("PlayerConnected", sf::Vector2f(posX, 450)));
      posX += 150;
    }
  while (i < InfosUser::getInstance().game.maxPlayer)
    {
      this->_listImage.push_back(new Image("PlayerNotConnected", sf::Vector2f(posX, 450)));
      ++i;
      posX += 150;
    }
  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), AScreen::CREATE_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), AScreen::JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), AScreen::REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), AScreen::BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), AScreen::SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  if (owner == 1)
    {
      this->_listWidget.push_back(new Button(this->_event, "Start", sf::Vector2f(250, 585), sf::Vector2f(254, 592), sf::Vector2f(447, 639), AScreen::GAME, true));
      this->_listWidget.push_back(new Button(this->_event, "Cancel", sf::Vector2f(500, 585), sf::Vector2f(505, 590), sf::Vector2f(697, 641), AScreen::CANCEL_GAME, true));
    }
  else
    {
      this->_listWidget.push_back(new Button(this->_event, "Start", sf::Vector2f(250, 585), sf::Vector2f(254, 592), sf::Vector2f(447, 639), AScreen::GAME, false));
      this->_listWidget.push_back(new Button(this->_event, "Cancel", sf::Vector2f(500, 585), sf::Vector2f(505, 590), sf::Vector2f(697, 641), AScreen::LEAVE_GAME, true));
    }
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new TextBlock( "ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 40));
}

void		MenuWindow::scroll()
{
  _firstPos = _firstBackground.getPosition();
  _secondPos = _secondBackground.getPosition();
  if (_firstPos.x == 0)
    _secondPos.x = 1280;
  if (_firstPos.x == -1280)
    _firstPos.x = 1280;
  if (_secondPos.x == -1280)
    _secondPos.x = 1280;
  _firstPos.x -= 2;
  _secondPos.x -= 2;
  _secondBackground.setPosition(_secondPos.x, 0);
  _firstBackground.setPosition(_firstPos.x, 0);
}

void		MenuWindow::setGameList()
{
  float y = 243.;
  float x = 62.;

  game_list::iterator itGame;

  for (itGame = this->_listGame.begin(); itGame != this->_listGame.end(); ++itGame)
    {
      (*itGame)->setPos(sf::Vector2f(x, y));
      (*itGame)->setFocus(sf::Vector2f(x + 7, y + 6), sf::Vector2f(x + 686, y + 26));
      y += 20;
    }
}

void	MenuWindow::draw()
{
  widget_list::iterator	it;
  image_list::iterator	itImg;
  game_list::iterator itGame;

  this->scroll();
  this->_window.draw(_firstBackground);
  this->_window.draw(_secondBackground);
  for (itImg = this->_listImage.begin(); itImg != this->_listImage.end(); itImg++)
    this->_window.draw((*itImg)->getImage());
  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    (*it)->draw(this->_window);
  if (this->_currentState == LOBBY)
    {
      for (itGame = this->_listGame.begin(); itGame != this->_listGame.end(); itGame++)
	(*itGame)->draw(this->_window);
    }
  this->_window.display();
}

AWidget	*MenuWindow::returnMouseFocus(float x, float y)
{
  widget_list::iterator	it;
  game_list::iterator	itgame;

  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    {
      if ((*it)->isFocus(sf::Vector2f(x, y)) == true)
	return *it;
    }
  for (itgame = this->_listGame.begin(); itgame != this->_listGame.end(); itgame++)
    {
      if ((*itgame)->isFocus(sf::Vector2f(x, y)) == true)
	return *itgame;
    }
  return (0);
}

void	MenuWindow::checkServer()
{
  game_list::iterator it;
  int		tmp = 0;

  for (it = this->_listGame.begin(); it != this->_listGame.end(); ++it)
    {
      if ((*it)->getFocus() == 1)
	{
	  this->_flag = 1;
	  this->_serverSelected = (*it)->getGameInfo();
	  tmp = 1;
	  this->removeWidget("Join");
	  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), AScreen::JOIN_GAME, true));
	  return ;
	}
    }
  if (this->_flag == 1 && tmp == 0)
    {
      this->_flag = 0;
      this->removeWidget("Join");
      this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), AScreen::JOIN_GAME, false));
    }
}

int	MenuWindow::checkNbPlayer()
{
  widget_list::iterator it;
  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); ++it)
    {
      if ((*it)->getType() == AWidget::CHECKBOX)
	{
	  if (dynamic_cast<CheckBox*>(*it)->getStates() == 1)
	    return (dynamic_cast<CheckBox*>(*it)->getNb());
	}
    }
  return 0;
}

const sf::Vector2f	&MenuWindow::getFirstPos() const
{
  return (this->_firstPos);
}

const sf::Vector2f	&MenuWindow::getSecondPos() const
{
  return (this->_secondPos);
}

const sf::Sprite	&MenuWindow::getFirstBackground() const
{
  return (this->_firstBackground);
}

const sf::Sprite	&MenuWindow::getSecondBackground() const
{
  return (this->_secondBackground);
}

void		MenuWindow::setFirstPos(float x, float y)
{
  this->_firstBackground.setPosition(x, y);
}

void		MenuWindow::setFirstPos(sf::Vector2f vector)
{
  this->_firstPos = vector;
}

void		MenuWindow::setSecondPos(float x, float y)
{
  this->_secondBackground.setPosition(x, y);
}

void		MenuWindow::setSecondPos(sf::Vector2f vector)
{
  this->_secondPos = vector;
}

int	MenuWindow::checkAction()
{
  std::string msgChat;
  switch (this->_status)
    {
    case AScreen::START:
      this->_status = CONTINUE;
      this->drawMenu();
      break;
    case AScreen::GAME:
      this->_network.sendRequest(new Party::Start());
      this->_status = CONTINUE;
      break;
    case AScreen::LAUNCH:
      this->clearWindow();
      this->_status = BACK_LOBY;
      return (2);
      break;
    case AScreen::WAIT:
      this->_status = CONTINUE;
      this->_network.sendRequest(new Party::Join(this->_serverSelected._name, dynamic_cast<Text*>(Interface::getInstance().getWidget("setPWD"))->getTmp()));
      break;
    case AScreen::LOGIN:
      this->_status = CONTINUE;
      if (dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"))->getTmp() == "" ||
	  dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"))->getTmp() == "Login")
	{
	  this->drawMenuWarning("Login area is empty !");
	  break;
	}
      else if (dynamic_cast<Text*>(Interface::getInstance().getWidget("PasswordText"))->getTmp() == "" ||
	       dynamic_cast<Text*>(Interface::getInstance().getWidget("PasswordText"))->getTmp() == "Password")
	{
	  this->drawMenuWarning(" Password area is empty !");
	  break;
	}
      InfosUser::getInstance().authenticate.login = dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"))->getTmp();
      InfosUser::getInstance().authenticate.password = dynamic_cast<Text*>(Interface::getInstance().getWidget("PasswordText"))->getTmp();
      if (!this->_network.setTcp(sf::IpAddress(InfosUser::getInstance().authenticate.addressIp), InfosUser::getInstance().authenticate.portTCP))
	{
	  this->drawMenuWarning("Unable to reach the server !");
	  break;
	}
      this->_network.switchTo(network::Manager::TCP);
      if (this->_network.isConnected())
	{
	  this->_network.sendRequest(new Auth::Connect(InfosUser::getInstance().authenticate.login, md5(InfosUser::getInstance().authenticate.password)));
	  break;
	}
      else
	{
	  this->drawMenuWarning("Bad server settings !");
	  break;
	}
    case AScreen::EXIT:
      this->_window.close();
      break;
    case AScreen::BACK_MENU:
      this->_network.closeTcp();
      this->_network.switchTo(network::Manager::NONE);
      this->_isConnected = 0;
      this->_status = CONTINUE;
      this->drawMenu();
      break;
    case AScreen::CREATE_GAME:
      this->_status = CONTINUE;
      MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
      this->drawLobbyCreate();
      break;
    case AScreen::REFRESH_GAME:
      this->_network.sendRequest(new Party::List());
      this->_status = CONTINUE;
      break;
    case AScreen::JOIN_GAME:
      this->_status = CONTINUE;
      if (this->_serverSelected._lock)
	this->drawGetPWD();
      else
	this->_network.sendRequest(new Party::Join(this->_serverSelected._name));
      break;
    case AScreen::VALIDE:
      if (dynamic_cast<Text*>(Interface::getInstance().getWidget("NameGame"))->getTmp() == "" ||
	  dynamic_cast<Text*>(Interface::getInstance().getWidget("NameGame"))->getTmp() == "Party Name")
	{
	  this->_status = CONTINUE;
	  this->drawLobbyWarning("Name game area is empty !");
	  break;
	}
      InfosUser::getInstance().game.partyName = dynamic_cast<Text*>(Interface::getInstance().getWidget("NameGame"))->getTmp();
      InfosUser::getInstance().game.partyPassword = dynamic_cast<Text*>(Interface::getInstance().getWidget("PWDGame"))->getTmp();
      InfosUser::getInstance().game.nbPlayer = 1;
      InfosUser::getInstance().game.maxPlayer = checkNbPlayer();
      if (InfosUser::getInstance().game.partyPassword.empty() || InfosUser::getInstance().game.partyPassword == "Party Password")
	this->_network.sendRequest(new Party::Create(InfosUser::getInstance().game.partyName, this->checkNbPlayer()));
      else
	this->_network.sendRequest(new Party::Create(InfosUser::getInstance().game.partyName, this->checkNbPlayer(), md5(InfosUser::getInstance().game.partyPassword)));
      this->_status = CONTINUE;
      break;
    case AScreen::SUBMIT:
      this->_status = CONTINUE;
      //Envoyer un message au serveur
      if (dynamic_cast<Text*>(Interface::getInstance().getWidget("MsgChat"))->getTmp() != "")
	{
	  msgChat = "[" + InfosUser::getInstance().authenticate.login + "] : " + dynamic_cast<Text*>(Interface::getInstance().getWidget("MsgChat"))->getTmp();
	  std::cout << msgChat << std::endl;

	  this->_network.sendRequest(new ChatSendRequest(msgChat));

	}
      dynamic_cast<Text*>(Interface::getInstance().getWidget("MsgChat"))->clearText();
      break;
    case AScreen::SELECT_SERVER:
      this->_status = CONTINUE;
      this->checkServer();
      break;
    case AScreen::SETTINGS:
      this->_status = CONTINUE;
      this->drawSettings();
      break;
    case AScreen::SET_CHANGE:
      if (dynamic_cast<Text*>(Interface::getInstance().getWidget("IPAddress"))->getTmp() == "" ||
	  dynamic_cast<Text*>(Interface::getInstance().getWidget("IPAddress"))->getTmp() == "Address Ip")
	{
	  this->_status = AScreen::CONTINUE;
	  this->drawMenu();
	  break;
	}
      else if (dynamic_cast<Text*>(Interface::getInstance().getWidget("PortTCP"))->getTmp() == "" ||
	       dynamic_cast<Text*>(Interface::getInstance().getWidget("PortTCP"))->getTmp() == "Port TCP")
	{
	  this->_status = AScreen::CONTINUE;
	  this->drawMenu();
	  break;
	}
      else if (dynamic_cast<Text*>(Interface::getInstance().getWidget("PortUDP"))->getTmp() == "" ||
	       dynamic_cast<Text*>(Interface::getInstance().getWidget("PortUDP"))->getTmp() == "Port UDP")
	{
	  this->_status = AScreen::CONTINUE;
	  this->drawMenu();
	  break;
	}
      else
	{
	  InfosUser::getInstance().authenticate.addressIp = dynamic_cast<Text*>(Interface::getInstance().getWidget("IPAddress"))->getTmp();
	  std::stringstream ss;
	  unsigned short int		    portTCP;
	  unsigned short int		    portUDP;
	  ss << dynamic_cast<Text*>(Interface::getInstance().getWidget("PortTCP"))->getTmp();
	  ss >> portTCP;
	  ss.clear();
	  ss << dynamic_cast<Text*>(Interface::getInstance().getWidget("PortUDP"))->getTmp();
	  ss >> portUDP;
	  InfosUser::getInstance().authenticate.portTCP = portTCP;
	  InfosUser::getInstance().authenticate.portUDP = portUDP;
	  this->_status = CONTINUE;
	  this->drawMenu();
	  break;
	}
    case AScreen::BACK_SET:
      this->_status = AScreen::CONTINUE;
      this->drawMenu();
      break;
    case AScreen::BACK_LOBY:
      this->_status = AScreen::CONTINUE;
      MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
      this->drawLobby();
      break;
    case AScreen::VERIF_PWD:
      this->_status = AScreen::CONTINUE;
      break;
    case AScreen::LEAVE_GAME:
      this->_status = AScreen::CONTINUE;
      std::cout << "Je leave comme un gros porc " << std::endl;
      this->_network.sendRequest(new Party::Cancel());
      break;
    case AScreen::CANCEL_GAME:
      this->_status = AScreen::CONTINUE;
      this->_network.sendRequest(new Party::Cancel());
      break;
    default:
      break;
    }
  return 0;
}

void	MenuWindow::clearWindow()
{
  for (image_list::iterator it = _listImage.begin(); it != _listImage.end();)
    {
      Image  *cur = *it;

      it = _listImage.erase(it);
      delete cur;
    }
  for (widget_list::iterator it = _listWidget.begin(); it != _listWidget.end();)
    {
      AWidget  *cur = *it;

      it = _listWidget.erase(it);
      delete cur;
    }
  _objectFocus = 0;
  _objectHover = 0;
}

void	MenuWindow::removeWidget(const std::string &widget)
{
  widget_list::iterator it;

  for (it = this->_listWidget.begin(); it != this->_listWidget.end();)
    {
      if ((*it)->getName() == widget)
	{
	  AWidget	*w = *it;

	  it = this->_listWidget.erase(it);
	  if (w == this->_objectFocus)
	    this->_objectFocus = 0;
	  if (w == this->_objectHover)
	    this->_objectHover = 0;
	  delete w;
	}
      else
	++it;
    }
}


void	MenuWindow::receiveLaunchGame(ARequest *req)
{
  (void)req;
  std::cout << "LAUNCH THE FUCKING GAME" << std::endl;
  MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
  this->_status = AScreen::LAUNCH;
}

void	MenuWindow::receiveStopParty(ARequest *req)
{
  (void)req;
  std::cout << "J'ANNULE" << std::endl;
  MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
  this->drawLobby();
}

void	MenuWindow::deleteLineServer(const std::string &nameParty)
{
  game_list::iterator	it;

  for (it = this->_listGame.begin(); it != this->_listGame.end();)
    {
      if ((*it)->getType() == AWidget::LINESERVER && (*it)->getGame() == nameParty)
	{
	  it = this->_listGame.erase(it);
	  return;
	}
      else
	++it;
    }
}

void	MenuWindow::removeImagePlayer()
{
  image_list::iterator it;
  std::string		tmpName;


  for (it = this->_listImage.begin(); it != this->_listImage.end();)
    {
      tmpName = (*it)->getName();
      std::cout << "NAME : " << tmpName << std::endl;
      if (tmpName == "PlayerConnected" || tmpName == "PlayerNotConnected")
	it = this->_listImage.erase(it);
      else
	++it;
    }
}

void	MenuWindow::updateLineServer(const std::string &nameParty, const std::string &slot)
{
  game_list::iterator	it;

  for (it = this->_listGame.begin(); it != this->_listGame.end();)
    {
      if ((*it)->getType() == AWidget::LINESERVER && (*it)->getGame() == nameParty)
	{
	  (*it)->setSlot(slot);
	  return;
	}
      else
	++it;
    }
  if (this->_currentState == WAIT)
    {
      float	posX = 150;
      unsigned int	i = 0;

      this->removeImagePlayer();
      for (i = 0; i < InfosUser::getInstance().game.nbPlayer; i++)
	{
	  this->_listImage.push_back(new Image("PlayerConnected", sf::Vector2f(posX, 450)));
	  posX += 150;
	}
      while (i < InfosUser::getInstance().game.maxPlayer)
	{
	  this->_listImage.push_back(new Image("PlayerNotConnected", sf::Vector2f(posX, 450)));
	  ++i;
	  posX += 150;
	}
    }
}

void	MenuWindow::gameExist(const std::string &slot, bool pwd)
{
  game_list::iterator	it;
  LineServer		*tmpServ;
  float x = 300.;
  float y = 300.;

  if (pwd)
    tmpServ = new LineServer(this->_event, sf::Vector2f(x, y), sf::Vector2f(x + 7, y + 6), sf::Vector2f(x + 686, y + 26), InfosUser::getInstance().game.partyName, slot, true);
  else
    tmpServ = new LineServer(this->_event, sf::Vector2f(x, y), sf::Vector2f(x + 7, y + 6), sf::Vector2f(x + 686, y + 26), InfosUser::getInstance().game.partyName, slot, false);

  for (it = this->_listGame.begin(); it != this->_listGame.end();)
    {
      if ((*it)->getType() == AWidget::LINESERVER && (*it)->getGame() == InfosUser::getInstance().game.partyName)
	{
	  *it = tmpServ;
	  return;
	}
      else
	++it;
    }
  this->_listGame.push_back(new LineServer(this->_event, sf::Vector2f(x, y), sf::Vector2f(x + 7, y + 6), sf::Vector2f(x + 686, y + 26),
					   InfosUser::getInstance().game.partyName, slot, true));
}

void	MenuWindow::receiveUpdateParty(ARequest *req)
{
  Party::Update *up;
  std::string slot;
  std::stringstream ss;
  int tmpnbMax;
  int tmpcurrent;


  up = dynamic_cast<Party::Update*>(req);
  tmpnbMax = up->_maxPlayers;
  tmpcurrent = (up->_maxPlayers - up->_availableSlots);
  ss << tmpcurrent;
  slot += ss.str();
  ss.str("");
  ss << tmpnbMax;
  slot += "/" + ss.str();

  InfosUser::getInstance().game.maxPlayer = tmpnbMax;
  InfosUser::getInstance().game.nbPlayer = tmpcurrent;
  InfosUser::getInstance().game.partyName = up->_partyName;
  // InfosUser::getInstance().party.pwd = ;

  if (up->_status == requestCode::party::OUT_GAME)
    {
      std::cout << "AJOUUUUUUUUUUUUUUUUUUUT" << std::endl;
      if (up->_isPassword == requestCode::party::PASS)
	gameExist(slot, true);
      else
	gameExist(slot, false);
    }
  else if ((up->_status == requestCode::party::CANCELED) || (up->_status == requestCode::party::FINISHED))
    {
      std::cout << "SUPPR" << std::endl;
      deleteLineServer(up->_partyName);
    }
  else if (up->_status == requestCode::party::UPDATE_GAME)
    {
      std::cout << "MODIF" << std::endl;
      updateLineServer(up->_partyName, slot);
    }
  this->setGameList();
}

void	MenuWindow::receiveChat(ARequest *req)
{
  (void)req;
  std::string Msg;

  Msg = dynamic_cast<ChatRecvRequest*>(req)->msg();
  dynamic_cast<TextBlock*>(Interface::getInstance().getWidget("ChatBlock"))->addText(Msg);
}

void	MenuWindow::receiveOk(ARequest *req)
{
  (void)req;
  if (this->_currentState == MENU)
    {
      this->_isConnected = 1;
      MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
      this->drawLobby();
    }
  else if (this->_currentState == CREATE)
    {
      MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
      this->drawLobbyWait(1);
    }
  else if (this->_currentState == LOBBY || this->_currentState == VERIF_PWD)
    {
      MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
      this->drawLobbyWait(0);
    }
  else if (this->_currentState == WAIT)
    {
      MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
      this->drawLobby();
    }
  else if (this->_currentState == VERIF_PWD)
    {
      MediaAudioManager::getInstance().getSound("SwitchScreen")->getSound().play();
      this->drawLobbyWait(0);
    }
}

void	MenuWindow::receiveForbidden(ARequest *req)
{
  (void)req;
  if (this->_currentState == MENU)
    this->drawMenuWarning("Authentification Failed");
  else if (this->_currentState == CREATE)
    this->drawLobbyWarning("Server can't created more games");
  else if (this->_currentState == VERIF_PWD)
    this->drawLobbyWarning("Bad Password");
  else if (this->_currentState == LOBBY)
    this->drawLobbyWarning("Can't join selected server");
}

void	MenuWindow::receiveSession(ARequest *req)
{
  InfosUser::getInstance().authenticate.id = dynamic_cast<SessionRequest*>(req)->SessionID();
}

void	MenuWindow::update()
{
  if (this->_network.isConnected())
    {
      ARequest *req;

      while ((req = this->_network.recvRequest()) != 0)
	{
	  callback_map::iterator	it = _mapCallBack.find(req->code());

	  if (it != _mapCallBack.end())
	    (this->*(it->second))(req);
	  else
	    std::cout << req->code() << ": not implemented yet" << std::endl;
	}
    }
  else if (!this->_network.isConnected() && this->_isConnected == 1)
    {
      this->drawMenuWarning("You've been Disconnected");
      this->_isConnected = 0;
    }
}

int	MenuWindow::catchEvent()
{
  while (this->_window.pollEvent(this->_event))
    {
      this->update();
      if (this->_flag == 1)
	checkServer();
      if (checkAction() == 2)
	return 2;
      switch (this->_event.type)
	{
	case sf::Event::Closed:
	  this->_window.close();
	  break;
	case sf::Event::KeyPressed:
	  if (this->_event.key.code == sf::Keyboard::Escape)
	    this->_window.close();
	  if (this->_event.key.code == sf::Keyboard::F1)
	    {
	      this->_status = BACK_LOBY;
	      return 2;
	    }
	  break;
	case sf::Event::TextEntered:
	  if (this->_objectFocus != 0)
	    this->_objectFocus->onFocus();
	  break;
	case sf::Event::MouseButtonPressed:
	  if (this->_objectFocus != 0)
	    this->_objectFocus->stopFocus();
	  this->_objectFocus = returnMouseFocus((float)this->_event.mouseButton.x, (float)this->_event.mouseButton.y);
	  if (this->_objectFocus != 0)
	    this->_status = this->_objectFocus->onFocus();
	  break;
	case sf::Event::MouseMoved:
	  if (this->_objectHover != 0)
	    this->_objectHover->stopHover();
	  this->_objectHover = returnMouseFocus((float)this->_event.mouseMove.x, (float)this->_event.mouseMove.y);
	  if (this->_objectHover != 0)
	    this->_objectHover->onHover();
	  break;
	case sf::Event::MouseButtonReleased:
	  if (this->_objectFocus != 0)
	    {
	      this->_objectFocus->stopFocus();
		  this->_objectFocus = returnMouseFocus((float)this->_event.mouseButton.x, (float)this->_event.mouseButton.y);
	      if (this->_objectFocus != 0)
		this->_objectFocus->stopFocus();
	    }
	  break;
	default:
	  break;
	}
    }
  return 0;
}

int	MenuWindow::run()
{
  this->_music.play();
  while (this->_window.isOpen())
    {
      if (this->_status == BACK_LOBY)
	this->_network.switchTo(network::Manager::TCP);
      if (this->catchEvent() == 2)
	{
	  this->_music.stop();
	  return (AScreen::SCR_GAME);
	}
      this->draw();
    }
  return (AScreen::SCR_EXIT);
}

const MenuWindow::image_list	&MenuWindow::getListImage() const
{
  return (this->_listImage);
}

const MenuWindow::widget_list	&MenuWindow::getListWidget() const
{
  return (this->_listWidget);
}
