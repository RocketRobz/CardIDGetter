/*-----------------------------------------------------------------
 Copyright (C) 2005 - 2013
	Michael "Chishm" Chisholm
	Dave "WinterMute" Murphy
	Claudio "sverx"

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>

#include <string.h>
#include <unistd.h>

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	videoSetModeSub(MODE_0_2D);
	vramSetBankH(VRAM_H_SUB_BG);
	consoleInit(NULL, 1, BgType_Text4bpp, BgSize_T_256x256, 15, 0, false, true);

	sysSetCardOwner (BUS_OWNER_ARM9);

	while (1) {
		if (isDSiMode()) {
			disableSlot1();
			for(int i = 0; i < 25; i++) { swiWaitForVBlank(); }
			enableSlot1();
			for(int i = 0; i < 15; i++) { swiWaitForVBlank(); }
		}
		consoleClear();
		u32 cardId = cardReadID(0);
		printf("Here is the card ID:\n");
		printf("%X", (int)cardId);

		printf("\n\n");
		printf("Press any button to re-get\ncard ID, if another card\nis inserted.");

		while (1) {
			scanKeys();
			swiWaitForVBlank();
			if (keysDown()) {
				break;
			}
		}
	}

	return 0;
}
