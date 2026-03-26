#ifndef PUBLIC_ENUM_H
#define PUBLIC_ENUM_H
enum BGMtype
{
	NORMAL,
	ACTIVE
};
enum soundType
{
	UPGRADE,
	MOUSEAWAY,	  //
	MOUSECLICKED, //
	MOUSEOUT,	  //

	Type,	//
	SLIDER, //

	BUTTONENTER, //
	BUTTONCLICK, //
};
enum operatorType
{

	//弹窗型操作，进行emit数值型操作信号就行
	GAMEWIN_POP,		//胜利弹窗
	GAMEFAIL_POP,		//失败弹窗
	GAMESETUP_POP,		//设置弹窗
	GAMESETUP_SURE_POP, //设置确认弹窗
	GAMEEXIT_POP,		//退出弹窗

	ISPOP, //这是分界线如果小于这个就说明要pop

	//幕后数值型操作，这里要层层更新，上层调用下层就行
	GAMEINIT,		 //回到初始化
	GAMETIMER_START, //所有计时器开启
	GAMETIMER_STOP,	 //所有计时器暂停
	GAMERESUME,		 //如果暂停就继续如果继续就暂停

	GAMEHARDER_ONE, //难度上升一级
	GLOBALSETTING
};
enum gameCondition
{
	PAUSE,
	CONTINUE,
	READYTOPLAY
};

#endif // PUBLIC_ENUM_H
