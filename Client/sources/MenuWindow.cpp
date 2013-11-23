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
#include	"Network.hh"
#include	"InfosUser.hh"

MenuWindow::MenuWindow(sf::RenderWindow &window, network::Manager &network):
  AScreen(window, network, START), _objectFocus(0), _objectHover(0)
{
  this->_flag = 0;
}

bool	MenuWindow::load()
{
  try
    {
      FontManager::getInstance().addFont("FontMenu", "./Font/NEUROPOL.ttf");
      FontManager::getInstance().addFont("FontLobby", "./Font/verdana.ttf");
     if (!this->_music.openFromFile("./Sounds/Menu/DeepSpace.ogg"))
	throw Exception("Failed to load sprite location: ./Sounds/Menu/DeepSpace.ogg");
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
    }
  catch (TextureManager::Exception &e)
    {
      std::cerr << e.what() << std::endl;
      throw AScreen::Exception("MenuWindow can't load all textures");
    }
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
  Text *tmp2;
  int flag = 0;

  Text *Stocktmp = dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"));
  this->clearWindow();
  if (Stocktmp != NULL)
    {
      if (Stocktmp->getTmp() != "" && Stocktmp->getTmp() != "Login")
	{
	  tmp = new Text("FontMenu", "LoginText", this->_event, sf::Vector2f(525, 410), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, true, Stocktmp->getTmp());
	  flag = 1;
	}
    }
  if (InfosUser::getInstance().authenticate.login == "Login" && flag == 0)
    tmp = new Text("FontMenu", "LoginText", this->_event, sf::Vector2f(525, 410), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, true, "Login");
  else if (flag == 0)
    tmp = new Text("FontMenu", "LoginText", this->_event, sf::Vector2f(525, 410), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, true, InfosUser::getInstance().authenticate.login);

  tmp2 = new Text("FontMenu", "PasswordText", this->_event, sf::Vector2f(525, 515), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, false, "Password");
  this->_listImage.push_back(new Image("Title", sf::Vector2f(370, 60)));
  this->_listImage.push_back(new Image("Formu", sf::Vector2f(370, 175)));
  this->_listWidget.push_back(new TextArea(this->_event, "LoginArea", *tmp, sf::Vector2f(480, 380), sf::Vector2f(520, 415), sf::Vector2f(760, 445)));
  this->_listWidget.push_back(new TextArea(this->_event, "PasswordArea", *tmp2, sf::Vector2f(480, 480), sf::Vector2f(520, 515), sf::Vector2f(765, 545)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new Button(this->_event, "Settings", sf::Vector2f(570, 570), sf::Vector2f(576, 577), sf::Vector2f(706, 611), SETTINGS, true));
  this->_listWidget.push_back(new Button(this->_event, "Enter", sf::Vector2f(482, 620), sf::Vector2f(488, 630), sf::Vector2f(619, 663), LOGIN, true));
  this->_listWidget.push_back(new Button(this->_event, "Exit", sf::Vector2f(658, 620), sf::Vector2f(663, 630), sf::Vector2f(795, 663), EXIT, true));
}

void	MenuWindow::drawMenuWarning(const std::string &Msg)
{
  this->clearWindow();
  this->_status = CONTINUE;
  Text *tmp = new Text("FontLobby", "WarningMessageMenu", this->_event, sf::Vector2f(500, 370), sf::Vector2f(499, 369), sf::Vector2f(678, 389), 10, true, Msg);

  this->_listImage.push_back(new Image("FondWarningMenu", sf::Vector2f(390, 160)));
  this->_listImage.push_back(new Image("TextAccessDenied", sf::Vector2f(410, 320)));
  this->_listImage.push_back(new Image("Warning", sf::Vector2f(570, 175)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(new Button(this->_event, "Back", sf::Vector2f(550, 410), sf::Vector2f(557, 416), sf::Vector2f(745, 464), BACK_MENU, true));
}


void	MenuWindow::drawSettings()
{
  Text *textIP;
  Text *textTCP;
  Text *textUDP;

  this->clearWindow();
  this->_status = CONTINUE;
  if (InfosUser::getInstance().authenticate.addressIp == "IPAddress")
    textIP = new Text("FontLobby", "IPAddress", this->_event, sf::Vector2f(525, 410), sf::Vector2f(519, 410), sf::Vector2f(766, 446), 15, true, "Address Ip");
  else
    textIP = new Text("FontLobby", "IPAddress", this->_event, sf::Vector2f(525, 410), sf::Vector2f(519, 410), sf::Vector2f(766, 446), 15, true, InfosUser::getInstance().authenticate.addressIp);

  if (InfosUser::getInstance().authenticate.portTCP == "Port TCP")
    textTCP = new Text("FontLobby", "PortTCP", this->_event, sf::Vector2f(525, 500), sf::Vector2f(518, 503), sf::Vector2f(764, 532), 5, true, "Port TCP");
  else
    textTCP = new Text("FontLobby", "PortTCP", this->_event, sf::Vector2f(525, 500), sf::Vector2f(518, 503), sf::Vector2f(764, 532), 5, true, InfosUser::getInstance().authenticate.portTCP);

  if (InfosUser::getInstance().authenticate.portUDP == "Port UDP")
    textUDP = new Text("FontLobby", "PortUDP", this->_event, sf::Vector2f(525, 580), sf::Vector2f(517, 580), sf::Vector2f(766, 614), 5, true, "Port UDP");
  else
    textUDP = new Text("FontLobby", "PortUDP", this->_event, sf::Vector2f(525, 580), sf::Vector2f(517, 580), sf::Vector2f(766, 614), 5, true, InfosUser::getInstance().authenticate.portUDP);

  this->_listImage.push_back(new Image("Title", sf::Vector2f(370, 60)));
  this->_listImage.push_back(new Image("FondSettings", sf::Vector2f(370, 175)));
  this->_listWidget.push_back(new TextArea(this->_event, "IPArea", *textIP, sf::Vector2f(480, 375), sf::Vector2f(519, 410), sf::Vector2f(766, 446)));
  this->_listWidget.push_back(new TextArea(this->_event, "PortTCPArea", *textTCP, sf::Vector2f(480, 465), sf::Vector2f(518, 503), sf::Vector2f(764, 532)));
  this->_listWidget.push_back(new TextArea(this->_event, "PortUDPArea", *textUDP, sf::Vector2f(480, 545), sf::Vector2f(517, 580), sf::Vector2f(766, 614)));
  this->_listWidget.push_back(textIP);
  this->_listWidget.push_back(textTCP);
  this->_listWidget.push_back(textUDP);
  this->_listWidget.push_back(new Button(this->_event, "Save", sf::Vector2f(500, 630), sf::Vector2f(505, 638), sf::Vector2f(615, 672), SET_CHANGE, true));
  this->_listWidget.push_back(new Button(this->_event, "CancelMenu", sf::Vector2f(650, 630), sf::Vector2f(655, 637), sf::Vector2f(767, 669), BACK_SET, true));
}

void	MenuWindow::drawLobbyWarning(const std::string &Msg)
{
  this->clearWindow();
  this->_status = CONTINUE;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  Text *tmp2 = new Text("FontLobby", "WarningMessageLobby", this->_event, sf::Vector2f(260, 464), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, true, Msg);

  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));

  this->_listImage.push_back(new Image("FondWarningLobby", sf::Vector2f(165, 250)));
  this->_listImage.push_back(new Image("TextCreationFailed", sf::Vector2f(190, 415)));
  this->_listImage.push_back(new Image("Warning", sf::Vector2f(340, 280)));
  this->_listWidget.push_back(new Button(this->_event, "Back", sf::Vector2f(320, 490), sf::Vector2f(326, 496), sf::Vector2f(516, 547), CREATE_GAME, true));

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 20));
}

void	MenuWindow::drawGetPWD()
{
  this->clearWindow();
  this->_status = CONTINUE;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  Text *tmp2 = new Text("FontLobby", "setPWD", this->_event, sf::Vector2f(440, 390), sf::Vector2f(393, 386), sf::Vector2f(641, 419), 10, false);

  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));

  this->_listImage.push_back(new Image("FondWarningLobby", sf::Vector2f(165, 250)));
  this->_listImage.push_back(new Image("TextGetPassword", sf::Vector2f(400, 285)));
  this->_listImage.push_back(new Image("Stop", sf::Vector2f(200, 280)));
  this->_listWidget.push_back(new Button(this->_event, "Valider", sf::Vector2f(200, 490), sf::Vector2f(207, 497), sf::Vector2f(395, 545), WAIT, true));
  this->_listWidget.push_back(new Button(this->_event, "Cancel", sf::Vector2f(440, 490), sf::Vector2f(446, 495), sf::Vector2f(635, 546), BACK_LOBY, true));

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(new TextArea(this->_event, "TextPWDArea", *tmp2, sf::Vector2f(355, 350), sf::Vector2f(393, 386), sf::Vector2f(641, 419)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 20));
}


void	MenuWindow::drawLobby()
{
  this->clearWindow();
  this->_status = CONTINUE;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));
  this->_listImage.push_back(new Image("ListServer", sf::Vector2f(50, 195)));
  float x = 62.;
  float y = 243.;

  this->_listWidget.push_back(new LineServer(this->_event, sf::Vector2f(x, y), sf::Vector2f(x + 7, y + 6), sf::Vector2f(x + 686, y + 26), "Poil", "2/4", true));
  y += 20;
  this->_listWidget.push_back(new LineServer(this->_event, sf::Vector2f(x, y), sf::Vector2f(x + 7, y + 6), sf::Vector2f(x + 686, y + 26), "Decul", "1/4", false));

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 20));
}

void	MenuWindow::drawLobbyCreate()
{
  this->clearWindow();
  this->_status = CONTINUE;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  Text *tmp2;
  Text *tmp3;

  if (InfosUser::getInstance().create.partyName == "Party Name")
    tmp2 = new Text("FontLobby", "NameGame", this->_event, sf::Vector2f(200, 300), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 15, true, "Party Name");
  else
    tmp2 = new Text("FontLobby", "NameGame", this->_event, sf::Vector2f(200, 300), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 15, true, InfosUser::getInstance().create.partyName);
  tmp3 = new Text("FontLobby", "PWDGame", this->_event, sf::Vector2f(245, 475), sf::Vector2f(520, 415), sf::Vector2f(760, 445), 10, false, "Party Password");

  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));
  this->_listImage.push_back(new Image("FondCreate", sf::Vector2f(50, 200)));
  this->_listImage.push_back(new Image("TextCreate", sf::Vector2f(80, 220)));

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  this->_listWidget.push_back(new TextArea(this->_event, "TextPassword", *tmp3, sf::Vector2f(200, 435), sf::Vector2f(238, 469), sf::Vector2f(487, 502)));
  this->_listWidget.push_back(new TextArea(this->_event, "TextName", *tmp2, sf::Vector2f(150, 265), sf::Vector2f(188, 301), sf::Vector2f(437, 332)));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckOnePlayer", sf::Vector2f(110, 390), sf::Vector2f(116, 397), sf::Vector2f(134, 414), 1, true));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckTwoPlayer", sf::Vector2f(250, 390), sf::Vector2f(256, 397), sf::Vector2f(275, 414), 2, false));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckThreePlayer", sf::Vector2f(390, 390), sf::Vector2f(396, 397), sf::Vector2f(414, 414), 3, false));
  this->_listWidget.push_back(new CheckBox(this->_event, "CheckFourPlayer", sf::Vector2f(530, 390), sf::Vector2f(536, 397), sf::Vector2f(555, 414), 4, false));
  this->_listWidget.push_back(new Button(this->_event, "Valider", sf::Vector2f(250, 585), sf::Vector2f(254, 592), sf::Vector2f(447, 639), VALIDE, true));
  this->_listWidget.push_back(new Button(this->_event, "Cancel", sf::Vector2f(500, 585), sf::Vector2f(505, 590), sf::Vector2f(697, 641), BACK_LOBY, true));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(tmp3);
  this->_listWidget.push_back(new TextBlock("ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 20));
}

void	MenuWindow::drawLobbyWait(int owner)
{
  int nbPlayer = 3;
  this->clearWindow();
  this->_status = CONTINUE;
  Text *tmp = new Text("FontLobby", "MsgChat", this->_event, sf::Vector2f(830, 640), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true);
  Text *tmp2 = new Text("FontLobby", "NameGameWait", this->_event, sf::Vector2f(170, 297), sf::Vector2f(825, 633), sf::Vector2f(1073, 666), 100, true, this->_serverSelected._name);
  this->_listImage.push_back(new Image("TitleLobby", sf::Vector2f(2, 10)));
  this->_listImage.push_back(new Image("FondLobby", sf::Vector2f(0, 55)));
  this->_listImage.push_back(new Image("MsgChat", sf::Vector2f(820, 200)));
  this->_listImage.push_back(new Image("FondCreate", sf::Vector2f(50, 200)));
  this->_listImage.push_back(new Image("TextWait", sf::Vector2f(80, 220)));
  //demander le nombre de joueur connecter

  float posX = 150;
  int i = 0;
  for (i = 0; i < nbPlayer; i++)
    {
      this->_listImage.push_back(new Image("PlayerConnected", sf::Vector2f(posX, 450)));
      posX += 150;
    }
  while (i < 4)
    {
      this->_listImage.push_back(new Image("PlayerNotConnected", sf::Vector2f(posX, 450)));
      ++i;
      posX += 150;
    }

  this->_listWidget.push_back(new Button(this->_event, "Create", sf::Vector2f(400, 110), sf::Vector2f(405, 112), sf::Vector2f(597, 166), CREATE_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), JOIN_GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Refresh", sf::Vector2f(800, 110), sf::Vector2f(805, 112), sf::Vector2f(997, 166), REFRESH_GAME, true));
  this->_listWidget.push_back(new Button(this->_event, "Disconnect", sf::Vector2f(1000, 110), sf::Vector2f(1005, 112), sf::Vector2f(1197, 166), BACK_MENU, true));
  this->_listWidget.push_back(new Button(this->_event, "Submit", sf::Vector2f(1100, 625), sf::Vector2f(1116, 633), sf::Vector2f(1224, 666), SUBMIT, true));
  this->_listWidget.push_back(new TextArea(this->_event, "TextChatArea", *tmp, sf::Vector2f(787, 600), sf::Vector2f(825, 633), sf::Vector2f(1073, 666)));
  if (owner == 1)
    this->_listWidget.push_back(new Button(this->_event, "Start", sf::Vector2f(250, 585), sf::Vector2f(254, 592), sf::Vector2f(447, 639), GAME, true));
  else
    this->_listWidget.push_back(new Button(this->_event, "Start", sf::Vector2f(250, 585), sf::Vector2f(254, 592), sf::Vector2f(447, 639), GAME, false));
  this->_listWidget.push_back(new Button(this->_event, "Cancel", sf::Vector2f(500, 585), sf::Vector2f(505, 590), sf::Vector2f(697, 641), BACK_LOBY, true));
  this->_listWidget.push_back(tmp);
  this->_listWidget.push_back(tmp2);
  this->_listWidget.push_back(new TextBlock( "ChatBlock", this->_event, sf::Vector2f(830, 210), sf::Vector2f(820, 200), sf::Vector2f(820, 200), 20));
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
  _firstPos.x -= 5;
  _secondPos.x -= 5;
  _secondBackground.setPosition(_secondPos.x, 0);
  _firstBackground.setPosition(_firstPos.x, 0);
}

void	MenuWindow::draw()
{
  widget_list::iterator	it;
  image_list::iterator	itImg;

  this->scroll();
  this->_window.draw(_firstBackground);
  this->_window.draw(_secondBackground);
  for (itImg = this->_listImage.begin(); itImg != this->_listImage.end(); itImg++)
    this->_window.draw((*itImg)->getImage());
  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    (*it)->draw(this->_window);
  this->_window.display();
}

AWidget	*MenuWindow::returnMouseFocus(float x, float y)
{
  widget_list::iterator	it;

  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); it++)
    {
      if ((*it)->isFocus(sf::Vector2f(x, y)) == true)
	return *it;
    }
  return (0);
}

void	MenuWindow::checkServer()
{
  widget_list::iterator it;
  int		tmp = 0;

  for (it = this->_listWidget.begin(); it != this->_listWidget.end(); ++it)
    {
      if ((*it)->getType() == AWidget::LINESERVER)
	{
	  LineServer	*lineServ = dynamic_cast<LineServer *>(*it);

	  if (lineServ->getFocus() == 1)
	    {
	      this->_flag = 1;
	      this->_serverSelected = lineServ->getGameInfo();
	      tmp = 1;
	      this->removeWidget("Join");
	      this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), JOIN_GAME, true));
	      return ;
	    }
	}
    }
  if (this->_flag == 1 && tmp == 0)
    {
      this->_flag = 0;
      this->removeWidget("Join");
      this->_listWidget.push_back(new Button(this->_event, "Join", sf::Vector2f(600, 110), sf::Vector2f(605, 112), sf::Vector2f(797, 166), JOIN_GAME, false));
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
  switch (this->_status)
    {
    case START:
      this->_status = CONTINUE;
      this->drawMenu();
      break;
    case GAME:
      // Lancer la partie
      this->clearWindow();
      this->_status = BACK_LOBY;
      return (2);
      break;
    case WAIT:
      //si le password est bon
      this->_status = CONTINUE;
      this->drawLobbyWait(0);
      // si le password foire
      // call le loby
      break;
    case LOGIN:
      if (dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"))->getTmp() == "" ||
	  dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"))->getTmp() == "Login")
	{
	  this->_status = CONTINUE;
	  this->drawMenuWarning("Login area is empty !");
	  break;
	}
      else if (dynamic_cast<Text*>(Interface::getInstance().getWidget("PasswordText"))->getTmp() == "" ||
	       dynamic_cast<Text*>(Interface::getInstance().getWidget("PasswordText"))->getTmp() == "Password")
	{
	  this->_status = CONTINUE;
	  this->drawMenuWarning(" Password area is empty !");
	  break;
	}
      InfosUser::getInstance().authenticate.login = dynamic_cast<Text*>(Interface::getInstance().getWidget("LoginText"))->getTmp();
      InfosUser::getInstance().authenticate.password = dynamic_cast<Text*>(Interface::getInstance().getWidget("PasswordText"))->getTmp();
      std::cout << "LOGIN : [" << InfosUser::getInstance().authenticate.login << "]" << std::endl;
      std::cout << "PASSWORD : [" << InfosUser::getInstance().authenticate.password << "]" << std::endl;
      // Demander au seveur si les identifiants sont bon !
      this->_status = CONTINUE;
      this->drawLobby();
      break;
    case EXIT:
      this->_window.close();
      break;
    case BACK_MENU:
      // Facultativement des annulations de création/join de partie
      // Envoyer une demande de déconnexion au serveur
      this->_status = CONTINUE;
      this->drawMenu();
      break;
    case CREATE_GAME:
      this->drawLobbyCreate();
      break;
    case REFRESH_GAME:
      // demander une update au serveur
      this->_status = CONTINUE;
      break;
    case JOIN_GAME:
      this->_status = CONTINUE;
      if (this->_serverSelected._lock)
	this->drawGetPWD();
      else
	this->drawLobbyWait(0);
      break;
    case VALIDE:
      if (dynamic_cast<Text*>(Interface::getInstance().getWidget("NameGame"))->getTmp() == "" ||
	  dynamic_cast<Text*>(Interface::getInstance().getWidget("NameGame"))->getTmp() == "Party Name")
	{
	  this->_status = CONTINUE;
	  this->drawLobbyWarning("Name game area is empty !");
	  break;
	}
      InfosUser::getInstance().create.partyName = dynamic_cast<Text*>(Interface::getInstance().getWidget("NameGame"))->getTmp();
      InfosUser::getInstance().create.partyPassword = dynamic_cast<Text*>(Interface::getInstance().getWidget("PWDGame"))->getTmp();
      std::cout << "LOGIN : [" << InfosUser::getInstance().create.partyName << "]" << std::endl;
      std::cout << "PASSWORD : [" << InfosUser::getInstance().create.partyPassword << "]" << std::endl;
      std::cout << "NB_PLAYER : [" << this->checkNbPlayer() << "]" << std::endl;
      // Envoyer une création de partie au serveur
      this->_status = CONTINUE;
      // this->drawLobbyWait(1);
      break;
    case BACK_LOBY:
      this->drawLobby();
      break;
    case SUBMIT:
      this->_status = CONTINUE;
      //Envoyer un message au serveur
      dynamic_cast<TextBlock*>(Interface::getInstance().getWidget("ChatBlock"))->addText(dynamic_cast<Text*>(Interface::getInstance().getWidget("MsgChat"))->getTmp());
      dynamic_cast<Text*>(Interface::getInstance().getWidget("MsgChat"))->clearText();
      break;
    case SELECT_SERVER:
      this->_status = CONTINUE;
      this->checkServer();
      break;
    case SETTINGS:
      this->_status = CONTINUE;
      this->drawSettings();
      break;
    case SET_CHANGE:
      if (dynamic_cast<Text*>(Interface::getInstance().getWidget("IPAddress"))->getTmp() == "" ||
	  dynamic_cast<Text*>(Interface::getInstance().getWidget("IPAddress"))->getTmp() == "Address Ip")
	{
	  this->_status = CONTINUE;
	  this->drawMenu();
	  break;
	}
      else if (dynamic_cast<Text*>(Interface::getInstance().getWidget("PortTCP"))->getTmp() == "" ||
	       dynamic_cast<Text*>(Interface::getInstance().getWidget("PortTCP"))->getTmp() == "Port TCP")
	{
	  this->_status = CONTINUE;
	  this->drawMenu();
	  break;
	}
      else if (dynamic_cast<Text*>(Interface::getInstance().getWidget("PortUDP"))->getTmp() == "" ||
	       dynamic_cast<Text*>(Interface::getInstance().getWidget("PortUDP"))->getTmp() == "Port UDP")
	{
	  this->_status = CONTINUE;
	  this->drawMenu();
	  break;
	}
      else
	{
	  InfosUser::getInstance().authenticate.addressIp = dynamic_cast<Text*>(Interface::getInstance().getWidget("IPAddress"))->getTmp();
	  InfosUser::getInstance().authenticate.portTCP = dynamic_cast<Text*>(Interface::getInstance().getWidget("PortTCP"))->getTmp();
	  InfosUser::getInstance().authenticate.portUDP = dynamic_cast<Text*>(Interface::getInstance().getWidget("PortUDP"))->getTmp();
	  std::cout << "IP : [" << InfosUser::getInstance().authenticate.addressIp << "]" << std::endl;
	  std::cout << "Port TCP : [" << InfosUser::getInstance().authenticate.portTCP << "]" << std::endl;
	  std::cout << "Port UDP : [" << InfosUser::getInstance().authenticate.portUDP << "]" << std::endl;
	  this->_status = CONTINUE;
	  this->drawMenu();
	  break;
	}
    case BACK_SET:
      this->_status = CONTINUE;
      this->drawMenu();
      break;
    case VERIF_PWD:
      this->_status = CONTINUE;
      this->drawLobbyWait(0);
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

int	MenuWindow::catchEvent()
{
  while (this->_window.pollEvent(this->_event))
    {
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
	    return 2;
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
	  std::cout << this->_event.mouseMove.x << " " << this->_event.mouseMove.y << std::endl;
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
      if (this->catchEvent() == 2)
	return (AScreen::SCR_GAME);
      this->draw();
    }
  this->_music.stop();
  return (AScreen::SCR_EXIT); // ASCREEN::Status
}

const MenuWindow::image_list	&MenuWindow::getListImage() const
{
  return (this->_listImage);
}

const MenuWindow::widget_list	&MenuWindow::getListWidget() const
{
  return (this->_listWidget);
}
