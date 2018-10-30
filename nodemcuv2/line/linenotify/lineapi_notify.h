#ifndef __LINEAPI_NOTIFY_H__
#define __LINEAPI_NOTIFY_H__

#include "wificlientlib.h"
//#include <ESP8266WiFi.h>

// Line config
#define LINE_TOKEN ".....linenotifytoken...."

void LineNotify(String message);

// sticker list: https://devdocs.line.me/files/sticker_list.pdf
void LineNotifySticker(String message, int StickerPackageID, int StickerID);

void LineNotifyImageUrl(String message, String imageUrl);

#endif /* __LINEAPI_NOTIFY_H__ */
