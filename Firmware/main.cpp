#include <Arduino.h>
#include <TFT_eSPI.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <AnimatedGIF.h>

// --- Hardware Pins ---
#define BTN_UP 8
#define BTN_DOWN 9
#define TFT_BL 10

// --- Globals ---
TFT_eSPI tft = TFT_eSPI();
AnimatedGIF gif;
AsyncWebServer server(80);
DNSServer dnsServer;

const byte DNS_PORT = 53;
const char* AP_SSID = "GIF Keychain";
const char* AP_PASS = "keychain123"; // Must be at least 8 characters

int backlight_brightness = 150;
File gifFile;
String currentFilename = "";
bool newGifUploaded = false;

// --- Web Server HTML Interface ---
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>GIF Keychain Uploader</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin: 50px auto; max-width: 400px; background: #222; color: #fff; }
    input[type=file] { margin-bottom: 20px; }
    input[type=submit] { background-color: #04AA6D; color: white; padding: 15px 32px; border: none; border-radius: 4px; cursor: pointer; }
    .box { background: #333; padding: 20px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.5); }
  </style>
</head>
<body>
  <div class="box">
    <h2>Keychain Uploader</h2>
    <p>Select a GIF (Max 240x320 recommended)</p>
    <form method="POST" action="/upload" enctype="multipart/form-data">
      <input type="file" name="update" accept=".gif" required><br>
      <input type="submit" value="Upload GIF">
    </form>
  </div>
</body>
</html>)rawliteral";

// --- GIF File Handlers for LittleFS ---
void * GIFOpenFile(const char *fname, int32_t *pSize) {
  gifFile = LittleFS.open(fname, "r");
  if (gifFile) {
    *pSize = gifFile.size();
    return (void *)&gifFile;
  }
  return NULL;
}

void GIFCloseFile(void *pHandle) { gifFile.close(); }
int32_t GIFReadFile(GIFFILE *pFile, uint8_t *pBuf, int32_t iLen) { return gifFile.read(pBuf, iLen); }
int32_t GIFSeekFile(GIFFILE *pFile, int32_t iPosition) { return gifFile.seek(iPosition); }

// --- GIF Draw Callback ---
void GIFDraw(GIFDRAW *pDraw) {
  uint8_t *s;
  uint16_t *d, *usPalette, usTemp[320];
  int x, y, iWidth;

  iWidth = pDraw->iWidth;
  if (iWidth > TFT_WIDTH) iWidth = TFT_WIDTH;
  usPalette = pDraw->pPalette;
  y = pDraw->iY + pDraw->y; // current line
  
  s = pDraw->pPixels;
  if (pDraw->ucHasTransparency) { // Handle transparent GIFs
    uint8_t *pEnd, c, ucTransparent = pDraw->ucTransparent;
    int x, iCount;
    pEnd = s + iWidth;
    x = 0;
    iCount = 0; 
    while(x < iWidth) {
      c = ucTransparent - 1;
      d = usTemp;
      while (c != ucTransparent && s < pEnd) {
        c = *s++;
        if (c == ucTransparent) {
          s--; 
        } else {
          *d++ = usPalette[c];
          iCount++;
        }
      } 
      if (iCount) { 
        tft.pushImage(pDraw->iX+x, y, iCount, 1, usTemp);
        x += iCount;
        iCount = 0;
      }
      c = ucTransparent;
      while (c == ucTransparent && s < pEnd) {
        c = *s++;
        if (c == ucTransparent) iCount++;
        else s--; 
      }
      if (iCount) {
        x += iCount; 
        iCount = 0;
      }
    }
  } else { // No transparency, fast draw
    s = pDraw->pPixels;
    for (x=0; x<iWidth; x++) usTemp[x] = usPalette[*s++];
    tft.pushImage(pDraw->iX, y, iWidth, 1, usTemp);
  }
}

// --- Setup Function ---
void setup() {
  Serial.begin(115200);

  // 1. Hardware Init
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(TFT_BL, OUTPUT);
  analogWrite(TFT_BL, backlight_brightness);

  tft.init();
  tft.setRotation(0); // Portrait for 240x320
  tft.setSwapBytes(true);
  
  // 2. Storage Init
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  
  if (!LittleFS.begin(true)) {
    tft.drawString("FS Error!", 10, 10);
    return;
  }
  
  // 3. Wi-Fi Access Point Init
  tft.drawString("Starting Wi-Fi...", 10, 10);
  WiFi.softAP(AP_SSID, AP_PASS);
  
  // 4. Captive Portal (DNS) Init
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // 5. Web Server Routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request){ request->redirect("/"); });
  server.on("/hotspot-detect.html", HTTP_GET, [](AsyncWebServerRequest *request){ request->redirect("/"); });
  server.onNotFound([](AsyncWebServerRequest *request){ request->redirect("/"); });

  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<h2>Uploaded!</h2><p>Check the screen.</p><meta http-equiv='refresh' content='2; url=/' />");
  }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if (!index) {
      Serial.printf("Upload Start: %s\n", filename.c_str());
      LittleFS.remove("/anim.gif"); 
      request->_tempFile = LittleFS.open("/anim.gif", "w");
    }
    if (request->_tempFile) {
      if (len) request->_tempFile.write(data, len);
      if (final) {
        request->_tempFile.close();
        Serial.printf("Upload Complete: %s, %u B\n", filename.c_str(), index + len);
        newGifUploaded = true;
      }
    }
  });

  server.begin();
  
  // 6. Draw connection details on screen
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Wi-Fi:", 10, 10);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString(AP_SSID, 10, 35);
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Pass:", 10, 65);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString(AP_PASS, 10, 90);
  
  gif.begin(LITTLE_ENDIAN_PIXELS);
}

// --- Main Loop ---
void loop() {
  dnsServer.processNextRequest();

  // Handle Brightness Buttons
  if (digitalRead(BTN_UP) == LOW) {
    backlight_brightness += 15;
    if (backlight_brightness > 255) backlight_brightness = 255;
    analogWrite(TFT_BL, backlight_brightness);
    delay(150); 
  }
  if (digitalRead(BTN_DOWN) == LOW) {
    backlight_brightness -= 15;
    if (backlight_brightness < 0) backlight_brightness = 0;
    analogWrite(TFT_BL, backlight_brightness);
    delay(150);
  }

  // Handle GIF Playback
  if (LittleFS.exists("/anim.gif")) {
    if (newGifUploaded) {
      tft.fillScreen(TFT_BLACK);
      newGifUploaded = false;
    }
    
    if (gif.open("/anim.gif", GIFOpenFile, GIFCloseFile, GIFReadFile, GIFSeekFile, GIFDraw)) {
      while (gif.playFrame(true, NULL)) {
        dnsServer.processNextRequest(); 
        if (newGifUploaded) break; 
      }
      gif.close();
    }
  }
}