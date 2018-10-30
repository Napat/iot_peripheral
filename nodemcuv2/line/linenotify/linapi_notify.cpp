#include "lineapi_notify.h"

void LineNotify(String message)
{
    WiFiClientSecure client;

    if (!client.connect("notify-api.line.me", 443))
    {
        Serial.println("connection failed");
        return;
    }

    String req = "";
    req += "POST /api/notify HTTP/1.1\r\n";
    req += "Host: notify-api.line.me\r\n";
    req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
    req += "Cache-Control: no-cache\r\n";
    req += "User-Agent: ESP8266\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/x-www-form-urlencoded\r\n";
    req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
    req += "\r\n";
    req += "message=" + message;
    // Serial.println(req);
    client.print(req);

    delay(20);

    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
        {
            break;
        }
    }
}

void LineNotifySticker(String message, int StickerPackageID, int StickerID)
{
    WiFiClientSecure client;

    if (!client.connect("notify-api.line.me", 443))
    {
        Serial.println("connection failed");
        return;
    }

    String boundary = "----LineNotifySticker--";
    String body = "--" + boundary + "\r\n";
    body += "Content-Disposition: form-data; name=\"message\"\r\n\r\n" + message + " \r\n";
    if (StickerPackageID > 0 && StickerID > 0)
    {
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"stickerPackageId\"\r\n\r\n" + String(StickerPackageID) + "\r\n";
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"stickerId\"\r\n\r\n" + String(StickerID) + "\r\n";
    }
    body += "--" + boundary + "--";

    String req = "";
    req += "POST /api/notify HTTP/1.1\r\n";
    req += "Host: notify-api.line.me\r\n";
    req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
    req += "Cache-Control: no-cache\r\n";
    req += "User-Agent: ESP8266\r\n";
    req += "Connection: close\r\n";
    req += "Cache-Control: no-cache\r\n";
    req += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
    req += "Content-Length: " + String(body.length()) + "\r\n";
    req += "\r\n";
    req += body;

    // Serial.println(req);
    client.print(req);

    delay(20);

    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
        {
            break;
        }
    }
}

void LineNotifyImageUrl(String message, String imageUrl)
{
    WiFiClientSecure client;

    if (!client.connect("notify-api.line.me", 443))
    {
        Serial.println("connection failed");
        return;
    }

    String boundary = "----LineNotifySticker--";
    String body = "--" + boundary + "\r\n";
    body += "Content-Disposition: form-data; name=\"message\"\r\n\r\n" + message + " \r\n";
    if (imageUrl != "")
    {
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"imageThumbnail\"\r\n\r\n" + imageUrl + "\r\n";
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"imageFullsize\"\r\n\r\n" + imageUrl + "\r\n";
    }
    body += "--" + boundary + "--";

    String req = "";
    req += "POST /api/notify HTTP/1.1\r\n";
    req += "Host: notify-api.line.me\r\n";
    req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
    req += "Cache-Control: no-cache\r\n";
    req += "User-Agent: ESP8266\r\n";
    req += "Connection: close\r\n";
    req += "Cache-Control: no-cache\r\n";
    req += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
    req += "Content-Length: " + String(body.length()) + "\r\n";
    req += "\r\n";
    req += body;

    // Serial.println(req);
    client.print(req);

    delay(20);

    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
        {
            break;
        }
    }
}
