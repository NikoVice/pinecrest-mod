#if !defined GAMBIT_FUNCTIONS_INC_
	#define GAMBIT_FUNCTIONS_INC_

	#define GAMBIT_FUNCTIONS_VER (100)

	#if !defined DIALOG_STYLE_LIST
		#define DIALOG_STYLE_LIST (2)
	#endif
	#if !defined DIALOG_STYLE_TABLIST
		#define DIALOG_STYLE_TABLIST (4)
	#endif
	#if !defined DIALOG_STYLE_TABLIST_HEADERS
		#define DIALOG_STYLE_TABLIST_HEADERS (5)
	#endif

	enum GF_HookTypes
	{
		GFT_STRING,
		GFT_INTEGER,
		GFT_FLOAT,
		GFT_BOOL
	};

	#if !defined __cplusplus
		public _gambit_functions_ver = GAMBIT_FUNCTIONS_VER;

		#pragma unused _gambit_functions_ver

		#define Dialog: #
		#define DialogCreate:%0(%1) \
			forward dcr_%0(%1); \
			public dcr_%0(%1)
		#define DialogResponse:%0(%1) \
			forward dre_%0(%1); \
			public dre_%0(%1)

		native Dialog_Open(playerid, const name[], style, const caption[], const info[], const button1[], const button2[]);
		native Dialog_Show(playerid, const name[], {GF_HookTypes, Float, _}:...);
		native Dialog_IsOpen(playerid, const name[] = "");

		stock Dialog_Message(playerid, const caption[], const info[], const button1[]) return Dialog_Open(playerid, Dialog:GBF_NULL, DIALOG_STYLE_MSGBOX, caption, info, button1, "");

		DialogResponse:GBF_NULL(playerid, response, listitem, inputtext[]) return 1;

		#if defined OnDialogReceived
			forward OnDialogReceived(playerid, const name[], response, listitem, const inputtext[]);
		#endif
		#if defined OnDialogPerformed
			forward OnDialogPerformed(playerid, const name[], response, listitem, const inputtext[], result);
		#endif
		#if defined OnDialogSpoofed
			forward OnDialogSpoofed(playerid, dialogid, listitem);
		#endif

		native Hook_Execution(const callback[], {GF_HookTypes, Float, _}:...);
		native Hook_Register(const callback[], const function[]);
	#endif
#endif
